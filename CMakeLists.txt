cmake_minimum_required(VERSION 3.26)
project(schokoban C)

set(CMAKE_C_STANDARD 11)

include_directories(include)
include_directories(src)

add_executable(schokoban
        src/main.c

        include/config.h

        include/lib/debugmalloc.h
        include/lib/econio.h
        include/lib/econio.c

        include/data.h
        src/data.c

        include/game.h
        src/game.c

        include/io_level.h
        src/io_level.c

        include/io_map.h
        src/io_map.c

        include/menu_custom.h
        src/menu_custom.c

        include/menu_main_printer.h
        src/menu_main_printer.c

        include/menu_level_handle.h
        src/menu_level_handle.c

        include/menu_level_printer.h
        src/menu_level_printer.c

        include/menu_main_handle.h
        src/menu_main_handle.c

        include/menu_main_printer.h
        src/menu_main_printer.c

        include/printer.h
        src/printer.c
)

file(GLOB_RECURSE SRC_DIR "src/*.c" "include/*.h")

set_source_files_properties(
        ${SRC_DIR}
        PROPERTIES
        COMPILE_FLAGS "-Wall -Werror"
)
