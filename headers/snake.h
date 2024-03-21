#ifndef SNAKE_H
#define SNAKE_H

#include <stdbool.h>
#include <SDL2/SDL.h>

void move(SDL_Event event, int* x, int* y, int speed);
void eat(int snake_x, int snake_y, int food_x, int food_y, bool* food_eaten, int* score);

#endif
