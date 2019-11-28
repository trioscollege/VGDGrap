#include "PlaySideBar.h"

PlaySideBar::PlaySideBar() {
	mTimer = Timer::Instance();
	mAudio = AudioManager::Instance();

	mBackground = new Texture("Black.png");
	mBackground->Parent(this);
	mBackground->Position(45.0f, 380.0f);
	mBackground->Scale(Vector2(3.0f, 10.0f));

	mHighLabel = new Texture("HIGH", "emulogic.ttf", 32, { 150, 0, 0 });
	mHighLabel->Parent(this);
	mHighLabel->Position(-25.0f, 0.0f);

	mScoreLabel = new Texture("SCORE", "emulogic.ttf", 32, { 150, 0, 0 });
	mScoreLabel->Parent(this);
	mScoreLabel->Position(25.0f, 32.0f);

	mHighScoreboard = new Scoreboard();
	mHighScoreboard->Parent(this);
	mHighScoreboard->Position(90.0f, 64.0f);

	mPlayerOneLabel = new Texture("1UP", "emulogic.ttf", 32, { 150, 0, 0 });
	mPlayerOneLabel->Parent(this);
	mPlayerOneLabel->Position(-45.0f, 160.0f);

	mBlinkTimer = 0.0f;
	mBlinkInterval = 0.5f;
	mPlayerOneLabelVisible = true;

	mPlayerOneScore = new Scoreboard();
	mPlayerOneScore->Parent(this);
	mPlayerOneScore->Position(90.0f, 192.0f);
}

PlaySideBar::~PlaySideBar() {
	mTimer = nullptr;
	mAudio = nullptr;

	delete mBackground;
	mBackground = nullptr;

	delete mHighLabel;
	mHighLabel = nullptr;

	delete mScoreLabel;
	mScoreLabel = nullptr;

	delete mHighScoreboard;
	mHighScoreboard = nullptr;

	delete mPlayerOneLabel;
	mPlayerOneLabel = nullptr;

	delete mPlayerOneScore;
	mPlayerOneScore = nullptr;
}

void PlaySideBar::SetHighScore(int score) {
	mHighScoreboard->Score(score);
}

void PlaySideBar::SetPlayerScore(int score) {
	mPlayerOneScore->Score(score);
}

void PlaySideBar::Update() {
	mBlinkTimer += mTimer->DeltaTime();
	if (mBlinkTimer >= mBlinkInterval) {
		mPlayerOneLabelVisible = !mPlayerOneLabelVisible;
		mBlinkTimer = 0.0f;
	}
}

void PlaySideBar::Render() {
	mBackground->Render();
	mHighLabel->Render();
	mScoreLabel->Render();
	mHighScoreboard->Render();

	if (mPlayerOneLabelVisible) {
		mPlayerOneLabel->Render();
	}

	mPlayerOneScore->Render();
}
