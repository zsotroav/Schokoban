#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "io_map.h"
#include "econio.h"
#include "printer.h"
#include "data.h"
#include "debugmalloc.h"


bool map_load_stats(map_data *map, bool print) {
    // Open stats file, which is just the xsb map file with .dat at the end
    FILE *statptr;
    char stats_loc[strlen(map->loc) + 5];
    memset(stats_loc, 0x00, strlen(map->loc) + 5);
    strcpy(stats_loc, map->loc);

    if ((statptr = fopen(strcat(stats_loc, ".dat"), "r")) == NULL) return false;

    // First number is always the record
    fscanf(statptr, "%d ", &(map->best));

    // If we're here to print the leaderboard and not just read the record:
    if (print) {
        econio_clrscr();
        print_logo();
        printf("    LEADERBOARD\n\nLevel: %s\n%3d ", map->title, map->best);

    }

    // TODO: Finish leaderboard printing

    fclose(statptr);
    return true;
}

map_data* map_open(char* loc) {
    // Create and initialize map data
    map_data *map = malloc(sizeof *map);

    map->loc = malloc(strlen(loc));
    map->loc = loc;
    map->width = 0;
    map->height = 0;
    map->best = 0;
    map->move_cnt = 0;
    map->box = 0;

    // Open XSB for reading
    map->mapptr = fopen(loc, "r");
    if (map->mapptr == NULL) return NULL;

    char c;
    int curr = 0; // Current width
    while(( c = fgetc(map->mapptr) ) != EOF ) {
        if (c == '\n') {
            (map->height)++;
            if (curr > map->width) map->width = curr;
            curr = 0;
            continue;
        }
        if (!map_is_valid_char(c)) break;
        curr++;
    }

    // Reset the file read head for potential future use
    fseek(map->mapptr, 0, 0);

    if (map->width == 0 || map->height == 0) return NULL;

    // malloc the required space for the map data
    map->map = malloc(map->width * map->height);
    memset(map->map, 0x00, map->width * map->height);

    map_load_stats(map, false);

    return map;
}

bool map_load(map_data *map) {
    char c;
    int i = 0, j = 0;
    while(( c = fgetc(map->mapptr) ) != EOF ) {
        if (c == '\n') {
            i++;
            j = 0;
            continue;
        }
        if (!map_is_valid_char(c)) break;
        set_xy(map, j++, i, c);
        if (c == '@' || c == '+') {
            map->player_x = j - 1;
            map->player_y = i;
        }
        if (c == '$') map->box++;
    }

    fseek(map->mapptr, 0, 0);
    return true;
}

void map_close(map_data *map) {
    fclose(map->mapptr);
    free(map->title);
    free(map->loc);
    free(map->map);
    free(map);
}
