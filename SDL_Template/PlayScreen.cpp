#include "PlayScreen.h"

PlayScreen::PlayScreen() {
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();

	mStars = BackgroundStars::Instance();

	mSideBar = new PlaySideBar();
	mSideBar->Parent(this);
	mSideBar->Position(Graphics::SCREEN_WIDTH * 0.87f, Graphics::SCREEN_HEIGHT * 0.05f);
	mSideBar->SetHighScore(30000);
	mSideBar->SetShips(3);
	mSideBar->SetLevel(3);
}

PlayScreen::~PlayScreen() {
	mTimer = nullptr;
	mInput = nullptr;

	mStars = nullptr;

	delete mSideBar;
	mSideBar = nullptr;
}

void PlayScreen::Update() {
	mSideBar->Update();
}

void PlayScreen::Render() {
	mSideBar->Render();
}
