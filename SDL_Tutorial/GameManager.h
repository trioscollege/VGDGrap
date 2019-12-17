#ifndef __GAMEMANAGER_H
#define __GAMEMANAGER_H
#include <SDL2/SDL.h>
#include "AnimatedTexture.h"
#include "Timer.h"
#include "InputManager.h"
#include "AudioManager.h"

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
		AudioManager * mAudioManager;

		Timer * mTimer;

		SDL_Event mEvent;

		AnimatedTexture * mTex;
		Texture * mFontTex;

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
