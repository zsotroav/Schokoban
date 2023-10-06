#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "io_map.h"
#include "data.h"
#include "debugmalloc.h"

FILE *fptr;

bool map_is_valid_char(int c) {
    const char* valid = "@+$*#._- ";
    return strchr(valid, c);
}

bool map_open(char* loc) {
    fptr = fopen(loc, "r");
    if (fptr == NULL) return false;

    char c;
    int curr = 0;
    while( ( c = fgetc(fptr) ) != EOF ) {
        if (c == '\n') {
            map_height++;
            if (curr > map_width) map_width = curr;
            curr = 0;
            continue;
        }
        if (!map_is_valid_char(c)) break;
        curr++;
    }

    fseek(fptr, 0, 0);

    if (map_width == 0 || map_height == 0) return false;

    map = malloc(map_width * map_height);
    memset(map, 0x00, map_width * map_height);

    map_loaded = true;
    return true;
}

bool map_load() {
    if (!map_loaded) return false;

    char c;
    int i = 0, j = 0;
    while( ( c = fgetc(fptr) ) != EOF ) {
        if (c == '\n') {
            i++;
            j = 0;
            continue;
        }
        if (!map_is_valid_char(c)) break;
        *map[i * map_width + j] = c;
        j++;
    }

    return true;
}

void map_close() {
    map_width = 0;
    map_height = 0;
    fclose(fptr);
    free(map);
}
