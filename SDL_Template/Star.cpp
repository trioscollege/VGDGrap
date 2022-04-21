#include "Star.h"

bool Star::mScroll = false;

void Star::Scroll(bool b) {
	mScroll = b;
}

Star::Star(int layer) 
: GLTexture("Stars.png", 0, 0, 4, 4), mVisible(true) {
	mTimer = Timer::Instance();
	mRand = Random::Instance();

	int starColor = mRand->RandomInt() % 4;

	mSourceRect.x = starColor * 4;

	Position(Vector2((float)(mRand->RandomInt() % Graphics::Instance()->SCREEN_WIDTH), (float)(mRand->RandomInt() % Graphics::Instance()->SCREEN_HEIGHT)));

	mFlickerTimer = 0.0f;
	mFlickerSpeed = mRand->RandomRange(0.15f, 1.0f);

	float inverseLayer = 1.0f / layer;
	Scale(Vec2_One * inverseLayer);

	mScrollSpeed = 8.0f / layer;
}

Star::~Star() {
	mTimer = nullptr;
	mRand = nullptr;
}

void Star::ScrollStar() {
	Translate(Vec2_Up * mScrollSpeed, World);

	Vector2 pos = Position(Local);

	if (pos.y > Graphics::Instance()->SCREEN_HEIGHT) {
		pos.y = 0.0f;
		pos.x = (float)(mRand->RandomInt() % Graphics::Instance()->SCREEN_WIDTH);
		Position(pos);
	}
}

void Star::Update() {
	mFlickerTimer += mTimer->DeltaTime();

	if (mFlickerTimer >= mFlickerSpeed) {
		mVisible = !mVisible;
		mFlickerTimer = 0.0f;
	}

	if (mScroll) {
		ScrollStar();
	}
}

void Star::Render() {
	if (mVisible) {
		GLTexture::Render();
	}
}
