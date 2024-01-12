
#include "Timer.h"

//#include "SDL.h"

using namespace sail;

// Timer& Timer::Instance()
// {
//     static Timer instance;
//     return instance;
// }

Timer::Timer()
{

}

Timer::~Timer()
{

}

Uint64 Timer::StartTimer()
{
    m_startTimer = SDL_GetTicks64();
    SDL_Log("\nTimer Started at: %li ms",SDL_GetTicks64() );

    return m_startTimer;
}

Uint64 Timer::EndTimer()
{
    m_endTimer = SDL_GetTicks64();

    m_endTimer = m_endTimer - m_startTimer;

    
    SDL_Log("\n Timer Ended at: %li ms",SDL_GetTicks64() );
    SDL_Log("\n incurring: %li ms",m_endTimer );

    return m_endTimer;
}


void Timer::Update()
{
    m_frames++;
    GetAppMilliseconds();
}

Uint64 Timer::GetAppMilliseconds()
{
    return SDL_GetTicks64();
    // m_currentTimeMS = SDL_GetTicks64();
    // return m_currentTimeMS;
}

Uint64 Timer::GetAppSeconds()
{

    return GetAppMilliseconds() / 1000;
}

Uint64 sail::Timer::GetAppMicoSeconds()
{
    static auto appStart = std::chrono::high_resolution_clock::now();
    auto now = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(now - appStart);

    return duration.count();


    //return Uint64();
}

float Timer::GetFPS()
{

    Uint64 currentTimeMS = GetAppMilliseconds();

    if (currentTimeMS > m_lastTime + 1000) //once per second
    {
        strFPS = std::to_string(m_frames);
        std::string titleFPS = "FPSTEST: ";
        titleFPS += strFPS;
        //SetWindowTitle(titleFPS.c_str());
        m_frames = 0;

        m_lastTime = currentTimeMS;
    }

    return 0.0f;
}

// Uint64 sail::Timer::GetLastFrameTime()
// {
//     m_lastFrameTime = GetAppMilliseconds();

//     return m_lastFrameTime;
// }

// Uint64 sail::Timer::GetCurrentFrameTime()
// {
//     m_currentFrameTime = GetAppMilliseconds();
//     return m_currentFrameTime;
// }

Uint64 sail::Timer::GetLastFrameTime()
{
    m_lastFrameTime = GetAppMicoSeconds();

    return m_lastFrameTime;
}

Uint64 sail::Timer::GetCurrentFrameTime()
{
    m_currentFrameTime = GetAppMicoSeconds();
    return m_currentFrameTime;
}

Uint64 sail::Timer::GetDeltaTime()
{
    m_deltaTime = m_currentFrameTime - m_lastFrameTime;

    return m_deltaTime;
}

float sail::Timer::GetDeltaSeconds()
{
    //return m_deltaTime /  1000.0f //for milliseconds
    return m_deltaTime / 1000000.0f; //for Microseconds
}

