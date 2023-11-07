#include <dirent.h>
#include <math.h>
#include "config.h"
#include "lib/debugmalloc.h"
#include "io_level.h"


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

char* io_level_get(char* directory, int id) {
    int size = sizeof(char) * (
            ceil((double) log10(id + 0.1))    // Length of the number
            + 4                              // .xsb
            + strlen(directory)              // /path/to/
            + 1);                            // '\0'
    char *level = malloc(size);

    strcpy(level, directory);
    sprintf(level + strlen(level), "%d", id);
    strcat(level, ".xsb");

    FILE *f = fopen(level, "r");

    if (f == NULL) {
        free(level);
        return NULL;
    }
    fclose(f);
    return level;
}