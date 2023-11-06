#ifndef SCHOKOBAN_MENU_HANDLE_MAIN_H
#define SCHOKOBAN_MENU_HANDLE_MAIN_H

#include "data.h"

/**
 * @brief Main menu movement looper
 * @param type_loc Current selection
 * @return Selection complete: false (to break out of loop)
 */
bool menu_main_move(game_type* type_loc);

/**
 * @brief Open main menu and wait for game type selection
 * @return Selected game type or exit request
 */
game_type menu_main_open();

#endif //SCHOKOBAN_MENU_HANDLE_MAIN_H
