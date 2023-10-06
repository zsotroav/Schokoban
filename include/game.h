#ifndef SCHOKOBAN_GAME_H
#define SCHOKOBAN_GAME_H

#include <stdbool.h>
#include "data.h"

#define obstr_ext(c) strchr("#$*", c)
#define is_box(c) strchr("$*", c)

/**
 * @brief Initialize and begin game on the given level
 * @param level Path to the XSB file for the map
 * @return generated map data
 */
map_data* game_init(const char* level);

void game_end(map_data *map);

/**
 * @brief Wait for and handle input
 * @return false if game is completed or aborted, true otherwise
 */
bool game_wait_input(map_data *map);

/**
 * @brief Attempt to move the player
 * @param ud Indicate if movement is on the ud axis
 * @param rd true: Right or Left movement
 */
void game_mv(map_data *map, bool ud, bool rd);

#endif //SCHOKOBAN_GAME_H
