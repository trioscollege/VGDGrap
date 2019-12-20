#include "Butterfly.h"

Vector2 Butterfly::LocalFormationPosition()
{
	Vector2 retVal;

	retVal.x = (sFormation->GridSize().x + sFormation->GridSize().x * 2 * (mIndex / 4)) * (float)pow(-1, mIndex % 2 + 1);
	retVal.y = sFormation->GridSize().y * ((mIndex % 4) / 2);

	return retVal;
}

void Butterfly::HandleDiveState()
{
}

void Butterfly::HandleDeadState()
{
}

void Butterfly::RenderDiveState() {

}

void Butterfly::RenderDeadState() {
}

Butterfly::Butterfly(int path, int index, bool challenge)
	: Enemy(path, index, challenge) {

	mTextures[0] = new Texture("AnimatedEnemies.png", 0, 0, 52, 40);
	mTextures[1] = new Texture("AnimatedEnemies.png", 52, 0, 52, 40);
	
	for (int i = 0; i < 2; i++) {
		mTextures[i]->Parent(this);
		mTextures[i]->Position(Vec2_Zero);
	}

	mType = Enemy::Butterfly;
}

Butterfly::~Butterfly() {
}
