#include <stdio.h>
#include "config.h"
#include "data.h"
#include "game.h"
#include "menu_level_handle.h"
#include "menu_main_handle.h"
#include "menu_custom.h"
#include "io_level.h"
#include "lib/debugmalloc.h"
#include "printer.h"
#ifdef _WIN32
    #include <windows.h>
#endif


int main(void) {
    #ifdef _WIN32
        SetConsoleOutputCP( CP_UTF8 );
    #endif

    int level = 0;
    char* map_loc;

    game_type t = INV;
    while (t == INV) {
        t = menu_main_open();
        switch (t) {
            case ARCADE:
                map_loc = io_level_fullpath(0);
                break;
            case FREE:
                level = menu_level_open();
                if (level == -1) { t = INV; break; }
                map_loc = io_level_fullpath(level);
                break;
            case CUSTOM:
                map_loc = menu_custom_open();
                break;
            case INV: break;
        }
    }

    map_data *map = game_init(map_loc);
    if (map == NULL) {
        printf("Game init failed!");
        return -1;
    }
    map->game_type = t;
    if (t != CUSTOM) map->level = level;

    while (game_wait_input(map) && map->functional);

    print_leaderboard(map);
    game_end(map);

    free(map_loc);

    return 0;
}