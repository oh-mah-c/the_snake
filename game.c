#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "game.h"
#include "engine.h"
#include "types.h"
#include "config.h"

void spawn_food(Point *food, Snake *snake)
{
    int valid = 0;
    while (!valid)
    {
        food->x = 1 + rand() % (WIDTH - 2);
        food->y = 1 + rand() % (HEIGHT - 2);

        valid = 1;

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

void init_snake(Snake *snake)
{
    snake->length = 4;
    snake->dir = 1;
    for (int i = 0; i < snake->length; i++)
    {
        snake->body[i].x = WIDTH / 2 - i;
        snake->body[i].y = HEIGHT / 2;
    }
}

void run_game()
{
    Snake snake;
    Point food;
    int score = 0;
    int running = 1;

    srand(time(NULL));
    init_snake(&snake);
    spawn_food(&food, &snake);
    init_console();

    while (running)
    {
        snake.dir = get_input(snake.dir);

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

        if (next_x <= 0 || next_x >= WIDTH - 1 || next_y <= 0 || next_y >= HEIGHT - 1)
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
        if (next_x == food.x && next_y == food.y)
        {
            snake.length++;
            score += 10;
            spawn_food(&food, &snake);
        }

        for (int i = snake.length - 1; i > 0; i--)
        {
            snake.body[i] = snake.body[i - 1];
        }

        snake.body[0].x = next_x;
        snake.body[0].y = next_y;

        render_frame(&snake, &food, score);
        usleep(DELAY_MS * 1000);
    }

    printf("\033[H\033[J");
    printf("\n\n\t\033[1;31mGAME OVER!\033[0m\n");
    printf("\tFinal Score: %d\n\n", score);
    printf("\033[?25h");
}