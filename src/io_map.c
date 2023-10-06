#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "io_map.h"
#include "econio.h"
#include "printer.h"
#include "data.h"
#include "debugmalloc.h"


bool map_load_stats(map_data *map, const char* loc, bool print) {
    char stats_loc[strlen(loc) + 5];
    memset(stats_loc, 0x00, strlen(loc) + 5);
    strcpy(stats_loc, loc);

    if ((map->statptr = fopen(strcat(stats_loc, ".dat"), "r")) == NULL) return false;

    fscanf(map->statptr, "%d ", &(map->best));

    if (print) {
        econio_clrscr();
        print_logo();
        printf("    LEADERBOARD\n\nLevel: %s\n%3d ", loc, map->best);

    }

    // TODO: Finish leaderboard printing

    fclose(map->statptr);
    return true;
}

map_data* map_open(const char* loc) {
    map_data *map = malloc(sizeof *map);
    map->width = 0;
    map->height = 0;

    map->mapptr = fopen(loc, "r");
    if (map->mapptr == NULL) return false;

    char c;
    int curr = 0;
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

    fseek(map->mapptr, 0, 0);

    if (map->width == 0 || map->height == 0) return false;

    map->map = malloc(map->width * map->height);
    memset(map->map, 0x00, map->width * map->height);

    map_load_stats(map, loc, false);

    return map;
}

bool map_load(map_data *map) {
    map->move_cnt = 0;

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
    }

    fseek(map->mapptr, 0, 0);
    return true;
}

void map_close(map_data *map) {
    fclose(map->mapptr);
    free(map->map);
    free(map);
}
