#include <iostream>
#include <SDL.h>
// MacOS using XCode
// #include <SDL2/SDL.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char * args[])
{
	// Our target window
	SDL_Window * window = nullptr;
	// The renderer for our target window
	SDL_Renderer * renderer = nullptr;
	bool quit = false;

	// Initialize SDL subsystems
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
	}
	else
	{
		// Attempt to create a new window
		window = SDL_CreateWindow(
			"SDL Tutorial",				// window title
			SDL_WINDOWPOS_UNDEFINED,	// window x pos
			SDL_WINDOWPOS_UNDEFINED,	// window y pos
			SCREEN_WIDTH,				// window width
			SCREEN_HEIGHT,				// window height
			SDL_WINDOW_SHOWN);			// window flags
		if (window == nullptr)
		{
			std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		}
		else
		{
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (renderer == nullptr) {
				std::cerr << "Unable to get create renderer! SDL_Error: " << SDL_GetError() << std::endl;
			}
			else {
				// Set the renderer draw colour - RGBA
				SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
				SDL_Event e = {};

				while (!quit) {
					while (SDL_PollEvent(&e)) {
						switch (e.type) {
						case SDL_QUIT:
							quit = true;
							break;
						}
					}
					SDL_RenderFillRect(renderer, nullptr);
					SDL_RenderPresent(renderer);
				}
			}
		}
	}
	// Destroy the renderer
	SDL_DestroyRenderer(renderer);
	// Destroy the window
	SDL_DestroyWindow(window);
	// Quit SDL subsystems
	SDL_Quit();

	return 0;
}