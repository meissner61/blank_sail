#pragma once


#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "Timer.h"

/*
    All animation resources are loaded through the TextureManager


    What do we need?
    -animation name
    -num of frames
    -frame
    -Gets created in the Object / Entity class
    -Assume on the sprite atlas each animation is the same width and height, only thing that changes is the row and total frames
    -Assume once a texture is loaded all the animation on it are the same width and height, example "idle" m_width = 37, m_height = 32. "attack" m_width = 37, m_height = 32;
    -This does not mean that every animation has to be the same width and height, just a dragon "idle" can have m_width = 150, m_height = 100 but dragon "attack" also needs to be 150 and 100
    -EXAMPLE: 
            {
            "skelly_full" -- texture ID - should be passed in from the entity object
            "idle"          --animation name
            11              --# of frames (for this specific animation name)
            0               --row #
            }
    TODO:DONE!Current the animation frame of whatever you are playing starts dependant on the Timer::Getmilliseconds -DONE!
        -I need it to always start at frame 0, and then 

    TODO: Need to add some additional animation info for specific animations like "attack" which might have properties like: 
    -untill what frame can i cancel the attack,
    -which frame does the damage part of the attack actually start, and untill which frame must it reach for attack to register.
    -if above detail is not provided perhaps default to just "on What frame does the attack hit"
    -which frames are you allowed to cancel with movement or which frames do you have to commit to and finish
    -Also "attack" should be pllayed out until movement cancels or animation finishes with only buttonPress not require buttonHold

*/


class Animation
{

    struct AnimationInfo
    {
        //std::string textureID
        std::string animationName;
        int frameCount;
        int row;
    };

public:
    Animation(); //TODO: I would like to throw an ERROR or log warning if Animation has not been properly constructed
    Animation(AnimationInfo info, float frameWidth, float frameHeight, int speed );
    ~Animation();

    void Update(std::string name);

    void AddAnimation(AnimationInfo info);

    void Play(std::string name, float x, float y, SDL_RendererFlip flip = SDL_FLIP_NONE);


private:


    //std::string m_animationName;
    std::unordered_set<std::string> m_animationNames;

    int m_frame;
    float m_width;
    float m_height;
    int m_speed;

    Uint64 m_lastStartTime;
    std::string m_currentAnimation;

    std::unordered_map<std::string, AnimationInfo> m_animations;

    
};