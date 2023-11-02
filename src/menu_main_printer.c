#include <stdio.h>
#include <stdbool.h>
#include "lib/econio.h"
#include "menu_main_printer.h"

void menu_print_highlighted(int id, bool highlighted) {
    econio_textcolor(highlighted ? COL_LIGHTCYAN : COL_RESET);
    switch (id) {
        case 0:
            econio_gotoxy(11, 9);
            printf("╔═════════════╗");
            econio_gotoxy(11, 10);
            printf("║ ARCADE MODE ║");
            econio_gotoxy(11, 11);
            printf("╚═════════════╝");
            break;
        case 1:
            econio_gotoxy(12, 12);
            printf("╔═══════════╗");
            econio_gotoxy(12, 13);
            printf("║ FREE PLAY ║");
            econio_gotoxy(12, 14);
            printf("╚═══════════╝");
            break;
        case 2:
            econio_gotoxy(11, 15);
            printf("╔═════════════╗");
            econio_gotoxy(11, 16);
            printf("║ CUSTOM MAPS ║");
            econio_gotoxy(11, 17);
            printf("╚═════════════╝");
            break;
    }
    econio_gotoxy(0, 24);
    econio_textcolor(COL_RESET);
}

void menu_print_main() {
    econio_clrscr();
    printf("    \n"
           "    \n"
           "    ╔═══════════════════════════╕\n"
           "    ║    ┏┓┏┓┓┏┏┓┓┏┓┏┓┳┓┏┓┳┓    │\n"
           "    ║    ┗┓┃ ┣┫┃┃┃┫ ┃┃┣┫┣┫┃┃    │\n"
           "    ║    ┗┛┗┛┛┗┗┛┛┗┛┗┛┻┛┛┗┛┗    │\n"
           "    ╟───────────────────────────┤\n"
           "    ║         GAME MODE         │\n"
           "    ║      ───────────────      │\n"
           "    ║      ╔═════════════╗      │\n"
           "    ║      ║ ARCADE MODE ║      │\n"
           "    ║      ╚═════════════╝      │\n"
           "    ║       ╔═══════════╗       │\n"
           "    ║       ║ FREE PLAY ║       │\n"
           "    ║       ╚═══════════╝       │\n"
           "    ║      ╔═════════════╗      │\n"
           "    ║      ║ CUSTOM MAPS ║      │\n"
           "    ║      ╚═════════════╝      │\n"
           "    ║                           │\n"
           "    ╙───────────────────────────┘");
    menu_print_highlighted(0, true);
}