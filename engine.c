#include <SDL.h>
#include <stdlib.h>
#include "engine.h"

#define TILE_SIZE 24

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

void cleanup_graphics()
{
    if (renderer)
        SDL_DestroyRenderer(renderer);
    if (window)
        SDL_DestroyWindow(window);
    SDL_Quit();
}

void init_console()
{
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("The Snake",
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              WIDTH * TILE_SIZE, HEIGHT * TILE_SIZE,
                              SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    atexit(cleanup_graphics);
}

void render_frame(Snake *snake, Point *food, SpecialFood *s_food, int map[HEIGHT][WIDTH], int score)
{
    SDL_SetRenderDrawColor(renderer, 20, 24, 30, 255);
    SDL_RenderClear(renderer);

    SDL_Rect rect;
    rect.w = TILE_SIZE;
    rect.h = TILE_SIZE;

    SDL_SetRenderDrawColor(renderer, 40, 80, 150, 255);
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            if (map[y][x] == 1)
            {
                rect.x = x * TILE_SIZE;
                rect.y = y * TILE_SIZE;
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }

    SDL_SetRenderDrawColor(renderer, 220, 50, 50, 255);
    rect.x = food->x * TILE_SIZE;
    rect.y = food->y * TILE_SIZE;
    SDL_RenderFillRect(renderer, &rect);

    if (s_food->active)
    {
        if (s_food->type == FOOD_GOLD)
            SDL_SetRenderDrawColor(renderer, 255, 215, 0, 255);
        else if (s_food->type == FOOD_POISON)
            SDL_SetRenderDrawColor(renderer, 150, 50, 200, 255);
        else if (s_food->type == FOOD_GHOST)
            SDL_SetRenderDrawColor(renderer, 0, 250, 250, 255);

        rect.x = s_food->pos.x * TILE_SIZE;
        rect.y = s_food->pos.y * TILE_SIZE;
        SDL_RenderFillRect(renderer, &rect);
    }

    for (int i = 0; i < snake->length; i++)
    {
        if (i == 0)
        {
            if (snake->ghost_steps > 0)
                SDL_SetRenderDrawColor(renderer, 50, 255, 255, 255);
            else if (snake->poison_timer > 0)
                SDL_SetRenderDrawColor(renderer, 200, 80, 255, 255);
            else
                SDL_SetRenderDrawColor(renderer, 80, 255, 80, 255);
        }
        else
        {
            if (snake->ghost_steps > 0)
                SDL_SetRenderDrawColor(renderer, 0, 150, 150, 255);
            else if (snake->poison_timer > 0)
                SDL_SetRenderDrawColor(renderer, 130, 30, 180, 255);
            else
                SDL_SetRenderDrawColor(renderer, 0, 180, 0, 255);
        }

        SDL_Rect body_rect = {
            (snake->body[i].x * TILE_SIZE) + 1,
            (snake->body[i].y * TILE_SIZE) + 1,
            TILE_SIZE - 2,
            TILE_SIZE - 2};

        SDL_RenderFillRect(renderer, &body_rect);
    }

    SDL_RenderPresent(renderer);
}

int get_input(int current_dir)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            exit(0);
        }

        if (event.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_w:
            case SDLK_UP:
                if (current_dir != 2)
                    return 0;
                break;
            case SDLK_d:
            case SDLK_RIGHT:
                if (current_dir != 3)
                    return 1;
                break;
            case SDLK_s:
            case SDLK_DOWN:
                if (current_dir != 0)
                    return 2;
                break;
            case SDLK_a:
            case SDLK_LEFT:
                if (current_dir != 1)
                    return 3;
                break;
            }
        }
    }

    return current_dir;
}