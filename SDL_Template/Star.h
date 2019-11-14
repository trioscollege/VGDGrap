#ifndef __STAR_H
#define __STAR_H
#include <random>
#include <chrono>
#include "Texture.h"
#include "Timer.h"
#include "RandomMT.h"

using namespace SDLFramework;

class Star : public Texture {

private:
	static bool mScroll;

	Timer * mTimer;
	RandomMT * mRand;

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

