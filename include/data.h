#ifndef SCHOKOBAN_DATA_H
#define SCHOKOBAN_DATA_H

#include <stdbool.h>
#include <stdio.h>

#define get_xy(map, y, x) *((map)->map[(x) * (map)->width + (y)])
#define get_xy_offset(map, x, y) get_xy(map, ((map)->player_x + (x)), ((map)->player_y + (y)))
#define set_xy(map, y, x, value) (*((map)->map[x * map->width + y]) = value)
#define set_xy_offset(map, x, y, value) set_xy(map, ((map)->player_x + (x)), ((map)->player_y + (y)), (value))
#define indent(map) ((20 - map->width) / 2)
#define go_to_last_move(move) while (move->next != NULL) move = move->next
#define is_valid_move(c) strchr("lurdLURDx", c)

typedef enum {
    MV_L = 'L',     //!< Left (box moved)
    MV_U = 'U',     //!< Up (box moved)
    MV_R = 'R',     //!< Right (box moved)
    MV_D = 'D',     //!< Down (box moved)
    MV_l = 'l',     //!< Left
    MV_u = 'u',     //!< Up
    MV_r = 'r',     //!< Right
    MV_d = 'd',     //!< Down
    MV_UNDO = 'x',  //!< Undo
    MV_INV          //!< Invalid move (reserved)
} move_type;        //!< Type of move made in the LURD format

typedef enum { ARCADE = 0, FREE = 1, CUSTOM = 2, INV = -1, EXIT = 3} game_type;

typedef struct move {
    move_type type;
    struct move *prev, *next;
} move;

typedef struct fame {
    char* name;
    int move;
    struct fame *next;
} fame;

typedef char map_char[1];

typedef struct {
    // Map information
    int level;          //!< Level number used if the game type is arcade
    char* loc;          //!< Location of the map data file
    map_char *map;      //!< Display data
    int width;          //!< Map's width
    int height;         //!< Map's height
    fame *fame_list;

    // Metadata
    char* title;        //!< Map's title metadata
    char* author;       //!< Map's author metadata

    // Game state information
    bool functional;    //!< Indicate if an internal error was encountered mid-game
    int move_cnt;       //!< Number of moves made (to not have to traverse the linked list each time it's needed)
    move *moves;        //!< List of made moves
    int player_x;       //!< Player character's current X location
    int player_y;       //!< Player character's current Y location
    int box;            //!< Number of boxes not on goals yet
} map_data;

/**
 * @brief Read long string from stdin
 * @return read text
 */
char* read_text();

/**
 * @brief Create a new map instance with default values
 * @param loc Default value for map_data.loc
 * @param width Width of the map for allocation
 * @param height Height of the map for allocation
 * @return Created and memory allocated map_data pointer
 */
map_data* map_init(char* loc, int width, int height);

/**
 * @brief Insert a new move at the end of the current chain
 * @param prev Any point of the current move chain
 * @return The new element
 */
move* get_next_move(move* prev);

/**
 * @brief Insert new fame list item after a given one
 * @param prev Element to insert after
 * @return The new element
 */
fame* add_new_fame(fame* prev);

/**
 * @brief Insert new fame list item after the n.th one
 * @param first List item to count from
 * @param Index to insert at
 * @param name List item name value
 * @param move List item move value
 * @return First item
 */
fame* insert_fame_at(fame* first, int n, char* name, int move);

#endif //SCHOKOBAN_DATA_H
