//
// Created by zsotroav on 2023-10-05.
//

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "map.h"
#include "debugmalloc.h"
#include "econio.h"

typedef char map_char[1];
map_char *map;

int player_x = 0, player_y = 0, map_width = 0, map_height = 0;

FILE *fptr;
bool file_loaded = false;

bool is_valid_map_char(int c) {
    const char* valid = "@+$*#._- ";
    return strchr(valid, c);
}

bool open_map_file(char* loc) {
    fptr = fopen(loc, "r");
    if (fptr == NULL) return false;

    char c, curr = 0;
    while( ( c = fgetc(fptr) ) != EOF ) {
        if (c == '\n') {
            map_height++;
            if (curr > map_width) map_width = curr;
            curr = 0;
            continue;
        }
        if (!is_valid_map_char(c)) break;
        curr++;
    }

    fseek(fptr, 0, 0);

    if (map_width == 0 || map_height == 0) return false;

    map = malloc(map_width * map_height);
    memset(map, 0x00, map_width * map_height);

    file_loaded = true;
    return true;
}

bool load_map_file() {
    if (!file_loaded) return false;

    char c;
    int i = 0, j = 0;
    while( ( c = fgetc(fptr) ) != EOF ) {
        if (c == '\n') {
            i++;
            j = 0;
            continue;
        }
        if (!is_valid_map_char(c)) break;
        *map[i * map_width + j] = c;
        j++;
    }

    return true;
}

void close_map_file() {
    map_width = 0;
    map_height = 0;
    fclose(fptr);
    free(map);
}

void print_xy(int x, int y) {
    econio_textcolor(COL_RESET);
    switch (get_xy(x, y)) {
        case '#': printf("█"); break;
        case '*':
            econio_textcolor(COL_GREEN);
            printf("◼");
            break;
        case '$':
            econio_textcolor(COL_BROWN);
            printf("◼");
            break;
        case '_':
        case '-':
        case ' ': printf(" "); break;
        case '+': econio_textcolor(COL_RED);
        case '@': printf("☻"); break;
        case '.':
            econio_textcolor(COL_RED);
            printf("⨯");
            break;
        default: printf("%c", get_xy(x, y)); break;
    }
    econio_textcolor(COL_RESET);
}

void print_all() {
    if (!file_loaded) return;

    for (int i = 0; i < map_height; ++i) {
        for (int j = 0; j < map_width; ++j) {
            print_xy(i, j);
        }
        printf("\n");
    }
}


