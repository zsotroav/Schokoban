#include <stdio.h>
#include "game.h"
#include "data.h"
#ifdef _WIN32
    #include <windows.h>
#endif

int main(void) {
    #ifdef _WIN32
        SetConsoleOutputCP( CP_UTF8 );
    #endif
    
    setvbuf(stdout, NULL, _IONBF, 0);

    map_data *map = game_init("0CNH-Alice.xsb");
    if (map == NULL) {
        printf("Game init failed!");
        return -1;
    }

    while (game_wait_input(map));

    if (map->box == 0) printf("Map cleared!\n");
    // TODO: Update best score

    game_end(map);
    return 0;
}