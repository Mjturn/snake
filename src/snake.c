#include <SDL2/SDL.h>
#include "../headers/snake.h"

void render_snake(SDL_Window* window, int screen_width, int screen_height) {
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if(renderer == NULL) {
        fprintf(stderr, "Renderer could not be created. SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }

    int snake_red = 255;
    int snake_green = 255;
    int snake_blue = 255;
    int snake_alpha = 255;

    int snake_width = 25;
    int snake_height = 25;
    int snake_x = (screen_width - snake_width) / 2;
    int snake_y = (screen_height - snake_height) / 2;

    SDL_SetRenderDrawColor(renderer, snake_red, snake_green, snake_blue, snake_alpha);
    SDL_Rect snake = { snake_x, snake_y, snake_width, snake_height };
    SDL_RenderFillRect(renderer, &snake);
    SDL_RenderPresent(renderer);

    SDL_DestroyRenderer(renderer);
}
