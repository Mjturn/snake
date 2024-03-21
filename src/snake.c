#include "../headers/snake.h"

void move(SDL_Event event, int* x, int* y, int speed) {
    switch(event.key.keysym.sym) {
        case SDLK_LEFT:
            *x -= speed;
            break;
        case SDLK_RIGHT:
            *x += speed;
            break;
        case SDLK_UP:
            *y -= speed;
            break;
        case SDLK_DOWN:
            *y += speed;
            break;
        default:
            break;
    }
}

void eat(int snake_x, int snake_y, int food_x, int food_y, bool* food_eaten, int* score) {
    if((!(*food_eaten)) && (snake_x == food_x && snake_y == food_y)) {
        *food_eaten = true;
        (*score)++;
    }
}
