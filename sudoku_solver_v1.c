// Compute the solution to an arbitrary soduku

#include <stdio.h>
#define SUDOKU_MAX_LEN 9

int main()
{
    int *grid, *set_grid(void);
    // Set up the grid in an 9 x 9 array
    grid = set_grid();

    // Loop over the 9 numbers
    // Iterate over the rows placing numbers in empty spaces
    unsigned num = 1;
    int col, row;
    for (col = 0; col < SUDOKU_MAX_LEN; col++) // num <= SUDOKU_MAX_LEN
    {
        for (row = 0; row < SUDOKU_MAX_LEN; row++)
        {
            if (grid[row])
            {
                // If empty, add in num. Start checking ALL other entries
            }
        }
    }

    // Check if it is a valid placement
}

int *set_grid(void)
{
    int grid[SUDOKU_MAX_LEN][SUDOKU_MAX_LEN];

    return grid;
}

int check_row(int *row)
{
    return 0;
}

int check_col(int *col)
{
    return 0;
}

int check_block(int *row, int *col)
{
    return 0;
}