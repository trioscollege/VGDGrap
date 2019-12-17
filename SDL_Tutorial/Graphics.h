#ifndef __GRAPHICS_H
#define __GRAPHICS_H
#include <SDL2/SDL.h>
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
