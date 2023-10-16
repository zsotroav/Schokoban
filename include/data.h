#ifndef SCHOKOBAN_DATA_H
#define SCHOKOBAN_DATA_H

#include <stdbool.h>
#include <stdio.h>

#define get_xy(map, x, y) *(map->map[x * map->width + y])
#define set_xy(map, x, y, value) (*(map->map[x * map->width + y]) = value)
#define indent(map) ((20 - map->width) / 2)
#define go_to_last_move(move) while (move->next != NULL) move = move->next

typedef enum { L, U, R, D, l, u, r, d, x, inv } move_type;

typedef struct move {
    move_type type;
    struct move *prev, *next;
} move;

typedef char map_char[1];

typedef struct {
    char title[50];
    char author[50];
    /**
     * @brief Location of the map data file
     */
    char* loc;
    /**
     * @brief Pointer to the map data file
     */
    FILE *mapptr;

    int player_x;
    int player_y;
    int width;
    int height;
    /**
     * @brief Record number of moves for this level
     */
    int best;

    /**
     * @brief Number of moves made
     */
    int move_cnt;
    /**
     * @brief Number of boxes not on goals yet
     */
    int box;
    map_char *map;
    move *moves;
} map_data;

move* get_next_move(move* prev);

#endif //SCHOKOBAN_DATA_H
