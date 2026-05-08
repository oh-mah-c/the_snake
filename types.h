#ifndef TYPES_H
#define TYPES_H

#include "config.h"

typedef struct
{
    int x;
    int y;
} Point;

typedef struct
{
    Point body[WIDTH * HEIGHT];
    int length;
    int dir;
} Snake;

#endif