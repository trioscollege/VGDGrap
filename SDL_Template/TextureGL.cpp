#include "textureGL.h"
#include "GraphicsGL.h"

namespace SDLFramework {

	void TextureGL::Generate(GLuint width, GLuint height, void* data)
	{
		
		mode = GL_RGBA;
		if (mSurf->format->BytesPerPixel < 4) {
			mode = GL_RGBA;
		}
		Width = width;
		Height = height;
		glEnable(GL_TEXTURE_2D); 

		glGenTextures(1, &ID);
		// Create Texture
		glBindTexture(GL_TEXTURE_2D, ID);
		glTexImage2D(GL_TEXTURE_2D, 0, mode, width, height, 0, mode, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		// Set Texture wrap and filter modes
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// Unbind texture
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	TextureGL::TextureGL(std::string filename, bool managed) : Texture(filename, managed)
	{
	}

	TextureGL::TextureGL(std::string filename, int x, int y, int w, int h, bool managed) : Texture(filename, x, y, w, h, managed)
	{
	}

	TextureGL::TextureGL(std::string text, std::string fontPath, int size, SDL_Color color, bool managed) : Texture(text, fontPath, size, color, managed)
	{
	}


	void TextureGL::Render()
	{
		Texture::Render();
		if (mSurf != nullptr)
		{
			GraphicsGL::Instance()->DrawSprite(*this, mClipped ? &mSourceRect : nullptr, &mDestinationRect, Rotation(World));

		}
		else
			std::cout << "mSurf nullptr Text in TextureGL" << std::endl;

	}
}