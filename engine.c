#include <stdio.h>
#include <conio.h>
#include "engine.h"

void init_console()
{
    printf("\033[?25l\033[H\033[J");
    fflush(stdout);
}

void render_frame(Snake *snake, Point *food, int score)
{
    char buffer[(WIDTH + 1) * HEIGHT + 100];
    int pos = 0;

    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            if (x == 0 || x == WIDTH - 1 || y == 0 || y == HEIGHT - 1)
            {
                pos += sprintf(&buffer[pos], "#");
            }
            else if (x == food->x && y == food->y)
            {
                pos += sprintf(&buffer[pos], "\033[1;31m*\033[0m");
            }
            else
            {
                int is_body = 0;
                for (int i = 0; i < snake->length; i++)
                {
                    if (snake->body[i].x == x && snake->body[i].y == y)
                    {
                        if (i == 0)
                        {
                            pos += sprintf(&buffer[pos], "\033[1;32mO\033[0m");
                        }
                        else
                        {
                            pos += sprintf(&buffer[pos], "\033[0;32mo\033[0m");
                        }

                        is_body = 1;
                        break;
                    }
                }

                if (!is_body)
                {
                    pos += sprintf(&buffer[pos], " ");
                }
            }
        }
        buffer[pos++] = '\n';
    }

    pos += sprintf(&buffer[pos], "\033[1;33mScore: %d\033[0m\n", score);
    buffer[pos] = '\0';

    printf("\033[H");
    fputs(buffer, stdout);
    fflush(stdout);
}

int get_input(int current_dir)
{
    if (_kbhit())
    {
        int ch = _getch();
        if (ch == 0 || ch == 224)
        {
            ch = _getch();
        }

        switch (ch)
        {
        case 'w':
        case 72:
            if (current_dir != 2)
                return 0;
            break;
        case 'd':
        case 77:
            if (current_dir != 3)
                return 1;
            break;
        case 's':
        case 80:
            if (current_dir != 0)
                return 2;
            break;
        case 'a':
        case 75:
            if (current_dir != 1)
                return 3;
            break;
        }
    }

    return current_dir;
}