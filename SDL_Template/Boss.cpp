#include "Boss.h"

Vector2 Boss::LocalFormationPosition() {
	Vector2 retVal;

	retVal.x = (sFormation->GridSize().x + sFormation->GridSize().x * 2 * (mIndex / 2)) * (float)pow(-1, mIndex % 2 + 1);
	retVal.y = -sFormation->GridSize().y;

	return retVal;
}

void Boss::HandleDiveState() {
}

void Boss::HandleDeadState() {
}

void Boss::RenderDiveState() {

}

void Boss::RenderDeadState() {

}

Boss::Boss(int path, int index, bool challenge)
	: Enemy(path, index, challenge) {
	mTextures[0] = new Texture("Bosses.png", 0, 0, 64, 64);
	mTextures[1] = new Texture("Bosses.png", 64, 0, 64, 64);
	
	for (int i = 0; i < 2; i++) {
		mTextures[i]->Parent(this);
		mTextures[i]->Position(Vec2_Zero);
	}

	mType = Enemy::Boss;
}

Boss::~Boss() {
}
