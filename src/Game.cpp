
#include "Game.h"
//#include "Shapes.h"
#include "ShapeManager.h"
#include "TextureManager.h"
#include "Timer.h"
#include "InputManager.h"
#include "GlyphManager.h"


#include <algorithm>
#include <iostream>
#include "Util.h"


Game::Game()
{
    
}

void Game::Init()
{
if( SDL_Init(SDL_INIT_EVERYTHING) != 0 )
    {
        SDL_Log( "SDL_Init() Failed! SDL_Error: %s\n", SDL_GetError() );
        return; 
    }

    //!TODO!: allow setting of window width and height through constructor of window class
    m_windowWidth = 800;
    m_windowHeight = 600;

        // https://wiki.libsdl.org/SDL_CreateWindow
    m_window = SDL_CreateWindow("Window Test Tittle", 
                                100, 
                                100, 
                                m_windowWidth, 
                                m_windowHeight, 
                                SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    if(m_window == NULL)
    {
        SDL_Log("SDL_Window() Failed! SDL_Error: %s\n", SDL_GetError());
        return;
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
    if(m_renderer == NULL)
    {
        SDL_Log("SDL_Renderer() Failed! SDL_Error: %s\n", SDL_GetError());
        return;
    }

    //init the shapeManager with the renderer
    sail::ShapeManager::GetInstance().Init(m_renderer);

    secondsSinceStart = 1;

    m_active = true;

}


void Game::Setup()
{ 

    frames = 0;

    sail::Timer::Instance().GetLastFrameTime();

    m_output = new int[m_windowWidth * m_windowHeight];
    m_state = new int[m_windowWidth * m_windowHeight];

    memset(m_output, 0, m_windowWidth * m_windowHeight * sizeof(int));
    memset(m_state, 0, m_windowWidth * m_windowHeight * sizeof(int));

    //randomly set each state to true or false

    srand(time(NULL));
    for(int i = 1; i < m_windowWidth * m_windowHeight - 1; i++)
    {
        m_state[i] = rand() % 2;
    }

    //auto set = [&](int x, int y, )
}

void Game::Run()
{

    Init();
    Setup();

    while(m_active)
    {
        Input();
        Update();
        Render();
    }
}

void Game::Input()
{
    SDL_PumpEvents(); // TODO: possibly un-needed

    SDL_Event sdlEvent;

    //SDL_Delay(25); //~ 30 fps when vsynced to 60 hz

// For the Confused:
    sail::Timer::Instance().GetCurrentFrameTime(); //current frame time done here
    sail::Timer::Instance().GetDeltaTime(); //calculation done here with currentTime - lastTime
///---------------------------------------------------------------------///
    sail::Timer::Instance().GetLastFrameTime(); //whatever is received here will be used in the next iteration of the loop




    while(SDL_PollEvent(&sdlEvent))
    {
        sail::InputManager::GetInstance().Update(sdlEvent);
        if(sdlEvent.type == SDL_QUIT)
        {
            m_active = false;
        }

        if(sdlEvent.type == SDL_WINDOWEVENT)
        {
            if(sdlEvent.window.event == SDL_WINDOWEVENT_FOCUS_LOST)
            {
                SDL_Log("Window Focus Loss!");
            }
        }

      
        if(sdlEvent.type == SDL_KEYDOWN)
        {
            switch (sdlEvent.key.keysym.sym)
            {
                
            }
        }


    }




}

void Game::Update()
{
    SDL_Delay(50);

    
}

void Game::Render()
{
    //Set background color and clear the renderer
    //SDL_SetRenderDrawColor(m_renderer, 50, 50, 50, 255);
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);

    //lambda function
    auto cell = [&](int x, int y)
    {
        return m_output[ y * m_windowWidth + x];
    };

    //store output state
    for(int i = 0; i < m_windowWidth * m_windowHeight; i++)
    {
        m_output[i] = m_state[i];
    }

    for(int x = 1; x < m_windowWidth - 1; x++)
    {
        for(int y = 1; y < m_windowHeight - 1; y++)
        {
            int neighbors = cell(x - 1, y - 1) + cell(x - 0, y - 1) + cell(x + 1, y - 1) + 
                            cell(x - 1, y + 0) +        0           + cell(x + 1, y + 0) + 
                            cell(x - 1, y + 1) + cell(x + 0, y + 1) + cell(x + 1, y + 1);

            if(cell(x,y) == 1)
            {
                m_state[y * m_windowWidth + x] = neighbors == 2 || neighbors == 3;
            }
            else
            {
                m_state[y * m_windowWidth + x] = neighbors == 3;
            }

            if(cell(x,y) == 1)
            {
                sail::ShapeManager::GetInstance().DrawRect(x, y, 1, 1, {255, 255, 255, 255});
            }
            else
            {
                sail::ShapeManager::GetInstance().DrawRect(x, y, 1, 1, {0, 0, 0, 255});
            }
        }
    }
  

    sail::InputManager::GetInstance().PostUpdate();
    //Stop Drawing stuff here and present 
    SDL_RenderSetScale(m_renderer, zoomScale, zoomScale);
    //SDL_RenderSetViewport(m_renderer, &viewport);
    SDL_RenderPresent(m_renderer);
    
}

void Game::calculateFPS()
{
    frames++;                                                                                                                                                                          
    //FPS = frames / secondsSinceStart;
    
    if (currentTime > lastTime + 1000) //once per second
    {
        std::string strFPS;
        strFPS = std::to_string(frames);
        std::string titleFPS = "FPS: ";
        titleFPS += strFPS;
        SetWindowTitle(titleFPS.c_str());
        frames = 0;
        lastTime = currentTime;
    }

}

void Game::TimeUpdates()
{
    currentTime = SDL_GetTicks();
    secondsSinceStart = currentTime / 1000;
}

void Game::SetWindowTitle(const char* newTitle)
{ 
    SDL_SetWindowTitle(m_window, newTitle);
}

SDL_Renderer* Game::GetRenderer()
{
    return m_renderer;
}

Game::~Game()
{

}
