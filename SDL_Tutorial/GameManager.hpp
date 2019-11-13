#ifndef __GAMEMANAGER_H
#define __GAMEMANAGER_H
#include <SDL2/SDL.h>
#include "Graphics.hpp"
#include "Timer.hpp"

namespace SDLFramework {

    class GameManager
    {
    private:
        static GameManager * sInstance;
        const int FRAME_RATE = 60;

        bool mQuit;
        Graphics * mGraphics;

        Timer * mTimer;

        SDL_Event mEvent;

    public:
        static GameManager * Instance();
        static void Release();

        void Run();
        
        void Update();
        void LateUpdate();
        
        void Render();

        GameManager();
        ~GameManager();
    };
}
#endif
