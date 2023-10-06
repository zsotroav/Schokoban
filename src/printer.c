#include "printer.h"
#include "data.h"
#include "econio.h"
#include <stdio.h>


void print_all() {
    print_logo();
    print_stats(map_best);
    print_map_all();
    print_controls();
}

void print_map_all() {
    if (!map_loaded) return;

    int indent = (20 - map_width) / 2;
    for (int i = 0; i < map_height; ++i) {
        for (int j = 0; j < indent; ++j) printf(" ");
        for (int j = 0; j < map_width; ++j) {
            print_xy(i, j);
        }
        printf("\n");
    }
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

void print_logo() {
    printf("┏┓┏┓┓┏┏┓┓┏┓┏┓┳┓┏┓┳┓\n"
           "┗┓┃ ┣┫┃┃┃┫ ┃┃┣┫┣┫┃┃\n"
           "┗┛┗┛┛┗┗┛┛┗┛┗┛┻┛┛┗┛┗\n");
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
    econio_gotoxy(0, 14 + map_height );
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