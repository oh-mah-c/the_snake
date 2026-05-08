cmake_minimum_required(VERSION 3.10)

project(StructSnake VERSION 1.0 LANGUAGES C)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

set(SOURCES
    main.c
    game.c
    engine.c
    map.c
)

add_executable(snake ${SOURCES})