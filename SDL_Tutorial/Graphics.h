#ifndef __GRAPHICS_H
#define __GRAPHICS_H
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(_WIN64)
#include <SDL.h>
#elif defined(__APPLE__)
#include <SDL2/SDL.h>
#endif
#include <iostream>
#include <string>

namespace SDLFramework {

	class Graphics
	{
	public:
		static const short SCREEN_WIDTH = 800;
		static const short SCREEN_HEIGHT = 600;

	private:
		static Graphics * sInstance;
		static bool sInitialized;

		SDL_Window * mWindow;
		SDL_Renderer * mRenderer;

	public:
		static Graphics * Instance();
		static void Release();
		static bool Initialized();

		void ClearBackBuffer();
		void Render();

	private:
		Graphics();
		~Graphics();

		bool Init();
	};
}
#endif
