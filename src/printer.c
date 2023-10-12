#include "printer.h"
#include "data.h"
#include "econio.h"
#include <stdio.h>


void print_all(map_data *map) {
    econio_clrscr();
    print_logo();
    print_metadata(map);
    print_stats(map->best);
    print_map_all(map);
    print_controls();
}

void print_map_all(map_data *map) {
    for (int i = 0; i < map->height; ++i) {
        for (int j = 0; j < indent(map); ++j) printf(" ");
        for (int j = 0; j < map->width; ++j) {
            print_xy(map, j, i);
        }
        printf("\n");
    }
}

void print_xy(map_data *map, int x, int y) {
    econio_textcolor(COL_RESET);
    switch (get_xy(map, x, y)) {
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
        default: printf("%c", get_xy(map, x, y)); break;
    }
    econio_textcolor(COL_RESET);
}

void print_xy_offset(map_data *map, int x, int y) {
    econio_gotoxy(indent(map) + x, 6 + y);
    print_xy(map, x, y);
    econio_gotoxy(0, 14 + map->height );
}

void print_logo() {
    printf("┏┓┏┓┓┏┏┓┓┏┓┏┓┳┓┏┓┳┓\n"
           "┗┓┃ ┣┫┃┃┃┫ ┃┃┣┫┣┫┃┃\n"
           "┗┛┗┛┛┗┗┛┛┗┛┗┛┻┛┛┗┛┗\n");
}

void print_metadata(map_data* map) {
    if (map->title[0] == '\0') return;

    econio_gotoxy(22, 0);
    printf("Map: ");
    econio_gotoxy(22, 1);
    printf("%s", map->title);

    if (map->creator[0] != '\0') {
        econio_gotoxy(22, 2);
        printf("by %s", map->creator);
    }
    econio_gotoxy(0, 3);
}

void print_stats(int best) {
    printf("    Moves:   0     \n"
           "    Best:  %3d   \n\n", best);
    if (best == 0) {
        econio_gotoxy(11, 4);
        printf("N/A\n\n");
    }
}

void print_update_move(int new){
    econio_gotoxy(11, 3);
    printf("%3d", new);
}

void print_controls() {
    printf("\n\n"
           "    ╔═══╗     ╔═══╗   ╔═══╗\n"
           "    ║ W ║     ║ R ║   ║ESC║\n"
           "    ╚═══╝     ╚═══╝   ╚═══╝\n"
           "╔═══╗╔═══╗╔═══╗       ╔═══╗\n"
           "║ A ║║ S ║║ D ║       ║ U ║\n"
           "╚═══╝╚═══╝╚═══╝       ╚═══╝\n");
}