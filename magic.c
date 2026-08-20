#include <stdio.h>
#include <stdbool.h>
#define N 5
#define MAGIC_SUM 65
bool CheckUnique(int grid[N][N]) {    
    for (int i = 0; i < N; i++) {
        int rowSum = 0;
        int colSum = 0;
        for (int j = 0; j < N; j++) {
            rowSum += grid[i][j]; // Summing row i
            colSum += grid[j][i]; // Summing column i
        }
        if (rowSum != MAGIC_SUM || colSum != MAGIC_SUM) return false;
    }
    return true;
}
bool checkMainDiagonals(int grid[N][N]) {
    int LR = 0; // left to right
    int RL = 0; // right to left
    for (int i = 0; i < N; i++) {
        LR += grid[i][i];
        RL += grid[i][4- i];
    }
    return (LR == MAGIC_SUM && RL == MAGIC_SUM);
}

bool isMagicSquare(int size, int grid[N][N]) {
    return true;		// YOUR JOB IS HERE !
}
int main() {
    int square[N][N] = {
        {17, 24, 1, 8, 15},
        {23, 5, 7, 14, 16},
        {4, 6, 13, 20, 22},
        {10, 12, 19, 21, 3},
        {11, 18, 25, 2, 9}
    };

    if (isMagicSquare(square)) {
        printf("Valid magic square!\n");
    } else {
        printf("Not a valid magic square.\n");
    }
    return 0;
}
