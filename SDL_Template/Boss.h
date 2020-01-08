#ifndef __BOSS_H
#define __BOSS_H
#include "Enemy.h"

class Boss : public Enemy {
private:
	// Inherited via Enemy
	Vector2 LocalFormationPosition() override;

	void HandleDiveState() override;
	void HandleDeadState() override;

	void RenderDiveState() override;
	void RenderDeadState() override;

public:
	Boss(int path, int index, bool challenge);
	~Boss();
};
#endif