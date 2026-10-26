# Snake

The classic Snake game for the console on Windows, Linux and macOS, written in C++ as an object-oriented programming class project.

## Requirements

- **Windows:** Visual Studio 2019 or newer with the **Desktop development with C++** workload
- **Linux and macOS:** a C++11 compiler and CMake 3.13 or newer

## Build and run

**Windows:** open `Snake.sln` in Visual Studio and press **Ctrl+F5**.

**Linux and macOS:** run these commands from the repository folder:

```sh
cmake -S . -B build
cmake --build build
cd Snake
../build/Snake
```

The game loads its files from `data/` relative to the working directory, so start it from the `Snake` folder (Visual Studio does this automatically).

## How to play

| Key | Action |
| --- | --- |
| ENTER | Start the game |
| TAB | Show the top 5 highscores |
| ESC | Exit the game, or go back to the menu from the highscores |
| Arrow keys | Move the snake |

Type your name on the main menu before starting, otherwise you play as `Unknown`. Eat `o` to grow and earn 3 points. The snake wraps around the edges, and the game ends when it runs into itself. Your score is saved if it makes the top 5.

## Project structure

```
Snake.sln                     Visual Studio solution
CMakeLists.txt                CMake build for Linux and macOS
Snake/
├── Snake.vcxproj             Visual Studio project
├── src/                      Source and header files
└── data/
    ├── menu-coordinates.txt  SNAKE title
    ├── end-coordinates.txt   GAME OVER title
    └── highscores.txt        Top 5 scores
```

Each line in a coordinates file (`x1 y1 x2 y2`) draws one line of a title letter, and letters are separated by empty lines.
