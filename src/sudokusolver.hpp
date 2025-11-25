#ifndef SUDOKU_SOLVER_HPP
#define SUDOKU_SOLVER_HPP

// Forward declaration
class SudokuValidator;

class SudokuSolver {
private:
    SudokuValidator* validator;  // Pointer to validator for checking moves
    
    // Helper method to find empty cell
    bool findEmptyCell(int board[16][16], int& row, int& col);
    
    // Recursive solving method
    bool solveRecursive(int board[16][16]);
    
public:
    // Constructor
    SudokuSolver(SudokuValidator* v);
    
    // Main solving method
    bool solveSudoku(int board[16][16]);
    
    // Get a single hint
    bool getHint(int board[16][16], int& row, int& col, int& value);
};

#endif // SUDOKU_SOLVER_HPP