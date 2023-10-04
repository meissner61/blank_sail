
#include <string>
#include <unordered_map>

#include "TextureManager.h"
#include "InputManager.h"


class Boat
{


//TODO: Need a method wherein changing diretion happens after about .5 seconds so that if you dont let go of Key(W & D) at the same time it will keep its course
public:
    Boat();
    Boat(float x, float y);

    void SetPosition(float x, float y);

    void Input();
    void Update();
    void Render();

    void KeyboardInput();
    void ControllerInput();

private:
    float x;
    float y;
    int m_width; //TODO: Change to radius for circle collision but still need width and height of texture for Rendering
    int m_height;
    float speed = 50.0f;

    

    std::string m_direction;
    std::string m_lastDirection;

    std::unordered_map<std::string, int> m_dir_map;
    std::unordered_map<std::string, std::pair<float, float>> m_directionCenter;
    /*
        NOTE:
                                            "Direction Name" -- (int)texture_x_position -- (float)centerX, float(centerY)
            Will probably want to do unordered_map<string, int, float float>
    */


    //texture_X
    //texture_y
    //texture_width
    //texture_height

};