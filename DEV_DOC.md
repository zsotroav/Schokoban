# SCHOKOBAN - DEVELOPER'S DOCUMENTATION

## Legal & License
Copyright (c) 2023 Zsombor Török

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

## Intro
It is sokoban, but spelled with sch because Schönherz.

This developer's documentation is only meant to be a complementary 
resource to the already documented source code.

GitHub repository for the project: [zsotroav/Schokoban](https://github.com/zsotroav/schokoban)

## High-level overview

### Files
The project follows a simple folder structure with C source code in the 
`src` directory and related header files in the `include` directory.
```
schokoban
├── src
|   ├── data.c                // Basic data handling
|   ├── game.c                // Main gameplay logic
|   ├── io_level.c            // Level (XSB) file path and location handling
|   ├── io_map.c              // Level (XSB) file reading
│   ├── main.c                // Main entry code and gameplay loop
|   ├── menu_custom.c         // Custom map select menu handling
|   ├── menu_level_handle.c   // Level select menu handling
|   ├── menu_level_printer.c  // Level select menu printer functions
|   ├── menu_main_handle.c    // Main menu movement handling
|   ├── menu_main_printer.c   // Main menu printer functions
|   └── printer.c             // Game UI Handling
├── include
|   ├── lib                   // Libraries
|   |   ├── debugmalloc.h
|   │   ├── ECONIO_LICENSE    // MIT License file for the econio library
|   │   ├── econio.c
|   │   └── econio.h
|   ├── config.h
│   │
|   └── ...
├── .gitignore
├── CMakeLists.txt
├── DEV_DOC.md
├── econio_readme.md    // Readme for econio lib, may get removed in the future
├── LICENSE             // GPL-3.0 (License file)
├── spec_ui.png
└── spec.md             // Specifications for the game
```

### Used external resources
- Libraries:
  1. [c-econio](https://infoc.eet.bme.hu/megjelenites/c-econio.zip) 
     by Zoltan Czirkos. [MIT License](include/lib/ECONIO_LICENSE)
  2. [debugmalloc](https://infoc.eet.bme.hu/debugmalloc/debugmalloc.h)
- Code snippets: Noted in source if applicable
- General reference documents:
  1. [Sokoban.org](http://sokoban.org/about_sokoban.php) for game rules 
     and XSB/LURD format specs
- Miscellaneous: 
   1. ASCII font for logo: tmplr by Eugene Ghanizadeh Khoub, 
   generated with [patorjk.com](https://patorjk.com/software/taag/#p=display&h=1&v=2&f=Tmplr&t=SCHOKOBAN)

### Gameplay loop
```mermaid
flowchart TD
    main[START] --> menu{main menu\nGame mode?} --> |ARCADE| game_master[Game_master]
    menu --> |FREE| menu_level_open(menu_level_open) --> game_master
    menu --> |CUSTOM| game_master --> |Begin init|initialize_game

    initialize_game --> |CUSTOM| menu_custom_open(menu_custom_open) 
    --> game_init(game_init)
    initialize_game --> |else| io_level_fullpath(io_level_fullpath) 
    --> game_init --> map_open(map_open) --> map_load(map_load)
    map_open --> map_load_stats(map_load_stats)
    game_master -.-> |Init failed\nreturn;| menu

    game_master --> |Init successful| master_loaded[Start game]
    --> save{Saved state\nfound?}
    --> |Yes| save_found{Ask user:\nLoad?}
    save_found --> |Yes| save_load(save load) -.-> |continue\nexecution| print_all(print_all)
    save_found --> |No| print_all
    save --> |No| print_all

    game_master --> |Game started| wait_input(wait_input)



    game_master --> |Game finished| cleanup 
    -.-> |continue\nexecution| print_leaderboard(print_leaderboard)
    -.-> |continue\nexecution| game_won{Did player win?\nboxes not on\ngoals = 0}
    game_won --> |No| ask_save{Ask: Save progress?}
    --> |Yes| save_state(map_save_moves)
    ask_save -.-> |No\n\ncontinue\nexecution| game_end(game_end)
    game_won -.-> |Yes\n\ncontinue\nexecution| game_end
    --> game_end_mode{What was\nthe game mode?}
    --> |ARCADE| ask_arcade_continue{Ask: Next level\nor main menu}
    -.-> |Next level\n\nStay in gameplay loop| game_master
    ask_arcade_continue -.-> |Main menu\n\nExit gameplay loop| menu

```

---


## SCHOKOBAN
```
┏┓┏┓┓┏┏┓┓┏┓┏┓┳┓┏┓┳┓    ┳┓┏┓┓┏ ┳┓┏┓┏┓┏┓
┗┓┃ ┣┫┃┃┃┫ ┃┃┣┫┣┫┃┃ ━━ ┃┃┣ ┃┃ ┃┃┃┃┃ ┗┓
┗┛┗┛┛┗┗┛┛┗┛┗┛┻┛┛┗┛┗    ┻┛┗┛┗┛ ┻┛┗┛┗┛┗┛
```