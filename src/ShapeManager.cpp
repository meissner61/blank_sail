
#include "ShapeManager.h"

#include <iostream>
#include <vector>

    /*---Large Side Note---- regarding static SDL_Renderer*:
    
        if you want this to be static you should either make it inline - 
        or DEFINE it somewhere at the top of the .cpp file
        like so:
        SDL_Renderer* ShapeManager::m_renderer = nullptr;
        
    */

//SDL_Renderer* ShapeManager::m_renderer = nullptr;


//Test Functions, to be removed./////////////////////////////////////////////////////////////
void mirrorPoints4(std::vector < std::pair<int, int>>& points);                             //
void mirror_points_4(std::vector< std::pair<int,int>>& points, int x, int y);               //
/////////////////////////////////////////////////////////////////////////////////////////////


sail::ShapeManager& sail::ShapeManager::GetInstance ()
{

    static sail::ShapeManager instance;

    return instance;
}   

bool sail::ShapeManager::Init(SDL_Renderer* renderer)
{
    if(renderer == nullptr)
    {   
        SDL_Log("ShapeManager Error: Renderer failed to initialize");
        return false;
    }
    else
    {
        m_renderer = renderer;
        return true;
    }
}

void sail::ShapeManager::DrawRect(int x, int y, int width, int height, SDL_Color color)
{
    static bool oneTimeWarning = false; // TODO: might want to use spdlog, put errors into error array, and stream one at a time 
    if(m_renderer == nullptr && oneTimeWarning == false)
    {
        SDL_Log("ShapeManager ERROR: NO INSTANCE");
        oneTimeWarning = true;

    }
    SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
    SDL_Rect rect = {x, y, width, height};
    SDL_RenderFillRect(m_renderer, &rect);
}

void sail::ShapeManager::DrawRectF(float x, float y, float width, float height, SDL_Color color)
{
    static bool oneTimeWarning = false; // TODO: might want to use spdlog, put errors into error array, and stream one at a time 
    if(m_renderer == nullptr && oneTimeWarning == false)
    {
        SDL_Log("ShapeManager ERROR: NO INSTANCE");
        oneTimeWarning = true;

    }
    SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
    SDL_FRect rect = {x, y, width, height};
    SDL_RenderFillRectF(m_renderer, &rect);
}

void sail::ShapeManager::DrawCircle(int centerX, int centerY, int radius)
{
    SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);
    int x = radius;
    int y = 0;
    int err = 0;

    while (x >= y)
    {
        SDL_RenderDrawPoint(m_renderer, centerX + x, centerY + y);
        SDL_RenderDrawPoint(m_renderer, centerX + y, centerY + x);
        SDL_RenderDrawPoint(m_renderer, centerX - y, centerY + x);
        SDL_RenderDrawPoint(m_renderer, centerX - x, centerY + y);
        SDL_RenderDrawPoint(m_renderer, centerX - x, centerY - y);
        SDL_RenderDrawPoint(m_renderer, centerX - y, centerY - x);
        SDL_RenderDrawPoint(m_renderer, centerX + y, centerY - x);
        SDL_RenderDrawPoint(m_renderer, centerX + x, centerY - y);

        if (err <= 0)
        {
            y += 1;
            err += 2 * y + 1;
        }

        if (err > 0)
        {
            x -= 1;
            err -= 2 * x + 1;
        }
    }
}

void sail::ShapeManager::DrawCircleTest(int centerX, int centerY, int radius) //
{

    SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);

    int zoom = 1;//dont use is broken
    
    const int32_t diameter = (radius * 2);

   int32_t x = (radius - 1);
   int32_t y = 0;
   int32_t tx = 1;
   int32_t ty = 1;
   int32_t error = (tx - diameter);

   while (x >= y)
   {
      //  Each of the following renders an octant of the circle
      SDL_RenderDrawPoint(m_renderer, (centerX + x) * zoom, (centerY - y) * zoom);
      SDL_RenderDrawPoint(m_renderer, (centerX + x) * zoom, (centerY + y) * zoom);
      SDL_RenderDrawPoint(m_renderer, (centerX - x) * zoom, (centerY - y) * zoom);
      SDL_RenderDrawPoint(m_renderer, (centerX - x) * zoom, (centerY + y) * zoom);
      SDL_RenderDrawPoint(m_renderer, (centerX + y) * zoom, (centerY - x) * zoom);
      SDL_RenderDrawPoint(m_renderer, (centerX + y) * zoom, (centerY + x) * zoom);
      SDL_RenderDrawPoint(m_renderer, (centerX - y) * zoom, (centerY - x) * zoom);
      SDL_RenderDrawPoint(m_renderer, (centerX - y) * zoom, (centerY + x) * zoom);
      if (error <= 0)
      {
         ++y;
         error += ty;
         ty += 2;
      }

      if (error > 0)
      {
         --x;
         tx += 2;
         error += (tx - diameter);
      }
   }

}

void sail::ShapeManager::DrawMark(int centerX, int centerY, int radius)
{
    DrawLine(centerX - radius, centerY,centerX + radius, centerY );
    DrawLine(centerX, centerY - radius, centerX, centerY + radius);
}

void sail::ShapeManager::DrawMarkF(float centerX, float centerY, float radius)
{
    DrawLine(centerX - radius, centerY,centerX + radius, centerY );
    DrawLine(centerX, centerY - radius, centerX, centerY + radius);
}

void sail::ShapeManager::DrawLine(int x1, int y1, int x2, int y2)
{
    SDL_SetRenderDrawColor(m_renderer, 0, 255, 0, 255);
    SDL_RenderDrawLine(m_renderer, x1, y1, x2, y2);
}

void sail::ShapeManager::DrawLine(float x1, float y1, float x2, float y2)
{
    SDL_SetRenderDrawColor(m_renderer, 0, 255, 0, 255);
    SDL_RenderDrawLineF(m_renderer, x1, y1, x2, y2);
}

void sail::ShapeManager::NaiveCircle4GPT(int centerX, int centerY, int radius)
{
    SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);

    for (int x = 0; x <= radius; x++)
    {
        int y = int(sqrt(radius * radius - x * x));
        // Draw the original point
        SDL_RenderDrawPoint(m_renderer, centerX + x, centerY + y);
        // Draw the mirrored points
        SDL_RenderDrawPoint(m_renderer, centerX + x, centerY - y);      // (1, -1)
        SDL_RenderDrawPoint(m_renderer, centerX - x, centerY - y);      // (-1, -1)
        SDL_RenderDrawPoint(m_renderer, centerX - x, centerY + y);      // (-1, 1)
    }
}



//https://funloop.org/post/2021-03-15-bresenham-circle-drawing-algorithm.html
//THIS IS CURRENTLY A HACKY FIX TO fix the "nipple tip of the circle
//http://members.chello.at/~easyfilter/bresenham.html
void sail::ShapeManager::NaiveCircle8(int centerX, int centerY, int radius)
{
    SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);

    for (int x = 0; x <= radius; x++) //!TODO!: This will waste cycles redrawing some points that have already been drawn
    {
        

        int y = int(sqrt(radius * radius - x * x));

        if(y == radius)
        {
            y -=1;
        }

        else if (x == radius)
        {
            SDL_RenderDrawPoint(m_renderer, centerX + x -1, centerY + y);      //(x,y)
                // Draw the mirrored points
            SDL_RenderDrawPoint(m_renderer, centerY + y, centerX + x - 1);      //(y,x)
            SDL_RenderDrawPoint(m_renderer, centerX - x + 1, centerY + y);      // (-x, y)
            SDL_RenderDrawPoint(m_renderer, centerY - y, centerX + x - 1);      // (-y, x)
            SDL_RenderDrawPoint(m_renderer, centerX + x - 1, centerY - y);      // (x, -y)
            SDL_RenderDrawPoint(m_renderer, centerY + y, centerX - x + 1);      // (y, -x)
            SDL_RenderDrawPoint(m_renderer, centerX - x + 1, centerY - y);      // (-x, -y)
            SDL_RenderDrawPoint(m_renderer, centerY - y, centerX - x + 1);      // (-x, -y)
        }

        else
        {
            // y = radius * radius - x * x;

 // Draw the original point
            SDL_RenderDrawPoint(m_renderer, centerX + x, centerY + y);      //(x,y)
            // Draw the mirrored points
            SDL_RenderDrawPoint(m_renderer, centerY + y, centerX + x);      //(y,x)
            SDL_RenderDrawPoint(m_renderer, centerX - x, centerY + y);      // (-x, y)
            SDL_RenderDrawPoint(m_renderer, centerY - y, centerX + x);      // (-y, x)
            SDL_RenderDrawPoint(m_renderer, centerX + x, centerY - y);      // (x, -y)
            SDL_RenderDrawPoint(m_renderer, centerY + y, centerX - x);      // (y, -x)
            SDL_RenderDrawPoint(m_renderer, centerX - x, centerY - y);      // (-x, -y)
            SDL_RenderDrawPoint(m_renderer, centerY - y, centerX - x);      // (-x, -y)
        }



    }

}


void sail::ShapeManager::NaiveCircle(int centerX, int centerY, int radius)
{
    SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255); 

    static bool done = false;

    std::vector<std::pair<int, int>> points;

    int y = 0; 

    for(int x = 0; x <= radius; x++ )
    {
        y = int(sqrt((radius * radius) - (x * x))); //dont need sqrt, just square y to be y^2
        points.push_back(std::make_pair(x, y));
        //SDL_RenderDrawPoint(m_renderer, x + 100, y + 100);
    }

    mirrorPoints4(points);

    for (size_t i = 0; i < points.size(); i++)
    {
        SDL_RenderDrawPoint(m_renderer, centerX + points[i].first, centerY + points[i].second);
    }



    //appending vectors
    //std::vector<std::pair<int, int>> points2;
    //points2.push_back(std::make_pair(999, 999));
    //points.insert(points.end(), points2.begin(), points2.end());


    // different ways to loop through vectors
    //mirror_points_4(points, 1,-1);
    //for (std::pair<int, int>& pair : points)
    //{
    //    SDL_RenderDrawPoint(m_renderer, pair.first + 10, pair.second + 10);
    //}

    //mirror_points_4(points, -1,1);
    //for (auto& pair : points)
    //{
    //    SDL_RenderDrawPoint(m_renderer, pair.first + 10, pair.second + 10);
    //}
    


    if (!done)
    {
        for (const std::pair<int, int>& pair : points)
        {
            std::cout <<"x: " << pair.first <<" y: " << pair.second << std::endl;
        }

        done = true;
    }

}



void mirror_points_4(std::vector< std::pair<int,int>>& points, int x, int y)
{
    if(x > 0 && y > 0)
    {
        for(size_t i = 0; i < points.size(); i++)
        {
            //std::cout << points[i].first << points[i].second << std::endl;
            points[i].second = abs(points[i].second);
            points[i].first = abs(points[i].first);
        }
    }

    if(x < 0 && y < 0)
    {        
        for(size_t i = 0; i < points.size(); i++)
        {
            //std::cout << points[i].first << points[i].second << std::endl;
            points[i].second *= -1;
            points[i].first *= -1;
        }
        
    }
    if(x > 0 && y < 0)
    {        
        for(size_t i = 0; i < points.size(); i++)
        {
            //std::cout << points[i].first << points[i].second << std::endl;
            points[i].first = abs(points[i].first);
            points[i].second *= -1;
        }
        
    }
    if(x < 0 && y > 0)
    {        
        for(size_t i = 0; i < points.size(); i++)
        {
            //std::cout << points[i].first << points[i].second << std::endl;
            points[i].first *= -1;
            points[i].second = abs(points[i].second);
        }
        
    }
    
}



void mirrorPoints4(std::vector < std::pair<int, int>>& points)
{
    //need to mirror 4 circle quadrants, 1,1 is done, that leaves ... (1,-1), (-1,-1), (-1,1).

    //std::vector<std::pair<int, int>> mirroredPoints;

    size_t originalSize = points.size();

    for (size_t i = 0; i < originalSize; i++) //(1,-1)
    {
        points.push_back(std::make_pair(points[i].first, -1 * (points[i].second)));
    }

    for (size_t i = 0; i < originalSize; i++) //(-1,-1)
    {
        points.push_back(std::make_pair(-1 * points[i].first, -1 * points[i].second));
    }

    for (size_t i = 0; i < originalSize; i++) //(-1,1)
    {
        points.push_back(std::make_pair(-1 * points[i].first, points[i].second));
    }

    //for (auto& pair : points)
    //{
    //    p
    //}
}