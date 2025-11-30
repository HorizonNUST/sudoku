#pragma once

// Making an enum for the difficult level
enum class Difficulty : int
{
    Easy = 20,
    Medium = 40,
    Hard = 60
};

class Sudoku
{
private:
    int grid[9][9];
    int sol[9][9];
    bool fixed[9][9];
    int selRow;
    int selCol;
    int score;

    // Helper function to check validity for solver
    bool valid(int a[9][9], int row, int col, int num);

    // Function to solve the sudoku board
    bool solveSudoku(int b[9][9]);

    // Function to randomly fill diagonal boxes
    void fillDiagonal();

public:
    Sudoku();

    // Function to check for a valid user move
    bool validMove(int row, int col, int input);

    // Function to generate a new puzzle
    void makePuzzle(Difficulty difficulty);

    // Function to select a cell
    void selectCell(int row, int col);

    // Function to input a number
    bool inputNumber(int num);

    // Function to give hint
    void hint();

    // Function to auto solve
    void autoSolve();

    // Function to check for win
    bool win();

    // Getter functions
    int getCell(int row, int col) const;
    bool isFixed(int row, int col) const;
    bool isSel(int row, int col) const;
    bool sameRow(int row) const;
    bool sameCol(int col) const;
    bool sameBox(int row, int col) const;
    int getScore() const;

    void setCell(int row, int col, int value);
};
