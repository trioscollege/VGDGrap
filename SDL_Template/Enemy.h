#ifndef __ENEMY_H
#define __ENEMY_H
#include "AnimatedTexture.h"
#include "BezierPath.h"

class Enemy : public GameEntity {
public:
	enum States { FlyIn, InFormation, Dive, Dead };

protected:
	static std::vector<std::vector<Vector2>> sPaths;

	Timer * mTimer;

	Texture * mTexture;

	States mCurrentState;

	unsigned mCurrentPath;

	unsigned mCurrentWaypoint;
	const float EPSILON = 5.0f;

	float mSpeed;

	virtual void HandleFlyInState();
	virtual void HandleFormationState();
	virtual void HandleDiveState();
	virtual void HandleDeadState();

	void HandleStates();

public:
	static void CreatePaths();

	Enemy(int path);
	virtual ~Enemy();

	void Update();
	void Render();
};
#endif

