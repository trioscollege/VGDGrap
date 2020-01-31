#ifndef __GRAPHICSGL_H
#define __GRAPHICSGL_H
#include "Graphics.h"
#include "ShaderUtil.h"
#include "Texture.h"

#include "glew.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include "TextureGL.h"

namespace SDLFramework {

	class GraphicsGL : public Graphics
	{
	private:

		SDL_GLContext glContext;
		ShaderUtil shaderUtil;

		glm::mat4 orthoMatrix;
		
	protected:


	public:
		static GraphicsGL* Instance();

		GraphicsGL();
		~GraphicsGL();
		TextureGL* textureGL;
		void DrawSprite(TextureGL& texture, SDL_Rect* srcRect = nullptr, SDL_Rect* dstRect = nullptr, float angle = 0.0f, SDL_RendererFlip flip = SDL_FLIP_NONE);


		virtual void ClearBackBuffer() override;
		virtual void Render() override;
		void InitRenderData(Texture* texture, SDL_Rect* srcRect, float angle, float x, float y, float w, float h, GLuint quadVAO);

	protected:
		virtual bool Init() override;
		void InitLoadShaderData();
		glm::mat4 getOrthoMatrix() { return orthoMatrix; };

	};
}
#endif