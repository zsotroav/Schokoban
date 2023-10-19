#include "data.h"
#include "debugmalloc.h"

map_data* map_init(char* loc) {
    map_data* map = malloc(sizeof(map_data));

    map->loc = malloc(strlen(loc) + 1);
    strcpy(map->loc, loc);

    map->functional = true;
    map->width = 0;
    map->height = 0;
    map->move_cnt = 0;
    map->box = 0;

    map->moves = malloc(sizeof(move));
    map->moves->prev = NULL;
    map->moves->next = NULL;
    map->moves->type = inv;

    map->fame_list = malloc(sizeof(fame));
    map->fame_list->next = NULL;
    map->fame_list->move = 0;
    return map;
}

move* get_next_move(move* prev) {
    while (prev->next != NULL) prev = prev->next;
    if (prev->type == inv) return prev;

    move* curr = malloc(sizeof(move));
    prev->next = curr;
    curr->prev = prev;
    curr->next = NULL;
    curr->type = inv;
    return curr;
}

fame* get_next_fame(fame* prev) {
    fame* curr = malloc(sizeof(fame));
    prev->next = curr;
    curr->next = NULL;
    curr->name = NULL;
    curr->move = 0;
    return curr;
}

fame* insert_fame_at(fame* first, int n, char* name, int move) {
    fame* curr = NULL;
    fame* next = NULL;
    if (n > 0) {
        curr = first;
        for (int i = 0; i < n; ++i) {
            if (curr->move == 0) return NULL;
            curr = curr->next;
        }
        next = curr->next;
        curr->next = malloc(sizeof(fame));
        curr = curr->next;
    } else {
        curr = malloc(sizeof(fame));
        next = first;
        first = curr;
    }

    //fame* next = curr->next;
    curr->name = name;
    curr->move = move;
    curr->next = next;

    return first;
}
