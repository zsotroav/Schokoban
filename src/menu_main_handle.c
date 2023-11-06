#include <stdbool.h>
#include "data.h"
#include "menu_main_printer.h"
#include "lib/econio.h"

bool menu_main_move(game_type* type_loc) {
    while (!econio_kbhit()) econio_sleep(0.2);
    int prev = -1;

    switch (econio_getch()) {
        case 'w': case KEY_UP:
            if (*type_loc == 0) break;
            prev = *type_loc; --*type_loc; break;
        case 's': case KEY_DOWN:
            if (*type_loc == 3) break;
            prev = *type_loc; ++*type_loc; break;
        case ' ': case KEY_ENTER: return false;
        default: return true;
    }

    menu_main_print_highlighted(prev, false);
    menu_main_print_highlighted(*type_loc, true);

    return true;
}

game_type menu_main_open() {
    menu_main_print();
    while (econio_kbhit()) { econio_getch(); econio_sleep(0.2); }

    game_type type = 0;
    while (menu_main_move(&type)) ;

    return type;
}