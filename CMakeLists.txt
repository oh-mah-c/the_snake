cmake_minimum_required(VERSION 3.10)

project(StructSnake VERSION 1.0 LANGUAGES C)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

set(SDL_STATIC ON CACHE BOOL "" FORCE)
set(SDL_SHARED OFF CACHE BOOL "" FORCE)
set(SDL_TEST OFF CACHE BOOL "" FORCE)

add_subdirectory(SDL)

set(SOURCES
    main.c
    game.c
    engine.c
    map.c
)

add_executable(snake ${SOURCES})

target_link_libraries(snake PRIVATE SDL2-static)
target_include_directories(snake PRIVATE SDL/include)