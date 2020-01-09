#include "Level.h"

void Level::HandleStartLabels() {
	mLabelTimer += mTimer->DeltaTime();
	if (mLabelTimer >= mStageLabelOffScreen) {
		mStars->Scroll(true);
		if (mStage > 1) {
			StartStage();
		}
		else {
			if (mLabelTimer >= mReadyLabelOffScreen) {
				StartStage();
				mPlayer->Active(true);
				mPlayer->Visible(true);
			}
		}
	}
}

void Level::HandleCollisions() {
	if (!mPlayerHit) {
		if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_X)) {
			mPlayer->WasHit();
			mSideBar->SetShips(mPlayer->Lives());

			mPlayerHit = true;
			mRespawnTimer = 0.0f;
			mPlayer->Active(false);
			mStars->Scroll(false);
		}
	}
}

void Level::HandlePlayerDeath() {
	if (!mPlayer->IsAnimating()) {
		if (mPlayer->Lives() > 0) {
			if (mRespawnTimer == 0.0f) {
				mPlayer->Visible(false);
			}

			mRespawnTimer += mTimer->DeltaTime();
			if (mRespawnTimer >= mRespawnDelay) {
				mPlayer->Active(true);
				mPlayer->Visible(true);
				mPlayerHit = false;
				mStars->Scroll(true);
			}
		}
		else {
			if (mGameOverTimer == 0.0f) {
				mPlayer->Visible(false);
			}
			mGameOverTimer += mTimer->DeltaTime();
			if (mGameOverTimer >= mGameOverDelay) {
				mCurrentState = GameOver;
			}
		}
	}
}

void Level::HandleEnemySpawning() {
	mSpawnTimer += mTimer->DeltaTime();
	if (mSpawnTimer >= mSpawnDelay) {
		XMLElement * element = mSpawningPatterns.FirstChildElement("Level")->FirstChild()->NextSiblingElement();
		bool spawned = false;
		bool priorityFound = false;

		while (element != nullptr) {
			int priority = element->IntAttribute("priority");
			int path = element->IntAttribute("path");
			XMLElement * child = element->FirstChildElement();

			if (mCurrentFlyInPriority == priority) {
				priorityFound = true;
				
				for (int i = 0; i < mCurrentFlyInIndex && child != nullptr; i++) {
					child = child->NextSiblingElement();
				}

				if (child != nullptr) {
					std::string type = child->Attribute("type");
					int index = child->IntAttribute("index");

					if (type.compare("Butterfly") == 0) {
						mEnemies.push_back(new Butterfly(path, index, false));
						mButterflyCount += 1;
					}
					else if (type.compare("Wasp") == 0) {
						mEnemies.push_back(new Wasp(path, index, false, false));
						mWaspCount += 1;
					}
					else if (type.compare("Boss") == 0) {
						mEnemies.push_back(new Boss(path, index, false));
						mBossCount += 1;
					}

					spawned = true;
				}
			}

			element = element->NextSiblingElement();
		}

		if (!priorityFound) {
			mSpawningFinished = true;
		}
		else {
			if (!spawned) {
				bool flyingIn = false;

				for (auto e : mEnemies) {
					if (flyingIn = (e->CurrentState() == Enemy::FlyIn)) {
						break; // enemy still flying in, can stop checking
					}
				}

				if (!flyingIn) {
					mCurrentFlyInPriority += 1;
					mCurrentFlyInIndex = 0;
				}
			}
			else {
				mCurrentFlyInIndex += 1;
			}
		}
		mSpawnTimer = 0.0f;
	}
}

void Level::HandleEnemyFormation() {
	mFormation->Update();
	if (mButterflyCount == MAX_BUTTERFLIES && mWaspCount == MAX_WASPS && mBossCount == MAX_BOSSES) {
		bool flyIn = false;
		for (auto e : mEnemies) {
			if (e->CurrentState() == Enemy::FlyIn) {
				flyIn = true;
				break;
			}
		}

		if (!flyIn) {
			mFormation->Lock();
		}
	}
}

void Level::HandleEnemyDiving() {
	if (mFormation->Locked()) {
		if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_V)) {
			for (auto e : mEnemies) {
				if (e->Type() == Enemy::Wasp && e->CurrentState() == Enemy::InFormation) {
					e->Dive();
					break; // work done, leave loop.
				}
			}
		}

		if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_B)) {
			for (auto e : mEnemies) {
				if (e->Type() == Enemy::Butterfly && e->CurrentState() == Enemy::InFormation) {
					e->Dive();
					break; // work done, leave loop.
				}
			}
		}

		if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_H)) {
			for (auto e : mEnemies) {
				if (e->Type() == Enemy::Boss && e->CurrentState() == Enemy::InFormation) {
					e->Dive();

					int index = e->Index();
					int firstEscortIndex = (index % 2 == 0) ? (index * 2) : (index * 2 - 1);
					int secondEscortIndex = firstEscortIndex + 4;

					for (auto f : mEnemies) {
						// verify the enemy is a butterfly in formation and has either the first or second escort index
						if (f->Type() == Enemy::Butterfly && f->CurrentState() == Enemy::InFormation
							&& (f->Index() == firstEscortIndex || f->Index() == secondEscortIndex)) {
							f->Dive(1);
						}
					}

					break; // work done, leave loop.
				}
			}
		}
	}
}

void Level::StartStage() {
	mStageStarted = true;
}

Level::Level(int stage, PlaySideBar * sideBar, Player * player) {
	mTimer = Timer::Instance();
	mSideBar = sideBar;
	mSideBar->SetLevel(stage);
	mStars = BackgroundStars::Instance();

	mStage = stage;
	mStageStarted = false;

	mLabelTimer = 0.0f;

	mStageLabel = new Texture("STAGE", "emulogic.ttf", 32, { 75, 75, 200 });
	mStageLabel->Parent(this);
	mStageLabel->Position(Graphics::SCREEN_WIDTH * 0.35f, Graphics::SCREEN_HEIGHT * 0.5f);

	mStageNumber = new Scoreboard({ 75, 75, 200 });
	mStageNumber->Score(mStage);
	mStageNumber->Parent(this);
	mStageNumber->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.5f);

	mStageLabelOnScreen = 0.0f;
	mStageLabelOffScreen = 1.5f;

	mReadyLabel = new Texture("READY", "emulogic.ttf", 32, { 150, 0, 0 });
	mReadyLabel->Parent(this);
	mReadyLabel->Position(Graphics::SCREEN_WIDTH * 0.4f, Graphics::SCREEN_HEIGHT * 0.5f);

	mReadyLabelOnScreen = mStageLabelOffScreen;
	mReadyLabelOffScreen = mReadyLabelOnScreen + 3.0f;

	mPlayer = player;
	mPlayerHit = false;
	mRespawnDelay = 3.0f;
	mRespawnTimer = 0.0f;
	mRespawnLabelOnScreen = 2.0f;

	mGameOverLabel = new Texture("GAME OVER", "emulogic.ttf", 32, { 150, 0, 0 });
	mGameOverLabel->Parent(this);
	mGameOverLabel->Position(Graphics::SCREEN_WIDTH * 0.4f, Graphics::SCREEN_HEIGHT * 0.5f);

	mGameOverDelay = 6.0f;
	mGameOverTimer = 0.0f;
	mGameOverLabelOnScreen = 1.0f;

	mCurrentState = Running;

	mFormation = new Formation();
	mFormation->Position(Graphics::SCREEN_WIDTH * 0.39f, 150.0f);
	Enemy::SetFormation(mFormation);
	
	mButterflyCount = 0;
	mWaspCount = 0;
	mBossCount = 0;

	std::string fullPath = SDL_GetBasePath();
	fullPath.append("Data/Level1.xml");
	mSpawningPatterns.LoadFile(fullPath.c_str());

	mCurrentFlyInPriority = 0;
	mCurrentFlyInIndex = 0;
	mSpawningFinished = false;
	mSpawnDelay = 0.2f;
	mSpawnTimer = 0.0f;
}

Level::~Level() {
	mTimer = nullptr;
	mSideBar = nullptr;
	mStars = nullptr;

	delete mStageLabel;
	mStageLabel = nullptr;
	delete mStageNumber;
	mStageNumber = nullptr;
	delete mReadyLabel;
	mReadyLabel = nullptr;

	mPlayer = nullptr;

	delete mGameOverLabel;
	mGameOverLabel = nullptr;

	delete mFormation;
	mFormation = nullptr;

	for (auto e : mEnemies) {
		delete e;
	}
	mEnemies.clear();
}

Level::LevelStates Level::State() {
	return mCurrentState;
}

void Level::Update() {
	if (!mStageStarted) {
		HandleStartLabels();
	}
	else {
		if (!mSpawningFinished) {
			HandleEnemySpawning();
		}
		HandleEnemyFormation();
		HandleEnemyDiving();
		
		for (auto e : mEnemies) {
			e->Update();
		}

		HandleCollisions();

		if (mPlayerHit) {
			HandlePlayerDeath();
		}
		else {
			if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_N)) {
				mCurrentState = Finished;
			}
		}
	}
}

void Level::Render() {
	if (!mStageStarted) {
		if (mLabelTimer > mStageLabelOnScreen && mLabelTimer < mStageLabelOffScreen) {
			mStageLabel->Render();
			mStageNumber->Render();
		}
		else if (mLabelTimer > mReadyLabelOnScreen && mLabelTimer < mReadyLabelOffScreen) {
			mReadyLabel->Render();
		}
	}
	else {
		for (auto e : mEnemies) {
			e->Render();
		}

		if (mPlayerHit) {
			if (mRespawnTimer >= mRespawnLabelOnScreen) {
				mReadyLabel->Render();
			}

			if (mGameOverTimer >= mGameOverLabelOnScreen) {
				mGameOverLabel->Render();
			}
		}
	}
}
