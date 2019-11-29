#ifndef __STARTSCREEN_H
#define __STARTSCREEN_H
#include "AnimatedTexture.hpp"
#include "InputManager.hpp"
#include "BackgroundStars.hpp"
#include "Scoreboard.hpp"

using namespace SDLFramework;

class StartScreen : public GameEntity {

private:
	Timer * mTimer;
	InputManager * mInput;

	// Top Bar Entities
	GameEntity * mTopBar;
	Texture * mPlayerOne;
	Texture * mPlayerTwo;
	Texture * mHiScore;
	Scoreboard * mPlayerOneScore;
	Scoreboard * mPlayerTwoScore;
	Scoreboard * mTopScore;

	// Logo Entities
	Texture * mLogo;
	AnimatedTexture * mAnimatedLogo;

	// Play Mode Entities
	GameEntity * mPlayModes;
	Texture * mOnePlayerMode;
	Texture * mTwoPlayerMode;
	Texture * mCursor;
	Vector2 mCursorStartPos;
	Vector2 mCursorOffset;
	int mSelectedMode;

	// Bottom Bar Entities
	GameEntity * mBottomBar;
	Texture * mNamco;
	Texture * mDates;
	Texture * mRights;

	// Screen Animation Variables
	Vector2 mAnimationStartPos;
	Vector2 mAnimationEndPos;
	float mAnimationTotalTime;
	float mAnimationTimer;
	bool mAnimationDone;

	// stars
	BackgroundStars * mStars;

public:
	StartScreen();
	~StartScreen();

	void ChangeSelectedMode(int change);

	void Update() override;
	void Render() override;
};
#endif
