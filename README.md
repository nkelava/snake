# Snake

The classic Snake game for the Windows console, written in C++ as an object-oriented programming class project.

## Requirements

- Windows
- Visual Studio 2019 or newer with the **Desktop development with C++** workload

## Build and run

1. Open `Snake.sln` in Visual Studio.
2. Press **Ctrl+F5** to build and run.

The game loads its files from `data/` relative to the working directory. To run `Snake.exe` outside Visual Studio, start it from the `Snake` folder.

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
Snake/
├── Snake.vcxproj             Visual Studio project
├── src/                      Source and header files
└── data/
    ├── menu-coordinates.txt  SNAKE title
    ├── end-coordinates.txt   GAME OVER title
    └── highscores.txt        Top 5 scores
```

Each line in a coordinates file (`x1 y1 x2 y2`) draws one line of a title letter, and letters are separated by empty lines.
