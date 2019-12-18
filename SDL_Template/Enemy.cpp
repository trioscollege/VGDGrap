#include "Enemy.h"

std::vector<std::vector<Vector2>> Enemy::sPaths;
Formation * Enemy::sFormation = nullptr;

void Enemy::CreatePaths() {
	int screenMidPoint = (int)(Graphics::Instance()->SCREEN_WIDTH * 0.4f);

	int currentPath = 0;
	BezierPath * path = new BezierPath();
	/*path->AddCurve({
		Vector2(500.0f, 10.0f),
		Vector2(500.0f, 0.0f),
		Vector2(500.0f, 310.0f),
		Vector2(500.0f, 300.0f) }, 1);*/
	path->AddCurve({
		Vector2(screenMidPoint + 50.0f, -10.0f),
		Vector2(screenMidPoint + 50.0f, -20.0f),
		Vector2(screenMidPoint + 50.0f, 30.0f),
		Vector2(screenMidPoint + 50.0f, 20.0f) }, 1);
	path->AddCurve({
		Vector2(screenMidPoint + 50.0f, 20.0f),
		Vector2(screenMidPoint + 50.0f, 100.0f),
		Vector2(75.0f, 325.0f),
		Vector2(75.0f, 425.0f) }, 25);
	path->AddCurve({
		Vector2(75.0f, 425.0f),
		Vector2(75.0f, 650.0f),
		Vector2(350.0f, 650.0f),
		Vector2(350.0f, 425.0f) }, 25);

	sPaths.push_back(std::vector<Vector2>());
	path->Sample(&sPaths[currentPath]);
	delete path;
}

void Enemy::SetFormation(Formation * formation) {
	sFormation = formation;
}

Enemy::Enemy(int path, int index, bool challenge)
	: mCurrentPath(path), mIndex(index), mChallengeStage(challenge) {
	mTimer = Timer::Instance();

	mCurrentState = FlyIn;

	mCurrentWaypoint = 1;
	Position(sPaths[mCurrentPath][0]);

	mTexture = nullptr;

	mSpeed = 400.0f;
}

Enemy::~Enemy() {
	mTimer = nullptr;

	delete mTexture;
	mTexture = nullptr;
}

void Enemy::PathComplete() {
	if (mChallengeStage) {
		mCurrentState = Dead;
	}
}

Vector2 Enemy::FlyInTargetPosition() {
	return sFormation->Position() + mTargetPosition;
}

void Enemy::FlyInComplete() {
	Position(FlyInTargetPosition());
	Rotation(0);
	Parent(sFormation);
	mCurrentState = InFormation;
}

void Enemy::HandleFlyInState() {
	if (mCurrentWaypoint < sPaths[mCurrentPath].size()) {
		Vector2 dist = sPaths[mCurrentPath][mCurrentWaypoint] - Position();

		Translate(dist.Normalized() * mSpeed * mTimer->DeltaTime(), World);
		Rotation(atan2(dist.y, dist.x) * RAD_TO_DEG + 90.0f);

		if ((sPaths[mCurrentPath][mCurrentWaypoint] - Position()).MagnitudeSqr() < EPSILON * mSpeed / 100.0f) {
			mCurrentWaypoint++;
		}

		if (mCurrentWaypoint >= sPaths[mCurrentPath].size()) {
			PathComplete();
		}
	}
	else {
		Vector2 dist = FlyInTargetPosition() - Position();

		Translate(dist.Normalized() * mSpeed * mTimer->DeltaTime(), World);
		Rotation(atan2(dist.y, dist.x) * RAD_TO_DEG + 90.0f);

		if (dist.MagnitudeSqr() < EPSILON * mSpeed / 100.0f) {
			FlyInComplete();
		}
	}
}

void Enemy::HandleFormationState() {
	Position(FormationPosition());
}

void Enemy::HandleStates() {
	switch (mCurrentState) {
	case FlyIn:
		HandleFlyInState();
		break;
	case InFormation:
		HandleFormationState();
		break;
	case Dive:
		HandleDiveState();
		break;
	case Dead:
		HandleDeadState();
		break;
	}
}

Enemy::States Enemy::CurrentState()
{
	return mCurrentState;
}

void Enemy::Update() {
	if (Active()) {
		HandleStates();
	}
}

void Enemy::Render() {
	if (Active()) {
		mTexture->Render();
	}
}
