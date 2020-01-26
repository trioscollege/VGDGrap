#ifndef TEXTUREGL_H
#define TEXTUREGL_H

#include <glew.h>
#include "Texture.h"


namespace SDLFramework {
	class TextureGL : public Texture
	{
	public:
		GLuint ID;
		GLuint Width, Height;
		GLuint Internal_Format;
		GLuint Image_Format;
		GLuint Wrap_S;
		GLuint Wrap_T;
		GLuint Filter_Min;
		GLuint Filter_Max;

		// Generates texture from image data
		void Generate(GLuint width, GLuint height, void* data);
		// Binds the texture as the current active GL_TEXTURE_2D texture object
		void Bind() const;
		TextureGL(std::string filename, bool managed = true);
		TextureGL(std::string filename, int x, int y, int w, int h, bool managed = false);
		TextureGL(std::string text, std::string fontPath, int size, SDL_Color color, bool managed = false);

		virtual void Render() override; 

	};
}
#endif