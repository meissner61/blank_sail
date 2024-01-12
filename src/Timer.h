#pragma once

#include "SDL.h"
#include <string>
#include <chrono>
#include <iostream>



namespace sail
{
    
class Timer
{

public:
    Timer();
    ~Timer();
    //static Timer& Instance();

    void Update();

    static Uint64 GetAppMilliseconds();
    static Uint64 GetAppSeconds();

    static Uint64 GetAppMicoSeconds();


    

    //  Timer  //
    Uint64 StartTimer();
    Uint64 EndTimer();

    void Reset();//TODO: not defined yet

    float GetFPS(); //TODO: not fully implemented, should be static

    static Uint64 GetLastFrameTime();
    static Uint64 GetCurrentFrameTime();
    static Uint64 GetDeltaTime();

    static float GetDeltaSeconds();


private:

    Uint64 m_startTimer = 0;
    Uint64 m_endTimer = 0;
    //Uint64 m_currentTimeMS = 0;

    //static std::chrono::time_point<std::chrono::high_resolution_clock> start; //= std::chrono::high_resolution_clock::now();
    //static std::chrono::time_point<std::chrono::high_resolution_clock> end;


    Uint64 m_lastTime = 0;

    Uint64 m_frames;
    std::string strFPS;

private:
    static inline Uint64 m_lastFrameTime;
    static inline Uint64 m_currentFrameTime;
    static inline Uint64 m_deltaTime;
    static inline float m_deltaSeconds;


    

};

}