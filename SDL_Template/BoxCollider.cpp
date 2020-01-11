#include "BoxCollider.h"

void BoxCollider::AddVert(int index, Vector2 pos) {
	mVerts[index] = new GameEntity(pos);
	mVerts[index]->Parent(this);
}

BoxCollider::BoxCollider(Vector2 size)
	: Collider(ColliderType::Box) {
	AddVert(0, Vector2(-0.5f*size.x,-0.5f*size.y));
	AddVert(1, Vector2( 0.5f*size.x,-0.5f*size.y));
	AddVert(2, Vector2(-0.5f*size.x, 0.5f*size.y));
	AddVert(3, Vector2( 0.5f*size.x, 0.5f*size.y));

	if (DEBUG_COLLIDERS) {
		SetDebugTexture(new Texture("BoxCollider.png"));
		mDebugTexture->Scale(size);
	}
}

BoxCollider::~BoxCollider() {
	for (auto v : mVerts) {
		delete v;
	}
}
