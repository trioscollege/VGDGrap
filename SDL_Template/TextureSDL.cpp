#include "TextureSDL.h"

namespace SDLFramework {

	TextureSDL::TextureSDL(std::string text, std::string fontPath, int size, SDL_Color color, bool managed /*= false*/) : Texture(text, fontPath, size, color, managed)
	{

	}

	TextureSDL::TextureSDL(std::string filename, int x, int y, int w, int h, bool managed /*= false*/) : Texture(filename, x, y, w, h, managed)
	{

	}

	TextureSDL::TextureSDL(std::string filename, bool managed /*= true*/) : Texture(filename, managed) 
	{

	}

	void TextureSDL::Render()
	{
		Texture::Render();

	}

}
