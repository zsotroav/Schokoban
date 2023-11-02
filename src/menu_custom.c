#include <stdio.h>
#include "lib/debugmalloc.h"
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


    int n = 1;

    char* text = calloc(2, sizeof(char));
    while((text[n-1] = fgetc(stdin)) != '\n' && text[n-1] != EOF) {
        text = realloc(text, (++n+1) * sizeof(char));
        //if (text == NULL) printf("Error");
    }
    text[n-1] = '\0';

    return text;
}