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
|   ├── config.h        // Global configuration constants (instead of .ENV)
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

## Program structure

### High-level
```mermaid
flowchart TD
   main(START) --> menu{main menu\nGame mode?} 
   menu --> |ARCADE| game_master
   menu --> |FREE| menu_level_open[menu_level_open] --> game_master[Game_master]
   menu --> |CUSTOM| game_master 
   game_master -.-> |Init failed\nreturn| menu
    
   game_master --> |Prepare the game\nand enter main gameplay loop| game_loop

   subgraph game_loop[Execution order]
      direction LR
      init>Initialize the game] 
      -.-> master_loaded>Start game] 
      -.-> gameplay>Gameplay] 
      -.-> finished{Finished?} -.-> |No\nloop back| gameplay
      finished -.-> |Yes| cleanup>cleanup]
      cleanup
   end

   
``` 

### Game initialization
```mermaid
flowchart TD
   init>Initialize the game]

   init --> mode{Game mode?} --> |CUSTOM| menu_custom   
   mode --> |else| io_level

   subgraph menu_custom[menu_custom.c]
      menu_custom_open[menu_custom_open]
   end


   subgraph io_level[io_level.c]
      io_level_fullpath[io_level_fullpath] 
   end

   subgraph game[game.c]
      game_init[game_init]
   end

   subgraph io_map[io_map.c]
      map_open[map_open]
      map_load[map_load]
      map_load_stats[map_load_stats]
   end

   menu_custom_open  --> game
   io_level_fullpath --> game

   game_init --> |Success| io_map
   game_init --> |Init failed| main_menu>main menu]
   map_open --> map_load
   map_open --> map_load_stats
```

### Start game
```mermaid
flowchart TD
   start>Start game]
   --> save{Found save?\nAsk: Load?}
   --> |Yes| io_map
   -.-> printer
   save --> |No| printer

   subgraph printer[printer.c]
      direction LR
      pall[print_all]
      pall --> print_meta 
      pall --> print_map_all
      pall --> height{"Height\n<12?"} --> |Yes| print_controls
   end

   subgraph io_map[io_map.c]
      save_load[save load] 
   end
```

### Cleanup
```mermaid

flowchart TD
   cleanup>Cleanup]
   -.-> printer
   -.-> game_won{Game lost?\nAsk: Save progress?}
   --> |Yes| map_save_moves -.-> game_e["game_end"]
   game_won -.-> |Game won| game_e

   subgraph printer[printer.c]
      print_leaderboar
   end 

   subgraph io_map[io_map.c]
      map_save_moves
      map_save_stats
   end 

   subgraph data[data.c]
        insert_fame_at
   end

   subgraph game[game.c]
      game_e -.-> fame_add{Qualify for fame list?\nAsk: Add to fame list?} 
      --> |Yes| insert_fame_at -.-> map_save_stats

   end 
    fame_add -.-> |No| ask_continue
   
   subgraph main[main.c]
   ask_continue{Ask: Next level/Retry\nor main menu?}
   -.-> |Next level/Retry\nStay in gameplay loop| game_master>game_master]
   ask_continue -.-> |Main menu\nExit gameplay loop| menu>main_menu]
    
end
```
---


## SCHOKOBAN
```
┏┓┏┓┓┏┏┓┓┏┓┏┓┳┓┏┓┳┓    ┳┓┏┓┓┏ ┳┓┏┓┏┓┏┓
┗┓┃ ┣┫┃┃┃┫ ┃┃┣┫┣┫┃┃ ━━ ┃┃┣ ┃┃ ┃┃┃┃┃ ┗┓
┗┛┗┛┛┗┗┛┛┗┛┗┛┻┛┛┗┛┗    ┻┛┗┛┗┛ ┻┛┗┛┗┛┗┛
```