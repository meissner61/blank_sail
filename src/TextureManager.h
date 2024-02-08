
#pragma once

#include "SDL.h"

#include <string>
#include <unordered_map>
#include <unordered_set>


/*
    USAGE:
        In your Setup() or Init() function:
            sail::TextureManager::GetInstance().LoadTexture("../data/ogre.png"); -- the id for the Draw texture gets cut from the filename path
        In your render loop:
            sail::TextureManager::GetInstance().DrawTexture("ogre", 40, 40);
*/


namespace sail
{

class TextureManager
{

public:
    static TextureManager& GetInstance();
    void Init(SDL_Renderer* renderer);
    
/*
Redundancy in LoadTexture:
Consider whether you need both LoadTexture and LoadandName. 
If the only difference is naming, you might combine them into one function with a default argument 
or other means of indication.


*/
    void LoadTexture( std::string filename); //loads texture, stripped filename used as name
    SDL_Surface* LoadSurface(std::string filename);
    void LoadandName(std::string filename, std::string idName); // load texture + give it a unique name

    //TODO: think about adding if know a width and height, so that the error rect can be scaled accordingly
    void DrawTexture(const std::string& id, int x, int y, SDL_RendererFlip flip = SDL_FLIP_NONE, Uint8 alpha = 255);
    void DrawTextureF(const std::string& id, float x, float y, SDL_RendererFlip flip = SDL_FLIP_NONE, Uint8 alpha = 255);
    void DrawClip(const std::string& id, int x, int y,int w, int h, int clipX, int clipY);
    void DrawClipF(const std::string& id, float x, float y, float w, float h, int clipX, int clipY);
    void DrawFrame(const std::string& id, int x, int y, int w, int h, int frame, int row = 0, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void DrawFrameF(const std::string& id, float x, float y, float w, float h, int frame, int row = 0, SDL_RendererFlip flip = SDL_FLIP_NONE);
    //void Rotate(const std::string& id, )
    
    void UpdateTextureAlpha(const std::string& id, Uint8 alphaValue); //NOTE: Will update every instance of ID with same alpha
    SDL_Texture* GetTexture(const std::string& id);
    void GetTextureDimensions(const std::string& id);

    void HandleMissingTexture(const std::string& id, float x, float y);

//Test//


    

private:

    std::string StripFileNameExtension(std::string& fileName);

    TextureManager();
    ~TextureManager() {}

    std::unordered_map<std::string, SDL_Texture* > m_textures;

    inline static SDL_Renderer* m_renderer;

    //TODO: m_size = 0++;

};

}