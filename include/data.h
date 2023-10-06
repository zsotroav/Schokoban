#ifndef SCHOKOBAN_DATA_H
#define SCHOKOBAN_DATA_H

#include <stdbool.h>
#include <stdio.h>

#define get_xy(map, x, y) *(map->map[x * map->width + y])
#define set_xy(map, x, y, value) (*(map->map[x * map->width + y]) = value)
#define indent(map) ((20 - map->width) / 2)

typedef enum { L, U, R, D, l, u, r, d, x } move_type;

typedef struct {
    move_type type;
    struct move *prev, *next;
} move;

typedef char map_char[1];

typedef struct {
    FILE *mapptr;
    FILE *statptr;

    int player_x;
    int player_y;
    int width;
    int height;
    int best;
    int move_cnt;
    map_char *map;
} map_data;

#endif //SCHOKOBAN_DATA_H
