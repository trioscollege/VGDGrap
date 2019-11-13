#include "StartScreen.hpp"

StartScreen::StartScreen() {
    mTimer = Timer::Instance();
    mInput = InputManager::Instance();
    
    // top bar entities
    mTopBar = new GameEntity(Graphics::Instance()->SCREEN_WIDTH * 0.5f, 80.0f);
    mPlayerOne = new Texture("1UP", "emulogic.ttf", 32, { 200, 0, 0 });
    mPlayerTwo = new Texture("2UP", "emulogic.ttf", 32, { 200, 0, 0 });
    mHiScore = new Texture("HI SCORE", "emulogic.ttf", 32, { 200, 0, 0 });
    
    mTopBar->Parent(this);
    mPlayerOne->Parent(mTopBar);
    mPlayerTwo->Parent(mTopBar);
    mHiScore->Parent(mTopBar);
    
    mPlayerOne->Position(Vector2(-Graphics::Instance()->SCREEN_WIDTH * 0.35f, 0.0f));
    mPlayerTwo->Position(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.2f, 0.0f));
    mHiScore->Position(Vec2_Zero);
    
    // logo entities
    mLogo = new Texture("GalagaLogo.png", 0, 0, 360, 180);
    mAnimatedLogo = new AnimatedTexture("GalagaLogo.png", 0, 0, 360, 180, 3, 0.2f, AnimatedTexture::Vertical);
    
    mLogo->Parent(this);
    mAnimatedLogo->Parent(this);
    
    mLogo->Position(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.32f));
    mAnimatedLogo->Position(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.32f));
    
    // play mode entities
    mPlayModes = new GameEntity(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.55f);
    mOnePlayerMode = new Texture("1 Player ", "emulogic.ttf", 32, { 230, 230, 230 });
    mTwoPlayerMode = new Texture("2 Players", "emulogic.ttf", 32, { 230, 230, 230 });
    mCursor = new Texture("Cursor.png");
    
    mPlayModes->Parent(this);
    mOnePlayerMode->Parent(mPlayModes);
    mTwoPlayerMode->Parent(mPlayModes);
    mCursor->Parent(mPlayModes);
    
    mOnePlayerMode->Position(Vector2(0.0f, -35.0f));
    mTwoPlayerMode->Position(Vector2(0.0f, 35.0f));
    mCursor->Position(Vector2(-175.0f, -35.0f));
    
    mCursorStartPos = mCursor->Position(Local);
    mCursorOffset = Vector2(0.0f, 70.0f);
    mSelectedMode = 0;
    
    // bottom bar entities
    mBottomBar = new GameEntity(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.7f);
    mNamco = new Texture("namcot", "namco__.ttf", 36, { 200, 0, 0 });
    mDates = new Texture("1981 1985 NAMCO LTD.", "emulogic.ttf", 32, { 230, 230, 230 });
    mRights = new Texture("ALL RIGHTS RESERVED", "emulogic.ttf", 32, { 230, 230, 230 });
    
    mBottomBar->Parent(this);
    mNamco->Parent(mBottomBar);
    mDates->Parent(mBottomBar);
    mRights->Parent(mBottomBar);
    
    mNamco->Position(Vec2_Zero);
    mDates->Position(Vector2(0.0f, 90.0f));
    mRights->Position(Vector2(0.0f, 170.0f));
    
    // sreen animation variables
    mAnimationStartPos = Vector2(0.0f, Graphics::Instance()->SCREEN_HEIGHT);
    mAnimationEndPos = Vec2_Zero;
    mAnimationTotalTime = 5.0f;
    mAnimationTimer = 0.0f;
    mAnimationDone = false;
    
    Position(mAnimationStartPos);
}

StartScreen::~StartScreen() {
    // top bar entities
    delete mTopBar;
    mTopBar = nullptr;
    
    delete mPlayerOne;
    mPlayerOne = nullptr;
    
    delete mPlayerTwo;
    mPlayerTwo = nullptr;
    
    delete mHiScore;
    mHiScore = nullptr;
    
    delete mCursor;
    mCursor = nullptr;
    
    // logo entities
    delete mLogo;
    mLogo = nullptr;
    
    delete mAnimatedLogo;
    mAnimatedLogo = nullptr;
    
    // play mode entities
    delete mPlayModes;
    mPlayModes = nullptr;
    
    delete mOnePlayerMode;
    mOnePlayerMode = nullptr;
    
    delete mTwoPlayerMode;
    mTwoPlayerMode = nullptr;
    
    // bottom bar entities
    delete mBottomBar;
    mBottomBar = nullptr;
    
    delete mNamco;
    mNamco = nullptr;
    
    delete mDates;
    mDates = nullptr;
    
    delete mRights;
    mRights = nullptr;
}

void StartScreen::ChangeSelectedMode(int change) {
    mSelectedMode += change;
    
    if (mSelectedMode < 0) {
        mSelectedMode = 1;
    }
    else if (mSelectedMode > 1) {
        mSelectedMode = 0;
    }
    
    mCursor->Position(mCursorStartPos + mCursorOffset * mSelectedMode);
}

void StartScreen::Update() {
    if (!mAnimationDone) {
        mAnimationTimer += mTimer->DeltaTime();
        Position(Lerp(mAnimationStartPos, mAnimationEndPos, mAnimationTimer / mAnimationTotalTime));
        
        if (mAnimationTimer >= mAnimationTotalTime) {
            mAnimationDone = true;
        }
        
        if (mInput->KeyPressed(SDL_SCANCODE_DOWN) || mInput->KeyPressed(SDL_SCANCODE_UP)) {
            mAnimationTimer = mAnimationTotalTime;
        }
    }
    else {
        mAnimatedLogo->Update();
        
        if (mInput->KeyPressed(SDL_SCANCODE_DOWN)) {
            ChangeSelectedMode(1);
        }
        else if (mInput->KeyPressed(SDL_SCANCODE_UP)) {
            ChangeSelectedMode(-1);
        }
    }
}

void StartScreen::Render() {
    mPlayerOne->Render();
    mPlayerTwo->Render();
    mHiScore->Render();
    
    if (!mAnimationDone) {
        mLogo->Render();
    }
    else {
        mAnimatedLogo->Render();
    }
    
    mOnePlayerMode->Render();
    mTwoPlayerMode->Render();
    mCursor->Render();
    
    mNamco->Render();
    mDates->Render();
    mRights->Render();
}
