#include "sudoku.hpp"
#include <vector>
#include <algorithm>
#include <random>

Sudoku::Sudoku() : selRow(-1), selCol(-1), score(0)
{
    // Initialize the board
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

bool Sudoku::valid(int a[9][9], int row, int col, int num)
{
    // Check row
    for (int i = 0; i < 9; i++)
    {
        if (a[row][i] == num)
        {
            return false;
        }
    }

    // Check column
    for (int j = 0; j < 9; j++)
    {
        if (a[j][col] == num)
        {
            return false;
        }
    }

    // Check 3x3 box
    int startingRow = row - row % 3;
    int startingCol = col - col % 3;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (a[i + startingRow][j + startingCol] == num)
            {
                return false;
            }
        }
    }

    return true;
}

bool Sudoku::validMove(int row, int col, int input)
{
    // Check row
    for (int i = 0; i < 9; i++)
    {
        if (i != col && grid[row][i] == input)
        {
            return false;
        }
    }

    // Check column
    for (int j = 0; j < 9; j++)
    {
        if (j != row && grid[j][col] == input)
        {
            return false;
        }
    }

    // Check 3x3 box
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

bool Sudoku::solveSudoku(int b[9][9])
{
    for (int row = 0; row < 9; row++)
    {
        for (int col = 0; col < 9; col++)
        {
            if (b[row][col] == 0)
            {
                for (int num = 1; num <= 9; num++)
                {
                    if (valid(b, row, col, num))
                    {
                        b[row][col] = num;
                        if (solveSudoku(b))
                        {
                            return true;
                        }
                        b[row][col] = 0;
                    }
                }
                return false;
            }
        }
    }
    return true;
}

void Sudoku::fillDiagonal()
{
    for (int i = 0; i < 9; i += 3)
    {
        std::vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        static std::mt19937 rng(std::random_device{}());
        std::shuffle(nums.begin(), nums.end(), rng);

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

void Sudoku::makePuzzle(Difficulty difficulty)
{
    // Reset the board
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            sol[i][j] = 0;
        }
    }

    // Generate solution
    fillDiagonal();
    solveSudoku(sol);

    // Copy solution to grid
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            grid[i][j] = sol[i][j];
            fixed[i][j] = true;
        }
    }

    // Create list of all cell coordinates
    std::vector<std::pair<int, int>> cells;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            cells.push_back({i, j});
        }
    }

    // Shuffle and remove cells
    static std::mt19937 rng(std::random_device{}());
    std::shuffle(cells.begin(), cells.end(), rng);
    for (int i = 0; i < static_cast<int>(difficulty); i++)
    {
        int rows = cells[i].first;
        int col = cells[i].second;
        grid[rows][col] = 0;
        fixed[rows][col] = false;
    }

    score = 0;
}

void Sudoku::selectCell(int row, int col)
{
    selRow = row;
    selCol = col;
}

bool Sudoku::inputNumber(int num)
{
    if (selRow >= 0 && selRow < 9 && selCol >= 0 && selCol < 9)
    {
        if (!fixed[selRow][selCol])
        {
            grid[selRow][selCol] = num;

            if (num != 0)
            {
                if (validMove(selRow, selCol, num))
                {
                    if (num == sol[selRow][selCol])
                    {
                        score += 10;
                    }
                    else
                    {
                        score -= 5;
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

void Sudoku::hint()
{
    if (selRow >= 0 && selRow < 9 && selCol >= 0 && selCol < 9)
    {
        if (!fixed[selRow][selCol])
        {
            grid[selRow][selCol] = sol[selRow][selCol];
            score -= 10;
        }
    }
}

void Sudoku::autoSolve()
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            grid[i][j] = sol[i][j];
        }
    }
    score -= 20;
}

bool Sudoku::win()
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

int Sudoku::getCell(int row, int col) const
{
    return grid[row][col];
}

bool Sudoku::isFixed(int row, int col) const
{
    return fixed[row][col];
}

bool Sudoku::isSel(int row, int col) const
{
    return selRow == row && selCol == col;
}

bool Sudoku::sameRow(int row) const
{
    return selRow == row;
}

bool Sudoku::sameCol(int col) const
{
    return selCol == col;
}

bool Sudoku::sameBox(int row, int col) const
{
    if (selRow < 0 || selCol < 0)
        return false;
    return (selRow / 3 == row / 3) && (selCol / 3 == col / 3);
}

int Sudoku::getScore() const
{
    return score;
}