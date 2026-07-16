// Compute the solution to an arbitrary soduku

#include <stdio.h>
#define SUDOKU_MAX_LEN 9
#define PUZZLE_MAX_LINE 81
#define HASH_MAX_LEN 12

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
    int *read_puzzle(int*);
    int grid[SUDOKU_MAX_LEN][SUDOKU_MAX_LEN];
    read_puzzle(grid[0]);

    return grid[0];
}

int *read_puzzle(int *grid)
{
    int i = 0, j = 0;
    int c;
    int hash_code[HASH_MAX_LEN], puzzle_info[PUZZLE_MAX_LINE];
    while ((c = getchar()) != ' ')
    {
        hash_code[i] = c - '0';
        i++;
    }

    i = 0;
    while ((c = getchar()) != ' ')
    {
        puzzle_info[i] = c - '0';
        i++;
    }

    for (i = 0; i < SUDOKU_MAX_LEN; i++)
    {
        for (; j < SUDOKU_MAX_LEN; j++)
        {
            grid[i][j] = puzzle_info[SUDOKU_MAX_LEN * i + j];
        }
    }

    return grid;
}

int check_row(int *row)
{
    /*Check if the given row contains no matching numbers*/
    return 0;
}

int check_col(int *col)
{
    /*Check if the given column contains no matching numbers*/
    return 0;
}

int check_block(int *row, int *col)
{
    /*Check if the given 3x3 block contains no natching numbers
    The box will start at N % 3 == 0 for rows and cols, so only iterate over N / 3
    different slots*/
    return 0;
}