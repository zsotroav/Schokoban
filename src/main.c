//
// Created by zsotroav on 2023-10-05.
//

#include <stdio.h>
#include "econio.h"
#include "debugmalloc.h"
#include "map.h"
#include <wchar.h>
#include <windows.h>


typedef enum { L, U, R, D, l, u, r, d } move_type;

typedef struct {
    struct move *prev;
    move_type type;
    struct move *next;
} move;

int main(void) {
    // Ensure that encoding on the terminal will be UTF-8 so the characters can display properly.
    // This one line took me 3 hours and a lot of headaches of back and forth and Windows Terminal having weird issues
    SetConsoleOutputCP( CP_UTF8 );
    setvbuf(stdout, NULL, _IONBF, 0);

    open_map_file("0CNH-Alice.xsb");
    load_map_file();

    print_all();

    close_map_file();
    return 0;
}