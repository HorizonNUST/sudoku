# Sudoku Game

**Team Members & Roles:**

- **Azhan Ali** - Sudoku Algorithm
- **Muhammad Mujtaba** - GUI in SFML
- **Sheharyar Khalid** - User interface, Art ,testing

## Overview

This is a console-based Sudoku game written in C++ with SFML:

- Allows users to play Sudoku puzzles of varying difficulty levels
- Includes an automatic solver using backtracking algorithm
- Validates moves in real-time according to Sudoku rules

## Execution Instructions (assuming VS Code)

### Initial steps after cloning

- CMake Preset have been setup depending on platform
- Select Preset `Win64` or `Mac` depending on platform
- Run `setup.bat` or `setup.sh` according to platform

### Running the Game

- Run `run.bat` or `run.sh` according to platform

### Design

The program consists of two important parts

## `Sudoku` class for Algorithm grid validation etc

The Sudoku grid is represented as a 9×9 2D array:

```cpp
int grid[9][9];
```

- **Value 0** represents empty cells
- **Values 1-9** represent filled cells
- **Pre-filled cells** are marked as prefilled / fixed during gameplay

## AI Tool Reflection

- Received suggestions for clear code commenting
- All core logic and algorithms were understood and implemented by team members
- AI was used as a learning tool, not a code generator

## Attributions

- [Google Fonts](https://fonts.google.com/) for font
- [Pixabay](https://pixabay.com/) for sound effect
