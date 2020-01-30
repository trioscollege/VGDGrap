#ifndef __STAR_H
#define __STAR_H
#include "TextureGL.h"
#include "Timer.h"
#include "Random.h"

using namespace SDLFramework;

class Star : public TextureGL {

private:
	static bool mScroll;

	Timer * mTimer;
	Random * mRand;

	bool mVisible;
	float mFlickerTimer;
	float mFlickerSpeed;

	float mScrollSpeed;

public:
	static void Scroll(bool b);

	Star(int layer);
	~Star();

	void Update();
	void Render();

private:
	void ScrollStar();
};
#endif

