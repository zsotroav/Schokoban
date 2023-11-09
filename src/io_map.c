#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "io_map.h"
#include "printer.h"
#include "data.h"
#include "game.h"
#include "lib/debugmalloc.h"
#include "lib/econio.h"

FILE* get_meta_file(char* loc, char* mode, bool stats) {
    int len = strlen(loc) + 5;
    char *stats_loc = malloc(len);
    strcpy(stats_loc, loc);
    stats_loc[len-1] = '\0';

    FILE* re = fopen(strcat(stats_loc, stats ? ".dat" : ".sav"), mode);
    free(stats_loc);
    return re;
}

char* read_long(FILE* fptr) {
    int n = 1;

    char* text = calloc(2, sizeof(char));
    while((text[n-1] = fgetc(fptr)) != '\n' && text[n-1] != EOF) {
        text = realloc(text, (++n+1) * sizeof(char));
        //if (text == NULL) printf("Error");
    }
    text[n-1] = '\0';

    return text;
}

bool map_load_stats(map_data *map) {
    FILE* statptr = get_meta_file(map->loc, "r", true);
    if (statptr == NULL) return  false;

    fame* curr = map->fame_list;
    while (1) {
        if (fscanf(statptr, "%d ", &(curr->move)) == EOF) break;
        curr->name = read_long(statptr);
        add_new_fame(curr);
        curr = curr->next;
    }
    // First number is always the record
    fscanf(statptr, "%d ", &(map->fame_list->move));

    fclose(statptr);
    return true;
}

bool map_save_moves(map_data *map) {
    FILE* savptr = get_meta_file(map->loc, "w", false);
    if (savptr == NULL) return  false;

    move* curr = map->moves;
    while (curr != NULL) {
        if (curr->type == MV_INV) continue;

        fprintf(savptr, "%c", curr->type);
        curr = curr->next;
    }

    fclose(savptr);
    return true;
}

void map_load_moves(map_data *map, FILE* savptr) {
    char c;
    while (fscanf(savptr, "%c", &c) != EOF) {
        if (!is_valid_move(c)) continue;

        if (c == 'x') game_undo(map);
        else game_mv(map, strchr("UDud", c), strchr("RDrd", c));
    }
}

bool map_save_stats(map_data *map) {
    FILE* statptr = get_meta_file(map->loc, "w", true);
    if (statptr == NULL) return  false;

    fame* curr = map->fame_list;
    for (int i = 0; i < 10 && curr != NULL && curr->move != 0; ++i) {
        fprintf(statptr, "%d %s\n", curr->move, curr->name);
        curr = curr->next;
    }

    fclose(statptr);
    return true;
}

bool meta_exists(char* meta, FILE* fptr) {
    char params[10] = {0};
    fread(params, 1, strlen(meta), fptr);
    return (strcmp(params, meta) == 0);
}

map_data* map_open(char* loc) {
    // Open XSB for reading
    FILE* mapptr = fopen(loc, "r");
    if (mapptr == NULL) return NULL;

    // Create and initialize map data
    map_data *map = map_init(loc);

    fscanf(mapptr, "%d,%d\n", &map->width, &map->height);
    if (map->width == 0 || map->height == 0) return NULL;

    // malloc the required space for the map data
    map->map = malloc((map->width * map->height * sizeof(char)));
    memset(map->map, 0x00, map->width * map->height);

    map_load(map, mapptr);

    // no T because that was already read above
    map->title  = meta_exists("itle: ", mapptr)   ? read_long(mapptr) : loc;
    map->author = meta_exists("Author: ", mapptr) ? read_long(mapptr) : calloc(1, sizeof(char));

    map_load_stats(map);

    fclose(mapptr);
    return map;
}

void map_load(map_data* map, FILE* mapptr) {
    char c;
    int i = 0, j = 0;
    while(( c = fgetc(mapptr) ) != EOF ) {
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
    FILE* mapptr = fopen(map->loc, "r");
    if (mapptr == NULL) {
        map->functional = false;
        return;
    }

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
    last->type = MV_INV;

    // Completely reload map
    fscanf(mapptr, "%*d,%*d\n");
    map_load(map, mapptr);

    print_all(map);

    fclose(mapptr);
}

void map_close(map_data *map) {
    move* last = map->moves;
    go_to_last_move(last);
    while (last->prev != NULL) {
        last = last->prev;
        free(last->next);
    }
    free(last);

    fame *prev_fame = NULL, *curr_fame = map->fame_list;
    while (curr_fame != NULL && curr_fame->move != 0){
        prev_fame = curr_fame;
        curr_fame = curr_fame->next;
        free(prev_fame->name);
        free(prev_fame);
    }

    free(curr_fame);
    free(map->loc);
    free(map->title);
    free(map->author);
    free(map->map);
    free(map);
}
