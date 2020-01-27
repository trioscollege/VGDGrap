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

		void DrawSprite(TextureGL& texture, SDL_Rect* srcRect = nullptr, SDL_Rect* dstRect = nullptr, float angle = 0.0f, SDL_RendererFlip flip = SDL_FLIP_NONE);


		virtual void ClearBackBuffer() override;
		virtual void Render() override;

	protected:
		virtual bool Init() override;
		void InitRenderData(float x, float y, float w, float h, GLuint quadVAO);
		void InitLoadShaderData();
		glm::mat4 getOrthoMatrix() { return orthoMatrix; };

	};
}
#endif