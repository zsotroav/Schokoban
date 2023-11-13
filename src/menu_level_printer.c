#include <stdbool.h>
#include <stdio.h>
#include "lib/econio.h"
#include "menu_level_printer.h"


void menu_print_level_nav(bool direction, int color) {
    int x = direction ? 22 : 8, y = 19;

    econio_textcolor(color);
    econio_gotoxy(x, y);
    printf("╔════╗ ");
    econio_gotoxy(x, ++y);
    printf(direction ? "║ >> ║ " : "║ << ║ ");
    econio_gotoxy(x, ++y);
    printf("╚════╝ ");

    econio_gotoxy(0, 24);
    econio_textcolor(COL_RESET);
}

void menu_print_level_item(int num, int color, int id) {
    econio_textcolor(color);

    // Only here as a backup in case things get messed up
    if (id == 9 || id == 11) {
        menu_print_level_nav(id == 11, color);
        return;
    }

    int x = 8 + (id%3) * 7;
    int y = 10 + (id/3)*3;


    econio_gotoxy(x, y);
    printf("╔════╗ ");
    econio_gotoxy(x, ++y);
    printf("║ %.2d ║ ", num);
    econio_gotoxy(x, ++y);
    printf("╚════╝ ");

    econio_gotoxy(0, 24);
    econio_textcolor(COL_RESET);
}

void menu_print_level_page(int page, int max) {
    for (int i = 0; i < 10; ++i) {
        int level = (page + i < max) ? (page + i + 1) : 0;
        menu_print_level_item(level, level == 0 ? COL_DARKGRAY : COL_RESET, i == 9 ? 10 : i);
    }

    menu_print_level_nav(true, page+10 > max ? COL_DARKGRAY : COL_RESET);
    menu_print_level_nav(false, page == 0 ? COL_DARKGRAY : COL_RESET);
}

bool menu_print_level(int page, int max) {
    if (page * 10 > max || page > 9) return false;
    econio_clrscr();
    page *= 10;

    printf("    \n"
           "    \n"
           "    ╔══════════════════════════╕\n"
           "    ║    ┏┓┏┓┓┏┏┓┓┏┓┏┓┳┓┏┓┳┓   │\n"
           "    ║    ┗┓┃ ┣┫┃┃┃┫ ┃┃┣┫┣┫┃┃   │\n"
           "    ║    ┗┛┗┛┛┗┗┛┛┗┛┗┛┻┛┛┗┛┗   │\n"
           "    ╟──────────────────────────┤\n"
           "    ║        FREE  PLAY        │\n"
           "    ║       LEVEL  SELECT      │\n"
           "    ║    ──────────────────    │\n"
           "    ║   ╔════╗ ╔════╗ ╔════╗   │\n"
           "    ║   ║ 00 ║ ║ 00 ║ ║ 00 ║   │\n"
           "    ║   ╚════╝ ╚════╝ ╚════╝   │\n"
           "    ║   ╔════╗ ╔════╗ ╔════╗   │\n"
           "    ║   ║ 00 ║ ║ 00 ║ ║ 00 ║   │\n"
           "    ║   ╚════╝ ╚════╝ ╚════╝   │\n"
           "    ║   ╔════╗ ╔════╗ ╔════╗   │\n"
           "    ║   ║ 00 ║ ║ 00 ║ ║ 00 ║   │\n"
           "    ║   ╚════╝ ╚════╝ ╚════╝   │\n"
           "    ║   ╔════╗ ╔════╗ ╔════╗   │\n"
           "    ║   ║ << ║ ║ 00 ║ ║ >> ║   │\n"
           "    ║   ╚════╝ ╚════╝ ╚════╝   │\n"
           "    ║                          │\n"
           "    ╙──────────────────────────┘");

    menu_print_level_page(page, max);

    return true;
}
