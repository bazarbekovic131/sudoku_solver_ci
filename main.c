#include <stdio.h>
#include <stdbool.h>

// Function to check if a number can be placed in a given cell
bool is_valid(int solution[9][9], int row, int col, int num) {
    // Check the row
    for (int c = 0; c < 9; c++) {
        if (solution[row][c] == num) {
            return false;
        }
    }

    // Check the column
    for (int r = 0; r < 9; r++) {
        if (solution[r][col] == num) {
            return false;
        }
    }

    // Check the 3x3 sub-grid
    int row_start = 3 * (row / 3);
    int col_start = 3 * (col / 3);
    for (int r = row_start; r < row_start + 3; r++) {
        for (int c = col_start; c < col_start + 3; c++) {
            if (solution[r][c] == num) {
                return false;
            }
        }
    }

    return true;
}

// Function to find an empty cell
bool find_empty(int solution[9][9], int *row, int *col) {
    for (int r = 0; r < 9; r++) {
        for (int c = 0; c < 9; c++) {
            if (solution[r][c] == 0) {
                *row = r;
                *col = c;
                return true;
            }
        }
    }
    return false;
}

// Backtracking solver
bool solve_sudoku(int solution[9][9]) {
    int row, col;
    if (!find_empty(solution, &row, &col)) {
        return true;  // Solution found
    }

    for (int num = 1; num <= 9; num++) {
        if (is_valid(solution, row, col, num)) {
            solution[row][col] = num;
            if (solve_sudoku(solution)) {
                return true;
            }
            solution[row][col] = 0;  // Reset cell
        }
    }

    return false;  // No valid number found, backtrack
}

// Function to print the solution in a grid format
void print_solution(int solution[9][9]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            printf("%d ", solution[i][j]);
            if ((j + 1) % 3 == 0 && j != 8) {
                printf("| ");
            }
        }
        printf("\n");
        if ((i + 1) % 3 == 0 && i != 8) {
            printf("------+-------+------\n");
        }
    }
}

// void inputSudoku() {

// }

int main() {
    // Initial Sudoku grid
    int initial_solution[9][9] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    // Solve the Sudoku puzzle
    if (solve_sudoku(initial_solution)) {
        printf("Sudoku solution found:\n");
        print_solution(initial_solution);
    } else {
        printf("No solution exists for the given Sudoku puzzle.\n");
    }

    return 0;
}
