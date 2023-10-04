
#include "InputManager.h"

using namespace sail;


InputManager::InputManager()
{
    m_currentKeys = SDL_GetKeyboardState(&m_keyLength);
    m_previousKeys.resize(m_keyLength);
    std::copy(m_currentKeys, m_currentKeys + m_keyLength, m_previousKeys.begin());
    //m_currentKeys = SDL_GetKeyboardState(NULL);

    SDL_GetMouseState(&mouseX, &mouseY);

}

InputManager& InputManager::GetInstance()
{
    static InputManager instance;

    return instance;
}

void InputManager::Update()
{
     std::copy(m_currentKeys, m_currentKeys + m_keyLength, m_previousKeys.begin());

    m_currentKeys = SDL_GetKeyboardState(NULL);
    SDL_GetMouseState(&mouseX, &mouseY);
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