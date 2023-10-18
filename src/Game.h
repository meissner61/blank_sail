
#pragma once

#include "SDL.h"
 
#include <string>
#include <vector>

#include "Shapes.h"
// #include "Camera.h"


#include "Boat.h"

struct sPoint2D
{
    float x;
    float y;
};

struct sSpline //Catmull-Rom spline
{
    std::vector<sPoint2D> points;

    sPoint2D GetSplinePoint(float t)
    {
        int p0, p1, p2, p3;
        p1 = (int)t + 1;
        p2 = p1 + 1;
        p3 = p2 + 1;
        p0 = p1 - 1;

        t = t - (int)t;

        float tt = t * t;
        float ttt = tt * t;

        float q1 = -ttt + 2.0f*tt - t;
        float q2 = 3.0f * ttt - 5.0f * tt + 2.0f;
        float q3 = -3.0f * ttt + 4.0f * tt + t;
        float q4 = ttt - tt;

        float tx = 0.5 * (points[p0].x * q1 + points[p1].x * q2 + points[p2].x * q3 + points[p3].x * q4);
        float ty = 0.5 * (points[p0].y * q1 + points[p1].y * q2 + points[p2].y * q3 + points[p3].y * q4);


        return {tx,ty};//return {tx,ty};
    }
};

class Game
{

public:

    //static Game& Instance();

    void Init();    //SDL Specific initializations
    void Setup();   //Game class setup, map, characters ...e.t.c
    void Run();     // TODO: Runs the Input(), Update(), Render() functions in a loop not yet employed

    void Input();
    void Update();
    void Render();

    void calculateFPS(); //TODO: Remove and use sail::Util::CalculateFPS

    void TimeUpdates(); //TODO: Remove and use sail::Util::CalculateFPS

    void SetWindowTitle(const char* newTitle);
    

    SDL_Renderer* GetRenderer();



    bool m_active; 

    Shapes shape;

    Game();
    ~Game();


private:

    int m_windowWidth = 800;
    int m_windowHeight = 600;

    SDL_Window* m_window = nullptr;
    SDL_Renderer* m_renderer = nullptr;

    int mouseX = 0;
    int mouseY = 0;

    int pointWidth = 9;

    
    //Private Repo Test

    ////Timers, frames, e.t.c////
    uint64_t frames = 0;
    Uint32 startTime = 0;
    int FPS = 60;
    double secondsSinceStart = 0;
    uint32_t currentTime = 0;
    uint32_t lastTime = 0;


    sSpline path;
    

    float zoomScale = 1.0f;

};