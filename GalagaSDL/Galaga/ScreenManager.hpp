#ifndef __SCREENMANAGER_H
#define __SCREENMANAGER_H
#include "StartScreen.hpp"
#include "PlayScreen.hpp"

class ScreenManager {
private:
	enum Screens { Start, Play };

	static ScreenManager * sInstance;

	InputManager * mInput;

	BackgroundStars * mBackgroundStars;
	StartScreen * mStartScreen;
	PlayScreen * mPlayScreen;

	Screens mCurrentScreen;

public:
	static ScreenManager * Instance();
	static void Release();

	void Update();
	void Render();

private:
	ScreenManager();
	~ScreenManager();
};
#endif
