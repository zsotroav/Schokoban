#include <stdbool.h>
#include <stdio.h>
#include "config.h"
#include "data.h"
#include "game.h"
#include "menu_custom.h"
#include "menu_level_handle.h"
#include "menu_main_handle.h"
#include "io_level.h"
#include "lib/debugmalloc.h"
#include "lib/econio.h"
#include "printer.h"
#ifdef _WIN32
    #include <windows.h>
#endif


bool game_master(game_type type, int* level) {
    char* map_loc =  type == CUSTOM ? menu_custom_open() : io_level_fullpath(*level + 1);

    // Don't need to check map_loc for null because that would be redundant - the other functions handle it
    map_data *map = game_init(map_loc);
    if (map == NULL) {
        printf("Game init failed! Press any key to return to the main menu...\n");
        free(map_loc);

        while (!econio_kbhit()) econio_sleep(0.2);
        return false;
    }
    if (type != CUSTOM) map->level = *level;

    // Main gameplay loop (get input and make sure we're still functional (no internal exceptions))
    while (game_wait_input(map) && map->functional);

    // Always print the leaderboard at the end
    print_leaderboard(map);
    game_end(map);
    free(map_loc);

    printf("Press any key to %s or ESC to go back to the main menu...\n",
           type == ARCADE ? "continue to the next level" : "retry");

    while (!econio_kbhit()) econio_sleep(0.2);
    if (econio_getch() == KEY_ESCAPE) return false;

    if (type == ARCADE) ++*level;
    return true;
}

bool menu() {
    int level = 0;
    game_type t = INV;

    while (t == INV) {
        t = menu_main_open();
        switch (t) {
            case ARCADE: level = 0; break;
            case FREE:
                level = menu_level_open();
                if (level == -1) { t = INV; break; }
                break;
            case EXIT: return false;
            default: break;
        }
    }

    // Start the gameplay loop (allow for multiple levels to be played/replayed)
    while (game_master(t, &level)) ;
    return true;
}

int main(void) {
    #ifdef _WIN32
        SetConsoleOutputCP( CP_UTF8 );
    #endif

    econio_rawmode();
    econio_set_title("SCHOKOBAN");

    // Menu is the main loop, we keep the app loaded until the player explicitly quits
    while ( menu() ) ;

    return 0;
}