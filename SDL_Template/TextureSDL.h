#ifndef __TEXTURESDL_H
#define __TEXTURESDL_H
#include "Texture.h"


namespace SDLFramework {

	class TextureSDL : public Texture {

	public:
		TextureSDL(std::string filename, bool managed = true);
		TextureSDL(std::string filename, int x, int y, int w, int h, bool managed = false);
		TextureSDL(std::string text, std::string fontPath, int size, SDL_Color color, bool managed = false);

		virtual void Render() override;

	};
}


#endif