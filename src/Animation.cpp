

#include "Animation.h"
#include "TextureManager.h"


/*
    struct AnimationInfo
    {
        string textureID;
        sting name
        int frameCount;
        int row;
    };

*/

Animation::Animation()
{
    //TODO: Put in some default common animation properties like 32 x 32, and 100speed
    SDL_Log("WARNING: Empty Animation constructor!\n");
    m_lastStartTime = sail::Timer::Instance().GetAppMilliseconds();

}

Animation::Animation( AnimationInfo info, float frameWidth, float frameHeight, int speed)
    :
    m_width(frameWidth),
    m_height(frameHeight),
    m_speed(speed)
{
    m_lastStartTime = sail::Timer::Instance().GetAppMilliseconds();

    m_animations[info.animationName].animationName = info.animationName;
    m_animations[info.animationName].frameCount = info.frameCount;
    m_animations[info.animationName].row = info.row;
    m_animationNames.insert(info.animationName);    
}

Animation::~Animation()
{
}

void Animation::Update(std::string name)
{

}

void Animation::AddAnimation(AnimationInfo info)
{
    m_animationNames.insert(info.animationName);

    m_animations[info.animationName].animationName = info.animationName;
    m_animations[info.animationName].frameCount = info.frameCount;
    m_animations[info.animationName].row = info.row;
}

void Animation::Play(std::string name, float x, float y, SDL_RendererFlip flip)
{
    Uint64 ms = sail::Timer::Instance().GetAppMilliseconds();

    if(m_currentAnimation != name)
    {
        m_currentAnimation = name;
        m_lastStartTime = ms;
    }

    Uint64 elapsed = ms - m_lastStartTime;

    sail::TextureManager::GetInstance().DrawFrameF("skelly_full", x, y,m_width, m_height,  (elapsed / m_speed) % m_animations[name].frameCount, m_animations[name].row, flip);

}

