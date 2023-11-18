# SCHOKOBAN - DEVELOPER'S DOCUMENTATION

## 1 Legal & License
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

## 2 Intro
It is Sokoban but spelled with sch because Schönherz.

This developer's documentation is only a complementary 
resource to the already documented source code.

GitHub repository for the project: 
[zsotroav/Schokoban](https://github.com/zsotroav/schokoban)

## 3 High-level overview

### 3.1 Files
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
├── econio_readme.md    // Readme for econio lib may get removed in the future
├── LICENSE             // GPL-3.0 (License file)
├── spec_ui.png
└── spec.md             // Specifications for the game
```

### 3.2 Used external resources
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

## 4 Code and logic structure
The following figures show a high-level (simplified) overview of the game's
underlying logic and structure, showing only the important connections and
relations. 

Solid lines represent function calls, while dotted lines show code execution
order; highlighted boxes are drawn around functions from the same file or for
visual separation.


### 4.1 Entry and gameplay loop
See Figures 4.2-4.6 for a more detailed overview of the main gameplay loop. 

```mermaid
flowchart TD
   main(START) --> menu{main menu\nGame mode?} 
   menu --> |ARCADE| game_master
   menu --> |FREE| menu_level_open --> game_master
   menu --> |CUSTOM| menu_custom_open --> game_master 
   game_master -.-> |Init failed\nreturn| menu
    
   game_master --> |Prepare the game\nand enter main gameplay loop| game_loop

   subgraph game_loop[Execution order]
      direction LR
      init>Initialize the game] 
      -.-> master_loaded>Start game] 
      -.-> gameplay>Gameplay]
      -.-> finished{Finished?} -.-> |No\nstay in loop| gameplay
      finished -.-> |Yes| cleanup>cleanup]
      cleanup
   end
``` 

### 4.2 Game initialization
```mermaid
flowchart TD
   init>Initialize the game]

   init --> mode{Game mode?} --> |CUSTOM| menu_custom   
   mode --> |else| io_level

   subgraph menu_custom[menu_custom.c]
      menu_custom_open
   end


   subgraph io_level[io_level.c]
      io_level_fullpath
   end

   subgraph game[game.c]
      game_init
   end

   subgraph io_map[io_map.c]
      map_open
      map_load
      map_load_stats
   end

   menu_custom_open  --> game
   io_level_fullpath --> game

   game_init --> |Success| io_map
   game_init --> |Init failed| main_menu>main menu]
   map_open --> map_load
   map_open --> map_load_stats
```

### 4.3 Start game
```mermaid
flowchart TD
   start>Start game]
   --> save{Found save?\nAsk: Load?}
   --> |Yes| io_map
   -.-> printer
   save -.-> |No| printer

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

### 4.4 Gameplay
One of `main.c`'s primary functions is to handle the gameplay loop: 
`game.c :: game_wait_input()` is called continuously in a loop until the game
ends or the user exits the level. This function handles waiting for inputs and
calling the logic functions related to the input.

```mermaid
flowchart TD
   gameplay>Gameplay] --> loop{Game loop} --> |input loop| game
   

   subgraph game[game.c]
      direction LR
      
      game_wait_input
      game_mv
      goal
      game_undo
      game_reset
      exit
   end

   game_wait_input --> |Directional move| game_mv -.-> goal{Goal met?}
   game_wait_input --> |Undo| game_undo -.-> goal
   game_wait_input --> |Reset| game_reset -.-> goal
   game_wait_input --> |Exit| exit

   goal -.-> |No| game_wait_input
   goal --> |Yes| exit([Exit loop])
```

### 4.5 Cleanup
```mermaid
flowchart TD
   cleanup>Cleanup]
   -.-> game_won{Game lost?\nAsk: Save?}
   --> |Yes| io_map -.-> game_e["game_end"]
   game_won -.-> |Game won| game

   subgraph io_map[io_map.c]
      map_save_moves
   end 

   subgraph game[game.c]
      fame>Process fame] -.-> game_e
   end

   game_e -.-> main
   
   subgraph main[main.c]
      direction LR
      ask_continue{Ask: Next/Retry\nor main menu?}
      -.-> |Next/Retry| stay[Stay in gameplay loop] 
      -.- game_master>game_master]
      ask_continue -.-> |Main menu| exit[Exit gameplay loop]
      -.- menu>main_menu]
   end
```

### 4.6 Process fame list entry
```mermaid
flowchart TD
   fame>Process fame] --> full

   subgraph data[data.c]
      insert_fame_at
   end

   subgraph io_map[io_map.c]
      map_save_stats
   end 

   subgraph game["game.c - fame_add()"]
      full{List not full?\nor\nIn TOP10?}
      --> |Yes| ask{Ask: Add to list?}
      ask --> |No| re(return;)
      full --> |No| re
   end

   ask --> |Yes| data -.-> io_map
```
