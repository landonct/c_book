// Compute the solution to an arbitrary soduku

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define SUDOKU_MAX_LEN 9
#define BOX_SIZE 3
#define PUZZLE_MAX_LINE 81
#define HASH_MAX_LEN 12

int is_solved(int (*)[SUDOKU_MAX_LEN]);
void attempt_solution(int (*)[SUDOKU_MAX_LEN], int **, const int, int *);
int read_puzzle(int (*)[SUDOKU_MAX_LEN]);
void print_puzzle(int (*)[SUDOKU_MAX_LEN]);
void save_mutable_idx(int (*)[SUDOKU_MAX_LEN], int **, int);
int check_puzzle(int (*)[SUDOKU_MAX_LEN]);
int check_row(int (*)[SUDOKU_MAX_LEN]);

int main() {
  int mutable_slots = 0;
  int (*grid)[SUDOKU_MAX_LEN];
  int mutable_cell_num = 0;

  // Set up the grid in an 9 x 9 array
  grid = (int (*)[SUDOKU_MAX_LEN])malloc(sizeof(int) * SUDOKU_MAX_LEN *
                                         SUDOKU_MAX_LEN);
  if (grid == NULL) {
    fprintf(stderr, "Memory NOT allocated, stopping\n");
    exit(EXIT_FAILURE);
  }
  mutable_slots = read_puzzle(grid);
  printf("There are %d mutable slots\n", mutable_slots);
  int *mutable_idx[mutable_slots]; // variable length as determined at runtime
                                   // by the puzzle
  save_mutable_idx(grid, mutable_idx, mutable_slots);

  print_puzzle(grid);
  putchar('\n');

  int iterations = 0;
  while (!is_solved(grid)) {
    attempt_solution(grid, mutable_idx, mutable_slots, &mutable_cell_num);
    // print_puzzle(grid);
    iterations++;
  }

  print_puzzle(grid);
  printf("The puzzle was solved in %d iterations\n", iterations);

  free(grid);

  return 0;
}

int read_puzzle(int (*grid)[SUDOKU_MAX_LEN]) {
  printf("Reading puzzle...\n");
  int i = 0, j;
  int c, mutable_slots = 0;
  int hash_code[HASH_MAX_LEN],
      puzzle_info[PUZZLE_MAX_LINE]; // hash_code will be used to check against
                                    // which puzzles i have already solved in
                                    // another file
  while ((c = getchar()) != ' ' && c != EOF) {
    if (i >= HASH_MAX_LEN) {
      while ((c = getchar()) != ' ')
        ;
      break;
    }
    hash_code[i] = c - '0';
    i++;
  }

  i = 0;
  while ((c = getchar()) != ' ' && c != EOF) {
    if (i >= PUZZLE_MAX_LINE) {
      while ((c = getchar()) != ' ')
        ;
      break;
    }
    puzzle_info[i] = c - '0';
    i++;
  }

  while ((c = getchar()) != '\n' && c != EOF)
    ;

  for (i = 0; i < SUDOKU_MAX_LEN; i++) {
    for (j = 0; j < SUDOKU_MAX_LEN; j++) {
      if (!puzzle_info[SUDOKU_MAX_LEN * i + j]) {
        mutable_slots++;
      }
      grid[i][j] = puzzle_info[SUDOKU_MAX_LEN * i + j];
    }
  }

  return mutable_slots;
}

void save_mutable_idx(int (*grid)[SUDOKU_MAX_LEN], int **idx, int n) {
  int i, j, k = 0;
  for (i = 0; i < SUDOKU_MAX_LEN; i++) {
    for (j = 0; j < SUDOKU_MAX_LEN; j++) {
      if (k >= n) {
        printf("k: %d, n: %d\n", k, n);
        fprintf(stderr,
                "Number of empty slots is larger than the allocated size\n");
        free(grid);
        exit(EXIT_FAILURE);
      }

      if (!grid[i][j]) {
        idx[k] = &grid[i][j];
        k++;
      }
    }
  }
}

int check_row(int (*grid)[SUDOKU_MAX_LEN]) {
  /*Check if the given row contains no matching numbers*/
  int i, j, *row;
  for (i = 0; i < SUDOKU_MAX_LEN; i++) {
    int seen_numbers[SUDOKU_MAX_LEN] = {0};
    row = grid[i];
    for (j = 0; j < SUDOKU_MAX_LEN; j++) {
      if (!row[j]) {
        continue;
      }

      if (seen_numbers[row[j] - 1]) {
        return 0;
      } else {
        seen_numbers[row[j] - 1] = 1;
      }
    }
  }

  return 1;
}

int check_col(int (*grid)[SUDOKU_MAX_LEN]) {
  /*Check if the given column contains no matching numbers*/
  int i, j;
  for (i = 0; i < SUDOKU_MAX_LEN; i++) {
    int seen_numbers[SUDOKU_MAX_LEN] = {0};
    for (j = 0; j < SUDOKU_MAX_LEN; j++) {
      if (!grid[j][i]) {
        continue;
      }
      if (seen_numbers[grid[j][i] - 1]) {
        return 0;
      }
      seen_numbers[grid[j][i] - 1] = 1;
    }
  }

  return 1;
}

int check_box(int (*grid)[SUDOKU_MAX_LEN]) {
  /*Check if the given 3x3 block contains no natching numbers
  The box will start at N % 3 == 0 for rows and cols, so only iterate over N / 3
  different slots*/
  int i, j, k, l, top_left_of_box = 0;
  for (i = 0; i < SUDOKU_MAX_LEN; i++) {
    for (j = 0; j < SUDOKU_MAX_LEN; j++) {
      top_left_of_box = (!(i % (int)BOX_SIZE) && !(j % (int)BOX_SIZE));

      if (top_left_of_box) {
        int seen_numbers[SUDOKU_MAX_LEN] = {0};
        for (k = i; k < i + (int)BOX_SIZE && k < SUDOKU_MAX_LEN; k++) {
          for (l = j; l < j + (int)BOX_SIZE && l < SUDOKU_MAX_LEN; l++) {
            if (!grid[k][l]) {
              continue;
            }
            if (seen_numbers[grid[k][l] - 1]) {
              return 0;
            }
            seen_numbers[grid[k][l] - 1] = 1;
          }
        }
      }
    }
  }

  return 1;
}

int check_puzzle(int (*grid)[SUDOKU_MAX_LEN]) {
  return check_row(grid) && check_col(grid) && check_box(grid);
}

int is_solved(int (*grid)[SUDOKU_MAX_LEN]) {
  int i, j;
  for (i = 0; i < SUDOKU_MAX_LEN; i++) {
    for (j = 0; j < SUDOKU_MAX_LEN; j++) {
      if (!grid[i][j])
        return 0;
    }
  }

  return check_puzzle(grid);
}

void attempt_solution(int (*grid)[SUDOKU_MAX_LEN], int **mutable_idx,
                      const int size, int *mutable_cell_num) {
  int valid_placement_found = 0;
  while (*mutable_idx[*mutable_cell_num] < 9) {
    (*mutable_idx[*mutable_cell_num])++;
    if (check_puzzle(grid)) {
      valid_placement_found = 1;
      (*mutable_cell_num)++;
      break;
    }
  }
  if (!valid_placement_found) {
    *mutable_idx[*mutable_cell_num] = 0;
    (*mutable_cell_num)--;
  }
  if (*mutable_cell_num < 0) {
    fprintf(stderr,
            "You will access out of bounds memory via mutable_cell_num, "
            "stopping\n");
    free(grid);
    exit(EXIT_FAILURE);
  }
}

// print the grid in a nice 9x9 format
void print_puzzle(int (*grid)[SUDOKU_MAX_LEN]) {
  int i, j;

  for (i = 0; i < SUDOKU_MAX_LEN; i++) {
    for (j = 0; j < SUDOKU_MAX_LEN; j++) {
      int val = grid[i][j];
      printf("%d ", val);
    }
    putchar('\n');
  }
}