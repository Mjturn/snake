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
