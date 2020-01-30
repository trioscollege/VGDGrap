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
	}

	GraphicsGL::~GraphicsGL()
	{

		SDL_GL_DeleteContext(mWindow);
	}

	void GraphicsGL::DrawSprite(TextureGL& texture, SDL_Rect* srcRect /*= nullptr*/, SDL_Rect* dstRect /*= nullptr*/, float angle /*= 0.0f*/, SDL_RendererFlip flip /*= SDL_FLIP_NONE*/)
	{
		int x = -1;	//xPos
		int y = -1;	//yPos
		int w = 1;	//Width
		int h = 1;

		if (texture.ID == 0)
			glGenBuffers(1, &texture.ID);

		float vertexData[12];
		//first Triangle
		vertexData[0] = x + w;
		vertexData[1] = y + h;

		vertexData[2] = x;
		vertexData[3] = y + h;

		vertexData[4] = x;
		vertexData[5] = y;

		//Second Triangle
		vertexData[6] = x;
		vertexData[7] = y;

		vertexData[8] = x + w;
		vertexData[9] = y;

		vertexData[10] = x + w;
		vertexData[11] = y + h;


		glBindBuffer(GL_ARRAY_BUFFER, texture.ID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);


		glBindBuffer(GL_ARRAY_BUFFER, texture.ID);


		glEnableVertexAttribArray(0);

		////this is position
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);


		glDrawArrays(GL_TRIANGLES, 0, 6);

		glDisableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
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
		
		return true;
	}

}
