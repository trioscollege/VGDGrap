#ifndef __BUTTERFLY_H
#define __BUTTERFLY_H
#include "Enemy.h"

class Butterfly : public Enemy {
private:
	// Inherited via Enemy
	virtual Vector2 FormationPosition() override;

	virtual void HandleDiveState() override;
	virtual void HandleDeadState() override;

public:
	Butterfly(int path, int index, bool challenge);
	~Butterfly();

};
#endif