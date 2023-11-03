#include "config.h"
#include "lib/debugmalloc.h"
#include "io_level.h"
#include <dirent.h>


char* io_level_fullpath(int id) {
    char* map_name = io_level_get(CFG_MAP_LOC, id);
    if (map_name == NULL) return NULL;

    char* map_loc = malloc(( strlen(map_name) + strlen(CFG_MAP_LOC) + 1) * sizeof(char));
    strcpy(map_loc, CFG_MAP_LOC);
    strcat(map_loc, map_name);
    return map_loc;
}

int io_level_parse(char* directory) {
    DIR *d;
    struct dirent *dir;
    d = opendir(directory);
    if (!d) return -1;

    int i;
    for (i = 0; (dir = readdir(d)) != NULL; ++i)
        if (strcmp(dir->d_name + dir->d_namlen - 4, ".xsb") != 0) i--;

    closedir(d);
    return i;
}

// TODO: Proper order - https://stackoverflow.com/questions/30516546/how-are-dirent-entries-ordered
char* io_level_get(char* directory, int id) {
    DIR *d;
    struct dirent *dir;
    d = opendir(directory);
    if (!d) return NULL;

    int i;
    for (i = 0; (dir = readdir(d)) != NULL; ++i) {
        if (strcmp(dir->d_name + dir->d_namlen - 4, ".xsb") != 0) i--;
        if (i == id) return dir->d_name;
    }
    return NULL;
}