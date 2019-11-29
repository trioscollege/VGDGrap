#ifndef __LEVEL_H
#define __LEVEL_H
#include "InputManager.hpp"
#include "PlaySideBar.hpp"
#include "BackgroundStars.hpp"

class Level : public GameEntity
{
private:
	Timer * mTimer;
	PlaySideBar * mSideBar;
	BackgroundStars * mStars;

	int mStage;
	bool mStageStarted;

	float mLabelTimer;

	Texture * mStageLabel;
	Scoreboard * mStageNumber;
	float mStageLabelOnScreen;
	float mStageLabelOffScreen;

	Texture * mReadyLabel;
	float mReadyLabelOnScreen;
	float mReadyLabelOffScreen;

	void StartStage();

public:
	Level(int stage, PlaySideBar * sideBar);
	~Level();

	void Update();
	void Render();
};
#endif
