# Sudoku Game

**Team Members & Roles:**

- **Azhan Ali** - Sudoku Algorithm, Create Doc
- **Muhammad Mujtaba** - GUI in SFML
- **Sheharyar Khalid** - User interface, Art Design, Testing

## Overview

This is a GUI-based Sudoku game written in C++ with SFML:

- Has difficulty
- Show Solution, If Required
- Validates moves in real-time according to Sudoku rules

## Execution Instructions (assuming VS Code)

### Prerequisites

- `Ninja` in CLI
  - On Mac use `brew install ninja`
  - On Windows use `choco install ninja`, assuming `Chocolatey` is installed, if not install it
- `CMake` in CLI
- `Git` in CLI

### Initial steps after cloning

- CMake Preset have been setup depending on platform
- Select Preset `Win64` or `Mac` depending on platform
- Run `setup.bat` or `setup.sh` according to platform
- This clones the `vcpkg` package and installs `SFML`

### Running the Game

- Run `run.bat` or `run.sh` according to platform

### Design

## `Sudoku` class for Algorithm grid validation etc

The class stores everything related to `Sudoku` in itself.
The Sudoku grid is represented as a 9×9 2D array:

```cpp
int grid[9][9];
```

- **Value 0** represents empty cells
- **Values 1-9** represent filled cells
- **Pre-filled cells** are marked as prefilled / fixed during gameplay

### Solving and filling the board

In order to solve the sudoku board backtracking logic was used. This was done by recursions. The function was called again and again to fill the board by numbers from 1-9 using nested for loops. if placing the number didn't break the sudoku rules function call returns true, but if it did break the rules function returns false and the function backtracks by setting that cell to 0 and then looping again trying different number. In this way we use recursion to fill the board by numbers until an valid board is formed and we store the result in the class.

## GUI Framework

### **SFML Framework**

The project uses SFML (Simple and Fast Multimedia Library) as the graphics framework, installed via vcpkg package manager.

### **Main Layout System**

- `MainLayoutGroup.cpp` / `MainLayoutGroup.hpp` - Manages the overall layout structure and UI element positioning
- Handles the arrangement of game board, buttons, and other UI components
- Is Custom for Sudoku

### **Visual Styling**

- `SudokuBoardStyles.hpp` - Contains styling constants for the Sudoku board
  - Text Config
  - Grid Style Config
  - Buttons Style Config

### **Entry Point**

- `main.cpp` - Application entry point that initializes and starts the game runner

## GUI Features

1. **Interactive Grid**: Click cells to select and input numbers
2. **Visual Feedback**:
   - Highlight selected cell
   - Show conflicts/errors in real-time
   - Distinguish pre-filled vs user-entered numbers
3. **Custom Fonts**
4. **Sound Effects**

## Engine Architecture

The engine directory likely contains:

- Window management wrapper
- Input handling system  
- Rendering utilities

The utils directory includes:

- General Helper functions i.e `DEBUG_PRINT`
- Constants for all program i.e `ZERO_VECTOR2F`

## AI Tool Reflection

- Received suggestions for clear code commenting
- All core logic and algorithms were understood and implemented by team members
- AI was used as a learning tool, not a code generator

## Attributions

- [Google Fonts](https://fonts.google.com/) for font
- [Pixabay](https://pixabay.com/) for sound effect
