#include "Butterfly.h"

Vector2 Butterfly::FormationPosition()
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

Butterfly::Butterfly(int path, int index, bool challenge)
	: Enemy(path, index, challenge) {

	if (!challenge) {
		mTargetPosition = FormationPosition();
	}

	mTexture = new Texture("AnimatedEnemies.png", 0, 0, 52, 40);
	mTexture->Parent(this);
	mTexture->Position(Vec2_Zero);
}

Butterfly::~Butterfly() {
}
