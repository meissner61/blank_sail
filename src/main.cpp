
#include <iostream>
#include <algorithm>

//#include "Game.h"
#include "Util.h"
#include "extern/glm/vec2.hpp"
#include "Random.h"

#include "SDL.h"

#ifdef _WIN32
#define NOMINMAX //for <limits> macro inside windows.h conflicts with this header
#include <windows.h>
#endif

#include <string>

#include <limits>
#include <iomanip>

bool InitSDL(SDL_Window** window, SDL_Renderer** renderer) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }
    *window = SDL_CreateWindow("Screen Wrapping", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    if (*window == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }
    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if (*renderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }
    SDL_SetRenderDrawColor(*renderer, 255, 255, 255, 255); // Set background color
    return true;
}



int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;

    #ifdef _WIN32 //set console position to top left corner
        HWND consoleWindow = GetConsoleWindow();
        SetWindowPos(consoleWindow, 0, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
    #endif

    if constexpr(sizeof(void*) == 8) //constexpr == solution for warning C4127: conditional expression is constant c++17
    {
        std::cout << "64-bit architecture..\n";
    }
    else if constexpr(sizeof(void*) == 4)
    {
        std::cout << "32-bit architecture..\n";
    }
    //__debugbreak();

    sail::Util::FindRootEnginePath();

    sail::Util::DisaplyProjectRootPath();


    if(sail::Util::root_path.empty()) //TODO: FIX This, not working properly. add a root_path_name for a stemmed version of root path and check against engine_name
    {
        std::cout << "WARNING! no project path set. Possible errors upon loading data!\n";
        std::cout << "See Util.h -> root_path\n";
    }


    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    if (!InitSDL(&window, &renderer)) {
        std::cerr << "Failed to initialize!" << std::endl;
        return -1;
    }

    
    

    

    // Game game;

    // game.Run();

    return 0;
}