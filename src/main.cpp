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

    // Add functions for checking the valid move
    // This will be used for sudoku solver 
    bool valid(int a[9][9], int row, int col, int num)
    {
        // loop to move through row to check for the same number
        for (int i = 0; i < 9; i++)
        {
            if (a[row][i] == num)
            {
                return false;
            }
        }
        
        // loop to move through column to check for the same number
        for (int j = 0; j < 9; j++)
        {
            if (a[j][col] == num)
            {
                return false;
            }
        }
        
        // loop to check for the same number inside a box of the sudoku
        int startingRow = row - row % 3;
        int startingCol = col - col % 3;
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                if (a[i + startingRow][j + startingCol] == num)
                {
                    return false;
                }
            }
        }

        return true;
    }

    // Function to check for a valid entered move
    // This will check if the user entered correct number
    bool validMove(int row, int col, int input)
    {
        // loop to move through row to check for the same number
        for (int i = 0; i < 9; i++)
        {
            if (i != col && grid[row][i] == input)
            {
                return false;
            }
        }

        // loop to move through column to check for the same number
        for (int j = 0; j < 9; j++)
        {
            if (j != row && grid[j][col] == input)
            {
                return false;
            }
        }

        // loop to check for the same number inside a box in sudoku
        int startingRow = row - row % 3;
        int startingCol = col - col % 3;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                int r = i + startingRow;
                int c = j + startingCol;
            if ((r != row || c != col) && grid[r][c] == input)
            {
                return false;
            }
            }
        }
        
        return true;
    }

    // Function to solve the sudoku board
    bool solveSudoku(int b[9][9])
    {
        for (int row = 0; row < 9; row++)
        {
            for (int col = 0; col < 9; col++)
            {
                if (b[row][col] == 0) // Checks if the block is filled by number or not
                {
                    for (int num = 1; num <= 9; num++) // loop to fill numbers from 1 to 9
                    {
                        if (valid(b, row, col, num))
                        {
                            b[row][col] = num;
                            // Using recursion to fill all the board
                            // If condition will become true when the last element is filled
                            if (solveSudoku(b))
                            {
                                return true;
                            }
                            // if no number is found then reset the block to 0 and loop again
                            b[row][col] = 0;
                        }
                    }
                    return false;
                }
            }
        }
    }
};

int main() {
    return 0;
}
