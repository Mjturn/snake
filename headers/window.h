#ifndef WINDOW_H
#define WINDOW_H

#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

void initialize_window();
void run(SDL_Window* window, SDL_Renderer* renderer, int screen_width, int screen_height, TTF_Font* font);
void render_object(SDL_Renderer* renderer, int x, int y, int width, int height, int red, int green, int blue, int alpha);
void render_snake(SDL_Renderer* renderer);
void render_food(SDL_Renderer* renderer, int screen_width, int screen_height);
void render_score(SDL_Renderer* renderer, TTF_Font* font, int screen_width);
bool detect_collision(int screen_width, int screen_height);
void display_game_over_screen(SDL_Renderer* renderer, TTF_Font* fonti, int screen_width, int screen_height);

#endif
