#include "printer.h"
#include "data.h"
#include "econio.h"
#include <stdio.h>
#include <string.h>


void print_all(map_data *map) {
    econio_clrscr();
    print_meta(map);
    print_map_all(map);
    // Only print controls if the map isn't too tall
    if (map->height < 12) print_controls();
}

void print_map_all(map_data *map) {
    for (int i = 0; i < map->height; ++i) {
        for (int j = 0; j < indent(map); ++j) printf(" ");
        for (int j = 0; j < map->width; ++j) {
            print_xy(map, j, i);
        }
        printf("\n");
    }
}

void print_xy(map_data *map, int x, int y) {
    econio_textcolor(COL_RESET);
    switch (get_xy(map, x, y)) {
        case '#': printf("█"); break;
        case '*':
            econio_textcolor(COL_GREEN);
            printf("◼");
            break;
        case '$':
            econio_textcolor(COL_BROWN);
            printf("◼");
            break;
        case '_':
        case '-':
        case ' ': printf(" "); break;
        case '+': econio_textcolor(COL_RED);
        case '@': printf("☻"); break;
        case '.':
            econio_textcolor(COL_RED);
            printf("⨯");
            break;
        default: printf("%c", get_xy(map, x, y)); break;
    }
    econio_textcolor(COL_RESET);
}

void print_xy_offset(map_data *map, int x, int y) {
    econio_gotoxy(indent(map) + x, 4 + y);
    print_xy(map, x, y);
    econio_gotoxy(0, 14 + map->height );
}

void print_meta(map_data* map) {
    printf("┏┓┏┓┓┏┏┓┓┏┓┏┓┳┓┏┓┳┓   Puzzle: \n"
           "┗┓┃ ┣┫┃┃┃┫ ┃┃┣┫┣┫┃┃   Record: \n"
           "┗┛┗┛┛┗┗┛┛┗┛┗┛┻┛┛┗┛┗   Moves:  %d\n",
           map->move_cnt);
    econio_gotoxy(30, 1);
    if (map->fame_list->move > 0) printf("%d", map->fame_list->move);
    else printf("N/A");

    /* Title is always set, at worst it's just the file name
     * We print it here because it's easier to already have the cursor at
     * the correct position if and when we also want to print the author
     * (We don't have to calculate where the cursor needs to go)
     */
    econio_gotoxy(30, 0);
    printf("%s", map->title);
    if (map->author[0] != '\0') printf(" by %s", map->author);

    // Reset cursor to not mess with other printer functions
    econio_gotoxy(0, 4);
}

void print_update_move(int new){
    econio_gotoxy(30, 2);
    printf("%d", new);
}

void print_controls() {
    printf("\n\n"
           "    ╔═══╗     ╔═══╗   ╔═══╗\n"
           "    ║ W ║     ║ R ║   ║ESC║\n"
           "    ╚═══╝     ╚═══╝   ╚═══╝\n"
           "╔═══╗╔═══╗╔═══╗       ╔═══╗\n"
           "║ A ║║ S ║║ D ║       ║ U ║\n"
           "╚═══╝╚═══╝╚═══╝       ╚═══╝\n");
}

void printnat(int x, int y, int n, char* c){
    econio_gotoxy(x, y);
    for (int i = 0; i < n; ++i) printf("%s", c);
}

void printat(int x, int y, char* c){
    econio_gotoxy(x, y);
    printf("%s", c);
}

void print_leaderboard(map_data* map) {
    econio_clrscr();
    print_meta(map);
    fame* curr = map->fame_list;

    int max = strlen(curr->name), n = 0;
    printf("╔══════╤\n"
           "║  %3d │ %s\n"
           "╟──────┼\n", curr->move, curr->name);
    curr = curr->next;
    while(curr->move != 0) {
        int l = strlen(curr->name);
        if (l > max) max = l;
        printf("║  %3d │ %s\n", curr->move, curr->name);
        curr = curr->next;
        n++;
    }
    max += 5;
    printnat(8, 4, max, "═");
    printf("╕");
    printnat(8, 6, max, "─");

    econio_gotoxy(0, n + 7);
    printf("╙──────┴");
    for (int i = 0; i < n + 2; ++i) printat(max + 8, i + 5, "│");
    printnat(8, n + 7, max, "─");
    printf("┘");
    econio_gotoxy(0, 20);

}