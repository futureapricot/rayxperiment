#ifndef STATS_H
#define STATS_H

#include "stddef.h"
#include "raylib.h"

void update_stats(size_t ph_fc, size_t rd_fc, double ph_time, double dt);
void draw_stats(Font f, int ox, int oy);

#endif /* STATS_H */