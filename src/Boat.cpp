
#include "Boat.h"
#include "Timer.h"
#include "ShapeManager.h"
#include "GlyphManager.h"

#include <iostream>
#include <cmath>
#include <math.h>

#define deltaTime sail::Timer::Instance().GetDeltaSeconds();

using std::round;



Boat::Boat(float X, float Y)
{

    m_lastDirection = "SW";
    x = X;
    y = Y;

    m_width = 112;
    m_height = 112;

// x pixel position of the texture, y = 0
    m_dir_map["N"] = 0;
    m_dir_map["W"] = 672;
    m_dir_map["S"] = 448;
    m_dir_map["E"] = 224;
    m_dir_map["NW"] = 784;
    m_dir_map["NE"] = 112;
    m_dir_map["SW"] = 560;
    m_dir_map["SE"] = 336;


//  Boat Objects center defined for each rotating texture
//X = m_dir_map + m_directionCenter[].first, Y = 0 + m_directionCenter[].second
    m_directionCenter["N"].first    = 59.0f,   m_directionCenter["N"].second    = 59.0f;
    m_directionCenter["W"].first    = 52.0f,    m_directionCenter["W"].second   = 72.0f;
    m_directionCenter["S"].first    = 52.0f,    m_directionCenter["S"].second   = 70.0f;
    m_directionCenter["E"].first    = 59.0f,    m_directionCenter["E"].second   = 70.0f;
    m_directionCenter["NW"].first   = 52.0f,    m_directionCenter["NW"].second  = 65.0f;
    m_directionCenter["NE"].first   = 66.0f,    m_directionCenter["NE"].second  = 63.0f;
    m_directionCenter["SW"].first   = 64.0f,    m_directionCenter["SW"].second  = 74.0f;
    m_directionCenter["SE"].first   = 60.0f,    m_directionCenter["SE"].second  = 69.0f;


}

/*
    TODO: NOTE:
        Originally when you had the if statements set as follows:
        if(W)
        if(A)
        if(S)
        if(D)

        I was getting some bug that when S + W were getting activated together it was producing WS, even when it was S + W or W + S it always made WS
        Thus that was not one of the directions from the map and the rendering would always mess up.
        This sounds like something subtle that might come back to bite me later, this note is for that
*/

void Boat::Input()
{
    
    m_direction.clear();

        if(sail::InputManager::GetInstance().IsKeyDown(SDL_SCANCODE_S))
        {
            m_direction += "S";
            y += speed* deltaTime;
        } 
        if(sail::InputManager::GetInstance().IsKeyDown(SDL_SCANCODE_W))
        {
            m_direction += "N";
            y -= speed * deltaTime;
        }
        if(sail::InputManager::GetInstance().IsKeyDown(SDL_SCANCODE_A))
        {
            m_direction += "W";
            x -= speed * deltaTime;
        }
        if(sail::InputManager::GetInstance().IsKeyDown(SDL_SCANCODE_D))
        {
            m_direction += "E";
            x += speed* deltaTime;
        }

        if(!m_direction.empty())
        {
            m_lastDirection = m_direction;
        }

        // if(m_direction == "SW" && (sail::InputManager::GetInstance().IsKeyReleased(SDL_SCANCODE_D) || sail::InputManager::GetInstance().IsKeyReleased(SDL_SCANCODE_S)))
        // {
        //     m_lastDirection = "SW";
        // }
        
}


//Boat rotation, cant decide if i want it yet or not: place into SDL_RenderCopyExf()
//std::sin((sail::Timer::Instance().GetAppMilliseconds()/500.0)) * 2.0
void Boat::Render()
{   
    Uint64 ms = sail::Timer::Instance().GetAppMilliseconds();

    //sail::TextureManager::GetInstance().DrawClipF("korl", x, y ,m_width,m_height, m_dir_map[m_lastDirection], 0);
    //sail::TextureManager::GetInstance().DrawClip("korl", int(round(x - m_directionCenter[m_lastDirection].first)), int(round( y - m_directionCenter[m_lastDirection].first)) ,m_width,m_height, m_dir_map[m_lastDirection], 0);
    sail::TextureManager::GetInstance().DrawClipF("korl", (x - m_directionCenter[m_lastDirection].first), ( (y - m_directionCenter[m_lastDirection].first + 3.0f * float(std::sin(float(ms)/300)))) , float(m_width), float(m_height), m_dir_map[m_lastDirection], 0);
    sail::TextureManager::GetInstance().DrawTextureF("orc_fighter", x, std::sin(float(ms)/500) + y);

    
    //sail::ShapeManager::GetInstance().DrawRect(int(round(x - m_directionCenter[m_lastDirection].first)), int(round( (y - m_directionCenter[m_lastDirection].first)) + 90), 200, 50, {0, 200, 200});
    sail::TextureManager::GetInstance().DrawTextureF("korl_E_water",x-33, y+ 13);
    sail::ShapeManager::GetInstance().DrawMarkF(x , y, 5 );

   // GlyphManager::GetInstace().DrawReal(x , y+50, x);

    GlyphManager::GetInstace().Draw2F(int(x), int(y+50), x, y);

}










///////////////////////////////////////////////////////////////////////////////////////
/////////////////////////Good Visualizaytion test code////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/*
    If you ever need to see how "off centered an image is" in relation to its other clipped textures 
    use the following code below:

    Basically always draw one texture in the render function.

    and then in the input function draw the different rotations above it, makes it easy to see if something
    is badly centered

*/

// void Boat::Input()
// {
//         if(sail::InputManager::GetInstance().IsKeyDown(SDL_SCANCODE_D))
//         {
//             x += speed;
//             sail::TextureManager::GetInstance().DrawClip("korl", x, y,96,96, 192, 0);
//         }
//         if(sail::InputManager::GetInstance().IsKeyDown(SDL_SCANCODE_A))
//         {
//             x -= speed;
//             sail::TextureManager::GetInstance().DrawClip("korl", x, y,96,96, 576, 0);
//         }
//         if(sail::InputManager::GetInstance().IsKeyDown(SDL_SCANCODE_W))
//         {
//             y -= speed;
//             sail::TextureManager::GetInstance().DrawClip("korl", x, y,96,96, 0, 0);
//         }
//         if(sail::InputManager::GetInstance().IsKeyDown(SDL_SCANCODE_S))
//         {
//             y += speed;
//             sail::TextureManager::GetInstance().DrawClip("korl", x, y,96,96, 384, 0);
//         }
// }

// void Boat::Render()
// {
//     //sail::TextureManager::GetInstance().DrawTexture("korl_SW",x,y);
//     sail::TextureManager::GetInstance().DrawClip("korl", x, y,96,96, 192, 0);
// }





    //     m_width = 96;
    // m_height = 96;

    // m_dir_map["N"] = 0;
    // m_dir_map["W"] = 576;
    // m_dir_map["S"] = 384;
    // m_dir_map["E"] = 192;
    // m_dir_map["NW"] = 672;
    // m_dir_map["NE"] = 96;
    // m_dir_map["SW"] = 480;
    // m_dir_map["SE"] = 288;