#ifndef __PLAYSIDEBAR_H
#define __PLAYSIDEBAR_H
#include "Timer.h"
#include "Scoreboard.h"
#include "AudioManager.h"

class PlaySideBar : public GameEntity {
private:
	static const int MAX_SHIP_TEXTURES = 5;

	Timer * mTimer;
	AudioManager * mAudio;

	Texture * mBackground;

	Texture * mHighLabel;
	Texture * mScoreLabel;
	Scoreboard * mHighScoreboard;

	Texture * mPlayerOneLabel;
	float mBlinkTimer;
	float mBlinkInterval;
	bool mPlayerOneLabelVisible;

	Scoreboard * mPlayerOneScore;

	GameEntity * mShips;
	Texture * mShipTextures[MAX_SHIP_TEXTURES];
	int mTotalShips;

public:
	PlaySideBar();
	~PlaySideBar();

	void SetHighScore(int score);
	void SetPlayerScore(int score);

	void Update();
	void Render();
};
#endif