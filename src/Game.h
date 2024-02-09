
#pragma once

#include "SDL.h"
 
#include <string>
#include <vector>

#include "Shapes.h"
// #include "Camera.h"
#include "Ent.h"

#include "Boat.h"

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
    void PrintWindowEvents(const SDL_Event* event);

    Uint32 GetPixel(SDL_Surface* surface, int x, int y);
    SDL_Point findWhitePixel(SDL_Surface* surface);

    

    SDL_Renderer* GetRenderer();

    bool m_active; 



    Game();
    ~Game();


private:

    SDL_Surface* loadedSurface;

    SDL_Surface* loadedSurface2;

    SDL_Texture* texture;

    SDL_Texture* texture2;

    int m_windowWidth = 800;
    int m_windowHeight = 600;

    SDL_Window* m_window = nullptr;
    //SDL_Surface* windowSurface = nullptr;
    SDL_Renderer* m_renderer = nullptr;

    int obj1X = 200;
    int obj1Y = 300;

    int obj1attaX;
    int obj1attaY;

    int obj2X = 0;
    int obj2Y = 500;

    int obj2attaX;
    int obj2attaY;



    ////Timers, frames, e.t.c////
    uint64_t frames = 0;
    Uint32 startTime = 0;
    int FPS = 60;
    double secondsSinceStart = 0;
    uint32_t currentTime = 0;
    uint32_t lastTime = 0;




    float zoomScale = 1.0f;

};