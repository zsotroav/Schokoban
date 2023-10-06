#ifndef SCHOKOBAN_DATA_H
#define SCHOKOBAN_DATA_H

#include <stdbool.h>

#define get_xy(x, y) *map[x * map_width + y]

/**
 * @brief Map's loaded status - Any other data value should be
 * considered garbage data if this is false
 */
extern bool map_loaded;

/**
 * @brief X coordinate of the player character
 */
extern int player_x;
/**
 * @brief Y coordinate of player character
 */
extern int player_y;
/**
 * @brief Width of current map
 */
extern int map_width;
/**
 * @brief Height of current map
 */
extern int map_height;
/**
 * @brief Best (least moves) run for this level. 0 if no data.
 */
extern int map_best;

typedef char map_char[1];
extern map_char *map;

#endif //SCHOKOBAN_DATA_H
