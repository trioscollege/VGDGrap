#ifndef __SCREENMANAGER_H
#define __SCREENMANAGER_H
#include "StartScreen.h"

class ScreenManager {
private:
	enum Screens { Start, Play };

	static ScreenManager * sInstance;

	InputManager * mInput;

	BackgroundStars * mBackgroundStars;
	StartScreen * mStartScreen;

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