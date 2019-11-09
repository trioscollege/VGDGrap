#include <iostream>
#include <SDL.h>
// MacOS using XCode
// #include <SDL2/SDL.h>

#include "GameManager.h"

int main(int argc, char * args[])
{
	GameManager * game = new GameManager();

	game->Run();

	GameManager::Release();
	game = nullptr;

	return 0;
}