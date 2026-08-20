#include <stdio.h>
#include <stdbool.h>
#define N 5
#define MAGIC_SUM 65
bool checkUniqueNumber(int grid[N][N]){
    bool check [26] ={false};
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            int num = grid[i][j];
            if(num < 1  || num > 26){
                return false;
            }
            if(check[num]){
                return false;
            }
            check [num] = true;
        }
    }
    return true;
}
bool checkMainDiagonals(int grid[N][N]){
    int LR = 0, RL= 0;
    for(int i = 0; i < N; i++){
        LR += grid[i][i];
        RL += grid [i][4-i];
    }
    if(LR != 65  || RL != 65){
        return false;
    }
    return true;
}
bool checkRow(int grid[N][N]){
    for(int i = 0; i < N ; i++){
        int sumRow = 0;
        for(int j = 0; j < N; j++){
            sumRow += grid[i][j];
        }
        if(sumRow != 65){
            return false;
        }
    }
    return true;
}
bool checkColumn(int grid[N][N]){
    for(int i = 0; i < N ; i++){
        int sumCol = 0;
        for(int j = 0; j < N; j++){
            sumCol += grid[j][i];
        }
        if(sumCol != 65){
            return false;
        }
    }
    return true;
}
bool isMagicSquare(int grid[N][N]) {
    if(!checkUniqueNumber(grid)) return false;
    if(!checkMainDiagonals(grid)) return false;
    if(!checkRow(grid)) return false;
    if(!checkColumn(grid)) return false;

    return true;
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