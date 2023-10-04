
#include "Timer.h"

//#include "SDL.h"

using namespace sail;

Timer& Timer::Instance()
{
    static Timer instance;
    return instance;
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
    m_currentTimeMS = SDL_GetTicks64();
    return m_currentTimeMS;
}

Uint64 Timer::GetAppSeconds()
{

    return GetAppMilliseconds() / 1000;
}

float Timer::GetFPS()
{
    if (m_currentTimeMS > m_lastTime + 1000) //once per second
    {
        strFPS = std::to_string(m_frames);
        std::string titleFPS = "FPSTEST: ";
        titleFPS += strFPS;
        //SetWindowTitle(titleFPS.c_str());
        m_frames = 0;

        m_lastTime = m_currentTimeMS;
    }

    return 0.0f;
}

Uint64 sail::Timer::GetLastFrameTime()
{
    m_lastFrameTime = GetAppMilliseconds();

    return m_lastFrameTime;
}

Uint64 sail::Timer::GetCurrentFrameTime()
{
    m_currentFrameTime = GetAppMilliseconds();
    return m_currentFrameTime;
}

Uint64 sail::Timer::GetDeltaTime()
{
    m_deltaTime = m_currentFrameTime - m_lastFrameTime;

    return m_deltaTime;
}

float sail::Timer::GetDeltaSeconds() const
{
    return m_deltaTime / 1000.0f;
}

Timer::Timer()
{

}

Timer::~Timer()
{

}