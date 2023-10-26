#ifndef SCHOKOBAN_PRINTER_H
#define SCHOKOBAN_PRINTER_H

#include "data.h"

#define cursor_bottom(map) econio_gotoxy(0, 13 + map->height)

/**
 * @brief Prints the full game to the screen
 */
void print_all(map_data *map);

/**
 * @brief Prints every map component to the screen
 */
void print_map_all(map_data *map);

/**
 * @brief Prints the current value to the screen at the given location of the map,
 * does not offset the print, prints wherever we're currently at
 * @param x Map location x
 * @param y Map location y
 */
void print_xy(map_data *map, int x, int y);

/**
 * @brief Prints the current value to the screen at the given location of the map,
 * with the appropriate amount of offset
 * @param x Map location of x
 * @param y Map location of y
 */
void print_xy_offset(map_data *map, int x, int y);

/**
 * @brief Print the logo and available map metadata (title, author, record)
 * @param map Pointer to map data
 */
void print_meta(map_data* map);

/**
 * @brief Update the number of moves displayed
 * @param new New number to show
 */
void print_update_move(int new);

/**
 * @brief Prints the control hints to the screen at current cursor position
 */
void print_controls();

/**
 * @brief Print the leaderboard of the map
 * @param map Pointer to map data
 */
void print_leaderboard(map_data* map);

#endif //SCHOKOBAN_PRINTER_H
