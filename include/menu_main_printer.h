#ifndef SCHOKOBAN_PRINTER_MAIN_H
#define SCHOKOBAN_PRINTER_MAIN_H


/**
 * @brief Print a single item on the main menu
 * @param id ID of the menu item (location)
 * @param highlighted Highlight selection active/inactive
 */
void menu_main_print_highlighted(int id, bool highlighted);

/**
 * @brief Print the full main menu
 */
void menu_main_print();

#endif // SCHOKOBAN_PRINTER_MAIN_H
