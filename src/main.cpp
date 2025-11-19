#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include <sstream>

// Making an enum for the game state
enum State
{
    Menu,
    Playing
};

// Making an enum for the difficult level
enum Difficulty
{
    Easy = 20,
    Medium = 40,
    Hard = 60
};

// Making class for sudoku that will hold the data for the game
class Sudoku 
{
private:
    int grid[9][9];
    int sol[9][9];
    int fixed[9][9];
    int selRow;
    int selCol;

public:
    Sudoku() : selRow(-1), selCol(-1) 
    {
        // Nested for loops to initialize the boxes in the sudoku board
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                grid[i][j] = 0;
                sol[i][j] = 0;
                fixed[i][j] = false;
            }
        }
    } 

}




















int main() {
    std::print("Hello from C++ template!\n");

    return 0;
}
