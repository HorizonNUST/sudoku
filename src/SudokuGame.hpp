#ifndef SUDOKU_GAME_HPP
#define SUDOKU_GAME_HPP

// Forward declarations
class SudokuBoard;
class SudokuValidator;
class SudokuSolver;

class SudokuGame {
private:
    SudokuBoard* board;           // Pointer to board instance
    SudokuValidator* validator;   // Pointer to validator instance
    SudokuSolver* solver;         // Pointer to solver instance
    
    int score;                    // Current player score
    int difficulty;               // Current difficulty (0=Easy, 1=Medium, 2=Hard)
    int solvedBoard[16][16];      // Stores the complete solution
    
    // Private helper methods for board generation
    void generateSolvedBoard();
    void removeNumbers(int numToRemove);
    void shuffleNumbers(int mapping[16]);
    bool fillBoard(int board[16][16], int row, int col);
    
public:
    // Constructor and Destructor
    SudokuGame();
    ~SudokuGame();
    
    // Game management methods
    void startNewGame(int difficulty);
    bool makeMove(int row, int col, int value);
    bool requestHint(int& row, int& col, int& value);
    bool solvePuzzle();
    bool checkBoard();
    
    // Query methods
    int getScore();
    bool isGameComplete();
    SudokuBoard* getBoard();
};

#endif // SUDOKU_GAME_HPP