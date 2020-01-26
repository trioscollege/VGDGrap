#include "GraphicsSDL.h"

namespace SDLFramework {

	GraphicsSDL* GraphicsSDL::Instance()
	{
		if (sInstance == nullptr) {
			Graphics::Instance();
		}

		return (GraphicsSDL*)sInstance;
	}

	GraphicsSDL::GraphicsSDL() : Graphics(), mRenderer(nullptr)
	{
		sInitialized = Init();
	}

	GraphicsSDL::~GraphicsSDL()
	{
		SDL_DestroyRenderer(mRenderer);

		mRenderer = nullptr;
	}

	SDL_Texture* GraphicsSDL::LoadTexture(std::string path)
	{
		SDL_Texture* tex = nullptr;
		SDL_Surface* surface = GetSurfaceTexture(path);
		if (surface == nullptr) {
			return nullptr;
		}

		tex = SDL_CreateTextureFromSurface(mRenderer, surface);
		if (tex == nullptr) {
			std::cerr << "Unable to create texture from surface! IMG Error: " << IMG_GetError() << std::endl;
			return nullptr;
		}

		SDL_FreeSurface(surface);
		return tex;
	}

	SDL_Texture* GraphicsSDL::CreateTextTexture(TTF_Font* font, std::string text, SDL_Color color)
	{
		SDL_Surface* surface = GetSurfaceText(font,text,color);
		if (surface == nullptr) {
			return nullptr;
		}

		SDL_Texture* tex = SDL_CreateTextureFromSurface(mRenderer, surface);
		if (tex == nullptr) {
			std::cerr << "CreateTextTexture:: SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
			return nullptr;
		}

		SDL_FreeSurface(surface);
		return tex;
	}

	void GraphicsSDL::DrawTexture(SDL_Texture* tex, SDL_Rect* srcRect /*= nullptr*/, SDL_Rect* dstRect /*= nullptr*/, float angle /*= 0.0f*/, SDL_RendererFlip flip /*= SDL_FLIP_NONE*/)
	{
		SDL_RenderCopyEx(mRenderer, tex, srcRect, dstRect, angle, nullptr, flip);
	}

	void GraphicsSDL::Render()
	{
		SDL_RenderPresent(mRenderer);
	}

	void GraphicsSDL::ClearBackBuffer()
	{
		SDL_RenderClear(mRenderer);
	}

	bool GraphicsSDL::Init()
	{
		if (!Graphics::Init())
			return false;

		mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
		if (mRenderer == nullptr) {
			std::cerr << "Unable to create renderer! SDL Error: " << SDL_GetError() << std::endl;
			return false;
		}

		return true;
	}
}