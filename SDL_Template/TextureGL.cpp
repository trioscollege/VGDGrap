#include "textureGL.h"
#include "GraphicsGL.h"

namespace SDLFramework {

	void TextureGL::Generate(GLuint width, GLuint height, void* data)
	{
		Width = width;
		Height = height;
		// Create Texture
		glBindTexture(GL_TEXTURE_2D, ID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		// Set Texture wrap and filter modes
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, Wrap_S);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, Wrap_T);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, Filter_Min);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, Filter_Max);
		// Unbind texture
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void TextureGL::Bind() const
	{
		glBindTexture(GL_TEXTURE_2D, ID);
	}

	TextureGL::TextureGL(std::string filename, bool managed) : Texture(filename, managed)
	{
		glGenTextures(1, &ID);
		if (mSurf != nullptr)
			Generate(mWidth, mHeight, mSurf->pixels);
	}

	TextureGL::TextureGL(std::string filename, int x, int y, int w, int h, bool managed) : Texture(filename, x, y, w, h, managed)
	{
		glGenTextures(1, &ID);
		if (mSurf != nullptr)
			Generate(mWidth, mHeight, mSurf->pixels);
	}

	TextureGL::TextureGL(std::string text, std::string fontPath, int size, SDL_Color color, bool managed) : Texture(text, fontPath, size, color, managed)
	{
		glGenTextures(1, &ID);
		if(mSurf != nullptr)
			Generate(mWidth, mHeight, mSurf->pixels);
	}


	void TextureGL::Render()
	{
		Texture::Render();
		if (mSurf != nullptr)
		{
			GraphicsGL::Instance()->DrawSprite(*this, mClipped ? &mSourceRect : nullptr, &mDestinationRect, Rotation(World));

		}
	}
}