#include <stdio.h>
#include <string.h>

#define SIZE 9 

// Converts a string of 81 digits into a 9x9 integer grid
void stringToGrid(const char *input, int grid[SIZE][SIZE]) {
    int length = strlen(input);

    if (length != SIZE * SIZE) {
        printf("Error: The input must have exactly 81 digits (got %d).\n", length);
        return;
    }

    int index = 0;
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            grid[row][col] = input[index] - '0';
            index++;
        }
    }
}

// Display the grid
void printGrid(int grid[SIZE][SIZE]) {
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            printf("%d ", grid[row][col]);
        }
        printf("\n");
    }
}

int check_if_num_is_taken(int grid[SIZE][SIZE], int num, int row, int column) {
    // Row and column check
    for (int i = 0; i < SIZE; i++) {
        if (grid[row][i] == num || grid[i][column] == num)
            return 0;
    }

    // 3x3 box check
    int boxRow = row - row % 3;
    int boxCol = column - column % 3;
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            if (grid[boxRow + r][boxCol + c] == num)
                return 0;
        }
    }

    return 1;
}

int solveSudoku(int sudoku[SIZE][SIZE]){
    for (int row = 0; row < SIZE; row++) {
        for (int column = 0; column < SIZE; column++) {
            if (sudoku[row][column] == 0 ) {

                for (int i = 1; i <= 9; i++) {
                    if (check_if_num_is_taken(sudoku, i, row, column)) {
                        sudoku[row][column] = i;

                        // Recurse — if success, done
                        if (solveSudoku(sudoku))
                            return 1;

                        // If not successful, undo and try next number
                        sudoku[row][column] = 0;
                    }
                }

                // No valid number found — trigger backtracking
                return 0;
            }
        }
    }
    // If no empty cell found, puzzle is solved
    return 1;
}

int main() {
    const char *puzzle = "004300209005009001070060043006002087190007400050083000600000105003508690042910300";
    int sudoku[SIZE][SIZE];

    stringToGrid(puzzle, sudoku);

    printf("Here's your Sudoku grid:\n");
    printGrid(sudoku);

    if (solveSudoku(sudoku)) {
        printf("\nSolved Sudoku:\n");
        printGrid(sudoku);
    } else {
        printf("No solution exists.\n");
    }

    return 0;
}
