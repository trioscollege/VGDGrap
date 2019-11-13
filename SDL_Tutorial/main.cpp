#include "GameManager.hpp"

using SDLFramework::GameManager;

int main(int argc, char * args[])
{
	GameManager * game = new GameManager();

	game->Run();

	GameManager::Release();
	game = nullptr;

	return 0;
}
