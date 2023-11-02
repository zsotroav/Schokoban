cmake_minimum_required(VERSION 3.26)
project(schokoban C)

set(CMAKE_C_STANDARD 11)

include_directories(include)
include_directories(src)

add_executable(schokoban
        src/main.c
        include/lib/debugmalloc.h
        include/lib/econio.h
        include/lib/econio.c
        include/io_map.h
        src/io_map.c
        include/data.h
        include/printer.h
        src/printer.c
        src/game.c
        include/game.h
        src/data.c)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror")


