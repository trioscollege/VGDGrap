#ifndef __PHYSENTITY_H
#define __PHYSENTITY_H
#include <vector>
#include "Collider.h"

class PhysEntity : public GameEntity {
protected:
	std::vector<Collider *> mColliders;

	void AddCollider(Collider * collider, Vector2 localPos = Vec2_Zero);

public:
	PhysEntity();
	~PhysEntity();

	virtual void Render() override;
};
#endif