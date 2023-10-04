#pragma once

#include <vector>

#include "SDL.h"


namespace sail
{

class InputManager
{

public:

    static InputManager& GetInstance();

    InputManager(InputManager const&) = delete;
    void operator=(InputManager const&) = delete;

    void Update();

    bool IsKeyPressed(SDL_Scancode key) const;
    bool IsKeyDown(SDL_Scancode key) const;
    bool IsKeyReleased(SDL_Scancode key) const;

    
    inline static int mouseX;
    inline static int mouseY;
    
private:

    const Uint8* m_currentKeys;
    std::vector<Uint8> m_previousKeys;
    int m_keyLength;



    InputManager();
    ~InputManager() = default;


};


}