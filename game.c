#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "game.h"
#include "engine.h"
#include "types.h"
#include "config.h"
#include "map.h"

void spawn_food(Point *food, Snake *snake, int map[HEIGHT][WIDTH])
{
    int valid = 0;
    while (!valid)
    {
        food->x = 1 + rand() % (WIDTH - 2);
        food->y = 1 + rand() % (HEIGHT - 2);
        valid = 1;

        if (map[food->y][food->x] == 1)
        {
            valid = 0;
            continue;
        }

        for (int i = 0; i < snake->length; i++)
        {
            if (food->x == snake->body[i].x && food->y == snake->body[i].y)
            {
                valid = 0;
                break;
            }
        }
    }
}

void spawn_special_food(SpecialFood *s_food, Snake *snake, int map[HEIGHT][WIDTH], Point *normal_food)
{
    int valid = 0;
    while (!valid)
    {
        s_food->pos.x = 1 + rand() % (WIDTH - 2);
        s_food->pos.y = 1 + rand() % (HEIGHT - 2);
        valid = 1;

        if (map[s_food->pos.y][s_food->pos.x] == 1)
        {
            valid = 0;
            continue;
        }
        if (s_food->pos.x == normal_food->x && s_food->pos.y == normal_food->y)
        {
            valid = 0;
            continue;
        }

        for (int i = 0; i < snake->length; i++)
        {
            if (s_food->pos.x == snake->body[i].x && s_food->pos.y == snake->body[i].y)
            {
                valid = 0;
                break;
            }
        }
    }

    s_food->active = 1;
    int r = rand() % 100;

    if (r < 40)
    {
        s_food->type = FOOD_GOLD;
        s_food->ttl = 60;
    }
    else if (r < 70)
    {
        s_food->type = FOOD_POISON;
        s_food->ttl = 100;
    }
    else
    {
        s_food->type = FOOD_GHOST;
        s_food->ttl = 100;
    }
}

void init_snake(Snake *snake)
{
    snake->length = 4;
    snake->dir = 1;
    snake->ghost_steps = 0;
    snake->poison_timer = 0;
    for (int i = 0; i < snake->length; i++)
    {
        snake->body[i].x = WIDTH / 2 - i;
        snake->body[i].y = HEIGHT / 2;
    }
}

void run_game(int base_delay)
{
    Snake snake;
    Point food;
    SpecialFood s_food = {0};
    int map[HEIGHT][WIDTH];
    int score = 0;
    int running = 1;

    unsigned int seed = (unsigned int)time(NULL);
    generate_map(map, seed);

    init_snake(&snake);
    spawn_food(&food, &snake, map);
    init_console();

    while (running)
    {
        snake.dir = get_input(snake.dir);

        if (!s_food.active && rand() % 100 < 3)
        {
            spawn_special_food(&s_food, &snake, map, &food);
        }

        if (s_food.active)
        {
            s_food.ttl--;
            if (s_food.ttl <= 0)
            {
                s_food.active = 0;
            }
        }

        if (snake.poison_timer > 0)
        {
            snake.poison_timer--;
        }

        int next_x = snake.body[0].x;
        int next_y = snake.body[0].y;

        if (snake.dir == 0)
            next_y--;
        else if (snake.dir == 1)
            next_x++;
        else if (snake.dir == 2)
            next_y++;
        else if (snake.dir == 3)
            next_x--;

        if (snake.ghost_steps > 0)
        {
            if (next_x <= 0)
                next_x = WIDTH - 2;
            else if (next_x >= WIDTH - 1)
                next_x = 1;

            if (next_y <= 0)
                next_y = HEIGHT - 2;
            else if (next_y >= HEIGHT - 1)
                next_y = 1;
        }

        if (next_x <= 0 || next_x >= WIDTH - 1 || next_y <= 0 || next_y >= HEIGHT - 1)
        {
            running = 0;
            break;
        }

        if (map[next_y][next_x] == 1 && snake.ghost_steps <= 0)
        {
            running = 0;
            break;
        }

        for (int i = 0; i < snake.length; i++)
        {
            if (next_x == snake.body[i].x && next_y == snake.body[i].y)
            {
                running = 0;
                break;
            }
        }

        if (!running)
            break;

        if (snake.ghost_steps > 0)
        {
            snake.ghost_steps--;
        }

        if (map[next_y][next_x] == 1 && snake.ghost_steps <= 0)
        {
            running = 0;
            break;
        }

        if (next_x == food.x && next_y == food.y)
        {
            snake.length++;
            score += 10;
            spawn_food(&food, &snake, map);
        }

        if (s_food.active && next_x == s_food.pos.x && next_y == s_food.pos.y)
        {
            if (s_food.type == FOOD_GOLD)
            {
                score += 50;
            }
            else if (s_food.type == FOOD_POISON)
            {
                score -= 10;
                snake.poison_timer = 120;
            }
            else if (s_food.type == FOOD_GHOST)
            {
                snake.ghost_steps = 16;
            }
            s_food.active = 0;
        }

        for (int i = snake.length - 1; i > 0; i--)
        {
            snake.body[i] = snake.body[i - 1];
        }
        snake.body[0].x = next_x;
        snake.body[0].y = next_y;

        render_frame(&snake, &food, &s_food, map, score);

        int actual_delay = (snake.dir == 0 || snake.dir == 2) ? (int)(base_delay * 2.0) : base_delay;

        if (snake.poison_timer > 0)
        {
            actual_delay /= 2;
        }

        usleep(actual_delay * 1000);
    }

    printf("\033[H\033[J");
    printf("\n\n\t\033[1;31mGAME OVER!\033[0m\n");
    printf("\tFinal Score: %d\n", score);
    printf("\tMap Seed: %u\n\n", seed);
    printf("\033[?25h");
}