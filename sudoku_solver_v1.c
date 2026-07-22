// Compute the solution to an arbitrary soduku

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define SUDOKU_MAX_LEN 9
#define PUZZLE_MAX_LINE 81
#define HASH_MAX_LEN 12

int (*set_grid(void))[SUDOKU_MAX_LEN];
int is_solved(int (*)[SUDOKU_MAX_LEN]);
int (*attempt_solution(int (*)[SUDOKU_MAX_LEN]))[SUDOKU_MAX_LEN];
int (*read_puzzle(int (*)[SUDOKU_MAX_LEN]))[SUDOKU_MAX_LEN];
void print_puzzle(int (*)[SUDOKU_MAX_LEN]);
void save_mutable_idx(int (*)[SUDOKU_MAX_LEN], int *, int n);

int main()
{
    int (*grid)[SUDOKU_MAX_LEN];
    int mutable_idx[SUDOKU_MAX_LEN * SUDOKU_MAX_LEN];

    // Set up the grid in an 9 x 9 array
    grid = set_grid();
    save_mutable_idx(grid, mutable_idx, SUDOKU_MAX_LEN * SUDOKU_MAX_LEN);

    print_puzzle(grid);

    while (!is_solved(grid))
    {
        attempt_solution(grid);
        sleep(2);
        print_puzzle(grid);
    }

    free(grid);

    return 0;
}

// this returns a pointer to heap alocted memory. caller MUST free
int (*set_grid(void)) [SUDOKU_MAX_LEN]
{
    int (*grid)[SUDOKU_MAX_LEN] = (int (*)[SUDOKU_MAX_LEN])malloc(sizeof(int) * SUDOKU_MAX_LEN * SUDOKU_MAX_LEN);
    read_puzzle(grid);

    return grid;
}

int (*read_puzzle(int (*grid)[SUDOKU_MAX_LEN])) [SUDOKU_MAX_LEN]
{
    printf("Reading puzzle...\n");
    int i = 0, j;
    int c;
    int hash_code[HASH_MAX_LEN], puzzle_info[PUZZLE_MAX_LINE]; // hash_code will be used to check against which puzzles i have already solved in another file
    while ((c = getchar()) != ' ' && c != EOF)
    {
        if (i >= HASH_MAX_LEN)
        {
            while ((c = getchar()) != ' ')
                ;
            break;
        }
        hash_code[i] = c - '0';
        i++;
    }

    i = 0;
    while ((c = getchar()) != ' ' && c != EOF)
    {
        if (i >= PUZZLE_MAX_LINE)
        {
            while ((c = getchar()) != ' ')
                ;
            break;
        }
        puzzle_info[i] = c - '0';
        i++;
    }

    while ((c = getchar()) != '\n' && c != EOF)
        ;

    for (i = 0; i < SUDOKU_MAX_LEN; i++)
    {
        for (j = 0; j < SUDOKU_MAX_LEN; j++)
        {
            grid[i][j] = puzzle_info[SUDOKU_MAX_LEN * i + j];
        }
    }

    return grid;
}

void save_mutable_idx(int (*grid)[SUDOKU_MAX_LEN], int *idx, int n)
{
    int i, j;
    for (i = 0; i < SUDOKU_MAX_LEN; i++)
    {
        for (j = 0; j < SUDOKU_MAX_LEN; j++)
        {
            idx[i * SUDOKU_MAX_LEN + j] = (!grid[i][j]) ? 1 : 0; // unsafe write since no bound is checked
        }
    }
}

int check_row(int (*row)[SUDOKU_MAX_LEN])
{
    /*Check if the given row contains no matching numbers*/
    return 0;
}

int check_col(int (*col)[SUDOKU_MAX_LEN])
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

int is_solved(int (*grid)[SUDOKU_MAX_LEN])
{
    return 0;
}

int (*attempt_solution(int (*grid)[SUDOKU_MAX_LEN])) [SUDOKU_MAX_LEN]
{
    int i, j;
    for (i = 0; i < SUDOKU_MAX_LEN; i++)
    {
        for (j = 0; j < SUDOKU_MAX_LEN; j++)
        {
            if (!grid[i][j] && grid[i][j] < 9)
            {
                grid[i][j]++;
                check_row(grid);
                check_col(grid);
            }
        }
    }
    return grid;
}

// print the grid in a nice 9x9 format
void print_puzzle(int (*grid)[SUDOKU_MAX_LEN])
{
    int i, j;

    for (i = 0; i < SUDOKU_MAX_LEN; i++)
    {
        for (j = 0; j < SUDOKU_MAX_LEN; j++)
        {
            int val = grid[i][j];
            if (val)
            {
                printf("%d ", val);
            }
            else
            {
                printf("%d ", val);
            }
        }
        putchar('\n');
    }
}