#include "GraphicsGL.h"
#include "AssetManager.h"

namespace SDLFramework {

	GraphicsGL* GraphicsGL::Instance()
	{
		if (sInstance == nullptr) {
			Graphics::Instance();
		}

		return (GraphicsGL*)sInstance;
	}

	GraphicsGL::GraphicsGL() : Graphics(), orthoMatrix(1.0f)
	{
		sInitialized = Init();
		time = 0;
	}

	GraphicsGL::~GraphicsGL()
	{


		SDL_GL_DeleteContext(mWindow);
	}

	void GraphicsGL::DrawSprite(TextureGL& texture, SDL_Rect* srcRect /*= nullptr*/, SDL_Rect* dstRect /*= nullptr*/, float angle /*= 0.0f*/, SDL_RendererFlip flip /*= SDL_FLIP_NONE*/)
	{
		InitRenderData(dstRect->x, dstRect->y, dstRect->w, dstRect->h, texture.ID);

		shaderUtil.Use();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture.ID);
		GLint location = shaderUtil.GetUniformLocation("tSampler");
		glUniform1i(location, GL_TEXTURE0);

		//location = shaderUtil.GetUniformLocation("time");
		//glUniform1f(location, time++);

		location = shaderUtil.GetUniformLocation("proj");
		glUniformMatrix4fv(location, 1, GL_FALSE, &(orthoMatrix[0][0]));

		//Start to draw to screen
		glBindBuffer(GL_ARRAY_BUFFER, texture.ID);

		glEnableVertexAttribArray(0);

		//this is position
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
		//this is UV
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

		glDrawArrays(GL_TRIANGLES, 0, 6);

		glDisableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		//glDrawArrays(GL_TRIANGLES, 0, 6);
		//shaderUtil.Use();

		//glm::vec2 position = glm::vec2(-1, -1);
		//glm::vec2 size = glm::vec2(1, 1);
		//GLfloat rotate = angle;
		//glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

		//glm::mat4 model;
		//model = glm::translate(model, glm::vec3(position, 0.0f));

		//model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
		//model = glm::rotate(model, rotate, glm::vec3(0.0f, 0.0f, 1.0f));
		//model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

		//model = glm::scale(model, glm::vec3(size, 1.0f));

		//shaderUtil.SetMatrix4("proj", model);
		////shaderUtil.SetVector3f("spriteColor", color);

		////glActiveTexture(GL_TEXTURE0);
		////texture.Bind();

		//glBindVertexArray(quadVAO);
		//glDrawArrays(GL_TRIANGLES, 0, 6);
		//glBindVertexArray(0);
	}

	void GraphicsGL::ClearBackBuffer()
	{
		//sets the depth to 1.0
		glClearDepth(1.0);

		//clear the color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void GraphicsGL::Render()
	{


		//Swap out buffer and draw to the screen
		SDL_GL_SwapWindow(mWindow);
	}

	bool GraphicsGL::Init()
	{
		if (!Graphics::Init())
			return false;

		//Setup openGL Context
		glContext = SDL_GL_CreateContext(mWindow);
		if (glContext == nullptr)
		{
			std::cerr << "SDL_GL context could not be created!";
		}

		//Setup glew
		GLenum error = glewInit();
		if (error != GLEW_OK)
		{
			std::cerr << "Could not initialize glew!";
		}

		//Enables a double buffer window - removes flickering.
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
		

		//Enable Shader and Render data
		InitLoadShaderData();
		
		return true;
	}

	void GraphicsGL::InitRenderData(float x, float y, float w, float h, GLuint quadVAO)
	{

		if (quadVAO == 0)
			glGenBuffers(1, &quadVAO);

		Vertex vertexData[12];
		//first Triangle
		vertexData[0].position.x = x + w;
		vertexData[0].position.y = y + h;
		vertexData[0].SetUV(1.0, 1.0);

		vertexData[1].position.x = x;
		vertexData[1].position.y = y + h;
		vertexData[1].SetUV(0.0, 1.0);

		vertexData[2].position.x = x;
		vertexData[2].position.y = y;
		vertexData[2].SetUV(0.0, 0.0);

		//Second Triangle
		vertexData[3].position.x = x;
		vertexData[3].position.y = y;
		vertexData[3].SetUV(0.0, 0.0);

		vertexData[4].position.x = x + w;
		vertexData[4].position.y = y;
		vertexData[4].SetUV(1.0, 0.0);

		vertexData[5].position.x = x + w;
		vertexData[5].position.y = y + h;
		vertexData[5].SetUV(1.0, 1.0);

		glBindBuffer(GL_ARRAY_BUFFER, quadVAO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void GraphicsGL::InitLoadShaderData()
	{
		shaderUtil = AssetManager::LoadShader("vs.shader", "fs.shader", nullptr, "sprite");
		orthoMatrix = glm::ortho(0.0f, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 0.0f, -1.0f, 1.0f);
		//AssetManager::GetShader("sprite").Use().SetInteger("image", 0);
		AssetManager::GetShader("sprite").Use().SetVector2f("vertexPosition", glm::vec2(0,0));
		AssetManager::GetShader("sprite").SetMatrix4("proj", orthoMatrix);


	}
}
