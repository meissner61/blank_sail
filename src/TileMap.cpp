#include "TileMap.h"

#include <iostream>

#include "ShapeManager.h"

TileMap::TileMap()
:
m_tileSize(16)
{
    //std::fill(m_TileMap.begin(), m_TileMap.end(),0);

    m_TileMap[45] = 1;
    m_TileMap[46] = 1;
    m_TileMap[55] = 1;
    m_TileMap[56] = 1;

    for(int i = 0; i < m_TileMap.size(); i++)
    {
        std::cout << "Map: " << (int)m_TileMap[i] << std::endl;
    }

}

TileMap::TileMap(int tileSize)
:
m_tileSize(tileSize)
{
}

void TileMap::Draw()
{
    for(int y=0; y < m_mapSize; y++)
    {
        for(int x = 0; x < m_mapSize; x++)
        {
            if(m_TileMap[y*m_mapSize+x] == 0)
            {
                sail::ShapeManager::GetInstance().DrawRect(x*m_tileSize, y*m_tileSize, m_tileSize, m_tileSize, {255,255,255});
            }
            else if(m_TileMap[y*m_mapSize+x] == 1)
            {
                sail::ShapeManager::GetInstance().DrawRect(x*m_tileSize, y*m_tileSize, m_tileSize, m_tileSize, {100,100,100});
            }

            sail::ShapeManager::GetInstance().DrawRectOutline(x*m_tileSize, y*m_tileSize, m_tileSize, m_tileSize);

        }
    }
}
