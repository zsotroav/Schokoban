#include "data.h"
#include "debugmalloc.h"

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
