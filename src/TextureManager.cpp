
#include "TextureManager.h"

#pragma warning(push, 0) //not recognized by GCC
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#pragma warning(pop)

#include <filesystem>
#include "Game.h"
#include <iostream>

//TODO: Just for a test remove timer
#include "Timer.h"
using namespace sail;

TextureManager::TextureManager()
{
    std::cout <<"TextureManager Constructor - m_texture size: " << m_textures.size() << "\n";
}


TextureManager& TextureManager::GetInstance()
{
    static TextureManager instance;
    return instance;
}

//  NOTE: Use Util::root_path+"/data/asset.bmp" for loading
void TextureManager::LoadTexture( std::string filename)
{   
    

    unsigned char* imageData = nullptr;
    int width, height, numChannels = 0;

    

    imageData = stbi_load(filename.c_str(), &width, &height, &numChannels, 4); //TODO: RESEARCH THIS, stbi_load(x,x,x,x,int req_comp = 0 or 4) used to be 0 which didnt work with 8BPP
    if(imageData == nullptr)
    {
        SDL_Log("stbi_load() Failed: %s\n", stbi_failure_reason());
    }


    SDL_Texture* l_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STATIC, width, height);
    if(l_texture == nullptr)
    {
        SDL_Log("Error with SDL_CreateTexture(): %s", SDL_GetError());
    }

    if (SDL_UpdateTexture(l_texture, NULL, imageData, width * sizeof(unsigned char) * 4) != 0)
    {
        SDL_Log("Error with SDL_UpdateTexture(): %s", SDL_GetError());
    }



    std::string id = StripFileNameExtension(filename);
    m_textures[id] = l_texture;
    
    SDL_SetTextureBlendMode(m_textures[id], SDL_BLENDMODE_BLEND); //TODO: stbi_load - 8BPP might have issues with this function

    stbi_image_free(imageData);

    std::cout <<"Here be the m_texture size: " << m_textures.size() << "\n";
}

SDL_Surface* sail::TextureManager::LoadSurface(std::string filename)
{
    int width, height, numChannels;
    unsigned char* imageData = stbi_load(filename.c_str(), &width, &height, &numChannels, 4); //force RGBA format

    if (imageData == nullptr)
    {
        SDL_Log("stbi_load() Failed: &s\n", stbi_failure_reason());
        return nullptr;
    }

    #if SDL_BYTEORDER == SDL_BIG_ENDIAN
        Uint32 rmask = 0xff000000;
        Uint32 gmask = 0x00ff0000;
        Uint32 bmask = 0x0000ff00;
        Uint32 amask = 0x000000ff;
    #else //little endian
        Uint32 rmask = 0x000000ff;
        Uint32 gmask = 0x0000ff00;
        Uint32 bmask = 0x00ff0000;
        Uint32 amask = 0xff000000; 
    #endif  

    SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(imageData, width, height, 32, width * 4, rmask, gmask, bmask, amask);

    if(surface == nullptr)
    {
        SDL_Log("SDL_CreateRGBSurfaceFrom() Failed: %s\n", SDL_GetError());
        stbi_image_free(imageData);
        return nullptr;
    }

        // The surface is now created, but be aware that SDL_CreateRGBSurfaceFrom() won't free the imageData when it's done.
    // You need to keep it until you are done with the surface.
    // When you're ready to release the surface (with SDL_FreeSurface()), also call stbi_image_free(imageData).

    return surface;



}

/*
NOTE:
    I want to have a method for checking whether a texture id that i am trying to draw is part of the 
    texture map, however i also dont want it to have to check through the entire list every single time 
    it tries to draw (For example if everything is fine it would still be wasting calls on checking)
    so want to have it somehow only do ONE check per unique id....
    think of solution

    Possibly keep a record if the map has grown. and then check only the latest one. One time untill again the map grows
*/



void TextureManager::DrawTexture(const std::string& id, int x, int y, SDL_RendererFlip flip, Uint8 alpha) 
{
    //map.find() is an iterator not a boolean
    //means find(id) returned an iterator pointing to a valid element in the map, signifying that the key id exists or not
    // end() == iterator pointing to the "one-past-the-end" element

    //TODO: See above NOTE: this is checking it every single time it draws it
    auto it = m_textures.find(id);

    if(it == m_textures.end())
    {
        HandleMissingTexture(id, float(x), float(y));
        return;
    }

    int width = 0;
    int height = 0;

    SDL_Texture* texture = it->second;

    SDL_QueryTexture(texture, NULL, NULL, &width, &height);
    //!TODO!: Add some error checking to make sure the texture is really here

    //SDL_Rect srcRect = {0, 0, width, height}; //only necesaary if you want to render part of a texture NULL for all
    SDL_Rect dstRect = {x, y, width, height};


    SDL_SetTextureAlphaMod(texture, alpha); //TODO: I dont expect to often need to change transparrency, this should be seperate.
    SDL_RenderCopyEx(m_renderer, texture, NULL, &dstRect, 0, NULL, flip);

}


void TextureManager::DrawClip(const std::string& id, int x, int y,int w, int h, int clipX, int clipY)
{

    auto it = m_textures.find(id);

    if(it == m_textures.end())
    {
        HandleMissingTexture(id, float(x), float(y));
        return;
    }
    
    SDL_Texture* texture = it->second;

    SDL_Rect srcRect;
    srcRect.x = clipX, srcRect.y = clipY;
    srcRect.w = w, srcRect.h = h;
    SDL_Rect dstRect;
    dstRect.x = x, dstRect.y = y;
    dstRect.w = w, dstRect.h = h;

    SDL_RenderCopy(m_renderer, texture, &srcRect, &dstRect);

    
}

void sail::TextureManager::DrawClipF(const std::string &id, float x, float y, float w, float h, int clipX, int clipY)
{
    auto it = m_textures.find(id);

    if(it == m_textures.end())
    {
        HandleMissingTexture(id, x, y);
        return;
    }
    
    SDL_Texture* texture = it->second;

    SDL_Rect srcRect;
    srcRect.x = clipX, srcRect.y = clipY;
    srcRect.w = int(w), srcRect.h = int(h);
    SDL_FRect dstRect;
    dstRect.x = x, dstRect.y = y;
    dstRect.w = w, dstRect.h = h;



    SDL_RenderCopyExF(m_renderer, texture, &srcRect, &dstRect, 0, NULL, SDL_FLIP_NONE);
}

void sail::TextureManager::DrawFrame(const std::string& id, int x, int y, int w, int h, int frame, int row, SDL_RendererFlip flip)
{


    SDL_Rect srcRect = {(frame * w), (row * h) , w, h};
    SDL_Rect dstRect = {x, y, w, h};

    SDL_RenderCopyEx(m_renderer, m_textures[id], &srcRect, &dstRect, 0, NULL, flip); 
    //SDL_RenderCopyEx(m_renderer, m_textures[id], &srcRect, &dstRect, NULL, NULL, flip);
}

void sail::TextureManager::DrawFrameF(const std::string &id, float x, float y, float w, float h, int frame, int row, SDL_RendererFlip flip)
{
    SDL_Rect srcRect = {(frame * static_cast<int>(w)), (row * static_cast<int>(h)), int(w), int(h)};
    SDL_FRect dstRect = {x, y, w, h};

    SDL_RenderCopyExF(m_renderer, m_textures[id], &srcRect, &dstRect, 0, NULL, flip); 
}

void TextureManager::UpdateTextureAlpha(const std::string& id, Uint8 alphaValue)
{
    //SDL_SetTextureBlendMode(m_textures[id], SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(m_textures[id], alphaValue);
        
}

SDL_Texture *sail::TextureManager::GetTexture(const std::string& id)
{
    return m_textures[id];
}

void sail::TextureManager::HandleMissingTexture(const std::string &id, float x, float y)
{
    static std::unordered_set<std::string> loggedTextures;

    if(loggedTextures.find(id) == loggedTextures.end())
    {
        SDL_Log("ERROR: could not find: %s", id.c_str());
        loggedTextures.insert(id);
    }

    SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);
    SDL_FRect errRect = {x, y, 100, 100};
    SDL_RenderFillRectF(m_renderer, &errRect);
}

void sail::TextureManager::DrawTextureF(const std::string &id, float x, float y, SDL_RendererFlip flip, Uint8 alpha)
{
    auto it = m_textures.find(id);

    if(it == m_textures.end())
    {
        HandleMissingTexture(id, x, y);
        return;
    }

    int width = 0;
    int height = 0;

    SDL_Texture* texture = it->second;

    SDL_QueryTexture(texture, NULL, NULL, &width, &height);
    //!TODO!: Add some error checking to make sure the texture is really here

    //SDL_Rect srcRect = {0, 0, width, height}; //only necesaary if you want to render part of a texture NULL for all
    SDL_FRect f_dstRect = {x, y, float(width), float(height)};
    //SDL_Rect dstRect = {x, y, width, height};


    SDL_SetTextureAlphaMod(texture, alpha); //TODO: I dont expect to often need to change transparrency, this should be seperate.
    SDL_RenderCopyExF(m_renderer, texture, NULL, &f_dstRect, 0, NULL, flip);
    //SDL_RenderCopyEx(m_renderer, texture, NULL, &dstRect, 0, NULL, flip);
}

std::string TextureManager::StripFileNameExtension(std::string& fileName)
{
    std::filesystem::path path(fileName);

    fileName = path.stem().u8string();

    return fileName;
}

void TextureManager::Init(SDL_Renderer* renderer)
{
    m_renderer = renderer;
}