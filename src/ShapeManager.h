
#pragma once

#include "SDL.h"


namespace sail
{
class ShapeManager
{

public:
    static ShapeManager& GetInstance(); //SHOULD be static
    bool Init(SDL_Renderer* renderer);//should not be static

    /*---Large Side Note---- regarding static DrawRect():

        ShapeManager::GetInstance().DrawRect(500,500,20,20); if not static you have to get the instance
        ShapeManager::DrawRect(500,500,20,20); if static you do not
        
    */

    static void DrawRect(int x, int y, int width, int height, SDL_Color color = {255,0,0,255});//
    static void DrawRectF(float x, float y, float width, float height, SDL_Color color = {255,0,0,255});//
    void DrawCircle(int centerX, int centerY, int radius);//should not be static
    void DrawMark(int centerX, int centerY, int radius);
    void DrawMarkF(float centerX, float centerY, float radius);
    void DrawLine(int x1, int y1, int x2, int y2);
    void DrawLine(float x1, float y1, float x2, float y2);

    void NaiveCircle(int centerX, int centerY, int radius);
    void NaiveCircle4GPT(int centerX, int centerY, int radius);
    void NaiveCircle8(int centerX, int centerY, int radius);
    

    void DrawCircleMid(int centerX, int centerY, int radius); //  Bresenhams / midpoint-circle

    /*---Large Side Note---- regarding static SDL_Renderer*:

        if you want this to be static you should either make it inline - 
        or DEFINE it somewhere at the top of the .cpp file
        
    */

    inline static SDL_Renderer* m_renderer; //should not be static

private:
    //need to be "defined"
    ShapeManager() {}
    ~ShapeManager() {}

    

};
}