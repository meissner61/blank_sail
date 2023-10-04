
#pragma once

#include <vector>

#include "SDL.h"

#include "Animation.h"
//need to implement an internal static vector so that I can always check on entities and remove and add them as necessary
//i.e death == static bottom layer object
//if they get too far away maybe copy them over to some cheaper datastructure




/*
    All resources are loaded through the TextureManager


    What do we need?
    -object  name
    - Static or Dynamic (Do we need to loop through it for correct z-order?)
    - float x, float y
    - int imgX, imgY, width, height
    - bool playerControlled
    - Tag? Name? id?
    - velocity? speed & direction, but not for everything i.e chests, boxes
*/


//Ent will be the test class for Ent

class Ent
{

public:
    Ent();
    Ent(bool playerControl);
    ~Ent();

    void Update();
    void Draw();

    void SetColor(SDL_Color color); //need SDL_Color
    void SetControl();
    void RemoveControl();

    static bool Z_order(const Ent& first, const Ent& second)
    {
        return first.y < second.y;
    }

    float x;
    float y;
    float speed = 30.0f;

public:
        Animation animation;

private:

    bool player_controlled = false;


    SDL_Color m_color;

    static std::vector<Ent> m_entities;

};