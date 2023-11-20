### 5.1 data.h
<!-- BEGIN DOC-COMMENT H4 include/data.h -->

#### `char* read_text()`

Read long string from stdin
**Returns:** `read` — text

#### `map_data* map_init(char* loc, int width, int height)`

Create a new map instance with default values

**Parameters:**

* `Default` — `loc` — value for map_data.loc
* `Width` — `width` — of the map for allocation
* `Height` — `height` — of the map for allocation

**Returns:** `Created` — and memory allocated map_data pointer

#### `move* get_next_move(move* prev)`

Insert a new move at the end of the current chain

**Parameters:**

* `Any` — `prev` — point of the current move chain

**Returns:** `The` — new element

#### `fame* add_new_fame(fame* prev)`

Insert new fame list item after a given one

**Parameters:**

* `Element` — `prev` — to insert after

**Returns:** `The` — new element

#### `fame* insert_fame_at(fame* first, int n, char* name, int move)`

Insert new fame list item after the n.th one\n

**Parameters:**

* `List` — `first` — item to count from
* `to` — `Index` — insert at
* `List` — `name` — item name value
* `List` — `move` — item move value

**Returns:** `First` — item

<!-- END DOC-COMMENT -->

### 5.3 io_level.h
<!-- BEGIN DOC-COMMENT H4 include/io_level.h -->

#### `io_level_fullpath(id)`

Get the number of xsb files in the directory 

**Note:** This function does not validate if the XSB files are valid 

**Parameters:**

* `Directory` — `directory` — to search in

**Returns:** The number of xsb files 

#### `int io_level_parse(char* directory)`

Get the full path based on config directory

**Parameters:**

* `ID` — `id` — of the map file

**Returns:** `full` — (relative) path to the XSB

#### `char* io_level_get(char* directory, int id)`

Get the file name of the map with a specific id

**Parameters:**

* `Directory` — `directory` — to search in
* `Number` — `id` — of the map file

**Returns:** `File` — name

<!-- END DOC-COMMENT -->

### 5.4 io_map.h
<!-- BEGIN DOC-COMMENT H4 include/io_map.h -->

#### `FILE* get_meta_file(char* loc, char* mode, bool stat)`

Open stats/save state file, which is just the xsb map file with .dat/.sav at the end

**Parameters:**

* `Location` — `loc` — of the XSB file
* `File` — `mode` — open mode
* `true` — `stat` — = stats file // false = save file

**Returns:** `File` — pointer to the stats file

#### `char* read_long(FILE* fptr)`

Read undefined length line

**Parameters:**

* `File` — `fptr` — pointer to read from

**Returns:** `Malloced` — string

#### `bool map_load_stats(map_data *map)`

Load the stats (leaderboard) of the map from the appropriate data file

**Parameters:**

* `Pointer` — `map` — to map data

**Returns:** `Success` — or Failure to load.

#### `bool map_save_moves(map_data *map)`

Save the moves of the map to the appropriate data file

**Parameters:**

* `Pointer` — `map` — to map data

**Returns:** `Success` — or Failure to save.

#### `void map_load_moves(map_data *map, FILE* savptr)`

Load the moves of the map from the data file

**Parameters:**

* `Pointer` — `map` — to map data
* `FILE*` — `savptr` — to save file

#### `bool map_save_stats(map_data *map)`

Save the stats of the map into the appropriate data file

**Parameters:**

* `Pointer` — `map` — to map data

**Returns:** `Success` — or Failure to save.

#### `bool meta_exists(char* meta, FILE* fptr)`

Check if given metadata value is in the file at the expected location

**Parameters:**

* `Metadata` — `meta` — name
* `XSB` — `fptr` — file pointer

**Returns:** `true/false` — based on result

#### `map_data* map_open(char *loc)`

Opens the given map file

**Parameters:**

* `relative` — `loc` — or absolute path to the xsb map file

**Returns:** `generated` — map data

#### `void map_load(map_data *map, FILE* mapptr)`

Loads the contents of the map. Must always be called after map_open()

**Parameters:**

* `Pointer` — `map` — to map data
* `file` — `mapptr` — pointer to map file

**Returns:** `Success` — or Failure to load map data.

#### `void map_reset(map_data *map)`

Lazily (only doing what's necessary) resets the map from the map file

**Parameters:**

* `Pointer` — `map` — to map data

#### `void map_close(map_data *map)`

Closes the map file and frees all allocated memory for the map

**Parameters:**

* `Pointer` — `map` — to map data

<!-- END DOC-COMMENT -->

### 5.5 menu_custom.h
<!-- BEGIN DOC-COMMENT H4 include/menu_custom.h -->

#### `char* menu_custom_open()`

Open the custom map input menu
**Returns:** `The` — user provided (!) path

<!-- END DOC-COMMENT -->

### 5.6 menu_level_handle.h
<!-- BEGIN DOC-COMMENT H4 include/menu_level_handle.h -->

#### `void menu_level_highlight(int id, int page, int max, bool active)`

Highlight level menu item

**Parameters:**

* `ID` — `id` — of the menu item (location on page)
* `Current` — `page` — page in view (for number calculation)
* `Maximum` — `max` — number of available levels (any more is greyed out)
* `State` — `active` — to highlight

#### `bool menu_level_move(int* loc, int* page, int max)`

Move level selection

**Parameters:**

* `Current` — `loc` — location
* `Current` — `page` — page
* `Maximum` — `max` — number of available levels

**Returns:** `Selection` — complete: false (to break out of loop)

#### `int menu_level_open()`

Open level select menu and wait for completed selection
**Returns:** `Selected` — level's number

<!-- END DOC-COMMENT -->

### 5.7 menu_level_printer.h
<!-- BEGIN DOC-COMMENT H4 include/menu_level_printer.h -->

#### `void menu_print_level_nav(bool direction, int color)`

Print navigation block in level select menu

**Parameters:**

* `ture:` — `direction` — Right // false: Left
* `(econio)` — `color` — color to print with

#### `void menu_print_level_item(int num, int color, int id)`

Print a single item on the level screen

**Parameters:**

* `Number` — `num` — to show
* `(econio)` — `color` — color to print with
* `Sequential` — `id` — ID of the button

#### `void menu_print_level_page(int page, int max)`

Print the full page of levels (loop through menu_print_level_item)

**Parameters:**

* `Page` — `page` — no. to  print
* `Maximum` — `max` — number of levels, any more is greyed out 00

#### `bool menu_print_level(int page, int max)`

Print the full level selection screen

**Parameters:**

* `Page` — `page` — to start printing at
* `Maximum` — `max` — number of levels, any more is greyed out 00

**Returns:** Success/Failure

<!-- END DOC-COMMENT -->

### 5.8 menu_main_handle.h
<!-- BEGIN DOC-COMMENT H4 include/menu_main_handle.h -->

#### `bool menu_main_move(game_type* type_loc)`

Main menu movement looper

**Parameters:**

* `Current` — `type_loc` — selection

**Returns:** `Selection` — complete: false (to break out of loop)

#### `game_type menu_main_open()`

Open main menu and wait for game type selection
**Returns:** `Selected` — game type or exit request

<!-- END DOC-COMMENT -->

### 5.9 menu_main_printer.h
<!-- BEGIN DOC-COMMENT H4 include/menu_main_printer.h -->

#### `void menu_main_print_highlighted(int id, bool highlighted)`

Print a single item on the main menu

**Parameters:**

* `ID` — `id` — of the menu item (location)
* `Highlight` — `highlighted` — selection active/inactive

#### `void menu_main_print()`

Print the full main menu

<!-- END DOC-COMMENT -->

### 5.10 printer.h
<!-- BEGIN DOC-COMMENT H4 include/printer.h -->

#### `void printnat(int x, int y, int n, char* c)`

Print a given number of characters at a location

**Parameters:**

* `X` — `x` — (Horizontal) location
* `Y` — `y` — (Vertical) location
* `Number` — `n` — of times to print character
* `Character` — `c` — to print

#### `void printat(int x, int y, char* c)`

Print a character at location

**Parameters:**

* `X` — `x` — (Horizontal) location)
* `Y` — `y` — (Vertical) location
* `Character` — `c` — to print

#### `void print_all(map_data *map)`

Prints the full game to the screen

#### `void print_map_all(map_data *map)`

Prints every map component to the screen

#### `void print_xy(map_data *map, int x, int y)`

Prints the current value to the screen at the given location of the map, does not offset the print, prints wherever we're currently at

**Parameters:**

* `Map` — `x` — location x
* `Map` — `y` — location y

#### `void print_xy_offset(map_data *map, int x, int y)`

Prints the current value to the screen at the given location of the map, with the appropriate amount of offset

**Parameters:**

* `Map` — `x` — location of x
* `Map` — `y` — location of y

#### `void print_meta(map_data* map)`

Print the logo and available map metadata (title, author, record)

**Parameters:**

* `Pointer` — `map` — to map data

#### `void print_update_move(int new)`

Update the number of moves displayed

**Parameters:**

* `New` — `new` — number to show

#### `void print_controls()`

Prints the control hints to the screen at current cursor position

#### `void print_leaderboard(map_data* map)`

Print the leaderboard of the map

**Parameters:**

* `Pointer` — `map` — to map data

<!-- END DOC-COMMENT -->
