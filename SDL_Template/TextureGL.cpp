#include "textureGL.h"
#include "GraphicsGL.h"
namespace SDLFramework {

	void TextureGL::Generate()
	{
		GLint nOfColors = mSurf->format->BytesPerPixel;
		if (nOfColors == 4)     // contains an alpha channel
		{
			if (mSurf->format->Rmask == 0x000000ff)
				mode = GL_RGBA;
			else
				mode = GL_BGRA;
		}
		else if (nOfColors == 3)     // no alpha channel
		{
			if (mSurf->format->Rmask == 0x000000ff)
				mode = GL_RGB;
			else
				mode = GL_BGR;
		}
		else
		{
			mode = GL_RGBA;
		}


		glGenTextures(1, &ID);
		glBindTexture(GL_TEXTURE_2D, ID);

		// set the texture wrapping/filtering options (on the currently bound texture object)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// load and generate the texture
		glTexImage2D(GL_TEXTURE_2D, 0, nOfColors, mSurf->w, mSurf->h, 0, mode, GL_UNSIGNED_BYTE, mSurf->pixels);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	void TextureGL::Bind() const
	{
		glBindTexture(GL_TEXTURE_2D, ID);
	}

	TextureGL::TextureGL(std::string filename, bool managed) : Texture(filename, managed), mode(GL_RGBA)
	{
		SetSurfaceTexture(filename, managed);
	}

	TextureGL::TextureGL(std::string filename, int x, int y, int w, int h, bool managed) : Texture(filename, x, y, w, h, managed), mode(GL_RGBA)
	{
		SetSurfaceTexture(filename, managed);
	}

	TextureGL::TextureGL(std::string text, std::string fontPath, int size, SDL_Color color, bool managed) : Texture(text, fontPath, size, color, managed), mode(GL_RGBA)
	{
		SetSurfaceTextTexture(text, fontPath, size, color, managed);
	}

	void TextureGL::Render()
	{
		Texture::Render();

		if (mSurf != nullptr)
		{
			GraphicsGL::Instance()->DrawSprite(*this, mClipped ? &mSourceRect : nullptr, &mDestinationRect, Rotation(World), Flip);
			return;
		}
		else
			std::cout << "mSurf nullptr Text in TextureGL" << std::endl;
	}

	void TextureGL::SetSurfaceTexture(std::string filename, bool managed)
	{
		mSurf = AssetManager::Instance()->GetSurfaceTexture(filename, managed);
		if (mSurf != nullptr)
			Generate();
		else
			std::cout << "mSurf nullptr Text in TextureGL" << std::endl;
	}


	void TextureGL::SetSurfaceTextTexture(std::string text, std::string fontPath, int size, SDL_Color color, bool managed)
	{
		mSurf = AssetManager::Instance()->GetSurfaceText(text, fontPath, size, color, managed);
		if (mSurf != nullptr)
			Generate();
		else
			std::cout << "mSurf nullptr Text in TextureGL" << std::endl;
	}

}