#include "GameManager.h"

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
			mInputManager->Update();
			
			if (mInputManager->KeyDown(SDL_SCANCODE_W)) {
				mTex->Translate(Vector2(0, -40.0f) * mTimer->DeltaTime());
			}
			else if (mInputManager->KeyDown(SDL_SCANCODE_S)) {
				mTex->Translate(Vector2(0, 40.0f) * mTimer->DeltaTime());
			}

			mGraphics->ClearBackBuffer();
			mTex->Render();
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

	mAssetManager = AssetManager::Instance();
	mInputManager = InputManager::Instance();

	mTimer = Timer::Instance();

	mTex = new Texture("SpriteSheet.png", 182, 54, 22, 22);
	mTex->Position(Vector2(Graphics::SCREEN_WIDTH*0.5f, Graphics::SCREEN_HEIGHT*0.5f));
}

GameManager::~GameManager() {
	delete mTex;
	mTex = nullptr;

	Timer::Release();
	mTimer = nullptr;

	InputManager::Release();
	mInputManager = nullptr;

	AssetManager::Release();
	mAssetManager = nullptr;

	Graphics::Release();
	mGraphics = nullptr;

	// Quit SDL subsystems
	SDL_Quit();
}