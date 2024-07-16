
#include <array>

class TileMap
{

public:
    TileMap(); //default constructs to 16x16 tiles
    TileMap(int tileSize);

    void Draw();



private:

    int m_tileSize;
    static constexpr int m_mapSize = 20; //this includes both the width and height. so mapSize(10) = 10x10 of each tile being tileSize width and height
    std::array<char, m_mapSize*m_mapSize> m_TileMap{};
};