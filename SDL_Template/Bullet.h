#ifndef __BULLET_H
#define __BULLET_H
#include "Texture.h"
#include "Timer.h"

using namespace SDLFramework;

class Bullet : public GameEntity {
private:
	const int OFFSCREEN_BUFFER = 10;

	Timer * mTimer;

	Texture * mTexture;

	float mSpeed;

public:
	Bullet();
	~Bullet();

	void Fire(Vector2 pos);
	void Reload();

	void Update();
	void Render();
};

#endif