#pragma once


#include "SDL.h"

#include <string>

/*
    TODO:
        when attempting to use DrawTexture with the polyducks.png which is 8BPP (Grayscale?) TextureManager had some failure or corruption of image data.
        Check into this at some point
*/

class GlyphManager
{

public:
    static GlyphManager& GetInstace();
    void Init(SDL_Renderer* renderer, SDL_Texture* fontAtlas = nullptr); //TODO: Need to ensure after Init, that SetFontTexture is called
    void SetFontTexture(SDL_Texture* fontAtlas, int width, int height);

    void DrawString(int x, int y, std::string text); 
    void DrawChar(int x, int y, char c);
    void DrawInt(int x, int y, long long int i);
    void DrawReal(int x, int y, float i); //TODO: just float for now.Will need to update to take both float and double
    void Draw2F(int x, int y, float a, float b);
    //void RenderIn

private:
    GlyphManager();
    ~GlyphManager() {};

    SDL_Texture* m_texture;
    SDL_Renderer* m_renderer;

    int m_textureWidth;
    int m_textureHeight;
    int m_charWidth;
    int m_charHeight;
    

};