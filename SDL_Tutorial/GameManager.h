#ifndef __GAMEMANAGER_H
#define __GAMEMANAGER_H
#include <SDL2/SDL.h>
#include "Texture.h"
#include "Timer.h"
#include "InputManager.h"

namespace SDLFramework {

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

		void Update();
		void LateUpdate();

		void Render();

		GameManager();
		~GameManager();
	};
}
#endif
