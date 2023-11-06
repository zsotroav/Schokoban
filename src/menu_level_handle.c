#include "config.h"
#include "io_level.h"
#include "lib/econio.h"
#include "menu_level_printer.h"
#include <stdbool.h>

#define NUM(page, id) ((page) * (10) + (id) + (1))
#define OVER(page, id, max) (bool)((max) < (NUM((page), (id))))

void menu_level_highlight(int id, int page, int max, bool active) {
    if (id < 0) return;
    menu_print_level_item(OVER(page, id, max) ? 0 : NUM(page, id),
                          active ? OVER(page, id, max) ? COL_BLUE : COL_LIGHTCYAN
                                 : OVER(page, id, max) ? COL_DARKGRAY : COL_RESET,
                          id);
}

bool menu_level_move(int* loc, int* page, int max) {
    while (!econio_kbhit()) econio_sleep(0.2);
    int prev = -1;

    switch (econio_getch()) {
        // Directional movements
        case 'w': case KEY_UP:
            if (*loc - 3 < 0) break;  // Don't go out of bounds
            prev = *loc;
            *loc -= 3; break;
        case 'a': case KEY_LEFT:
            if (*loc < 1) break;
            prev = (*loc)--; break;
        case 's': case KEY_DOWN:
            if (*loc + 3 > 11) break;
            prev = *loc;
            *loc += 3; break;
        case 'd': case KEY_RIGHT:
            if (*loc > 10) break;
            prev = (*loc)++; break;

        //Selection confirm
        case KEY_ENTER:
        case ' ':
            switch (*loc) { // Action depends on the current location
                case 9:  // "<<" (previous page button)
                    if (*page > 0) {
                        // Don't under index if we are on the first page
                        menu_print_level_page(--*page, max);
                        break;
                    }
                case 11: // ">>" (next page button)
                    if (OVER((*page) * 10 + 1, 0, max))  break; // Don't over index if we don't have any more pages
                    menu_print_level_page(++*page, max); break;
                default: // Regular map number
                    // Don't open a map if it isn't available (grey 00)
                    if (OVER((*page), *loc, max)) break;
                    // False --> We got a result, break out of the loop
                    return false;
            }
            break;

        case KEY_ESCAPE: case KEY_BACKSPACE:
            *loc = -1; return false;
    }

    // Update the UI highlights
    menu_level_highlight(*loc, *page, max, true);
    menu_level_highlight(prev, *page, max, false);

    // True --> continue the loop because we aren't done selecting yet
    return true;
}

int menu_level_open() {
    int max = io_level_parse(CFG_MAP_LOC);
    int page = 0;
    if (!menu_print_level(page, max)) return -1;

    int loc = 0;
    menu_level_highlight(loc, page, max, true);

    while (econio_kbhit()) { econio_getch(); econio_sleep(0.2); }

    while(menu_level_move(&loc, &page, max)) ;

    return loc < 0 ? -1 : page*10 + loc;
}