# Sudoku Game

**Team Members & Roles:**

- **Azhan Ali** - Sudoku Algorithm
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
