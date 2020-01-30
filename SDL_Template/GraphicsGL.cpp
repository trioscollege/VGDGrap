#include "GraphicsGL.h"
#include "AssetManager.h"
#include "stb_image.h"
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



	}

	GraphicsGL::~GraphicsGL()
	{


		SDL_GL_DeleteContext(mWindow);
	}

	void GraphicsGL::DrawSprite(TextureGL& texture, SDL_Rect* srcRect /*= nullptr*/, SDL_Rect* dstRect /*= nullptr*/, float angle /*= 0.0f*/, SDL_RendererFlip flip /*= SDL_FLIP_NONE*/)
	{


		float rad = angle * (3.1415926535 / 180);

  		InitRenderData(&texture, srcRect, rad, dstRect->x, dstRect->y, dstRect->w, dstRect->h, texture.ID);

		shaderUtil.Use();
		glBindTexture(GL_TEXTURE_2D, texture.ID);

		//glActiveTexture(GL_TEXTURE0);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		GLint location = shaderUtil.GetUniformLocation("tSampler");
		glUniform1i(location, 0);
	
		//location = shaderUtil.GetUniformLocation("flip");
		//glUniform1f(location, 1.0f);

		//if (flip != SDL_FLIP_NONE)
			//glUniform1f(location, 0);

		location = shaderUtil.GetUniformLocation("proj");
		glUniformMatrix4fv(location, 1, GL_FALSE, &(orthoMatrix[0][0]));

		//Start to draw to screen
		glBindBuffer(GL_ARRAY_BUFFER, texture.ID);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		//this is position
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
		//this is Color
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
		//this is UV
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
		
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindTexture(GL_TEXTURE_2D, 0);

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
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glEnable(GL_TEXTURE_2D);


		//Enable Shader and Render data
		InitLoadShaderData();


		return true;
	}
														//Source Info		//World Placement Info floats.
	void GraphicsGL::InitRenderData(Texture* texture, SDL_Rect* srcRect, float angle, float x, float y, float w, float h, GLuint quadVAO)
	{
		TextureGL* texGL = (TextureGL*)texture;
		if (!texGL)
		{
			std::cout << "TEXTURE ERROR" << std::endl;
	
			return;
		}

		//Get the exact PIXEL with and height from the Texture class
		float height = texGL->mSurf->h;
		float width = texGL->mSurf->w;

		if (quadVAO == 0)
			glGenBuffers(1, &quadVAO);
		//set defaults
		glm::vec2 topRight = glm::vec2(1,1);
		glm::vec2 topLeft = glm::vec2(0, 1);
		glm::vec2 BottomLeft = glm::vec2(0, 0);
		glm::vec2 BottomRight = glm::vec2(1, 0);

		if (srcRect)
		{
			topRight = glm::vec2((srcRect->x + srcRect->w) / width, (srcRect->y + srcRect->h)/ height);		
			topLeft = glm::vec2(srcRect->x / width, (srcRect->y + srcRect->h) / height);		

			BottomLeft = glm::vec2(srcRect->x / width, (srcRect->y) / height);
			BottomRight = glm::vec2((srcRect->x + srcRect->w) / width, (srcRect->y) / height);
		}
	
		Vertex vertexData[6];
		//first Triangle
		vertexData[0].SetPosition(x + w, y + h);
		vertexData[0].SetUV(topRight.x, topRight.y);				//TopRight (1.0, 1.0)

		vertexData[1].position.x = x;
		vertexData[1].position.y = y + h;
		vertexData[1].SetUV(topLeft.x, topLeft.y);					//Top Left (0.0, 1.0)

		vertexData[2].position.x = x;
		vertexData[2].position.y = y;
		vertexData[2].SetUV(BottomLeft.x, BottomLeft.y);			//Bottom Left (0.0, 0.0)

		//Second Triangle
		vertexData[3].position.x = x;
		vertexData[3].position.y = y;
		vertexData[3].SetUV(BottomLeft.x, BottomLeft.y);			//BottomLeft (0.0, 0.0)

		vertexData[4].position.x = x + w;
		vertexData[4].position.y = y;
		vertexData[4].SetUV(BottomRight.x, BottomRight.y);			//Bottom Right (1.0, 0.0)

		vertexData[5].position.x = x + w;
		vertexData[5].position.y = y + h;
		vertexData[5].SetUV(topRight.x, topRight.y);				//top right (1.0, 1.0)

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
