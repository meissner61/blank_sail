#pragma once

#include <vector>
#include <string>

#include "SDL.h"

class TextureMangr
{

public:
    TextureMangr()
    {

    }
    ~TextureMangr()
    {

    }
    void LoadTexture(std::string filepath, SDL_Renderer* renderer);
    void DrawTexture(SDL_Renderer* renderer, int index, int x, int y, SDL_RendererFlip flip = SDL_FLIP_NONE, Uint8 alpha = 255);



private:

std::vector<SDL_Texture*> m_textures;


};

