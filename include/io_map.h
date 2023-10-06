#ifndef SCHOKOBAN_IO_MAP_H
#define SCHOKOBAN_IO_MAP_H


/**
 * @brief Opens the map file at the given location
 * @param loc Location (including file name) of map file
 * @return Success or Failure to open file
 */
bool map_open(const char *loc);

/**
 * @brief Loads the contents of the map. Must always be called after map_open()
 * @return Success or Failure to load map data.
 */
bool map_load();

/**
 * @brief Closes the map file
 */
void map_close();

void print_all();

#endif //SCHOKOBAN_IO_MAP_H
