#include "SudokuUI.hpp"
//#include "SudokuGame.hpp"
#include <iostream>

using namespace std;

int main() {
    // Create game instance
    SudokuGame game;
    
    // Create UI instance with game reference
    SudokuUI ui(&game);
    
    // Display welcome message
    ui.displayWelcome();
    
    // Let user select difficulty
    int difficulty = ui.selectDifficulty();
    
    // Start the game with selected difficulty
    // 0 = Easy (35% filled - 90 cells)
    // 1 = Medium (25% filled - 64 cells)
    // 2 = Hard (20% filled - 51 cells)
    //game.startNewGame(difficulty);
    
    // Run the main game loop
    ui.run();
    
    return 0;
}