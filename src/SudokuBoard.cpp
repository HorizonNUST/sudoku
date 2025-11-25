#include "SudokuBoard.hpp"

// Constructor - initializes empty board
SudokuBoard::SudokuBoard() {
    clearBoard();
}

// Resets all cells to 0 and unlocks all cells
void SudokuBoard::clearBoard() {
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            board[i][j] = 0;
            initialCells[i][j] = false;
        }
    }
}

// Returns value at position (0-15)
int SudokuBoard::getCell(int row, int col) const {
    if (row >= 0 && row < 16 && col >= 0 && col < 16) {
        return board[row][col];
    }
    return -1; // Invalid position
}

// Sets value at position
void SudokuBoard::setCell(int row, int col, int value) {
    if (row >= 0 && row < 16 && col >= 0 && col < 16) {
        if (value >= 0 && value <= 15) {
            board[row][col] = value;
        }
    }
}

// Checks if cell is pre-filled (locked)
bool SudokuBoard::isCellLocked(int row, int col) const {
    if (row >= 0 && row < 16 && col >= 0 && col < 16) {
        return initialCells[row][col];
    }
    return false;
}

// Marks cell as pre-filled
void SudokuBoard::lockCell(int row, int col) {
    if (row >= 0 && row < 16 && col >= 0 && col < 16) {
        initialCells[row][col] = true;
    }
}

// Marks cell as modifiable
void SudokuBoard::unlockCell(int row, int col) {
    if (row >= 0 && row < 16 && col >= 0 && col < 16) {
        initialCells[row][col] = false;
    }
}

// Checks if all cells are filled (non-zero)
bool SudokuBoard::isBoardFull() const {
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            if (board[i][j] == 0) {
                return false;
            }
        }
    }
    return true;
}

// Copies current board state to destination array
void SudokuBoard::copyBoard(int destination[16][16]) const {
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            destination[i][j] = board[i][j];
        }
    }
}

// Loads board from source array
void SudokuBoard::loadBoard(int source[16][16]) {
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            board[i][j] = source[i][j];
        }
    }
}