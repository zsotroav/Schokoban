#ifndef SCHOKOBAN_IO_MAP_H
#define SCHOKOBAN_IO_MAP_H

#include "data.h"

#define map_is_valid_char(c) strchr("@+$*#._- ", c)

/**
 * @brief Get the xsb metadata file's name, which is the file name with .dat/.sav at the end
 * @param loc Location of the XSB file
 * @param stat true = stats file // false = save file
 * @return Malloced string
 */
char* get_meta_file_name(char* loc, bool stats);

/**
 * @brief Open stats/save state file, which is just the xsb map file with .dat/.sav at the end
 * @param loc Location of the XSB file
 * @param mode File open mode
 * @param stat true = stats file // false = save file
 * @return File pointer to the stats file
 */
FILE* get_meta_file(char* loc, char* mode, bool stat);

/**
 * @brief Read undefined length line
 * @param fptr File pointer to read from
 * @return Malloced string
 */
char* read_long(FILE* fptr);

/**
 * @brief Load the stats (leaderboard) of the map from the appropriate data file
 * @param map Pointer to map data
 * @return Success or Failure to load.
 */
bool map_load_stats(map_data *map);

/**
 * @brief Save the moves of the map to the appropriate data file
 * @param map Pointer to map data
 * @return Success or Failure to save.
 */
bool map_save_moves(map_data *map);

/**
 * @brief Load the moves of the map from the data file
 * @param map Pointer to map data
 * @param savptr FILE* to save file
 */
void map_load_moves(map_data *map, FILE* savptr);

/**
 * @brief Save the stats of the map into the appropriate data file
 * @param map Pointer to map data
 * @return Success or Failure to save.
 */
bool map_save_stats(map_data *map);

/**
 * @brief Check if given metadata value is in the file at the expected location
 * @param meta Metadata name
 * @param fptr XSB file pointer
 * @return true/false based on result
 */
bool meta_exists(char* meta, FILE* fptr);

/**
 * @brief Opens the given map file
 * @param loc relative or absolute path to the xsb map file
 * @return generated map data
 */
map_data* map_open(char *loc);

/**
 * @brief Loads the contents of the map. Must always be called after map_open()
 * @param map Pointer to map data
 * @param mapptr file pointer to map file
 * @return Success or Failure to load map data.
 */
void map_load(map_data *map, FILE* mapptr);

/**
 * @brief Lazily (only doing what's necessary) resets the map from the map file
 * @param map Pointer to map data
 */
void map_reset(map_data *map);

/**
 * @brief Closes the map file and frees all allocated memory for the map
 * @param map Pointer to map data
 */
void map_close(map_data *map);

#endif // SCHOKOBAN_IO_MAP_H
