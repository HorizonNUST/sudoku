#ifndef SUDOKU_UI_HPP
#define SUDOKU_UI_HPP

#include <string>
using namespace std;

// Forward declarations for game components
class SudokuGame;
class SudokuBoard;

class SudokuUI {
private:
    SudokuGame* game;  // Pointer to game instance for accessing game logic
    
    // Display helper methods
    void displayBoard();
    void displayMenu();
    void displayScore();
    void clearScreen();
    void clearInputBuffer();  // Clear cin buffer
    
    // Conversion utilities for hexadecimal Sudoku
    char valueToChar(int value);  // Converts 0-15 to '0'-'9', 'A'-'F'
    int charToValue(char c);      // Converts '0'-'9', 'A'-'F' to 0-15
    
    // Input handling
    bool getValidInput(int& row, int& col, char& value);
    int getMenuChoice();
    
public:
    // Constructor and Destructor
    SudokuUI(SudokuGame* g);
    ~SudokuUI();
    
    // Game flow methods
    void displayWelcome();
    void displayMessage(const string& message);
    void displayVictory();
    int selectDifficulty();
    
    // Main game loop
    void run();
};
#endif // SUDOKU_UI_HPP