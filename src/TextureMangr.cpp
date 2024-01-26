#include "TextureMangr.h"
#include "stb_image.h"


void TextureMangr::LoadTexture(std::string filepath, SDL_Renderer* renderer)
{
    unsigned char* imageData = nullptr;
    int width, height, numChannels = 0;

    imageData = stbi_load(filepath.c_str(), &width, &height, &numChannels, 4 );

    if(imageData == nullptr)
    {
        SDL_Log("stbi_load() Failed: %s\n", stbi_failure_reason());
    }

    SDL_Texture* l_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STATIC, width, height);
    if(l_texture == nullptr)
    {
        SDL_Log("Error with SDL_CreateTexture(): %s", SDL_GetError());
    }

    if (SDL_UpdateTexture(l_texture, NULL, imageData, width * sizeof(unsigned char) * 4) != 0)
    {
        SDL_Log("Error with SDL_UpdateTexture(): %s", SDL_GetError());
    }

    m_textures.push_back(l_texture);

    if(!m_textures.empty())
        SDL_SetTextureBlendMode(m_textures.back(), SDL_BLENDMODE_BLEND); //TODO: stbi_load - 8BPP might have issues with this function

    stbi_image_free(imageData);

    printf("VecTextures size: %zi",m_textures.size());

}

void TextureMangr::DrawTexture(SDL_Renderer* renderer, int index, int x, int y, SDL_RendererFlip flip, Uint8 alpha)
{
    int width, height = 0;

    SDL_QueryTexture(m_textures[index], nullptr, nullptr, &width, &height);

    SDL_Rect dstRect = {x, y, width, height};

    SDL_RenderCopyEx(renderer, m_textures[index], NULL, &dstRect, 0, NULL, flip);
}
