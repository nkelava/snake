cmake_minimum_required(VERSION 3.13)
project(Snake LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Snake
    Snake/src/Board.cpp
    Snake/src/Console.cpp
    Snake/src/Game.cpp
    Snake/src/main.cpp
)
