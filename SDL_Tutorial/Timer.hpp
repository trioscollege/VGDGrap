#ifndef __TIMER_H
#define __TIMER_H
#include <SDL2/SDL.h>

namespace SDLFramework {

    class Timer
    {
    private:
        static Timer * sInstance;

        unsigned int mStartTicks;
        unsigned int mElapsedTicks;
        float mDeltaTime;
        float mTimeScale;

    public:
        static Timer * Instance();
        static void Release();

        void Reset();
        float DeltaTime() const;

        void TimeScale(float ts);
        float TimeScale() const;

        void Update();

    private:
        Timer();
        ~Timer();
    };
}
#endif
