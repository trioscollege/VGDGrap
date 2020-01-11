#ifndef __BOSS_H
#define __BOSS_H
#include "Enemy.h"

class Boss : public Enemy {
private:
	static std::vector<std::vector<Vector2>> sDivePaths;

	bool mCapturing;

	// Inherited via Enemy
	Vector2 LocalFormationPosition() override;

	void HandleDiveState() override;
	void HandleDeadState() override;

	void RenderDiveState() override;
	void RenderDeadState() override;

public:
	static void CreateDivePaths();

	void Dive(int type = 0) override;

	Boss(int path, int index, bool challenge);
	~Boss();
};
#endif