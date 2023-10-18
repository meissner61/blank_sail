#pragma once

#include <vector>

#include "SDL.h"
#include "extern/glm/vec2.hpp"

namespace sail
{

class InputManager
{

public:

    static InputManager& GetInstance();

    InputManager(InputManager const&) = delete;
    void operator=(InputManager const&) = delete;

    void Update(SDL_Event& e);

    //TODO: Not yet implemented or working, might have to do same logic as mouse press in the PostUpdate()
    bool IsKeyPressed(SDL_Scancode key) const;
    bool IsKeyDown(SDL_Scancode key) const;
    bool IsKeyReleased(SDL_Scancode key) const;


    // bool IsMousePressed(SDL_BUTTON_LEFT) const;
    // bool IsMouseDown(SDL_Scancode key) const;
    // bool IsMouseReleased(SDL_Scancode key) const;

    glm::ivec2 GetMousePos();
    
    //TODO: This is just for now, i think i want to handle mouse input with SDL_Events, not mouse state//NOTE: Done Below
    bool IsMouseLeftDown();

    bool IsMousePressed(int button);
    bool IsMouseReleased(int button);

    //NOTE: This needs to be at the end of the game loop (or update loop) To reset the state, otherwise events will keep firing
    void PostUpdate();


    

    glm::ivec2 mousePos;
    // inline static int mouseX;
    // inline static int mouseY;
    
private:

    const Uint8* m_currentKeys;
    std::vector<Uint8> m_previousKeys;
    int m_keyLength;
    Uint32 m_mouseState;

    static constexpr int MOUSE_BUTTON_MAX = 4;
    
    bool m_mouseButtonState[MOUSE_BUTTON_MAX]; //0 for unused, 1, for left, 2 for middle, 3 for right
    bool m_PreviousMouseButtonState[MOUSE_BUTTON_MAX]; //TODO: To be implemented with IsMouseDown();


    InputManager();
    ~InputManager() = default;


};


};