#include <stdbool.h>
#include <string.h>
#include "data.h"
#include "econio.h"
#include "game.h"
#include "io_map.h"
#include "printer.h"


map_data *game_init(const char* level) {
    map_data *map = map_open(level);
    if (map == NULL) return NULL;
    if (!map_load(map)) return NULL;

    print_all(map);
    econio_rawmode();

    return map;
}

void game_end(map_data *map) {
    map_close(map);
}

bool game_wait_input(map_data *map){
    while (!econio_kbhit()) econio_sleep(0.2);

    switch (econio_getch()) {
        case 'w': game_mv(map, true, false); break;
        case 'a': game_mv(map, false, false); break;
        case 's': game_mv(map, true, true); break;
        case 'd': game_mv(map, false, true); break;
        case 'r': map_load(map);
        case KEY_F12: print_all(map); break;
        case KEY_ESCAPE: return false;
    }
    return true;
}

void game_mv(map_data *map, bool ud, bool rd) {
    // XY offsets
    int x = (ud ? 0 : (rd ? 1 : -1));
    int y = (ud ? (rd ? 1 : -1) : 0);

    if (map->player_x + x < 0 || map->player_x + x > map->width) return;
    if (map->player_y + y < 0 || map->player_y + y > map->height) return;


    char next = get_xy(map, (map->player_x + x), (map->player_y + y));
    if (next == '#') return; // No going through walls

    // if we want to go into a box, and that box is obstructed
    // (by another box or a wall), don't move
    char further = get_xy(map, (map->player_x + x*2), (map->player_y + y*2));
    if (is_box(next) && obstr_ext(further)) return;


    // Pay attention if we were on a goal or not
    set_xy(map, map->player_x, map->player_y,
           (get_xy(map, map->player_x, map->player_y) == '+' ? '.' : ' '));
    print_xy_offset(map, map->player_x, map->player_y);

    if (is_box(next)) {
        set_xy(map, (map->player_x + 2*x), (map->player_y + 2*y),
               (further == '.' ? '*' : '$'));
        print_xy_offset(map, map->player_x + 2*x, map->player_y + 2*y);
    }

    set_xy(map, (map->player_x + x), (map->player_y + y), ((next == '.' ||  next == '*' )? '+' : '@'));
    print_xy_offset(map, (map->player_x + x), (map->player_y + y));
    map->player_x += x;
    map->player_y += y;
    print_update_move(++(map->move_cnt));
}
