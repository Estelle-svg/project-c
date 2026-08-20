#include <stdbool.h>
#include <stdio.h>

#define GAME_SIZE 5 // Game row and columns
#define WIN_COUNT 5 // Game row and columns

#define PLAYER_1_SYMBOL 'X'
#define PLAYER_2_SYMBOL 'O'

#define PLAYER_1_WON 1
#define PLAYER_2_WON 2
#define DRAW_GAME 3

// -------------------------------------------------------------------
// GLOBAL VARIABLES
// -------------------------------------------------------------------
char board[5][5] = {
    {'.', '.', '.', '.', '.'},  // Row 1
    {'O', 'O', '.', '.', '.'},  // Row 2
    {'X', 'X', 'X', 'X', '.'},  // Row 3 ← Winning row
    {'.', '.', 'O', '.', '.'},  // Row 4
    {'.', '.', '.', '.', '.'}   // Row 5
    }; 
// YOUR FUNCTION
void showBoard( char grid[GAME_SIZE][GAME_SIZE] ) {
    printf("Board is being display\n");
    for ( int i=0; i<GAME_SIZE ;i++){
        for ( int j=0;j<GAME_SIZE;j++){
            printf("'.'");
        }printf("\n");
    }
}
bool isValidMove (char grid[GAME_SIZE][GAME_SIZE]){
    int check;
    if(check < GAME_SIZE || check == PLAYER_1_SYMBOL){
        return false;
    }
    if(check < GAME_SIZE || check ==PLAYER_2_SYMBOL) {
        return false;
    }
    if ( check) {
        
    }

}

// MAIN
int main() { 
    int rows;
    int cols;
    
    printf("%d", checkGame());   // Check player 1 won
    return 0;
}
