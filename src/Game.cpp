
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



    sail::ShapeManager::GetInstance().Init(m_renderer);

    secondsSinceStart = 1;

    //windowSurface = SDL_GetWindowSurface(m_window);

    m_active = true;

}


void Game::Setup()
{ 

    frames = 0;

    loadedSurface = sail::TextureManager::GetInstance().LoadSurface("C:/devop/blank_sail/data/ogre.png");

    SDL_Point whitePixel = findWhitePixel(loadedSurface);

    obj1attaX = whitePixel.x;
    obj1attaY = whitePixel.y;

    std::cout << "\n\n-----White pixel found at, (X: "<<whitePixel.x << " Y: " << whitePixel.y << "), Of the image coordinate-----\n\n" << std::endl;

    texture = SDL_CreateTextureFromSurface(m_renderer, loadedSurface);

    loadedSurface2 = sail::TextureManager::GetInstance().LoadSurface("C:/devop/blank_sail/data/helm.png");
    SDL_Point whitePixel2 = findWhitePixel(loadedSurface2);

    obj2attaX = whitePixel2.x;
    obj2attaY = whitePixel2.y;

    std::cout << "\n\n--second White pixel found at, (X: "<<whitePixel2.x << " Y: " << whitePixel2.y << "), Of the image coordinate--\n\n" << std::endl;

    texture2 = SDL_CreateTextureFromSurface(m_renderer, loadedSurface2);

    obj2X = (obj1X) - (obj2attaX - obj1attaX);

    obj2Y = (obj1Y) - (obj2attaY - obj1attaY);

//    obj2X = obj1X;
//    obj2Y = obj1Y;


    //sail::Timer::Instance().GetLastFrameTime();
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

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// For the Confused:
    sail::Timer::GetCurrentFrameTime(); //current frame time done here
    sail::Timer::GetDeltaTime(); //calculation done here with currentTime - lastTime
///---------------------------------------------------------------------///
    sail::Timer::GetLastFrameTime(); //whatever is received here will be used in the next iteration of the loop

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



    while(SDL_PollEvent(&sdlEvent))
    {
        sail::InputManager::GetInstance().Update(sdlEvent);
        if(sdlEvent.type == SDL_QUIT)
        {
            m_active = false;
        }

        PrintWindowEvents(&sdlEvent);

        if(sdlEvent.type == SDL_WINDOWEVENT)
        {
            if(sdlEvent.window.event == SDL_WINDOWEVENT_FOCUS_LOST)
            {
                SDL_Log("Window Focus Loss!");
            }
            if(sdlEvent.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) //SDL_WINDOWEVENT_RESIZED (gets called twice) //SDL_WINDOWEVENT_SIZE_CHANGED
            {
                SDL_Log("Window Resized!");
                SDL_GetWindowSize(m_window, &m_windowWidth, &m_windowHeight);
                std::cout << "Window Width: " << m_windowWidth << std::endl;
                std::cout << "Window Height: " << m_windowHeight << std::endl;

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
    //SDL_Delay(1);

    
}

void Game::Render()
{
    //Set background color and clear the renderer
    //SDL_SetRenderDrawColor(m_renderer, 50, 50, 50, 255);
    SDL_SetRenderDrawColor(m_renderer, 99, 155, 255, 255);
    SDL_RenderClear(m_renderer);

    //sail::ShapeManager::GetInstance().DrawCircleTest(100,100,16);

    // SDL_FillRect(windowSurface, NULL, SDL_MapRGB(windowSurface->format, 255, 255, 255));

    // SDL_BlitSurface(loadedSurface, NULL, windowSurface, NULL);

    SDL_Rect txRect = {obj1X,obj1Y,0,0};

    SDL_QueryTexture(texture, NULL, NULL, &txRect.w, &txRect.h);

    SDL_RenderCopy(m_renderer, texture, NULL,&txRect);

    SDL_Rect txRect2 = {obj2X, obj2Y, 0,0};

    SDL_QueryTexture(texture2, NULL, NULL, &txRect2.w, &txRect2.h);

    SDL_RenderCopy(m_renderer, texture2, NULL,&txRect2);
    

    //////sail::InputManager::GetInstance().PostUpdate();
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

void Game::PrintWindowEvents(const SDL_Event *event)
{

    //see more here:
    //https://wiki.libsdl.org/SDL2/SDL_WindowEvent
    //https://wiki.libsdl.org/SDL2/SDL_WindowEventID

    if(event->type == SDL_WINDOWEVENT)
    {
        switch (event->window.event)
        {
            case SDL_WINDOWEVENT_SHOWN:
            {
                SDL_Log("Window %d shown", event->window.windowID);
                break;
            }
            case SDL_WINDOWEVENT_HIDDEN:
            {
                SDL_Log("Window %d hidden", event->window.windowID);
                break;
            }
            case SDL_WINDOWEVENT_EXPOSED:
            {
                SDL_Log("Window %d exposed", event->window.windowID);
                break;
            }
            case SDL_WINDOWEVENT_MOVED:
            {
                SDL_Log("Window %d moved to %d,%d",
                        event->window.windowID, event->window.data1,
                        event->window.data2);
                break;
            }
            case SDL_WINDOWEVENT_RESIZED:
            {
                SDL_Log("Window %d resized to %dx%d",
                        event->window.windowID, event->window.data1,
                        event->window.data2);
                break;
            }
            case SDL_WINDOWEVENT_SIZE_CHANGED:
            {
                SDL_Log("Window %d size changed to %dx%d",
                        event->window.windowID, event->window.data1,
                        event->window.data2);
                break;
            }
            case SDL_WINDOWEVENT_MINIMIZED:
            {
                SDL_Log("Window %d minimized", event->window.windowID);
                break;
            }
            case SDL_WINDOWEVENT_MAXIMIZED:
            {
                SDL_Log("Window %d maximized", event->window.windowID);
                break;
            }
            case SDL_WINDOWEVENT_RESTORED:
            {
                SDL_Log("Window %d restored", event->window.windowID);
                break;
            }
            case SDL_WINDOWEVENT_ENTER:
            {
                SDL_Log("Mouse entered window %d",
                        event->window.windowID);
                break;
            }
            case SDL_WINDOWEVENT_LEAVE:
            {
                SDL_Log("Mouse left window %d", event->window.windowID);
                break;
            }
            case SDL_WINDOWEVENT_FOCUS_GAINED:
            {
                SDL_Log("Window %d gained keyboard focus",
                        event->window.windowID);
                break;
            }
            case SDL_WINDOWEVENT_FOCUS_LOST:
            {
                SDL_Log("Window %d lost keyboard focus",
                        event->window.windowID);
                break;
            }
            case SDL_WINDOWEVENT_CLOSE:
            {
                SDL_Log("Window %d closed", event->window.windowID);
                break;
            }

        }
    }
}

Uint32 Game::GetPixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    Uint8* p = static_cast<Uint8*>(surface->pixels) + y * surface->pitch + x * bpp;

    switch (bpp)
    {
        case 1:
        {
            return *p;
        }
        case 2:
        {
            return *reinterpret_cast<Uint16*>(p);
        }
        case 3:
        {
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            {
                return p[0] << 16 | p[1] << 8 | p[2];
            }
            else
            {
                return p[0] | p[1] << 8 | p[2] << 16;
            }
        }
        case 4:
        {
            return *reinterpret_cast<Uint32*>(p);
        }
        default:
            return 0; //shouldnt happen but avoids warnings
    }
}

SDL_Point Game::findWhitePixel(SDL_Surface *surface)
{
    SDL_Point whitePixel = {-1,-1}; //default if no white pixel found

    for(int y = 0; y < surface->h; ++y)
    {
        for(int x = 0; x < surface->w; ++x)
        {
            Uint32 pixel = GetPixel(surface, x, y);

            Uint8 r, g, b;

            SDL_GetRGB(pixel, surface->format, &r, &g, &b);

            if(r == 255 && g == 255 && b == 255)
            {
                whitePixel.x = x;
                whitePixel.y = y;
                return whitePixel;
            }
        }
    }

    return whitePixel;
}

SDL_Renderer* Game::GetRenderer()
{
    return m_renderer;
}

Game::~Game()
{

}
