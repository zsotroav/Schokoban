#ifndef SCHOKOBAN_HANDLE_LEVEL_H
#define SCHOKOBAN_HANDLE_LEVEL_H


/**
 * @brief Highlight level menu item
 * @param id ID of the menu item (location on page)
 * @param page Current page in view (for number calculation)
 * @param max Maximum number of available levels (any more is greyed out)
 * @param active State to highlight
 */
void menu_level_highlight(int id, int page, int max, bool active);

/**
 * @brief Move level selection
 * @param loc Current location
 * @param page Current page
 * @param max Maximum number of available levels
 * @return Selection complete: false (to break out of loop)
 */
bool menu_level_move(int* loc, int* page, int max);

/**
 * @brief Open level select menu and wait for completed selection
 * @return Selected level's number
 */
int menu_level_open();

#endif // SCHOKOBAN_HANDLE_LEVEL_H
