#include "Collider.h"

void Collider::SetDebugTexture(Texture * tex) {
	delete mDebugTexture;
	mDebugTexture = tex;
	mDebugTexture->Parent(this);
}

Collider::Collider(ColliderType type)
	: mType(type) {
	mDebugTexture = nullptr;
}

Collider::~Collider() {
	delete mDebugTexture;
	mDebugTexture = nullptr;
}


void Collider::Render() {
//#ifdef _DEBUG
//	mDebugTexture->Render();
//#endif
	if (DEBUG_COLLIDERS) {
		mDebugTexture->Render();
	}
}
