
#include "Ent.h"

#include "ShapeManager.h"
#include "InputManager.h"
#include "Timer.h"
#include "TextureManager.h"
#include "GlyphManager.h"

#include <stdlib.h>

Ent::Ent()
    //:
    //animation("idle",{11, 0}, 32, 37, 100), //animation_name, struct{frameCount, row#}, 
    // x(float(rand() % 100)),
    // y(float(rand() % 100))
{
    
    x = float(rand() % 800);
    y = float(rand() % 600);

    m_color.r = rand() % 255;
    m_color.g = rand() % 255;
    m_color.b = rand() % 255;



}

Ent::Ent(bool playerControl)
    :
    animation({"idle", 11, 0 }, 32, 37, 100), //idle = 11frames, row 0, , //walk = 13 frames , row 1, , // attack =18 frames, row 2, 
    player_controlled(playerControl)
{
    x = float(rand() % 800);
    y = float(rand() % 600);
}

Ent::~Ent()
{

}

void Ent::Draw() //TODO: Draw based on direction
{
    // static int x;
    // static int y;
    // SDL_GetMouseState(&x, &y);
    
    if(!player_controlled)
    {
        sail::ShapeManager::GetInstance().DrawRectF(x,y, 16.0f,16.0f, m_color);
    }

    if (sail::InputManager::GetInstance().IsKeyDown(SDL_SCANCODE_SPACE))
    {
        animation.Play("attack", x, y);
    }

    else
    {
        this->animation.Play("idle", x, y);
    }
    
    //sail::ShapeManager::GetInstance().DrawRectF(x,y, float(16),float(16), m_color);
    GlyphManager::GetInstace().Draw2F(int(x) - 45, int(y) +45, x, y);
    //sail::TextureManager::GetInstance().DrawTexture("ogre", x, y);
}

void Ent::Update()
{
    //auto& inputManager = sail::InputManager::GetInstance();

    if(player_controlled)
    {

        if(sail::InputManager::GetInstance().IsKeyDown(SDL_SCANCODE_RIGHT))
        {
            x += speed * sail::Timer::GetDeltaSeconds();
        }
        if(sail::InputManager::GetInstance().IsKeyDown(SDL_SCANCODE_LEFT))
        {
            x -= speed * sail::Timer::GetDeltaSeconds();
        }
        if(sail::InputManager::GetInstance().IsKeyDown(SDL_SCANCODE_UP))
        {
            y -= speed * sail::Timer::GetDeltaSeconds();
        }
        if(sail::InputManager::GetInstance().IsKeyDown(SDL_SCANCODE_DOWN))
        {
            y += speed * sail::Timer::GetDeltaSeconds();
        }



    }



}

void Ent::SetControl()
{
    player_controlled = true;
}

void Ent::RemoveControl()
{
    player_controlled = false;
}

void Ent::SetColor(SDL_Color color)
{
    m_color = color;
    //m_color.r = color.r; m_color.g = color.g; m_color.b = color.b; m_color.a = color.a;
}