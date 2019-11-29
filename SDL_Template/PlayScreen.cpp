#include "PlayScreen.h"

void PlayScreen::StartNextLevel() {
	mCurrentStage += 1;
	mLevelStartTimer = 0.0f;
	mLevelStarted = true;
	
	delete mLevel;
	mLevel = new Level(mCurrentStage, mSideBar);
}

PlayScreen::PlayScreen() {
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();
	mAudio = AudioManager::Instance();

	mStars = BackgroundStars::Instance();

	mSideBar = new PlaySideBar();
	mSideBar->Parent(this);
	mSideBar->Position(Graphics::SCREEN_WIDTH * 0.87f, Graphics::SCREEN_HEIGHT * 0.05f);

	mStartLabel = new Texture("START", "emulogic.ttf", 32, { 150, 0, 0 });
	mStartLabel->Parent(this);
	mStartLabel->Position(Graphics::SCREEN_WIDTH * 0.4f, Graphics::SCREEN_HEIGHT * 0.5f);

	mLevel = nullptr;
	mLevelStartDelay = 1.0f;
	mLevelStarted = false;
}

PlayScreen::~PlayScreen() {
	mTimer = nullptr;
	mInput = nullptr;

	mStars = nullptr;

	delete mSideBar;
	mSideBar = nullptr;

	delete mStartLabel;
	mStartLabel = nullptr;

	delete mLevel;
	mLevel = nullptr;
}

void PlayScreen::StartNewGame() {
	mStars->Scroll(false);
	mSideBar->SetHighScore(30000);
	mSideBar->SetShips(2);
	mGameStarted = false;
	mAudio->PlayMusic("MUS\\GameStart.wav", 0);
	mCurrentStage = 0;
}

void PlayScreen::Update() {
	if (mGameStarted) {
		if (!mLevelStarted) {
			mLevelStartTimer += mTimer->DeltaTime();
			if (mLevelStartTimer >= mLevelStartDelay) {
				StartNextLevel();
			}
		}
	}
	else {
		if (!Mix_PlayingMusic()) {
			mGameStarted = true;
		}
	}
	
	if (mGameStarted && mLevelStarted) {
		mSideBar->Update();
		mLevel->Update();
	}
}

void PlayScreen::Render() {
	mSideBar->Render();

	if (!mGameStarted) {
		mStartLabel->Render();
	}

	if (mGameStarted && mLevelStarted) {
		mLevel->Render();
	}
}
