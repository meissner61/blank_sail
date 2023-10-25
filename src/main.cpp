
#include <iostream>
#include <algorithm>

#include "Game.h"
#include "Util.h"
#include "extern/glm/vec2.hpp"
#include "Random.h"

#ifdef _WIN32
#define NOMINMAX //for <limits> macro inside windows.h conflicts with this header
#include <windows.h>
#endif

#include <string>

#include <limits>
#include <iomanip>


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


    sail::Util::FindRootEnginePath();

    sail::Util::DisaplyProjectRootPath();


    if(sail::Util::root_path.empty()) //TODO: FIX This, not working properly. add a root_path_name for a stemmed version of root path and check against engine_name
    {
        std::cout << "WARNING! no project path set. Possible errors upon loading data!\n";
        std::cout << "See Util.h -> root_path\n";
    }


    
    

    

    Game game;

    game.Run();

    return 0;
}