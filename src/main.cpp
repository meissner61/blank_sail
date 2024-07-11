#include <SDL.h>
#include "TextureManager.h"
//#include <SDL_image.h>

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);  // Initialize SDL2
    //IMG_Init(IMG_INIT_PNG);    // Initialize SDL2_image

    SDL_Window* window = SDL_CreateWindow("SDL Lighting Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    sail::TextureManager::GetInstance().Init(renderer);

    // Load images
    sail::TextureManager::GetInstance().LoadTexture("../data/terrain.png");
    // SDL_Surface* terrainSurface = IMG_Load("terrain.png");
    // SDL_Texture* terrainTexture = SDL_CreateTextureFromSurface(renderer, terrainSurface);
    // SDL_FreeSurface(terrainSurface);


    sail::TextureManager::GetInstance().LoadTexture("../data/light.png");
    // SDL_Surface* lightSurface = IMG_Load("light.png");  // Light.png should be a radial gradient
    // SDL_Texture* lightTexture = SDL_CreateTextureFromSurface(renderer, lightSurface);
    // SDL_FreeSurface(lightSurface);


    SDL_Texture* lightTexture = sail::TextureManager::GetInstance().GetTexture("light");

    SDL_SetTextureBlendMode(lightTexture, SDL_BLENDMODE_ADD);  // Set blend mode to add to simulate lighting

    

    bool running = true;
    SDL_Event event;
    int mouseX, mouseY;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        SDL_GetMouseState(&mouseX, &mouseY);  // Get mouse position

        // Clear screen
        SDL_RenderClear(renderer);

        // Render terrain
        SDL_RenderCopy(renderer, sail::TextureManager::GetInstance().GetTexture("terrain"), NULL, NULL);

        // Render light at mouse position
        SDL_Rect destRect = { mouseX - 128, mouseY - 128, 256, 256 };  // Adjust size and position as needed
        SDL_RenderCopy(renderer, lightTexture, NULL, &destRect);

        // Update screen
        SDL_RenderPresent(renderer);
    }

    // Clean up
    //SDL_DestroyTexture(terrainTexture);
    //SDL_DestroyTexture(lightTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    //IMG_Quit();
    SDL_Quit();

    return 0;
}
