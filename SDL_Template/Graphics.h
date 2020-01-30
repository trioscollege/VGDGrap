#ifndef __GRAPHICS_H
#define __GRAPHICS_H
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>

namespace SDLFramework {

	class Graphics
	{
	public:
		static const short SCREEN_WIDTH = 1024;
		static const short SCREEN_HEIGHT = 896;
		const char* WINDOW_TITLE = "Galaga";

	protected:
		static Graphics* sInstance;
		static bool sInitialized;

		SDL_Window* mWindow;
		SDL_Renderer* mRenderer;

	public:
		static Graphics* Instance();
		static void Release();
		static bool Initialized();

		SDL_Texture* LoadTexture(std::string path);
		SDL_Texture* CreateTextTexture(TTF_Font* font, std::string text, SDL_Color color);
		SDL_Surface* GetSurfaceTexture(std::string path);
		SDL_Surface* GetSurfaceText(TTF_Font* font, std::string text, SDL_Color color);
		virtual void DrawTexture(SDL_Texture* tex, SDL_Rect* srcRect = nullptr, SDL_Rect* dstRect = nullptr, float angle = 0.0f, SDL_RendererFlip flip = SDL_FLIP_NONE) { };

		virtual void ClearBackBuffer() = 0;
		virtual void Render() = 0;

	protected: //Changed private to protected
		Graphics();
		~Graphics();

		virtual bool Init();
	};
}
#endif