#include "PhysEntity.h"

void PhysEntity::AddCollider(Collider * collider, Vector2 localPos) {
	collider->Parent(this);
	collider->Position(localPos);
	mColliders.push_back(collider);
}

PhysEntity::PhysEntity() {

}

PhysEntity::~PhysEntity() {
	for (auto c : mColliders) {
		delete c;
	}
	mColliders.clear();
}

void PhysEntity::Render() {
	for (auto c : mColliders) {
		c->Render();
	}
}
