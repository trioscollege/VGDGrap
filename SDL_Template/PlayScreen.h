#ifndef __PLAYSCREEN_H
#define __PLAYSCREEN_H
#include "InputManager.h"
#include "BackgroundStars.h"
#include "PlaySideBar.h"

class PlayScreen : public GameEntity {
private:
	Timer * mTimer;
	InputManager * mInput;

	BackgroundStars * mStars;

	PlaySideBar * mSideBar;

public:
	PlayScreen();
	~PlayScreen();

	void Update();
	void Render();
};


#endif