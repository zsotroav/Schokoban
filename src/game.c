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

void fame_add(int i, map_data* map) {
    printf("Do you want to add yourself to the leaderboard? (Y/N)\n");

    while (1) {
        while (!econio_kbhit()) econio_sleep(0.2);
        int ch = econio_getch();

        if (ch == 'n') break;
        if (ch != 'y') continue;

        printf("Please enter your nickname:\nSchokoban > ");
        map->fame_list = insert_fame_at(map->fame_list, i, read_text(), map->move_cnt);

        if (!map_save_stats(map)) printf("Failed to save leaderboard!");
        break;
    }
}

void game_end(map_data *map) {
    if (!map->functional){
        printf("An internal exception occurred. Please try again later.");
        map_close(map);
        return;
    }

    if(map->box != 0) {
        map_close(map);
        return;
    }

    printf("Map cleared!\n");
    // Best is always the first
    fame* curr = map->fame_list;
    int i;
    for (i = 0; curr->move != 0 && curr != NULL; ++i) {
        if (map->move_cnt < curr->move) {
            fame_add(i, map);
            break;
        }
        curr = curr->next;
    }
    if (i < 10 && (curr->move == 0 || curr == NULL)) fame_add(i, map);
    map_close(map);
}

void game_undo(map_data *map) {
    move* prev = map->moves;
    go_to_last_move(prev);

    // No undo before the first move
    if (prev->type == MV_INV) return;

    int x_off = 0, y_off = 0;
    bool box = false;

    // Find the move we want to  undo
    int i = 0;
    while (prev->type == MV_UNDO) {
        ++i;
        prev = prev->prev;
    }
    for (int j = 0; j < i; ++j) {
        if (prev->prev == NULL) return;
        prev = prev->prev;
        if (prev->type == MV_UNDO)
            j -=2;
    }

    // Calculate what that undo should do
    switch (prev->type) {
        case MV_L: box = true;
        case MV_l: x_off = 1; break;
        case MV_U: box = true;
        case MV_u: y_off = 1; break;
        case MV_R: box = true;
        case MV_r: x_off = -1; break;
        case MV_D: box = true;
        case MV_d: y_off = -1; break;
        default: return;
    }

    // Pay attention if we were on a goal or not
    set_xy(map, map->player_x, map->player_y,
           (get_xy(map, map->player_x, map->player_y) == '+' ? '.' : ' '));

    set_xy_offset(map, x_off, y_off,
           ((get_xy_offset(map, x_off, y_off)) == '.' ? '+' : '@'));

    // If we moved a box, make sure it gets moved back as well
    if (box) {
        bool was_goal = get_xy_offset(map, (x_off * -1), (y_off * -1))  == '*';
        bool to_goal = get_xy(map, map->player_x, map->player_y) == '.';
        set_xy_offset(map, (x_off * -1), (y_off * -1), (was_goal ? '.' : ' '));

        print_xy_offset(map, (map->player_x + (x_off * -1)), (map->player_y + (y_off * -1)));

        set_xy(map, map->player_x, map->player_y, (to_goal ? '*' : '$'));

        if (was_goal) map->box++;
        if (to_goal) map->box--;
    }

    print_xy_offset(map, map->player_x, map->player_y);
    print_xy_offset(map, (map->player_x + x_off), (map->player_y + y_off));

    // Add the undo to the move list
    go_to_last_move(prev);
    move* curr = get_next_move(prev);
    curr->type = MV_UNDO;

    // Update move count and player location
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
        case '0': map->box = 0; return false;  // Cheat mode (debug)
        case ' ': print_all(map); break;        // Re-print (debug)
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
    if (map->player_x + x < 0 || map->player_x + x > map->width ||
        map->player_y + y < 0 || map->player_y + y > map->height) return;

    char next =    get_xy_offset(map,   x,   y);
    char further = get_xy_offset(map, 2*x, 2*y);

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
        set_xy_offset(map, (2*x), (2*y), (further == '.' ? '*' : '$'));
        print_xy_offset(map, map->player_x + 2*x, map->player_y + 2*y);

        curr->type = (ud ? (rd ? MV_D : MV_U) : (rd ? MV_R : MV_L));
    }

    set_xy_offset(map, x, y, ((next == '.' ||  next == '*' )? '+' : '@'));
    print_xy_offset(map, (map->player_x + x), (map->player_y + y));
    map->player_x += x;
    map->player_y += y;
    print_update_move(++(map->move_cnt));

    if (curr->type == MV_INV) curr->type = (ud ? (rd ? MV_d : MV_u) : (rd ? MV_r : MV_l));

    cursor_bottom(map);
}
