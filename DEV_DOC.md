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
```
schokoban
├── src
|   ├── debugmalloc.c   // Library code
|   ├── econio.c        // Library code
│   ├── main.c          // Main code
|   └── map.c           // Map handling
├── include
|   ├── debugmalloc.h
│   ├── econio.h
│   ├── ECONIO_LICENSE  // MIT License file for the econio library
|   └── map.h
├── .gitignore
├── CMakeLists.txt
├── DEV_DOC.md          // This documentation
├── econio_readme.md    // Readme for econio lib, may get removed in the future
└── LICENSE             // GPL-3.0 (License file)

```

#### Used external code
- Libraries:
  1. [c-econio](https://infoc.eet.bme.hu/megjelenites/c-econio.zip) 
     by Zoltan Czirkos. [MIT License](include/ECONIO_LICENSE)
  2. [debugmalloc](http://www.3d-scene.hu/csuli/debugmalloc/debugmalloc.c) 
     ([.h](http://www.3d-scene.hu/csuli/debugmalloc/debugmalloc.h))
- Code snippets: Noted in source if applicable
- General reference documents:
  1. [Sokoban.org](http://sokoban.org/about_sokoban.php) for game rules 
     and XSB/LURD format specs

## Dev notes
- The handed out library [econio](https://infoc.eet.bme.hu/megjelenites/c-econio.zip) 
  had a `char-subscripts` warning that was disabled with `#pragma` statements on 
  lines [256](src/econio.c#L256), [257](src/econio.c#L257), and [327](src/econio.c#L327) 
  in [src/econio.c](src/econio.c#L256-L257) due to the `-Wall -Werror` compiler requirements. 
  The library's code is otherwise untouched. 