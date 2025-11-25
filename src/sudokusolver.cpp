#include "SudokuGame.hpp"
#include "SudokuBoard.hpp"
#include "SudokuValidator.hpp"
#include "SudokuSolver.hpp"
#include <cstdlib>
#include <ctime>

// Constructor
SudokuGame::SudokuGame() {
    board = new SudokuBoard();
    validator = new SudokuValidator();
    solver = new SudokuSolver(validator);
    
    score = 0;
    difficulty = 0;
    
    // Initialize solvedBoard to all zeros
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            solvedBoard[i][j] = 0;
        }
    }
    
    // Seed random number generator
    srand(static_cast<unsigned int>(time(0)));
}

// Destructor
SudokuGame::~SudokuGame() {
    delete board;
    delete validator;
    delete solver;
}

// Shuffle numbers for board generation
void SudokuGame::shuffleNumbers(int mapping[16]) {
    // Initialize mapping (1-16)
    for (int i = 0; i < 16; i++) {
        mapping[i] = i + 1;
    }
    
    // Fisher-Yates shuffle
    for (int i = 15; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = mapping[i];
        mapping[i] = mapping[j];
        mapping[j] = temp;
    }
}

// Fill board recursively for generation
bool SudokuGame::fillBoard(int tempBoard[16][16], int row, int col) {
    // Move to next row if we've filled current row
    if (col == 16) {
        row++;
        col = 0;
    }
    
    // Board is complete
    if (row == 16) {
        return true;
    }
    
    // Create shuffled number list
    int numbers[16];
    for (int i = 0; i < 16; i++) {
        numbers[i] = i + 1;
    }
    
    // Shuffle numbers
    for (int i = 15; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = numbers[i];
        numbers[i] = numbers[j];
        numbers[j] = temp;
    }
    
    // Try each number
    for (int i = 0; i < 16; i++) {
        int num = numbers[i];
        
        if (validator->isValidMove(tempBoard, row, col, num)) {
            tempBoard[row][col] = num;
            
            if (fillBoard(tempBoard, row, col + 1)) {
                return true;
            }
            
            tempBoard[row][col] = 0;
        }
    }
    
    return false;
}

// Generate a solved Sudoku board
void SudokuGame::generateSolvedBoard() {
    // Clear the solved board
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            solvedBoard[i][j] = 0;
        }
    }
    
    // Fill the board recursively
    fillBoard(solvedBoard, 0, 0);
}

// Remove numbers based on difficulty
void SudokuGame::removeNumbers(int numToRemove) {
    int removed = 0;
    
    while (removed < numToRemove) {
        int row = rand() % 16;
        int col = rand() % 16;
        
        if (board->getCell(row, col) != 0) {
            board->setCell(row, col, 0);
            board->unlockCell(row, col);
            removed++;
        }
    }
}

// Start a new game with given difficulty
void SudokuGame::startNewGame(int diff) {
    difficulty = diff;
    score = 0;
    
    // Clear the board
    board->clearBoard();
    
    // Generate a complete solved board
    generateSolvedBoard();
    
    // Copy solved board to game board
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            board->setCell(i, j, solvedBoard[i][j]);
            board->lockCell(i, j);
        }
    }
    
    // Remove numbers based on difficulty
    // Total cells = 256
    // Easy: 35% filled = 90 cells, remove 166
    // Medium: 25% filled = 64 cells, remove 192
    // Hard: 20% filled = 51 cells, remove 205
    
    int numbersToRemove;
    if (difficulty == 0) {
        numbersToRemove = 166;  // Easy
    } else if (difficulty == 1) {
        numbersToRemove = 192;  // Medium
    } else {
        numbersToRemove = 205;  // Hard
    }
    
    removeNumbers(numbersToRemove);
}

// Make a move on the board
bool SudokuGame::makeMove(int row, int col, int value) {
    // Validate move
    int tempBoard[16][16];
    board->copyBoard(tempBoard);
    
    if (validator->isValidMove(tempBoard, row, col, value)) {
        board->setCell(row, col, value);
        score += 10;  // +10 for correct move
        return true;
    } else {
        board->setCell(row, col, 0);  // Keep cell empty
        score -= 5;   // -5 for invalid move
        return false;
    }
}

// Request a hint
bool SudokuGame::requestHint(int& row, int& col, int& value) {
    int tempBoard[16][16];
    board->copyBoard(tempBoard);
    
    if (solver->getHint(tempBoard, row, col, value)) {
        score -= 10;  // -10 for hint
        return true;
    }
    
    return false;
}

// Solve the puzzle automatically
bool SudokuGame::solvePuzzle() {
    // Copy current board to temp
    int tempBoard[16][16];
    board->copyBoard(tempBoard);
    
    // Try to solve
    if (solver->solveSudoku(tempBoard)) {
        // Load solved board back
        for (int i = 0; i < 16; i++) {
            for (int j = 0; j < 16; j++) {
                if (!board->isCellLocked(i, j)) {
                    board->setCell(i, j, tempBoard[i][j]);
                }
            }
        }
        
        score -= 20;  // -20 for auto-solve
        return true;
    }
    
    return false;
}

// Check if current board state is valid
bool SudokuGame::checkBoard() {
    int tempBoard[16][16];
    board->copyBoard(tempBoard);
    
    return validator->checkCurrentState(tempBoard);
}

// Get current score
int SudokuGame::getScore() {
    return score;
}

// Check if game is complete
bool SudokuGame::isGameComplete() {
    // Check if board is full
    if (!board->isBoardFull()) {
        return false;
    }
    
    // Check if board is valid
    int tempBoard[16][16];
    board->copyBoard(tempBoard);
    
    return validator->isCompleteAndValid(tempBoard);
}

// Get board pointer
SudokuBoard* SudokuGame::getBoard() {
    return board;
}