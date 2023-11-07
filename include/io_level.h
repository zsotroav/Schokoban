#ifndef SCHOKOBAN_IO_LEVEL_H
#define SCHOKOBAN_IO_LEVEL_H

/**
 * @brief Get the full path based on config directory
 * @param id ID of the map file
 * @return full (relative) path to the XSB
 */
#define io_level_fullpath(id) io_level_get(CFG_MAP_LOC, (id))


/**
 * @brief Get the number of xsb files in the directory
 * @note This function does not validate if the XSB files are valid
 * @param directory Directory to search in
 * @return The number of xsb files
 */
int io_level_parse(char* directory);

/**
 * @brief Get the file name of the map with a specific id
 * @param directory Directory to search in
 * @param id Number of the map file
 * @return File name
 */
char* io_level_get(char* directory, int id);

#endif // SCHOKOBAN_IO_LEVEL_H
