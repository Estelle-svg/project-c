#include <stdio.h>
#include <stdbool.h>
char R; // Right
char L; // left
char U; // up
char D; // down
bool moveCaptain(char grid[5][5],char move){
    int row=0;
    int column=0;
    for(int i=0;i<5;i++){
        for (int j=0;j<5;j++){
            if ( grid[i][j]=='C') {
                row=i;
                column=j;
                break;
            }
        }
    }
    int lastRow=row;
    int lastCol=column;
    if ( move == 'U'){
        lastRow--;
    } else if (move == 'D') {
        lastRow++;
    } else if (move == 'L'){
        lastCol--;
    } else if (move == 'R') {
        lastCol++;
    } else {
        return false;
    }
    if (lastRow < 0 || lastRow >= 5 || lastCol < 0 || lastCol >= 5) {
        return false;
    }
    // check the wall
    if ( grid[lastRow][lastCol] == 'W') {
        return false;
    }
    grid[row][column]='0';
    grid[lastRow][lastCol]='C';
    return true;
}
int main(){
    char grid[5][5] =
        {
            {'0', '0', '0', '0', '0'},
            {'0', 'C', 'W', '0', '0'},
            {'0', '0', 'W', '0', '0'},
            {'0', '0', 'W', '0', '0'},
            {'0', '0', '0', '0', '0'},
        };

    moveCaptain(grid,'U');
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5;j++){
            printf("%c ", grid[i][j]);
        }
        printf("\n");
    }
    return 0;
}
