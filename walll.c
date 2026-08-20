#include <stdio.h>
#include <stdbool.h>

#define SIZE 4

bool canMove(int row, int col, char grid[SIZE][SIZE + 1]) {
    if (row < 0 row >= SIZE col < 0 || col >= SIZE ) {
        return false;
    // check wall
    if (grid[row][col] == 'W') {
        return false;
    }
    return true;
    }
}
int main() {

    char grid[SIZE][SIZE + 1];
    char moves[100];

    int row = 0;
    int col = 0;
 // input grid
    printf("Enter 4 rows of the grid:\n");

    for (int i = 0; i < SIZE; i++) {
        scanf("%s", grid[i]);
    }

    // input moves
    printf("Enter moves (R,L,U,D): ");
    scanf("%s", moves);

    bool failed = false;

    // process moves
    for (int i = 0; moves[i] != '\0'; i++) {

    int newRow = row;
    int newCol = col;

    if (moves[i] == 'R') {
        newCol++;
    } else if (moves[i] == 'L') {
        newCol--;
    } else if (moves[i] == 'U') {
        newRow--;
    } else if (moves[i] == 'D') {
        newRow++;
    }

    if (canMove(newRow, newCol, grid)) {
            row = newRow;
            col = newCol;
    } else {
        failed = true;
        break;
    }
}

    // result  
    if (failed) {
        printf("Mission FAILED. Final position: (%d, %d)\n", row, col);
    } else {
         printf("Mission COMPLETED. Final position: (%d, %d)\n", row, col);
    }
    return 0;
}