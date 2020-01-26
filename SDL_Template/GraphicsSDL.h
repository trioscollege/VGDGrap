#ifndef __GRAPHICSSDL_H
#define __GRAPHICSSDL_H
#include "Graphics.h"
#include "SDL_image.h"
namespace SDLFramework 
{

	class GraphicsSDL : public Graphics
	{
	protected:

		SDL_Renderer* mRenderer;


	public:
		static GraphicsSDL* Instance();

		GraphicsSDL();
		~GraphicsSDL();

		virtual SDL_Texture* LoadTexture(std::string path) override;
		virtual SDL_Texture* CreateTextTexture(TTF_Font* font, std::string text, SDL_Color color);

		virtual void DrawTexture(SDL_Texture* tex, SDL_Rect* srcRect = nullptr, SDL_Rect* dstRect = nullptr, float angle = 0.0f, SDL_RendererFlip flip = SDL_FLIP_NONE) override;

		virtual void  Render() override;
		virtual void ClearBackBuffer() override;

	protected:

		virtual bool Init() override;

	};
}

#endif