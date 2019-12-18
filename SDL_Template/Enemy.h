#ifndef __ENEMY_H
#define __ENEMY_H
#include "AnimatedTexture.h"
#include "BezierPath.h"
#include "Formation.h"

class Enemy : public GameEntity {
public:
	enum States { FlyIn, InFormation, Dive, Dead };

protected:
	static std::vector<std::vector<Vector2>> sPaths;
	static Formation * sFormation;

	Timer * mTimer;

	Texture * mTexture;

	States mCurrentState;

	unsigned mCurrentPath;

	unsigned mCurrentWaypoint;
	const float EPSILON = 5.0f;

	float mSpeed;

	int mIndex;

	Vector2 mTargetPosition;

	bool mChallengeStage;

protected:
	virtual void PathComplete();

	virtual Vector2 FlyInTargetPosition();
	virtual void FlyInComplete();

	virtual Vector2 FormationPosition() = 0;

	virtual void HandleFlyInState();
	virtual void HandleFormationState();
	virtual void HandleDiveState() = 0;
	virtual void HandleDeadState() = 0;

	void HandleStates();

public:
	static void CreatePaths();
	static void SetFormation(Formation * formation);

	Enemy(int path, int index, bool challenge);
	virtual ~Enemy();
	
	States CurrentState();

	void Update();
	void Render();
};
#endif

