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
    int len = strlen(map->loc) + 5;
    char *stats_loc = malloc(len);
    memset(stats_loc, 0x00, len);
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

    free(stats_loc);
    fclose(statptr);
    return true;
}

void map_init(map_data* map, char* loc){
    // Initialize map metadata
    memset(map->title, 0, 50);
    memset(map->creator, 0, 50);
    map->loc = malloc(strlen(loc) + 1);
    strcpy(map->loc, loc);
    map->width = 0;
    map->height = 0;
    map->best = 0;
    map->move_cnt = 0;
    map->box = 0;
    map->moves = malloc(sizeof(move));
    map->moves->prev = NULL;
    map->moves->next = NULL;
    map->moves->type = inv;
}

map_data* map_open(char* loc) {
    // Create and initialize map data
    map_data *map = malloc(sizeof *map);
    map_init(map, loc);

    // Open XSB for reading
    map->mapptr = fopen(loc, "r");
    if (map->mapptr == NULL) return NULL;

    fscanf(map->mapptr, "%d,%d\n", &map->width, &map->height);
    if (map->width == 0 || map->height == 0) return NULL;

    // malloc the required space for the map data
    map->map = malloc(map->width * map->height);
    memset(map->map, 0x00, map->width * map->height);

    map_load(map);

    char c;
    char params[9] = {0};
    fread(params, 1, 6, map->mapptr);
    if (strcmp(params, "itle: ") == 0) { // no T because that was already read above
        int i = 0;
        while(( c = fgetc(map->mapptr) ) != EOF && c != '\n' && i < 50)
            map->title[i++] = c;
    }

    fread(params, 1, 8, map->mapptr);
    if (strcmp(params, "Author: ") == 0) {
        int i = 0;
        while(( c = fgetc(map->mapptr) ) != EOF && c != '\n' && i < 50)
            map->creator[i++] = c;
    }

    // Reset the file read head for potential future use
    fseek(map->mapptr, 0, 0);

    map_load_stats(map, false);

    return map;
}

void map_load(map_data* map) {
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
}

void map_reset(map_data *map) {
    // Reset values
    map->move_cnt = 0;
    map->box = 0;

    // Free all moves except the first
    move* last = map->moves;
    go_to_last_move(last);
    while (last->prev != NULL) {
        last = last->prev;
        free(last->next);
    }
    last->next = NULL;

    // Completely reload map
    fscanf(map->mapptr, "%*d,%*d\n");
    map_load(map);

    print_all(map);

    fseek(map->mapptr, 0, 0);
}

void map_close(map_data *map) {
    move* last = map->moves;
    go_to_last_move(last);
    while (last->prev != NULL) {
        last = last->prev;
        free(last->next);
    }
    free(last);

    fclose(map->mapptr);
    free(map->loc);
    free(map->map);
    free(map);
}
