#ifndef SCHOKOBAN_PRINTER_LEVEL_H
#define SCHOKOBAN_PRINTER_LEVEL_H

#include <stdbool.h>


/**
 * @brief Print navigation block in level select menu
 * @param direction ture: Right // false: Left
 * @param color (econio) color to print with
 */
void menu_print_level_nav(bool direction, int color);

/**
 * @brief Print a single item on the level screen
 * @param num Number to show
 * @param color (econio) color to print with
 * @param id Sequential ID of the button
 */
void menu_print_level_item(int num, int color, int id);

/**
 * @brief Print the full page of levels (loop through menu_print_level_item)
 * @param page Page no. to  print
 * @param max Maximum number of levels, any more is greyed out 00
 */
void menu_print_level_page(int page, int max);

/**
 * @brief Print the full level selection screen
 * @param page Page to start printing at
 * @param max Maximum number of levels, any more is greyed out 00
 * @return Success/Failure
 */
bool menu_print_level(int page, int max);

#endif // SCHOKOBAN_PRINTER_LEVEL_H
