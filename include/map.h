#ifndef SCHOKOBAN_MAP_H
#define SCHOKOBAN_MAP_H

#define get_xy(x, y) *map[x * map_width + y]

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
 * @brief Opens the map file at the given location
 * @param loc Location (including file name) of map file
 * @return Success or Failure to open file
 */
bool open_map_file(char *loc);

/**
 * @brief Loads the contents of the map. Must always be called after open_map_file()
 * @return Success or Failure to load map data.
 */
bool load_map_file();

/**
 * @brief Closes the map file
 */
void close_map_file();

void print_all();

#endif //SCHOKOBAN_MAP_H
