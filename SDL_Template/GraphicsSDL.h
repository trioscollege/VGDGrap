#ifndef __GRAPHICSSDL_H
#define __GRAPHICSSDL_H
#include "Graphics.h"
#include "SDL_image.h"
namespace SDLFramework 
{

	class GraphicsSDL : public Graphics
	{
	protected:



	public:
		static GraphicsSDL* Instance();

		GraphicsSDL();
		~GraphicsSDL();
		virtual void DrawTexture(SDL_Texture* tex, SDL_Rect* srcRect = nullptr, SDL_Rect* dstRect = nullptr, float angle = 0.0f, SDL_RendererFlip flip = SDL_FLIP_NONE) override;

		virtual void  Render() override;
		virtual void ClearBackBuffer() override;

	protected:

		virtual bool Init() override;

	};
}

#endif