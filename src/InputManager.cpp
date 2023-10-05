
#include "InputManager.h"

//#include "imgui.h"

#include <iostream>

using namespace sail;


InputManager::InputManager()
{
    m_currentKeys = SDL_GetKeyboardState(&m_keyLength);
    m_previousKeys.resize(m_keyLength);
    std::copy(m_currentKeys, m_currentKeys + m_keyLength, m_previousKeys.begin());
    //m_currentKeys = SDL_GetKeyboardState(NULL);

    SDL_GetMouseState(&mousePos.x, &mousePos.y);

    //

}

InputManager& InputManager::GetInstance()
{
    static InputManager instance;

    return instance;
}

void InputManager::Update(SDL_Event& e)
{
    

    std::copy(m_currentKeys, m_currentKeys + m_keyLength, m_previousKeys.begin());

    m_currentKeys = SDL_GetKeyboardState(NULL);
    m_mouseState = SDL_GetMouseState(&mousePos.x, &mousePos.y);

    //std::copy(std::begin(m_mouseButtonState), std::end(m_mouseButtonState), std::begin(m_PreviousMouseButtonState));
    if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button)
    {
        m_mouseButtonState[e.button.button] = true;
    }
    else if(e.type == SDL_MOUSEBUTTONUP && e.button.button)
    {
        m_mouseButtonState[e.button.button] = false;
    }

    
}


bool InputManager::IsKeyPressed(SDL_Scancode key) const
{
    return m_currentKeys[key] && !m_previousKeys[key];
}

bool InputManager::IsKeyDown(SDL_Scancode key) const
{
    return m_currentKeys[key];
}

bool InputManager::IsKeyReleased(SDL_Scancode key) const
{
    return !m_currentKeys[key] && m_previousKeys[key];
}

// bool sail::InputManager::IsMousePressed(SDL_Scancode key) const
// {
//     std::cout << "Buttonpress!!!\n";
//     return m_mouseState & SDL_BUTTON(SDL_BUTTON_LEFT);
// }

// bool sail::InputManager::IsMouseDown(SDL_Scancode key) const
// {
//     return false;
// }

// bool sail::InputManager::IsMouseReleased(SDL_Scancode key) const
// {
//     return false;
// }

glm::ivec2 sail::InputManager::GetMousePos()
{
    return mousePos;
}

bool sail::InputManager::IsMouseLeftDown()
{
    m_mouseState = SDL_GetMouseState(&mousePos.x, &mousePos.y);
    if((m_mouseState & SDL_BUTTON_LMASK) != 0)
    {
        return true;
    }
    return false;
}

bool sail::InputManager::IsMousePressed(int button)
{
    return m_mouseButtonState[button] && !m_PreviousMouseButtonState[button];
    //return m_mouseButtonState[button];
}

bool sail::InputManager::IsMouseReleased(int button)
{
    return !m_mouseButtonState[button] && m_PreviousMouseButtonState[button];
}

void sail::InputManager::PostUpdate()
{

    std::copy(std::begin(m_mouseButtonState), std::end(m_mouseButtonState), std::begin(m_PreviousMouseButtonState));

    // for(int i = 0; i < MOUSE_BUTTON_MAX; i++)
    // {
    //     m_PreviousMouseButtonState[i] = m_mouseButtonState[i];
    // }
}
