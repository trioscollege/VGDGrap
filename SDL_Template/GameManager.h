#ifndef __GAMEMANAGER_H
#define __GAMEMANAGER_H

#include <SDL.h>
#include "Texture.h"
#include "Timer.h"
#include "InputManager.h"

class GameManager
{
private:
	static GameManager * sInstance;
	const int FRAME_RATE = 60;

	bool mQuit;
	Graphics * mGraphics;
	AssetManager * mAssetManager;
	InputManager * mInputManager;

	Timer * mTimer;

	SDL_Event mEvent;

	Texture * mTex;

public:
	static GameManager * Instance();
	static void Release();

	void Run();

	GameManager();
	~GameManager();
};
#endif