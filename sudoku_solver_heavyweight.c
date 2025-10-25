#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <omp.h>

#define SIZE 9
#define MAX_LINE 256

// -------------------- Utility functions --------------------

void printGrid(int grid[SIZE][SIZE]) {
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            printf("%d ", grid[row][col]);
        }
        printf("\n");
    }
}


void stringToGrid(const char *input, int grid[SIZE][SIZE]) {
    int length = strlen(input);

    if (length != SIZE * SIZE) {
        printf("Error: The input must have exactly 81 digits (got %d).\n", length);
        return;
    }

    int index = 0;
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            //got to know that to convert string numeral into an int, subtracting ascii of '0' from the ascii of the string numeral, will give the ascii value of the int
            grid[row][col] = input[index] - '0';
            index++;
        }
    }
}

int check_if_num_is_taken(int grid[SIZE][SIZE], int num, int row, int column) {
    // Row and column check
    for (int i = 0; i < SIZE; i++) {
        if (grid[row][i] == num || grid[i][column] == num)
            return 0;
    }

    // 3x3 box check
    // basically, what we are doing here is, deciding which 3x3 box it is in, like 
    /*
    our 9x9 array, with 3x3 blocks looks like this (the indices i mean)
    (0,0) (0,1) (0,2) | (0,3) (0,4) (0,5) | (0,6) (0,7) (0,8)
    (1,0) (1,1) (1,2) | (1,3) (1,4) (1,5) | (1,6) (1,7) (1,8)
    (2,0) (2,1) (2,2) | (2,3) (2,4) (2,5) | (2,6) (2,7) (2,8)
    -------------------+-------------------+-------------------
    (3,0) (3,1) (3,2) | (3,3) (3,4) (3,5) | (3,6) (3,7) (3,8)
    (4,0) (4,1) (4,2) | (4,3) (4,4) (4,5) | (4,6) (4,7) (4,8)
    (5,0) (5,1) (5,2) | (5,3) (5,4) (5,5) | (5,6) (5,7) (5,8)
    -------------------+-------------------+-------------------
    (6,0) (6,1) (6,2) | (6,3) (6,4) (6,5) | (6,6) (6,7) (6,8)
    (7,0) (7,1) (7,2) | (7,3) (7,4) (7,5) | (7,6) (7,7) (7,8)
    (8,0) (8,1) (8,2) | (8,3) (8,4) (8,5) | (8,6) (8,7) (8,8)


    so the boxes start at
    (0,0),(0,3),(0,6)
    (3,0),(3,3),(3,6)
    (6,0),(6,3),(6,6)

    take a a random index, say (4,4)
    row%3, will give me 1
    column % 3 gives 1 as welll
    
    so if i remove this from the row and column,(i.e row - row % 3 and column - column % 3)
    i basically get the index of the first cell in the box.

    now i can loop through the box and chek whether the number already exists

    
    */
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


/*
-----------------solving the sudoku, the logic--------------------------
According to wikepedia
""Briefly, a program would solve a puzzle by placing the digit "1" in the first cell and checking if it is allowed to be there.
If there are no violations (checking row, column, and box constraints) then the algorithm advances to the next cell and places a "1" in that cell.
When checking for violations, if it is discovered that the "1" is not allowed, the value is advanced to "2".
If a cell is discovered where none of the 9 digits is allowed, then the algorithm leaves that cell blank and moves back to the previous cell.
The value in that cell is then incremented by one.
This is repeated until the allowed value in the last (81st) cell is discovered.""

My take on this approach, especially the backtracking part coz, it didnt work with for loop and i had to go for recursion

- Find the empty cell
        If no empty cell (no zeros) is found --> return True
- For each number n from 1 to 9:
    Check if placing n is valid at the current empty cell:
        n is not already present in the same row
        n is not already present in the same colun
        n is not already present in the same 3×3 subgrid
    If valid:
        Place n in the cell (sudoku[row][col] = n)
        Recursively call solveSudoku(sudoku) to solve the rest of the board.
        If the recursive call returns True --> success (return True).
        Otherwise, undo the placement (sudoku[row][col] = 0) and try the next number.
- If no number (1–9) works:
    Return False --> triggers backtracking (previous step will undo its move).

*/





int solveSudoku(int sudoku[SIZE][SIZE]){
    for (int row = 0; row < SIZE; row++) {
        for (int column = 0; column < SIZE; column++) {
            // making sure that im not replacing the clues and only the blank spaces (i.e The Zeros)
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



int compareGrids(int grid[SIZE][SIZE], const char *solution) {
    int k = 0;
    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {
            if (grid[r][c] != solution[k++] - '0')
                return 0;
        }
    }
    return 1;
}




void showProgressBar(int current, int total) {
    int width = 50;
    float progress = (float)current / total;
    int filled = (int)(progress * width);

    printf("\r[");
    for (int i = 0; i < width; i++) {
        if (i < filled) printf("=");
        else printf(" ");
    }
    printf("] %6.2f%% (%d/%d)", progress * 100, current, total);
    fflush(stdout);
}



int main() {
    FILE *file = fopen("sudoku.csv", "r");
    if (!file) {
        perror("Failed to open sudoku.csv");
        return 1;
    }

    char line[MAX_LINE];
    int total = 0;

    // Skip header and count total puzzles
    fgets(line, sizeof(line), file);
    while (fgets(line, sizeof(line), file))
        total++;

    rewind(file);
    fgets(line, sizeof(line), file);  // skip header again

    // Allocate arrays to store all puzzles & solutions
    char **puzzles = malloc(total * sizeof(char *));
    char **solutions = malloc(total * sizeof(char *));
    if (!puzzles || !solutions) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }

    int idx = 0;
    while (fgets(line, sizeof(line), file)) {
        char *puzzle = strtok(line, ",");
        char *solution = strtok(NULL, ",");
        if (!puzzle || !solution) continue;

        // Remove newline if present
        solution[strcspn(solution, "\r\n")] = 0;

        puzzles[idx] = strdup(puzzle);
        solutions[idx] = strdup(solution);
        idx++;
    }
    fclose(file);

    int solvedCorrectly = 0;
    int current = 0;

    printf("Solving %d puzzles using %d threads...\n", total, omp_get_max_threads());


    
    // Parallel loop over puzzles
    #pragma omp parallel for reduction(+:solvedCorrectly) shared(current)
    for (int i = 0; i < total; i++) {
        int grid[SIZE][SIZE];
        stringToGrid(puzzles[i], grid);
        solveSudoku(grid);

        if (compareGrids(grid, solutions[i]))
            solvedCorrectly++;

        // progress bar update (only 1 thread prints)
        #pragma omp critical
        {
            current++;
            if (current % 100 == 0 || current == total)
                showProgressBar(current, total);
        }
    }

    printf("\nFinished solving %d puzzles.\n", total);
    printf("Correctly solved: %d\n", solvedCorrectly);
    printf("Accuracy: %.2f%%\n", 100.0 * solvedCorrectly / total);

    // Free allocated memory
    for (int i = 0; i < total; i++) {
        free(puzzles[i]);
        free(solutions[i]);
    }
    free(puzzles);
    free(solutions);

    return 0;
}
