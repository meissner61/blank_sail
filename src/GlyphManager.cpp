
#include "GlyphManager.h"


GlyphManager& GlyphManager::GetInstace()
{
    static GlyphManager instance;
    return instance;
}

void GlyphManager::Init(SDL_Renderer *renderer, SDL_Texture *fontAtlas)
{
    m_renderer = renderer;
    m_texture = fontAtlas;

    if(m_texture != nullptr)
    {
        system("Pause");
    }
}

void GlyphManager::SetFontTexture(SDL_Texture *fontAtlas, int width, int height)
{
    m_texture = fontAtlas;
    m_charWidth = width;
    m_charHeight = height;
    SDL_QueryTexture(fontAtlas,NULL, NULL, &m_textureWidth, &m_textureHeight);
}

void GlyphManager::DrawString(int x, int y, std::string text)
{
    for(int i = 0;i < text.size(); ++i )
    {
        DrawChar(x + i * m_charWidth+1, y, text[i] );
    }
}

//example:
// 12 x 12 = char
// 192 x 72 = texture
//  192 / 12 = 16 cols
//  72 / 12 = 6 rows
void GlyphManager::DrawChar(int x, int y, char c) //TODO: maybe, add possibility to draw with different type fonts if they are loaded in
{
    int ascii = int(c);
    int position = ascii - 32; // 32 = start position on ascii table, position = char position on our bitmap

    int cols = m_textureWidth / m_charWidth;
    //int rows = m_textureHeight / m_charHeight;

    int x_start = (position % cols) * m_charWidth;
    int y_start = (position / cols) * m_charHeight;

    SDL_Rect srcRect = {x_start, y_start, m_charWidth, m_charHeight};
    SDL_Rect dstRect = {x, y, m_charWidth, m_charHeight};

    SDL_RenderCopy(m_renderer, m_texture, &srcRect, &dstRect);
}

void GlyphManager::DrawInt(int x, int y, long long int i)
{
    std::string str;
    str = std::to_string(i);

    DrawString(x, y, str);
}

void GlyphManager::DrawReal(int x, int y, float i)
{
    std::string str;
    str = std::to_string(i);

    DrawString(x, y, str);
}

void GlyphManager::Draw2F(int x, int y, float a, float b)
{
    std::string strA;
    strA = std::to_string(a);
    DrawString(x, y, strA);

    // for(int i = 0; i < 10; i ++)
    // {
    //     DrawChar(x * m_charWidth, y, ' ');
    // }
    std::string strB;
    strB = std::to_string(b);
    DrawString(x + 60, y, strB);
}

GlyphManager::GlyphManager()
{

}
