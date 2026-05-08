#ifndef ENGINE_H
#define ENGINE_H

#include "types.h"

void init_console();
void render_frame(Snake *snake, Point *food, int score);
int get_input(int current_dir);

#endif