#include <stdio.h>
#include <windows.h>
#include "game.h"
#include "data.h"


int main(void) {
    // Ensure that encoding on the terminal will be UTF-8 so the characters can display properly.
    // This one line took me 3 hours and a lot of headaches of back and forth and Windows Terminal having weird issues
    SetConsoleOutputCP( CP_UTF8 );
    setvbuf(stdout, NULL, _IONBF, 0);

    map_data *map = game_init("0CNH-Alice.xsb");
    if (map == NULL) {
        printf("Game init failed!");
        return -1;
    }

    while (game_wait_input(map)) ;

    game_end(map);
    return 0;
}