#include <stdlib.h>
#include "map.h"

int validate_map(int map[HEIGHT][WIDTH])
{
    int visited[HEIGHT][WIDTH] = {0};
    Point queue[WIDTH * HEIGHT];
    int head = 0, tail = 0;
    int empty_count = 0;
    int start_x = -1, start_y = -1;

    for (int y = 1; y < HEIGHT - 1; y++)
    {
        for (int x = 1; x < WIDTH - 1; x++)
        {
            if (map[y][x] == 0)
            {
                empty_count++;
                if (start_x == -1)
                {
                    start_x = x;
                    start_y = y;
                }
            }
        }
    }

    queue[tail].x = start_x;
    queue[tail].y = start_y;
    tail++;
    visited[start_y][start_x] = 1;
    int reachable = 0;

    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};

    while (head < tail)
    {
        Point p = queue[head++];
        reachable++;

        for (int i = 0; i < 4; i++)
        {
            int nx = p.x + dx[i];
            int ny = p.y + dy[i];

            if (nx > 0 && nx < WIDTH - 1 && ny > 0 && ny < HEIGHT - 1)
            {
                if (map[ny][nx] == 0 && !visited[ny][nx])
                {
                    visited[ny][nx] = 1;
                    queue[tail].x = nx;
                    queue[tail].y = ny;
                    tail++;
                }
            }
        }
    }

    return reachable == empty_count;
}

void generate_map(int map[HEIGHT][WIDTH], unsigned int seed)
{
    srand(seed);

    while (1)
    {
        for (int y = 0; y < HEIGHT; y++)
        {
            for (int x = 0; x < WIDTH; x++)
            {
                if (x == 0 || x == WIDTH - 1 || y == 0 || y == HEIGHT - 1)
                {
                    map[y][x] = 1;
                }
                else
                {
                    map[y][x] = 0;
                }
            }
        }

        int num_walls = 20 + rand() % 25;
        for (int i = 0; i < num_walls; i++)
        {
            int wx = 2 + rand() % (WIDTH - 4);
            int wy = 2 + rand() % (HEIGHT - 4);
            int len = 2 + rand() % 5;
            int is_horiz = rand() % 2;

            for (int j = 0; j < len; j++)
            {
                if (is_horiz && wx + j < WIDTH - 2)
                {
                    map[wy][wx + j] = 1;
                }
                else if (!is_horiz && wy + j < HEIGHT - 2)
                {
                    map[wy + j][wx] = 1;
                }
            }
        }

        int cx = WIDTH / 2;
        int cy = HEIGHT / 2;
        for (int y = cy - 2; y <= cy + 2; y++)
        {
            for (int x = cx - 5; x <= cx + 5; x++)
            {
                map[y][x] = 0;
            }
        }

        if (validate_map(map))
        {
            break;
        }
    }
}