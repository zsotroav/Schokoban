#include <stdbool.h>
#include <string.h>
#include "data.h"
#include "lib/econio.h"
#include "game.h"
#include "io_map.h"
#include "printer.h"


map_data *game_init(char* level) {
    map_data *map = map_open(level);
    if (map == NULL) return NULL;

    print_all(map);
    econio_rawmode();

    return map;
}

void game_end(map_data *map) {
    // TODO: Update best score (WIP)

    if (!map->functional){
        printf("An internal exception occurred. Please try again later.");
        map_close(map);
        return;
    }

    if(map->box != 0) {
        map_close(map);
        return;
    }

    printf("Map cleared!");
    // Best is always the first
    if (map->move_cnt < map->fame_list->move) {
        printf("New record! Do you want to add yourself to the leaderboard? (Y/N)\n");

        bool waiting = true;
        while (waiting) {
            while (!econio_kbhit()) econio_sleep(0.2);
            switch (econio_getch()) {
                case 'y':
                    map->fame_list = insert_fame_at(map->fame_list, 0, "Da best", map->move_cnt);
                    if (!map_save_stats(map)) printf("Failed to save leaderboard!");
                    // TODO: Read name from stdin
                case 'n': waiting = false; break;
            }
        }

        // printf("%s", map->move_cnt == map->fame_list->move ? "Record met!" : "New record!");
    }


    map_close(map);
}

void game_undo(map_data *map) {
    move* prev = map->moves;
    go_to_last_move(prev);

    // No undo before the first move
    if (prev->type == inv) return;

    int x_off = 0, y_off = 0;
    bool box = false;

    int i = 0;
    while (prev->type == x) {
        ++i;
        prev = prev->prev;
    }
    for (int j = 0; j < i; ++j) {
        if (prev->prev == NULL) return;
        prev = prev->prev;
    }

    switch (prev->type) {
        case L: box = true;
        case l: x_off = 1; break;
        case U: box = true;
        case u: y_off = 1; break;
        case R: box = true;
        case r: x_off = -1; break;
        case D: box = true;
        case d: y_off = -1; break;
        default: return;
    }

    // Pay attention if we were on a goal or not
    set_xy(map, map->player_x, map->player_y,
           (get_xy(map, map->player_x, map->player_y) == '+' ? '.' : ' '));

    set_xy(map, (map->player_x + x_off), (map->player_y + y_off),
           (get_xy(map, (map->player_x + x_off), (map->player_y + y_off)) == '.' ? '+' : '@'));

    if (box) {
        bool was_goal = get_xy(map,
                               (map->player_x + (x_off * -1)),
                               (map->player_y + (y_off * -1)))  == '*';
        bool to_goal = get_xy(map, map->player_x, map->player_y) == '.';
        set_xy(map, (map->player_x + (x_off * -1)), (map->player_y + (y_off * -1)),
               (was_goal ? '.' : ' '));

        print_xy_offset(map, (map->player_x + (x_off * -1)), (map->player_y + (y_off * -1)));

        set_xy(map, map->player_x, map->player_y,
               (to_goal ? '*' : '$'));

        if (was_goal) map->box++;
        if (to_goal) map->box--;
    }

    print_xy_offset(map, map->player_x, map->player_y);
    print_xy_offset(map, (map->player_x + x_off), (map->player_y + y_off));

    go_to_last_move(prev);
    move* curr = get_next_move(prev);
    curr->type = x;

    print_update_move(++map->move_cnt);
    map->player_x += x_off;
    map->player_y += y_off;
}

bool game_wait_input(map_data *map) {
    while (!econio_kbhit()) econio_sleep(0.2);

    switch (econio_getch()) {
        case 'w':
        case KEY_UP: game_mv(map, true, false); break;
        case 'a':
        case KEY_LEFT: game_mv(map, false, false); break;
        case 's':
        case KEY_DOWN: game_mv(map, true, true); break;
        case 'd':
        case KEY_RIGHT: game_mv(map, false, true); break;
        case 'r': map_reset(map); break;
        case 'u': game_undo(map); break;
        case '0': map->box = 0; return  false;  // Cheat mode
        case KEY_F12: print_all(map); break;        // Re-print (debug)
        case KEY_ESCAPE: return false;
    }

    // Goal reached if boxes are zero
    if (map->box == 0) return false;
    return true;
}

void game_mv(map_data *map, bool ud, bool rd) {
    // XY offsets
    int x = (ud ? 0 : (rd ? 1 : -1));
    int y = (ud ? (rd ? 1 : -1) : 0);

    // No going out of bounds, even if the map isn't surrounded by walls
    if (map->player_x + x < 0 || map->player_x + x > map->width) return;
    if (map->player_y + y < 0 || map->player_y + y > map->height) return;

    char next =    get_xy(map, (map->player_x +   x), (map->player_y +   y));
    char further = get_xy(map, (map->player_x + 2*x), (map->player_y + 2*y));

    // No going through walls
    if (next == '#') return;

    // If we want to go into a box, and that box is obstructed
    // (by another box or a wall), don't move
    if (is_box(next) && obstr_ext(further)) return;

    move* curr = get_next_move(map->moves);


    // Pay attention if we were on a goal or not
    set_xy(map, map->player_x, map->player_y,
           (get_xy(map, map->player_x, map->player_y) == '+' ? '.' : ' '));
    print_xy_offset(map, map->player_x, map->player_y);

    if (is_box(next)) {
        // Keep the number of boxes on and off goals
        if (further == '.') map->box--;
        if (next == '*') map->box++;
        set_xy(map, (map->player_x + 2*x), (map->player_y + 2*y),
               (further == '.' ? '*' : '$'));
        print_xy_offset(map, map->player_x + 2*x, map->player_y + 2*y);

        curr->type = (ud ? (rd ? D : U) : (rd ? R : L));
    }

    set_xy(map, (map->player_x + x), (map->player_y + y),
           ((next == '.' ||  next == '*' )? '+' : '@'));
    print_xy_offset(map, (map->player_x + x), (map->player_y + y));
    map->player_x += x;
    map->player_y += y;
    print_update_move(++(map->move_cnt));

    if (curr->type == inv) curr->type = (ud ? (rd ? d : u) : (rd ? r : l));

    cursor_bottom(map);
}
