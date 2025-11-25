#ifndef SUDOKUBOARD_HPP
#define SUDOKUBOARD_HPP

class SudokuBoard {
private:
    int board[16][16];           // The game board (0-15 representing 0-9, A-F)
    bool initialCells[16][16];   // Tracks which cells were pre-filled (locked)

public:
    // Constructor
    SudokuBoard();
    
    // Board operations
    void clearBoard();
    
    // Cell accessors
    int getCell(int row, int col) const;
    void setCell(int row, int col, int value);
    
    // Cell locking
    bool isCellLocked(int row, int col) const;
    void lockCell(int row, int col);
    void unlockCell(int row, int col);
    
    // Board state
    bool isBoardFull() const;
    
    // Board copy operations
    void copyBoard(int destination[16][16]) const;
    void loadBoard(int source[16][16]);
};

#endif // SUDOKUBOARD_HPP