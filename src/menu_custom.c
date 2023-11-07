#include <stdio.h>
#include "data.h"
#include "lib/econio.h"
#include "menu_custom.h"

char* menu_custom_open() {
    econio_clrscr();
    printf("    \n"
           "    \n"
           "    ╔═══════════════════════════╕\n"
           "    ║    ┏┓┏┓┓┏┏┓┓┏┓┏┓┳┓┏┓┳┓    │\n"
           "    ║    ┗┓┃ ┣┫┃┃┃┫ ┃┃┣┫┣┫┃┃    │\n"
           "    ║    ┗┛┗┛┛┗┗┛┛┗┛┗┛┻┛┛┗┛┗    │\n"
           "    ╟───────────────────────────┤\n"
           "    ║        CUSTOM MAPS        │\n"
           "    ║      ───────────────      │\n"
           "    ║   PLEASE INPUT THE PATH   │\n"
           "    ║      TO THE XSB FILE      │\n"
           "    ║                           │\n"
           "    ╙───────────────────────────┘\n"
           "\n"
           "Schokoban > ");

    return read_text();
}