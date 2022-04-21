#include "Butterfly.h"
#include "BoxCollider.h"
#include "AudioManager.h"

std::vector<std::vector<Vector2>> Butterfly::sDivePaths;

void Butterfly::CreateDivePaths() {
	int currentPath = 0;
	BezierPath * path = new BezierPath();

	path->AddCurve({
		Vector2(0.0f, 0.0f),
		Vector2(0.0f, -45.0f),
		Vector2(-60.0f, -45.0f),
		Vector2(-60.f, 0.0f) }, 15);
	path->AddCurve({
		Vector2(-60.0f, 0.0f),
		Vector2(-60.0f, 80.0f),
		Vector2(200.0f, 125.0f),
		Vector2(200.0f, 200.0f) }, 15);
	path->AddCurve({
		Vector2(200.0f, 200.0f),
		Vector2(200.0f, 275.0f),
		Vector2(175.0f, 250.0f),
		Vector2(175.0f, 325.0f) }, 15);
	path->AddCurve({
		Vector2(175.0f, 325.0f),
		Vector2(175.0f, 425.0f),
		Vector2(375.0f, 425.0f),
		Vector2(375.0f, 525.0f) }, 15);
	path->AddCurve({
		Vector2(375.0f, 525.0f),
		Vector2(375.0f, 575.0f),
		Vector2(300.0f, 625.0f),
		Vector2(300.0f, 775.0f) }, 15);

	sDivePaths.push_back(std::vector<Vector2>());
	path->Sample(&sDivePaths[currentPath]);
	delete path;

	currentPath = 1;
	path = new BezierPath();

	path->AddCurve({
		Vector2(0.0f, 0.0f),
		Vector2(0.0f, -45.0f),
		Vector2(60.0f, -45.0f),
		Vector2(60.f, 0.0f) }, 15);
	path->AddCurve({
		Vector2(60.0f, 0.0f),
		Vector2(60.0f, 80.0f),
		Vector2(-200.0f, 125.0f),
		Vector2(-200.0f, 200.0f) }, 15);
	path->AddCurve({
		Vector2(-200.0f, 200.0f),
		Vector2(-200.0f, 275.0f),
		Vector2(-175.0f, 250.0f),
		Vector2(-175.0f, 325.0f) }, 15);
	path->AddCurve({
		Vector2(-175.0f, 325.0f),
		Vector2(-175.0f, 425.0f),
		Vector2(-375.0f, 425.0f),
		Vector2(-375.0f, 525.0f) }, 15);
	path->AddCurve({
		Vector2(-375.0f, 525.0f),
		Vector2(-375.0f, 575.0f),
		Vector2(-300.0f, 625.0f),
		Vector2(-300.0f, 775.0f) }, 15);

	sDivePaths.push_back(std::vector<Vector2>());
	path->Sample(&sDivePaths[currentPath]);
	delete path;

	currentPath = 2;
	path = new BezierPath();

	path->AddCurve({
		Vector2(0.0f, 0.0f),
		Vector2(0.0f, -60.0f),
		Vector2(-90.0f, -60.0f),
		Vector2(-90.0f, 0.0f) }, 15);
	path->AddCurve({
		Vector2(-90.0f, 0.0f),
		Vector2(-90.0f, 60.0f),
		Vector2(-100.0f, 272.0f),
		Vector2(-15.0f, 275.0f) }, 15);
	path->AddCurve({
		Vector2(-15.0f, 275.0f),
		Vector2(85.0f, 275.0f),
		Vector2(85.0f, 125.0f),
		Vector2(-15.0f, 125.0f) }, 15);
	path->AddCurve({
		Vector2(-15.0f, 125.0f),
		Vector2(-175.0f, 125.0f),
		Vector2(0.0f, 450.0f),
		Vector2(125.0f, 450.0f) }, 25);
	path->AddCurve({
		Vector2(120.0f, 450.0f),
		Vector2(160.0f, 450.0f),
		Vector2(200.0f, 500.0f),
		Vector2(200.0f, 550.0f) }, 15);
	path->AddCurve({
		Vector2(200.0f, 550.0f),
		Vector2(200.0f, 540.0f),
		Vector2(200.0f, 810.0f),
		Vector2(200.0f, 800.0f) }, 15);

	sDivePaths.push_back(std::vector<Vector2>());
	path->Sample(&sDivePaths[currentPath]);
	delete path;

	currentPath = 3;
	path = new BezierPath();

	path->AddCurve({
		Vector2(0.0f, 0.0f),
		Vector2(0.0f, -60.0f),
		Vector2(90.0f, -60.0f),
		Vector2(90.0f, 0.0f) }, 15);
	path->AddCurve({
		Vector2(90.0f, 0.0f),
		Vector2(90.0f, 60.0f),
		Vector2(100.0f, 272.0f),
		Vector2(15.0f, 275.0f) }, 15);
	path->AddCurve({
		Vector2(15.0f, 275.0f),
		Vector2(-85.0f, 275.0f),
		Vector2(-85.0f, 125.0f),
		Vector2(15.0f, 125.0f) }, 15);
	path->AddCurve({
		Vector2(15.0f, 125.0f),
		Vector2(175.0f, 125.0f),
		Vector2(0.0f, 450.0f),
		Vector2(-125.0f, 450.0f) }, 25);
	path->AddCurve({
		Vector2(-120.0f, 450.0f),
		Vector2(-160.0f, 450.0f),
		Vector2(-200.0f, 500.0f),
		Vector2(-200.0f, 550.0f) }, 15);
	path->AddCurve({
		Vector2(-200.0f, 550.0f),
		Vector2(-200.0f, 540.0f),
		Vector2(-200.0f, 810.0f),
		Vector2(-200.0f, 800.0f) }, 15);

	sDivePaths.push_back(std::vector<Vector2>());
	path->Sample(&sDivePaths[currentPath]);
	delete path;
}

Vector2 Butterfly::LocalFormationPosition()
{
	Vector2 retVal;
	int dir = mIndex % 2 == 0 ? -1 : 1;

	retVal.x = (sFormation->GridSize().x + sFormation->GridSize().x * 2 * (mIndex / 4)) * (float)dir;
	retVal.y = sFormation->GridSize().y * ((mIndex % 4) / 2);

	return retVal;
}

void Butterfly::HandleDiveState() {
	int currentPath = mIndex % 2;

	if (mEscort) {
		currentPath += 2;
	}

	if (mCurrentWaypoint < sDivePaths[currentPath].size()) {
		// follow dive path
		Vector2 waypointPos = mDiveStartPosition + sDivePaths[currentPath][mCurrentWaypoint];
		Vector2 dist = waypointPos - Position();

		Translate(dist.Normalized() * mSpeed * mTimer->DeltaTime(), World);
		Rotation(atan2(dist.y, dist.x) * RAD_TO_DEG + 90.0f);

		if ((waypointPos - Position()).MagnitudeSqr() < EPSILON * mSpeed / 25.0f) {
			mCurrentWaypoint += 1;
		}

		if (mCurrentWaypoint == sDivePaths[currentPath].size()) {
			Position(Vector2(WorldFormationPosition().x, 20.0f));
		}
	}
	else {
		// return to formation
		Vector2 dist = WorldFormationPosition() - Position();

		Translate(dist.Normalized() * mSpeed * mTimer->DeltaTime(), World);
		Rotation(atan2(dist.y, dist.x) * RAD_TO_DEG + 90.0f);

		if (dist.MagnitudeSqr() < EPSILON * mSpeed / 25.0f) {
			JoinFormation();
		}
	}
}

void Butterfly::RenderDiveState() {
	mTextures[0]->Render();
}

void Butterfly::Dive(int type) {
	mEscort = type != 0;

	Enemy::Dive();
}

void Butterfly::Hit(PhysEntity * other) {
	AudioManager::Instance()->PlaySFX("SFX/ButterflyDestroyed.wav", 0, 3);
	sPlayer->AddScore(mCurrentState == Enemy::InFormation ? 80 : 160);
	Enemy::Hit(other);
}

Butterfly::Butterfly(int path, int index, bool challenge)
	: Enemy(path, index, challenge) {

	mTextures[0] = new GLTexture("AnimatedEnemies.png", 0, 0, 52, 40);
	mTextures[1] = new GLTexture("AnimatedEnemies.png", 60, 0, 36, 40);
	
	for (int i = 0; i < 2; i++) {
		mTextures[i]->Parent(this);
		mTextures[i]->Position(Vec2_Zero);
	}

	mType = Enemy::Butterfly;

	AddCollider(new BoxCollider(mTextures[1]->ScaledDimensions()));
}

Butterfly::~Butterfly() {
}
