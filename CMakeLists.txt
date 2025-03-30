cmake_minimum_required(VERSION 3.29)
project(ECEFUS C)

set(CMAKE_C_STANDARD 23)

add_executable(ECEFUS main.c
        game.c
        game.h
        caracter.c
)

target_link_libraries(ECEFUS -lmingw32 -lalleg44)