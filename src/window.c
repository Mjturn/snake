#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "../headers/window.h"
#include "../headers/snake.h"
    
typedef struct {
    int width;
    int height;
    int x;
    int y;
    int speed;

    int red;
    int green;
    int blue;
    int alpha;
} Snake;

Snake snake;
    
typedef struct {
    int width;
    int height;
    int x;
    int y;

    int red;
    int green;
    int blue;
    int alpha;
} Food;

Food food;
    

void initialize_window() {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL could not initialize. SDL Error: %s\n", SDL_GetError());
        return;
    }
    
    if (TTF_Init() == -1) {
        fprintf(stderr, "SDL_ttf could not initialize. SDL_ttf Error: %s\n", TTF_GetError());
        SDL_Quit();
        return;
    }
    
    char font_path[] = "../../../../mnt/c/Windows/Fonts/arial.ttf";
    int font_size = 24;

    TTF_Font* font = NULL;
    font = TTF_OpenFont(font_path, font_size);
    if (font == NULL) {
        fprintf(stderr, "Failed to load font. SDL_ttf Error: %s\n", TTF_GetError());
        TTF_Quit();
        SDL_Quit();
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
        TTF_CloseFont(font);
        TTF_Quit();
        SDL_Quit();
        return;
    }
    
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    if(renderer == NULL) {
        fprintf(stderr, "Renderer could not be created. SDL Error: %s\n", SDL_GetError());
        TTF_CloseFont(font);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return;
    }

    run(window, renderer, screen_width, screen_height, font);
}

void run(SDL_Window* window, SDL_Renderer* renderer, int screen_width, int screen_height, TTF_Font* font) {
    bool running = true;
    SDL_Event event;

    snake.x = (screen_width - snake.width) / 2;
    snake.y = (screen_height - snake.height) / 2;
    snake.speed = 50;

    while(running) {
        while(SDL_PollEvent(&event) != 0) {
            move(event, &snake.x, &snake.y, snake.speed);
            
            if(event.type == SDL_KEYDOWN) {
                if(event.key.keysym.sym == SDLK_ESCAPE) {
                    running = false;
                }
            } else if(event.type == SDL_QUIT) {
                running = false;
            }
        }

        render_snake(renderer);
        render_food(renderer, screen_width, screen_height);
        render_score(renderer, font, screen_width);
        
        bool collision_detected = detect_collision(screen_width, screen_height);

        if(collision_detected) {
            display_game_over_screen(renderer, font, screen_width, screen_height);
            sleep(5);
            running = false;
        }

        int background_color_red = 0;
        int background_color_green = 0;
        int background_color_blue = 0;
        int background_color_alpha = 255;

        SDL_SetRenderDrawColor(renderer, background_color_red, background_color_green, background_color_blue, background_color_alpha);
        SDL_Rect clear_snake = { snake.x, snake.y, snake.width, snake.height };
        SDL_RenderFillRect(renderer, &clear_snake);
    }

    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}

void render_object(SDL_Renderer* renderer, int x, int y, int width, int height, int red, int green, int blue, int alpha) {
    SDL_SetRenderDrawColor(renderer, red, green, blue, alpha);
    SDL_Rect object = { x, y, width, height };
    SDL_RenderFillRect(renderer, &object);
    SDL_RenderPresent(renderer);

}

void render_snake(SDL_Renderer* renderer) {
    snake.width = 25;
    snake.height = 25;
    
    snake.red = 255;
    snake.green = 255;
    snake.blue = 255;
    snake.alpha = 255;
    
    render_object(renderer, snake.x, snake.y, snake.width, snake.height, snake.red, snake.green, snake.blue, snake.alpha);
}

void render_food(SDL_Renderer* renderer, int screen_width, int screen_height) {
    static bool food_rendered = false;

    if(food_rendered) {
        return;
    }
    
    srand(time(NULL));
        
    food.width = 25;
    food.height = 25;
    food.x = rand() % (screen_width - food.width);
    food.y = rand() % (screen_height - food.height);

    food.red = 255;
    food.green = 255;
    food.blue = 0;
    food.alpha = 255;

    render_object(renderer, food.x, food.y, food.width, food.height, food.red, food.green, food.blue, food.alpha);

    food_rendered = true;
}

void render_score(SDL_Renderer* renderer, TTF_Font* font, int screen_width) {
    int score = 0;
    char score_text[20];
    SDL_Surface* text_surface = NULL;
    SDL_Texture* text_texture = NULL;
    
    sprintf(score_text, "Score: %d", score);

    int score_red = 255;
    int score_green = 255;
    int score_blue = 255;
    int score_alpha = 255;
    
    text_surface = TTF_RenderText_Solid(font, score_text, (SDL_Color){ score_red, score_green, score_blue, score_alpha });
    
    if(text_surface == NULL) {
        fprintf(stderr, "Failed to render text surface. SDL_ttf Error: %s\n", TTF_GetError());
        return;
    }

    text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    
    if (text_texture == NULL) {
        fprintf(stderr, "Failed to create text texture. SDL Error: %s\n", SDL_GetError());
        return;
    }

    int text_width = text_surface->w;
    int text_height = text_surface->h;
    int text_x = (screen_width - text_width) / 2;
    int text_y = 10;

    SDL_Rect text = { text_x, text_y, text_width, text_height };
    SDL_RenderCopy(renderer, text_texture, NULL, &text);

    SDL_FreeSurface(text_surface);
    SDL_DestroyTexture(text_texture);
}

bool detect_collision(int screen_width, int screen_height) {
    if((snake.x == food.x && snake.y == food.y) || (snake.x < 0 || snake.y < 0 || snake.x > screen_width || snake.y > screen_height)) {
        return true;
    }

    return false;
}

void display_game_over_screen(SDL_Renderer* renderer, TTF_Font* font, int screen_width, int screen_height) {
    int background_color_red = 0;
    int background_color_green = 0;
    int background_color_blue = 0;
    int background_color_alpha = 255;

    SDL_SetRenderDrawColor(renderer, background_color_red, background_color_green, background_color_blue, background_color_alpha);
    SDL_RenderClear(renderer);
    
    int text_color_red = 255;
    int text_color_green = 255;
    int text_color_blue = 255;

    char game_over_text[] = "Game Over";
    SDL_Color text_color = { text_color_red, text_color_green, text_color_blue };
    
    SDL_Surface* text_surface = TTF_RenderText_Solid(font, game_over_text, text_color);
    
    if(text_surface == NULL) {
        fprintf(stderr, "Failed to render text surface. SDL_ttf Error: %s\n", TTF_GetError());
        return;
    }
    
    SDL_Texture* text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    
    if (text_texture == NULL) {
        fprintf(stderr, "Failed to create text texture. SDL Error: %s\n", SDL_GetError());
        return;
    }

    int text_width = text_surface->w;
    int text_height = text_surface->h;
    int text_x = (screen_width - text_width) / 2;
    int text_y = (screen_height - text_height) / 2;

    SDL_Rect text = { text_x, text_y, text_width, text_height };
    SDL_RenderCopy(renderer, text_texture, NULL, &text);

    SDL_FreeSurface(text_surface);
    SDL_DestroyTexture(text_texture);
    SDL_RenderPresent(renderer);
}
