# CPPND: Capstone Snake Game Example

This is a starter repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

<img src="snake_game.gif"/>

This project have added the function to enter player name to save highscore and can display 5 highest scores.

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source. 
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* SDL_TTF >= 2.0
  * Linux: sudo apt-get install libsdl2-ttf-dev
  * Mac: [Click here](https://macappstore.org/sdl2_ttf/) for installation instructions
  * Windows: Download from this link: [SDL2_ttf](https://github.com/libsdl-org/SDL_ttf/releases)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.

## File structure
1. [game.cpp](https://github.com/Dinha1/CppND-Capstone-Snake-Game/blob/master/src/game.cpp): implement the game loop
2. [controller.cpp](https://github.com/Dinha1/CppND-Capstone-Snake-Game/blob/master/src/controller.cpp): handle the user control
3. [renderer.cpp](https://github.com/Dinha1/CppND-Capstone-Snake-Game/blob/master/src/renderer.cpp): render game screen in game loop
4. [score.cpp](https://github.com/Dinha1/CppND-Capstone-Snake-Game/blob/master/src/score.cpp): define each highscore record
5. [scoreList.cpp](https://github.com/Dinha1/CppND-Capstone-Snake-Game/blob/master/src/scoreList.cpp): define list of highscores
6. [snake.cpp](https://github.com/Dinha1/CppND-Capstone-Snake-Game/blob/master/src/snake.cpp): define status and behavior of the snake

## Rubric points addressed
1. The project reads data from a file and process the data, or the program writes data to a file.([scoreList.cpp](https://github.com/Dinha1/CppND-Capstone-Snake-Game/blob/master/src/scoreList.cpp) - line 2, line 30)
2. The project accepts user input and processes the input. ([game.cpp](https://github.com/Dinha1/CppND-Capstone-Snake-Game/blob/master/src/game.cpp) - line 48)
3. The project uses Object Oriented Programming techniques.
4. Classes use appropriate access specifiers for class members.
5. Class constructors utilize member initialization lists.
6. Classes encapsulate behavior.
(rubric from 3 to 6 are addressed in class [score.cpp](https://github.com/Dinha1/CppND-Capstone-Snake-Game/blob/master/src/score.cpp) and [scoreList.cpp](https://github.com/Dinha1/CppND-Capstone-Snake-Game/blob/master/src/scoreList.cpp))
7. The project uses multithreading. ([game.cpp](https://github.com/Dinha1/CppND-Capstone-Snake-Game/blob/master/src/game.cpp) - line 37)
8. A mutex or lock is used in the project.([renderer.cpp](https://github.com/Dinha1/CppND-Capstone-Snake-Game/blob/master/src/renderer.cpp) - line 103, line 175)

## CC Attribution-ShareAlike 4.0 International


Shield: [![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

This work is licensed under a
[Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[![CC BY-SA 4.0][cc-by-sa-image]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg
