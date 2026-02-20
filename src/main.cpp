// controller_info.cpp
#include <SDL.h>
#include <cstdio>
#include <string>

// Helper: get a short ID string like "045E:028E" from vendor/product
std::string VIDPID(SDL_GameController *gc)
{
    Uint16 vid = SDL_GameControllerGetVendor(gc);
    Uint16 pid = SDL_GameControllerGetProduct(gc);
    char buf[10];
    std::snprintf(buf, sizeof(buf), "%04X:%04X", vid, pid);
    return buf;
}

void listExistingControllers()
{
    int n = SDL_NumJoysticks();
    for (int i = 0; i < n; ++i)
    {
        if (!SDL_IsGameController(i))
            continue;                       // Skip unknown devices

        SDL_GameController *gc = SDL_GameControllerOpen(i);
        if (!gc)
        {
            SDL_Log("Couldnt open controller %d: %s", i, SDL_GetError());
            continue;
        }

        SDL_JoystickID id = SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(gc));
        SDL_Log("Found [%d] %s (%s)",
                id,
                SDL_GameControllerName(gc),
                VIDPID(gc).c_str());

        SDL_GameControllerClose(gc);        // Just probing – close it again
    }
}

int main(int argc, char **argv)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) != 0)
    {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return 1;
    }

    SDL_ControllerButtonEvent controller;

    if(controller.button == SDL_CONTROLLER_BUTTON_X)
    {
        puts("X!!!");
    }


    SDL_Log("Press ESC to quit.");
    listExistingControllers();

    bool running = true;
    while (running)
    {
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            if(e.type == SDL_KEYDOWN)
            {
                switch (e.key.keysym.sym)
                {
                    case SDLK_i:
                    {
                        puts("i key pressed");
                    }
                }
            }

            switch (e.type)
            {
                case SDL_QUIT:
                    running = false;
                    break;

                case SDL_KEYDOWN:
                {
                    if (e.key.keysym.sym == SDLK_k)
                    {
                        puts("k key pressed");
                    }
                        
                    break;
                }
                

                case SDL_CONTROLLER_BUTTON_X :
                {
                    if(e.cbutton.button == SDL_CONTROLLER_BUTTON_X)
                    {
                        puts("Controller right axxis");
                    }
                    float rightx = 0;
                    
                    break;
                }

                case SDL_JOYAXISMOTION:
                {
                    puts("Joy axis motion");
                }

                // A new device appeared (plug‑in)
                case SDL_CONTROLLERDEVICEADDED:
                {
                    int devIndex = e.cdevice.which;            // index in current list
                    SDL_GameController *gc = SDL_GameControllerOpen(devIndex);
                    if (!gc)
                    {
                        SDL_Log("Couldn’t open new controller: %s", SDL_GetError());
                        break;
                    }
                    SDL_JoystickID id = SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(gc));
                    SDL_Log(">> Attached [%d] %s (%s)",
                            id,
                            SDL_GameControllerName(gc),
                            VIDPID(gc).c_str());
                    // Keep it open so we can read later, or close immediately:
                    SDL_GameControllerClose(gc);
                    break;
                }

                // Device removed (unplug)
                case SDL_CONTROLLERDEVICEREMOVED:
                {
                    SDL_JoystickID id = e.cdevice.which;
                    SDL_Log("<< Removed  [%d]", id);
                    break;
                }
            }
        }
        SDL_Delay(10);   // Tiny sleep so we’re not 100 % CPU
    }

    SDL_Quit();
    return 0;
}
