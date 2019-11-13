#include "GameManager.hpp"

namespace SDLFramework {

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
                Update();
                LateUpdate();
                Render();
                mTimer->Reset();
            }
        }
    }

    void GameManager::Update() {
        
    }

    void GameManager::LateUpdate() {
        
    }

    void GameManager::Render() {
        mGraphics->ClearBackBuffer();
        mGraphics->Render();
    }

    GameManager::GameManager() : mQuit(false) {
        mGraphics = Graphics::Instance();

        if (!Graphics::Initialized()) {
            mQuit = true;
        }

        mTimer = Timer::Instance();

        // sanity test
        mParent = new GameEntity(100.0f, 400.0f);
        mChild = new GameEntity(100.0f, 500.0f);

        // print local position of mChild with no parent set
        printf("Child local pos: (%f, %f)\n",
            mChild->Position(GameEntity::Local).x,
            mChild->Position(GameEntity::Local).y);

        // set parent of mChild to mParent
        mChild->Parent(mParent);
        mParent->Rotation(0.0f);

        // print local position of mChild with parent set
        printf("Child local pos: (%f, %f)\n",
            mChild->Position(GameEntity::Local).x,
            mChild->Position(GameEntity::Local).y);
        printf("Child world pos: (%f, %f)\n",
            mChild->Position(GameEntity::World).x,
            mChild->Position(GameEntity::World).y);
    }

    GameManager::~GameManager() {
        delete mChild;
        mChild = nullptr;
        
        delete mParent;
        mParent = nullptr;
        
        Timer::Release();
        mTimer = nullptr;
        
        Graphics::Release();
        mGraphics = nullptr;

        // Quit SDL subsystems
        SDL_Quit();
    }
}
