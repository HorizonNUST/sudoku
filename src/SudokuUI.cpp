#include "SudokuUI.hpp"
#include "SudokuGame.hpp"
#include "SudokuBoard.hpp"
#include <iostream>
#include <iomanip>
#include <cctype>

using namespace std;

// Constructor
SudokuUI::SudokuUI(SudokuGame* g) : game(g) {
    if (game == nullptr) {
        cerr << "Error: Game instance is null!" << endl;
    }
}

// Destructor
SudokuUI::~SudokuUI() {
    // Don't delete game - it's managed externally
}

// Clear input buffer
void SudokuUI::clearInputBuffer() {
    cin.clear();
    while (cin.get() != '\n');
}

// Clear screen (cross-platform approach)
void SudokuUI::clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Convert value (0-15) to character ('0'-'9', 'A'-'F')
char SudokuUI::valueToChar(int value) {
    if (value == 0) return '.';  // Empty cell
    if (value >= 1 && value <= 9) return '0' + value;
    if (value >= 10 && value <= 15) return 'A' + (value - 10);
    return '?';  // Invalid
}

// Convert character to value (0-15)
int SudokuUI::charToValue(char c) {
    c = toupper(c);
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'F') return 10 + (c - 'A');
    return -1;  // Invalid input
}

// Display the 16x16 Sudoku board
void SudokuUI::displayBoard() {
    SudokuBoard* board = game->getBoard();
    
    cout << "\n    ";
    for (int col = 0; col < 16; col++) {
        cout << setw(2) << valueToChar(col + 1) << " ";
        if ((col + 1) % 4 == 0 && col < 15) cout << "| ";
    }
    cout << "\n   +";
    for (int i = 0; i < 16; i++) {
        cout << "---";
        if ((i + 1) % 4 == 0 && i < 15) cout << "+";
    }
    cout << "+\n";
    
    for (int row = 0; row < 16; row++) {
        cout << setw(2) << valueToChar(row + 1) << " |";
        
        for (int col = 0; col < 16; col++) {
            int value = board->getCell(row, col);
            
            // Display locked cells differently (can be styled in GUI later)
            if (board->isCellLocked(row, col)) {
                cout << " " << valueToChar(value) << " ";
            } else {
                if (value == 0) {
                    cout << " . ";
                } else {
                    cout << " " << valueToChar(value) << " ";
                }
            }
            
            if ((col + 1) % 4 == 0 && col < 15) cout << "| ";
        }
        cout << "|\n";
        
        if ((row + 1) % 4 == 0 && row < 15) {
            cout << "   +";
            for (int i = 0; i < 16; i++) {
                cout << "---";
                if ((i + 1) % 4 == 0 && i < 15) cout << "+";
            }
            cout << "+\n";
        }
    }
    
    cout << "   +";
    for (int i = 0; i < 16; i++) {
        cout << "---";
        if ((i + 1) % 4 == 0 && i < 15) cout << "+";
    }
    cout << "+\n";
}

// Display game menu
void SudokuUI::displayMenu() {
    cout << "\n=================================\n";
    cout << "        SUDOKU MENU\n";
    cout << "=================================\n";
    cout << "1. Make a move\n";
    cout << "2. Request hint (-10 points)\n";
    cout << "3. Check board validity\n";
    cout << "4. Solve puzzle (-20 points)\n";
    cout << "5. Start new game\n";
    cout << "6. Exit game\n";
    cout << "=================================\n";
    cout << "Enter your choice: ";
}

// Display current score
void SudokuUI::displayScore() {
    cout << "\n>>> Current Score: " << game->getScore() << " <<<\n";
}

// Display welcome message
void SudokuUI::displayWelcome() {
    clearScreen();
    cout << "\n";
    cout << "*       WELCOME TO 16x16 SUDOKU GAME!        *\n\n";
    cout << "*   Rules:                                    *\n";
    cout << "*   - Fill grid with 0-9 and A-F             *\n";
    cout << "*   - Each row must contain all 16 values    *\n";
    cout << "*   - Each column must contain all 16 values *\n";
    cout << "*   - Each 4x4 box must contain all values   *\n";
    cout << "*                                             *\n";
    cout << "*   Scoring:                                  *\n";
    cout << "*   +10 for correct move                     *\n";
    cout << "*   -5 for invalid move                      *\n";
    cout << "*   -10 for hint                             *\n";
    cout << "*   -20 for auto-solve                       *\n";
    cout << "*                                             *\n";
    cout << "***********************************************\n\n";
}

// Display custom message
void SudokuUI::displayMessage(const string& message) {
    cout << "\n>>> " << message << " <<<\n";
}

// Display victory message
void SudokuUI::displayVictory() {
    clearScreen();
    displayBoard();
    cout << "\n";
    cout << "***********************************************\n";
    cout << "*                                             *\n";
    cout << "*         CONGRATULATIONS! YOU WON!          *\n";
    cout << "*                                             *\n";
    cout << "*        Final Score: " << setw(4) << game->getScore() << "                      *\n";
    cout << "*                                             *\n";
    cout << "***********************************************\n\n";
}

// Select difficulty level
int SudokuUI::selectDifficulty() {
    int choice;
    cout << "\nSelect Difficulty Level:\n";
    cout << "1. Easy (35% filled - 90 cells)\n";
    cout << "2. Medium (25% filled - 64 cells)\n";
    cout << "3. Hard (20% filled - 51 cells)\n";
    cout << "\nEnter your choice (1-3): ";
    
    while (true) {
        cin >> choice;
        
        if (cin.fail() || choice < 1 || choice > 3) {
            clearInputBuffer();
            cout << "Invalid choice! Please enter 1, 2, or 3: ";
        } else {
            clearInputBuffer();
            return choice - 1;  // Return 0, 1, or 2
        }
    }
}

// Get menu choice from user
int SudokuUI::getMenuChoice() {
    int choice;
    cin >> choice;
    
    if (cin.fail()) {
        clearInputBuffer();
        return -1;
    }
    
    clearInputBuffer();
    return choice;
}

// Get valid input for row, column, and value
bool SudokuUI::getValidInput(int& row, int& col, char& value) {
    char rowChar, colChar;
    
    cout << "\nEnter row (1-9, A-G): ";
    cin >> rowChar;
    
    cout << "Enter column (1-9, A-G): ";
    cin >> colChar;
    
    cout << "Enter value (1-9, A-F): ";
    cin >> value;
    
    clearInputBuffer();
    
    // Convert row and column
    row = charToValue(rowChar) - 1;  // Subtract 1 for 0-based indexing
    col = charToValue(colChar) - 1;
    
    // Validate row and column
    if (row < 0 || row >= 16 || col < 0 || col >= 16) {
        displayMessage("Invalid row or column!");
        return false;
    }
    
    return true;
}

// Main game loop
void SudokuUI::run() {
    bool running = true;
    
    while (running) {
        clearScreen();
        displayBoard();
        displayScore();
        displayMenu();
        
        int choice = getMenuChoice();
        
        switch (choice) {
            case 1: {  // Make a move
                int row, col;
                char valueChar;
                
                if (getValidInput(row, col, valueChar)) {
                    int value = charToValue(valueChar);
                    
                    if (value < 1 || value > 15) {
                        displayMessage("Invalid value! Use 1-9 or A-F.");
                        cin.get();
                        break;
                    }
                    
                    SudokuBoard* board = game->getBoard();
                    
                    // Check if cell is locked
                    if (board->isCellLocked(row, col)) {
                        displayMessage("This cell is locked! Cannot modify pre-filled cells.");
                        cin.get();
                        break;
                    }
                    
                    // Try to make the move
                    if (game->makeMove(row, col, value)) {
                        displayMessage("Valid move! +10 points");
                        
                        // Check if game is complete
                        if (game->isGameComplete()) {
                            displayVictory();
                            cout << "Press Enter to continue...";
                            cin.get();
                            
                            cout << "\nStart a new game? (y/n): ";
                            char answer;
                            cin >> answer;
                            clearInputBuffer();
                            
                            if (tolower(answer) == 'y') {
                                int difficulty = selectDifficulty();
                                game->startNewGame(difficulty);
                            } else {
                                running = false;
                            }
                        } else {
                            cin.get();
                        }
                    } else {
                        displayMessage("Invalid move! Cell remains empty. -5 points");
                        cin.get();
                    }
                }
                break;
            }
            
            case 2: {  // Request hint
                int row, col, value;
                
                if (game->requestHint(row, col, value)) {
                    cout << "\nHint: Place " << valueToChar(value) 
                         << " at position (" << valueToChar(row + 1) 
                         << ", " << valueToChar(col + 1) << ")";
                    displayMessage("-10 points for hint");
                } else {
                    displayMessage("No hints available or puzzle already solved!");
                }
                
                cout << "\nPress Enter to continue...";
                cin.get();
                break;
            }
            
            case 3: {  // Check board validity
                if (game->checkBoard()) {
                    displayMessage("Board is valid so far! Keep going!");
                } else {
                    displayMessage("Board has conflicts! Check your entries.");
                }
                
                cout << "\nPress Enter to continue...";
                cin.get();
                break;
            }
            
            case 4: {  // Solve puzzle
                cout << "\nAre you sure you want to solve the puzzle? (-20 points) (y/n): ";
                char confirm;
                cin >> confirm;
                clearInputBuffer();
                
                if (tolower(confirm) == 'y') {
                    if (game->solvePuzzle()) {
                        displayMessage("Puzzle solved! -20 points");
                    } else {
                        displayMessage("Could not solve puzzle!");
                    }
                }
                
                cout << "\nPress Enter to continue...";
                cin.get();
                break;
            }
            
            case 5: {  // Start new game
                cout << "\nAre you sure you want to start a new game? (y/n): ";
                char confirm;
                cin >> confirm;
                clearInputBuffer();
                
                if (tolower(confirm) == 'y') {
                    int difficulty = selectDifficulty();
                    game->startNewGame(difficulty);
                    displayMessage("New game started!");
                }
                
                cout << "\nPress Enter to continue...";
                cin.get();
                break;
            }
            
            case 6: {  // Exit
                cout << "\nThank you for playing Sudoku!\n";
                cout << "Final Score: " << game->getScore() << "\n\n";
                running = false;
                break;
            }
            
            default:
                displayMessage("Invalid choice! Please select 1-6.");
                cout << "\nPress Enter to continue...";
                cin.get();
                break;
        }
    }
}