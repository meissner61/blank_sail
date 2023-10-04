#pragma once

#include "SDL.h"
#include <string>



namespace sail
{
    
class Timer
{

public:
    static Timer& Instance();

    void Update();

    Uint64 GetAppMilliseconds();
    Uint64 GetAppSeconds();

    //  Timer  //
    Uint64 StartTimer();
    Uint64 EndTimer();

    void Reset();//TODO: not defined yet

    float GetFPS(); //TODO: not fully implemented

    Uint64 GetLastFrameTime();
    Uint64 GetCurrentFrameTime();
    Uint64 GetDeltaTime();

    float GetDeltaSeconds() const;


private:

    Uint64 m_startTimer = 0;
    Uint64 m_endTimer = 0;
    Uint64 m_currentTimeMS = 0;


    Uint64 m_lastTime = 0;

    Uint64 m_frames;
    std::string strFPS;

private:
    Uint64 m_lastFrameTime;
    Uint64 m_currentFrameTime;
    Uint64 m_deltaTime;
    float m_deltaSeconds;

Timer();
~Timer();
    

};

}