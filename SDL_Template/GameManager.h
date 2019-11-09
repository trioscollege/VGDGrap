#ifndef __GAMEMANAGER_H
#define __GAMEMANAGER_H

#include <SDL.h>
#include "Graphics.h"
#include "Timer.h"

class GameManager
{
private:
	static GameManager * sInstance;
	const int FRAME_RATE = 60;

	bool mQuit;
	Graphics * mGraphics;

	Timer * mTimer;

	SDL_Event mEvent;

public:
	static GameManager * Instance();
	static void Release();

	void Run();

	GameManager();
	~GameManager();
};
#endif