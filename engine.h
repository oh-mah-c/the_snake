#ifndef ENGINE_H
#define ENGINE_H

#include "types.h"

void init_console();
void render_frame(Snake *snake, Point *food, SpecialFood *s_food, int map[HEIGHT][WIDTH], int score);
int get_input(int current_dir);

#endif