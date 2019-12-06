#include "Enemy.h"

std::vector<std::vector<Vector2>> Enemy::sPaths;

void Enemy::CreatePaths() {
	int currentPath = 0;
	BezierPath * path = new BezierPath();
	path->AddCurve({ Vector2(500.0f, 10.0f), Vector2(500.0f, 0.0f), Vector2(500.0f, 310.0f), Vector2(500.0f, 300.0f) }, 1);

	sPaths.push_back(std::vector<Vector2>());
	path->Sample(&sPaths[currentPath]);
	delete path;
}

Enemy::Enemy(int path) {
	mTimer = Timer::Instance();

	mCurrentPath = path;

	mCurrentState = FlyIn;

	mCurrentWaypoint = 0;
	Position(sPaths[mCurrentPath][mCurrentWaypoint]);

	mTexture = new Texture("AnimatedEnemies.png", 0, 0, 52, 40);
	mTexture->Parent(this);
	mTexture->Position(Vec2_Zero);

	mSpeed = 100.0f;
}

Enemy::~Enemy() {
	mTimer = nullptr;

	delete mTexture;
	mTexture = nullptr;
}

void Enemy::HandleFlyInState() {
	if ((sPaths[mCurrentPath][mCurrentWaypoint] - Position()).MagnitudeSqr() < EPSILON) {
		mCurrentWaypoint++;
	}

	if (mCurrentWaypoint < sPaths[mCurrentPath].size()) {
		Vector2 dist = sPaths[mCurrentPath][mCurrentWaypoint] - Position();
		Translate(dist.Normalized() * mSpeed * mTimer->DeltaTime());
	}
	else {
		mCurrentState = Formation;
	}
}

void Enemy::HandleFormationState() {
}

void Enemy::HandleDiveState() {
}

void Enemy::HandleDeadState() {
}

void Enemy::HandleStates() {
	switch (mCurrentState) {
	case FlyIn:
		HandleFlyInState();
		break;
	case Formation:
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

void Enemy::Update() {
	if (Active()) {
		HandleStates();
	}
}

void Enemy::Render() {
	if (Active()) {
		mTexture->Render();

		for (unsigned i = 0; i < sPaths[mCurrentPath].size() - 1; ++i) {
			Graphics::Instance()->DrawLine(sPaths[mCurrentPath][i].x, sPaths[mCurrentPath][i].y, sPaths[mCurrentPath][i + 1].x, sPaths[mCurrentPath][i + 1].y);
		}
	}
}
