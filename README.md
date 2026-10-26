# Snake

For my OOP class project I chose to make an ASCII console game, so I went with one of the best old-school classic games, (dramatic pause) Snake :D For people who have never played Snake before, here is a link with a little more information about the game: https://en.wikipedia.org/wiki/Snake_(video_game_genre).

When the player starts the game, the main menu shows up and there are 3 options:

1. Press ESC to exit the game
2. Press TAB to see the TOP 5 highscores
3. Press ENTER to start the game

Before pressing ENTER to start the game, the player has the option to enter any username they wish, although the username length is limited to 12 characters. If the player does not enter anything, their username is set to "Unknown" by default.

# Commands

To move the snake, the player can only use the arrow keys: left arrow key (<-) to go left, right arrow key (->) to go right, etc. It is not possible for the snake to go downward if it is moving upward and vice versa; the same applies to left and right movement. Lastly, the snake can go through the border and it will end up on the opposite side, so it is not game over if the snake touches it.

# Files

To draw the bigger text (SNAKE and GAME OVER on the main and end screens) on the board, the program uses 2 files (menu-coordinates.txt, end-coordinates.txt). They hold letter coordinates, so make sure they are in the Snake/data folder. Every letter is separated by an empty row, and every row is one line that makes up a letter. For example, (1 1 2 2) represents x1, y1, x2, y2 and the program draws a line from point 1 to point 2. Furthermore, highscores are saved in highscores.txt, which means that file should also be in the Snake/data folder.

# Project structure

```
Snake.sln                 Visual Studio solution
Snake/
    Snake.vcxproj         Visual Studio project
    src/                  source and header files
    data/                 coordinates and highscores files used by the game
```

Open Snake.sln in Visual Studio and run the game from there; data files are loaded relative to the Snake project folder.
