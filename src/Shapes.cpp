

#include "Shapes.h"

Shapes::Shapes()

{

}

Shapes::~Shapes()
{

}

void Shapes::DrawRect(int x, int y, int width, int height)
{
    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
    SDL_Rect rect = {x, y, width, height};
    SDL_RenderDrawRect(m_renderer, &rect);
}

void Shapes::SetRenderer(SDL_Renderer* renderer)
{
    m_renderer = renderer;
}