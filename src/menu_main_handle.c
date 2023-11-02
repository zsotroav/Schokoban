#include "data.h"
#include "menu_main_printer.h"
#include "menu_level_handle.h"
#include "lib/econio.h"
#include <stdbool.h>

bool menu_main_move(game_type * type_loc) {
    econio_rawmode();
    while (!econio_kbhit()) econio_sleep(0.2);
    int prev = -1;

    switch (econio_getch()) {
        case 'w': case KEY_UP:
            if (*type_loc == 0) break;
            prev = *type_loc; --*type_loc; break;
        case 's': case KEY_DOWN:
            if (*type_loc == 2) break;
            prev = *type_loc; ++*type_loc; break;
        case ' ': case KEY_ENTER:
            // Selection finished, break out of loop
            return false;
        default: return true;
    }

    menu_print_highlighted(prev, false);
    menu_print_highlighted(*type_loc, true);

    return true;
}

game_type menu_main_open() {
    menu_print_main();

    game_type type = 0;
    while (menu_main_move(&type)) ;

    return type;
}