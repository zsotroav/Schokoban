#include "printer.h"
#include "data.h"
#include "econio.h"
#include <stdio.h>


void print_all() {
    if (!map_loaded) return;

    for (int i = 0; i < map_height; ++i) {
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