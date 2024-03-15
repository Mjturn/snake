#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>

void initialize_window();
void render_object(SDL_Renderer* renderer, int x, int y, int width, int height, int red, int green, int blue, int alpha);
void render_snake(SDL_Renderer* renderer, int screen_width, int screen_height);
void render_food(SDL_Renderer* renderer, int screen_width, int screen_height);

#endif
