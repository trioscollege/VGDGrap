#ifndef __ENEMY_H
#define __ENEMY_H
#include "AnimatedTexture.h"
#include "BezierPath.h"

class Enemy : public GameEntity {
private:
	static std::vector<std::vector<Vector2>> sPaths;

	enum States { FlyIn, Formation, Dive, Dead };

	Timer * mTimer;

	Texture * mTexture;

	States mCurrentState;

	unsigned mCurrentPath;

	unsigned mCurrentWaypoint;
	const float EPSILON = 5.0f;

	float mSpeed;

public:
	static void CreatePaths();

	Enemy(int path);
	virtual ~Enemy();

	virtual void HandleFlyInState();
	virtual void HandleFormationState();
	virtual void HandleDiveState();
	virtual void HandleDeadState();

	void HandleStates();

	void Update();
	void Render();
};
#endif

