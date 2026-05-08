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
    int ghost_steps;
    int poison_timer;
    int length;
    int dir;
} Snake;

typedef enum
{
    FOOD_NONE = 0,
    FOOD_GOLD,
    FOOD_POISON,
    FOOD_GHOST
} FoodType;

typedef struct
{
    Point pos;
    FoodType type;
    int active;
    int ttl;
} SpecialFood;

#endif