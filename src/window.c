#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "../headers/window.h"

void initialize_window() {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL could not initialize. SDL Error: %s\n", SDL_GetError());
        return;
    }

    char title[] = "Snake";
    int screen_width = 800;
    int screen_height = 600;

    SDL_Window* window = SDL_CreateWindow (
        title,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        screen_width,
        screen_height,
        SDL_WINDOW_SHOWN
    );

    if(window == NULL) {
        fprintf(stderr, "Window could not be created. SDL Error: %s\n", SDL_GetError());
        return;
    }
    
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    if(renderer == NULL) {
        fprintf(stderr, "Renderer could not be created. SDL Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }
    
    bool running = true;
    SDL_Event event;
   
    while(running) {
        while(SDL_PollEvent(&event) != 0) {
            if(event.type == SDL_QUIT) {
                running = false;
            }
        }
    
        render_snake(renderer, screen_width, screen_height);
        render_food(renderer, screen_width, screen_height);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void render_object(SDL_Renderer* renderer, int x, int y, int width, int height, int red, int green, int blue, int alpha) {
    SDL_SetRenderDrawColor(renderer, red, green, blue, alpha);
    SDL_Rect object = { x, y, width, height };
    SDL_RenderFillRect(renderer, &object);
    SDL_RenderPresent(renderer);

}

void render_snake(SDL_Renderer* renderer, int screen_width, int screen_height) {
    int snake_width = 25;
    int snake_height = 25;
    int snake_x = (screen_width - snake_width) / 2;
    int snake_y = (screen_height - snake_height) / 2;

    int snake_red = 255;
    int snake_green = 255;
    int snake_blue = 255;
    int snake_alpha = 255;

    render_object(renderer, snake_x, snake_y, snake_width, snake_height, snake_red, snake_green, snake_blue, snake_alpha);
}

void render_food(SDL_Renderer* renderer, int screen_width, int screen_height) {
    static bool food_rendered = false;

    if(food_rendered) {
        return;
    }
    
    srand(time(NULL));
    
    int food_width = 25;
    int food_height = 25;
    int food_x = rand() % (screen_width - food_width);
    int food_y = rand() % (screen_height - food_height);

    int food_red = 255;
    int food_green = 255;
    int food_blue = 0;
    int food_alpha = 255;
    
    render_object(renderer, food_x, food_y, food_width, food_height, food_red, food_green, food_blue, food_alpha);

    food_rendered = true;
}
