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
    int score;

public:
    Sudoku() : selRow(-1), selCol(-1), score(0) 
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

    // Function to solve the sudoku board and store the result 
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
        return true;
    }

    // Function to randomly fill the diagonal box of the sudoku board
    void fillDiagonal()
    {
        for (int i = 0; i < 9; i++)
        {
            std::vector<int> nums = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
            static std::mt19937 rng(std::random_device{}());
            std::shuffle(nums.begin(), nums.end(), rng); // Shuffles the vector array so that each box can be randomly filled

            // Using nested loop to fill the 3x3 diagonal box in sudoku
            int pos = 0;
            for (int j = 0; j < 3; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    sol[i + j][i + k] = nums[pos++];
                }
            }
        }
    }

    // Funciton to reset the board and generate a new puzzle
    void generatePuzzle(int difficulty)
    {
        // Resetting the entire board to 0
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                sol[i][j] = 0;
            }
        }

        // Calling funcitons to fill diagonal and generate solution
        fillDiagonal();
        solveSudoku(sol);

        // for loop to solve the board after calling the functions. This is initial condition
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            grid[i][j] = sol[i][j]; // Initializes the grid by sol[][] elements 
            fixed[i][j] = true; // Fixes the values
        }

        // Declaring a vector that will store the 81 coordinates
        std::vector<std::pair<int, int>> cells;
        // nested for loop to initialize by coordinates of each cell
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                cells.push_back({i, j}); // this creates a list of coordinates. push_back creates new element at each iteration
            }
        }

        // Shuffling the list of cells
        std::shuffle(cells.begin(), cells.end(), std::mt19937(std::random_device()()));
        // For loop to remove the entries and initialize it back to 0. 
        for (int i = 0; i < difficulty; i++)
        {
            // Initializing the rows and column by the coordinates of the cells already made
            int rows = cells[i].first;
            int col = cells[i].second;
            grid[rows][col] = 0; // Sets the grid element to 0
            fixed[rows][col] = false; // Sets the fixed cell to false, so that the user can enter the element
        }

        score = 0; // Initializes the score to 0
    }

    void selectCell(int row, int col) 
    {
     selRow = row;
     selCol = col;
    }

    // Functiont to place the number
    bool inputNumber(int num)
    {
        if (selRow >= 0 && selRow < 9 && selCol >= 0 && selCol < 9)
        {
            if(!fixed[selRow][selCol])
            {
                grid[selRow][selCol] = num;

                // Apply conditions to check if the number entered is valid or not
                if (num != 0)
                {
                    // Check if the input number is valid or not 
                    if (validMove(selRow, selCol, num))
                    {
                        if (num == sol[selRow][selCol])
                        {
                            score += 10; // Incrementing by 10 if correct 
                        }
                        else
                        {
                            score -= 5; // Decrementing by 5 is imcorrect
                        }
                    }
                    else
                    {
                        score -= 5;
                    }
                }
                return true;
            }
        } 
        return false;
    }

    // Function to give hints to user
    void hint()
    {
        // Apply if condition to check if the right grid is selected or not 
        if (selRow >= 0 && selRow < 9 && selCol >= 0 && selCol < 9)
        {
            // Check if the grid is fixed or not 
            if (!fixed[selRow][selCol])
            {
                grid[selRow][selCol] = sol[selRow][selCol];
                score -= 10;
            }
        }
    }

    // Function to auto solve the board
    void autoSolve()
    {
        // for loop to fill the grid by the sol of the board
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                grid[i][j] = sol[i][j]; // Puts the elements of sol[][] into grid[][]
            }
        }
        score -= 20;
    }

    // Function to check for the win 
    bool win()
    {
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                if (grid[i][j] != sol[i][j])
                    return false;
            }
        }
        return true;
    }
    
    // Function to get a cell from the board
    int getCell(int row, int col) const
    {
        return grid[row][col];
    }
    // Function to check if the cell is fixed or not 
    bool isFixed(int row, int col) const
    {
        return fixed[row][col];
    }
    // Function to check if the selected cell matches the cell you are checkinf
    bool isSel(int row, int col) const
    {
        return selRow == row && selCol == col;
    }
    // Function to check if the selected row is the same as given row
    bool sameRow(int row) const
    {
        return selRow == row;
    }
    // Function to check if the selected column is same as given column
    bool sameCol(int col) const
    {
        return selCol == col;
    }
    // Function to check if the given cell is in the 3x3 box of the sudoku
    bool sameBox(int row, int col) const
    {
        if (selRow < 0 || selCol < 0)
            return false;
        return (selRow / 3 == row / 3) && (selCol / 3 == col / 3);
    }
};

int main() {
    return 0;
}
