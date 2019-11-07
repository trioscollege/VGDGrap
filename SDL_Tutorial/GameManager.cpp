#include "GameManager.hpp"

GameManager * GameManager::sInstance = nullptr;

GameManager * GameManager::Instance()
{
	if (sInstance == nullptr) {
		sInstance = new GameManager();
	}
	return sInstance;
}

void GameManager::Release() {
	delete sInstance;
	sInstance = nullptr;
}

void GameManager::Run() {
	while (!mQuit) {
		mTimer->Update();

		while (SDL_PollEvent(&mEvent)) {
			switch (mEvent.type) {
			case SDL_QUIT:
				mQuit = true;
				break;
			}
		}

		if (mTimer->DeltaTime() >= 1.0f / FRAME_RATE) {
			std::cout << "Detla time: " << mTimer->DeltaTime() << std::endl;
			mGraphics->Render();
			mTimer->Reset();
		}
	}
}

GameManager::GameManager() : mQuit(false) {
	mGraphics = Graphics::Instance();

	if (!Graphics::Initialized()) {
		mQuit = true;
	}

	mTimer = Timer::Instance();
}

GameManager::~GameManager() {
	Timer::Release();
	mTimer = nullptr;
	
	Graphics::Release();
	mGraphics = nullptr;

	// Quit SDL subsystems
	SDL_Quit();
}
