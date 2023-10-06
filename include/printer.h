#ifndef SCHOKOBAN_PRINTER_H
#define SCHOKOBAN_PRINTER_H

/**
 * @brief Prints the full game to the screen
 */
void print_all();

/**
 * @brief Prints every map component to the screen
 */
void print_map_all();

/**
 * @brief Prints the current value to the screen at the given location of the map
 * @param x Map location x
 * @param y Map location y
 */
void print_xy(int x, int y);

void print_logo();

void print_stats(int best);

void print_update_move(int new);

void print_controls();

#endif //SCHOKOBAN_PRINTER_H
