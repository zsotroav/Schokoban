#ifndef SCHOKOBAN_IO_MAP_H
#define SCHOKOBAN_IO_MAP_H

#include "data.h"

#define map_is_valid_char(c) strchr("@+$*#._- ", c)

/**
 * @brief Save the stats of the map into the appropriate data file
 * @param map Map data
 * @return Success or Failure to save.
 */
bool map_save_stats(map_data *map);

/**
 * @brief Opens the given map file
 * @param loc relative or absolute path to the xsb map file
 * @return generated map data
 */
map_data* map_open(char *loc);

/**
 * @brief Loads the contents of the map. Must always be called after map_open()
 * @return Success or Failure to load map data.
 */
void map_load(map_data *map, FILE* mapptr);

void map_reset(map_data *map);
/**
 * @brief Closes the map file
 */
void map_close(map_data *map);


#endif //SCHOKOBAN_IO_MAP_H
