#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "io_map.h"
#include "econio.h"
#include "printer.h"
#include "data.h"
#include "debugmalloc.h"


FILE *mapptr;
FILE *statptr;

bool map_is_valid_char(int c) {
    const char* valid = "@+$*#._- ";
    return strchr(valid, c);
}

bool map_load_stats(const char* loc, bool print) {
    char stats_loc[strlen(loc) + 5];
    memset(stats_loc, 0x00, strlen(loc) + 5);
    strcpy(stats_loc, loc);

    if ((statptr = fopen(strcat(stats_loc, ".dat"), "r")) == NULL) return false;

    fscanf(statptr, "%d ", &map_best);

    if (print) {
        econio_clrscr();
        print_logo();
        printf("    LEADERBOARD\n\nLevel: %s\n%3d ", loc, map_best);

    }

    // TODO: Finish leaderboard printing

    fclose(statptr);
    return true;
}

bool map_open(const char* loc) {
    mapptr = fopen(loc, "r");
    if (mapptr == NULL) return false;

    char c;
    int curr = 0;
    while(( c = fgetc(mapptr) ) != EOF ) {
        if (c == '\n') {
            map_height++;
            if (curr > map_width) map_width = curr;
            curr = 0;
            continue;
        }
        if (!map_is_valid_char(c)) break;
        curr++;
    }

    fseek(mapptr, 0, 0);

    if (map_width == 0 || map_height == 0) return false;

    map = malloc(map_width * map_height);
    memset(map, 0x00, map_width * map_height);

    map_load_stats(loc, false);

    map_loaded = true;
    return true;
}

bool map_load() {
    if (!map_loaded) return false;

    char c;
    int i = 0, j = 0;
    while(( c = fgetc(mapptr) ) != EOF ) {
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
    fclose(mapptr);
    free(map);
}
