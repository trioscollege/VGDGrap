#include "GameManager.h"

using namespace SDLFramework;

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
			Update();
			LateUpdate();
			Render();
			mTimer->Reset();
		}
	}
}

void GameManager::Update() {
	std::cout << "Delta time: " << mTimer->DeltaTime() << std::endl;
}

void GameManager::LateUpdate() {
	
}

void GameManager::Render() {
	mGraphics->ClearBackBuffer();
	mGraphics->Render();
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