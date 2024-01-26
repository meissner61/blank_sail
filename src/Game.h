
#pragma once

#include "SDL.h"
//#include "stb_image.h"
 
#include <string>
#include <vector>

#include "Shapes.h"
// #include "Camera.h"
#include "Ent.h"

//#include "Boat.h"

#include "TextureMangr.h"

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
    

    SDL_Renderer* GetRenderer();

    bool m_active; 



    Game();
    ~Game();


private:

    int m_windowWidth = 800;
    int m_windowHeight = 600;

    SDL_Window* m_window = nullptr;
    SDL_Renderer* m_renderer = nullptr;

    


    ////Timers, frames, e.t.c////
    uint64_t frames = 0;
    Uint32 startTime = 0;
    int FPS = 60;
    double secondsSinceStart = 0;
    uint32_t currentTime = 0;
    uint32_t lastTime = 0;

    TextureMangr txMnr;


//texture test
    SDL_Texture* ogre;
    unsigned char* ogreData = nullptr;
    int width, height, numChannels = 0;
    SDL_FRect dstRect;


    float zoomScale = 1.0f;

};