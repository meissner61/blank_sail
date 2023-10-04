
#pragma once

#include "SDL.h"

class Shapes
{
public:
    Shapes(); //Make Sure you use SetRenderer() if using this constructor.
    Shapes(SDL_Renderer* renderer);
    ~Shapes();

    void SetRenderer(SDL_Renderer* renderer);

    void DrawRect(int x, int y, int width, int height);
    void DrawCircle(int centerX, int centerY, int radius);

private:
    SDL_Renderer* m_renderer;

};