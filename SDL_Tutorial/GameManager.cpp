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
			mInputManager->Update();
			
			if (mInputManager->KeyDown(SDL_SCANCODE_W)) {
				mTex->Translate(Vector2(0, -40.0f) * mTimer->DeltaTime());
			}
			else if (mInputManager->KeyDown(SDL_SCANCODE_S)) {
				mTex->Translate(Vector2(0, 40.0f) * mTimer->DeltaTime());
			}

			if (mInputManager->KeyDown(SDL_SCANCODE_1)) {
				mAudioManager->PlaySFX("SFX/coin_credit.wav", 0, 0);
			}

			mTex->Update();

			mGraphics->ClearBackBuffer();
			mFontTex->Render();
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
	mAudioManager = AudioManager::Instance();

	mTimer = Timer::Instance();

	mTex = new AnimatedTexture("SpriteSheet.png", 204, 45, 40, 38, 4, 0.5f, AnimatedTexture::Horizontal);
	mTex->Position(Vector2(Graphics::SCREEN_WIDTH*0.5f, Graphics::SCREEN_HEIGHT*0.5f));

	mFontTex = new Texture("Hello World!", "ARCADE.TTF", 72, { 255, 0, 0 });
	mFontTex->Position(Vector2(400, 200));
}

GameManager::~GameManager() {
	delete mTex;
	mTex = nullptr;

	delete mFontTex;
	mFontTex = nullptr;
	
	Timer::Release();
	mTimer = nullptr;

	AudioManager::Release();
	mAudioManager = nullptr;

	InputManager::Release();
	mInputManager = nullptr;

	AssetManager::Release();
	mAssetManager = nullptr;

	Graphics::Release();
	mGraphics = nullptr;

	// Quit SDL subsystems
	SDL_Quit();
}
