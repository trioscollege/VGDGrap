#ifndef __GAMEMANAGER_H
#define __GAMEMANAGER_H
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(_WIN64)
#include <SDL.h>
#elif defined(__APPLE__)
#include <SDL2/SDL.h>
#endif
#include "Timer.h"
#include "AudioManager.h"
#include "ScreenManager.h"

namespace SDLFramework {

	class GameManager {
	private:
		static GameManager * sInstance;
		const int FRAME_RATE = 60;

		bool mQuit;
		Graphics * mGraphics;
		AssetManager * mAssetManager;
		InputManager * mInputManager;
		AudioManager * mAudioManager;

		Timer * mTimer;

		SDL_Event mEvent;

		ScreenManager * mScreenManager;

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