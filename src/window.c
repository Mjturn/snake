#include <SDL2/SDL.h>
#include <stdbool.h>
#include "../headers/window.h"
#include "../headers/snake.h"

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

    render_snake(window, screen_width, screen_height);

    bool running = true;
    SDL_Event event;

    while(running) {
        while(SDL_PollEvent(&event) != 0) {
            if(event.type == SDL_QUIT) {
                running = false;
            }
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
}
