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
		if (mPlayer->WasHit()) {
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

bool Level::EnemyFlyingIn() {
	for (Butterfly * b : mFormationButterflies) {
		if (b != nullptr && b->CurrentState() == Enemy::FlyIn) {
			return true;
		}
	}

	for (Wasp * w : mFormationWasps) {
		if (w != nullptr && w->CurrentState() == Enemy::FlyIn) {
			return true;
		}
	}

	for (Boss * b : mFormationBosses) {
		if (b != nullptr && b->CurrentState() == Enemy::FlyIn) {
			return true;
		}
	}

	return false;
}

void Level::HandleEnemySpawning() {
	mSpawnTimer += mTimer->DeltaTime();
	if (mSpawnTimer >= mSpawnDelay) {
		XMLElement * element = mSpawningPatterns.FirstChildElement("Level")->FirstChild()->NextSiblingElement();
		bool spawned = false;
		bool priorityFound = false;

		while (element != nullptr) {
			int priority = element->IntAttribute("priority");

			if (mCurrentFlyInPriority == priority) {
				priorityFound = true;
				int path = element->IntAttribute("path");
				XMLElement * child = element->FirstChildElement();				

				for (int i = 0; i < mCurrentFlyInIndex && child != nullptr; i++) {
					child = child->NextSiblingElement();
				}

				if (child != nullptr) {
					std::string type = child->Attribute("type");
					int index = child->IntAttribute("index");

					if (type.compare("Butterfly") == 0) {
						if (!mChallengeStage) {
							mFormationButterflies[index] = new Butterfly(path, index, false);
							mButterflyCount += 1;
						}
						else {
							mEnemies.push_back(new Butterfly(path, index, false));
						}
					}
					else if (type.compare("Wasp") == 0) {
						if (!mChallengeStage) {
							mFormationWasps[index] = new Wasp(path, index, false, false);
							mWaspCount += 1;
						}
						else {
							mEnemies.push_back(new Wasp(path, index, false, false));
						}
					}
					else if (type.compare("Boss") == 0) {
						if (!mChallengeStage) {
							mFormationBosses[index] = new Boss(path, index, false);
							mBossCount += 1;
						}
						else {
							mEnemies.push_back(new Boss(path, index, false));
						}
					}

					spawned = true;
				}
			}

			element = element->NextSiblingElement();
		}

		if (!priorityFound) {
			// no priorities found means no more Spawn elements
			mSpawningFinished = true;
		}
		else {
			if (!spawned) {
				// We have Spawn elements waiting, but we didn't spawn anything
				if (!EnemyFlyingIn()) {
					mCurrentFlyInPriority += 1;
					mCurrentFlyInIndex = 0;
				}
			}
			else {
				// We haven't finished spawning this element's enemies, next index!
				mCurrentFlyInIndex += 1;
			}
		}
		mSpawnTimer = 0.0f;
	}
}

void Level::HandleEnemyFormation() {
	mFormation->Update();

	bool levelCleared = mSpawningFinished;

	for (Butterfly * b : mFormationButterflies) {
		if (b != nullptr) {
			b->Update();
			if (b->CurrentState() != Enemy::Dead || b->InDeathAnimation()) {
				levelCleared = false;
			}
		}
	}

	for (Wasp * w : mFormationWasps) {
		if (w != nullptr) {
			w->Update();
			if (w->CurrentState() != Enemy::Dead || w->InDeathAnimation()) {
				levelCleared = false;
			}
		}
	}

	for (Boss * b : mFormationBosses) {
		if (b != nullptr) {
			b->Update();
			if (b->CurrentState() != Enemy::Dead || b->InDeathAnimation()) {
				levelCleared = false;
			}
		}
	}

	if (!mFormation->Locked()) {
		if (mButterflyCount == MAX_BUTTERFLIES && mWaspCount == MAX_WASPS && mBossCount == MAX_BOSSES) {
			if (!EnemyFlyingIn()) {
				mFormation->Lock();
			}
		}
	}
	else {
		HandleEnemyDiving();
	}

	if (levelCleared) {
		mCurrentState = Finished;
	}
}

void Level::HandleEnemyDiving() {
	// Butterfly diving
	if (mDivingButterfly == nullptr) {
		mButterflyDiveTimer += mTimer->DeltaTime();

		if (mButterflyDiveTimer >= mButterflyDiveDelay) {
			bool skipped = false;

			for (int i = MAX_BUTTERFLIES - 1; i >= 0; i--) {
				if (mFormationButterflies[i] != nullptr 
					&& mFormationButterflies[i]->CurrentState() == Enemy::InFormation) {
					if (!mSkipFirstButterfly || (mSkipFirstButterfly && skipped)) {
						mDivingButterfly = mFormationButterflies[i];
						mDivingButterfly->Dive();
						mSkipFirstButterfly = !mSkipFirstButterfly;
						break; // work done, leave loop
					}
				}
				skipped = true;
			}

			mButterflyDiveTimer = 0.0f;
		}
	}
	else {
		if (mDivingButterfly->CurrentState() != Enemy::Diving) {
			mDivingButterfly = nullptr;
		}
	}

	// Wasp diving
	mWaspDiveTimer += mTimer->DeltaTime();
	if (mWaspDiveTimer >= mWaspDiveDelay) {
		for (int i = MAX_WASPS - 1; i >= 0; i--) {
			if (mFormationWasps[i]->CurrentState() == Enemy::InFormation) {
				if (mDivingWasp == nullptr) {
					mDivingWasp = mFormationWasps[i];
					mDivingWasp->Dive();
				}
				else if (mDivingWasp2 == nullptr) {
					mDivingWasp2 = mFormationWasps[i];
					mDivingWasp2->Dive();
				}
				break; // work done, leave loop
			}
		}

		mWaspDiveTimer = 0.0f;
	}

	if (mDivingWasp != nullptr && mDivingWasp->CurrentState() != Enemy::Diving) {
		mDivingWasp = nullptr;
	}
	if (mDivingWasp2 != nullptr && mDivingWasp2->CurrentState() != Enemy::Diving) {
		mDivingWasp2 = nullptr;
	}

	// Boss diving
	if (mDivingBoss == nullptr) {
		mBossDiveTimer += mTimer->DeltaTime();

		if (mBossDiveTimer >= mBossDiveDelay) {
			bool skipped = false;
			for (int i = MAX_BOSSES - 1; i >= 0; i--) {
				if (mFormationBosses[i]->CurrentState() == Enemy::InFormation) {
					if (!mSkipFirstBoss || (mSkipFirstBoss && skipped)) {
						mDivingBoss = mFormationBosses[i];
						if (mCaptureDive) {
							mDivingBoss->Dive(1);
						}
						else {
							mDivingBoss->Dive();
							int index = mDivingBoss->Index();
							int firstEscortIndex = (index % 2 == 0) ? (index * 2) : (index * 2 - 1);
							int secondEscortIndex = firstEscortIndex + 4;

							if (mFormationButterflies[firstEscortIndex]->CurrentState() == Enemy::InFormation) {
								mFormationButterflies[firstEscortIndex]->Dive(1); 
							}
							if (mFormationButterflies[secondEscortIndex]->CurrentState() == Enemy::InFormation) {
								mFormationButterflies[secondEscortIndex]->Dive(1);
							}
						}
						mSkipFirstBoss = !mSkipFirstBoss;
						mCaptureDive = !mCaptureDive;
						break; // work done, leave loop
					}
					skipped = true;
				}
			}

			mBossDiveTimer = 0.0f;
		}
	}
	else {
		if (mDivingBoss->CurrentState() != Enemy::Diving) {
			mDivingBoss = nullptr;
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

	mButterflyCount = 0;
	mWaspCount = 0;
	mBossCount = 0;

	std::string fullPath = SDL_GetBasePath();
	fullPath.append("Data/Level1.xml");
	mSpawningPatterns.LoadFile(fullPath.c_str());

	mChallengeStage = mSpawningPatterns.FirstChildElement("Level")->FirstChildElement()->BoolAttribute("value");

	if (!mChallengeStage) {
		mFormation = new Formation();
		mFormation->Position(Graphics::SCREEN_WIDTH * 0.39f, 150.0f);
		Enemy::SetFormation(mFormation);

		for (unsigned i = 0; i < MAX_BUTTERFLIES; i++) {
			mFormationButterflies[i] = nullptr;
		}

		for (unsigned i = 0; i < MAX_WASPS; i++) {
			mFormationWasps[i] = nullptr;
		}

		for (unsigned i = 0; i < MAX_BOSSES; i++) {
			mFormationBosses[i] = nullptr;
		}
	}

	mCurrentFlyInPriority = 0;
	mCurrentFlyInIndex = 0;
	mSpawnDelay = 0.2f;
	mSpawnTimer = 0.0f;
	mSpawningFinished = false;

	mDivingButterfly = nullptr;
	mSkipFirstButterfly = false;
	mButterflyDiveDelay = 1.0f;
	mButterflyDiveTimer = 0.0f;

	mDivingWasp = nullptr;
	mDivingWasp2 = nullptr;
	mWaspDiveDelay = 3.0f;
	mWaspDiveTimer = 0.0f;

	mDivingBoss = nullptr;
	mCaptureDive = true;
	mSkipFirstBoss = true;
	mBossDiveDelay = 5.0f;
	mBossDiveTimer = 0.0f;

	Enemy::CurrentPlayer(mPlayer);
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

	for (auto b : mFormationButterflies) {
		delete b;
	}

	for (auto w : mFormationWasps) {
		delete w;
	}

	for (auto b : mFormationBosses) {
		delete b;
	}

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

		if (!mChallengeStage) {
			HandleEnemyFormation();
		}
		else {
			for (auto e : mEnemies) {
				e->Update();
			}
		}

		HandleCollisions();

		if (mPlayerHit) {
			HandlePlayerDeath();
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
		if (!mChallengeStage) {
			for (Butterfly * b : mFormationButterflies) {
				if (b != nullptr) {
					b->Render();
				}
			}

			for (Wasp * w : mFormationWasps) {
				if (w != nullptr) {
					w->Render();
				}
			}

			for (Boss * b : mFormationBosses) {
				if (b != nullptr) {
					b->Render();
				}
			}
		}
		else {
			for (auto e : mEnemies) {
				e->Render();
			}
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
