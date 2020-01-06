#ifndef __BUTTERFLY_H
#define __BUTTERFLY_H
#include "Enemy.h"

class Butterfly : public Enemy {
private:
	// Inherited via Enemy
	Vector2 LocalFormationPosition() override;

	void HandleDiveState() override;
	void HandleDeadState() override;

	void RenderDiveState() override;
	void RenderDeadState() override;

public:
	Butterfly(int path, int index, bool challenge);
	~Butterfly();
};
#endif