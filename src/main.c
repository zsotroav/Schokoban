#include <stdio.h>
#include <windows.h>
#include "data.h"
#include "io_map.h"
#include "printer.h"


int main(void) {
    // Ensure that encoding on the terminal will be UTF-8 so the characters can display properly.
    // This one line took me 3 hours and a lot of headaches of back and forth and Windows Terminal having weird issues
    SetConsoleOutputCP( CP_UTF8 );
    setvbuf(stdout, NULL, _IONBF, 0);

    map_data *map = map_open("0CNH-Alice.xsb");
    if (map == NULL) {
        printf("Game init failed!");
        return -1;
    }
    map_load(map);

    print_all(map);

    map_close(map);
    return 0;
}