#include<stdio.h>
#include<stdbool.h>
#define PLAYER_1_SYMBOl 'X'
#define PLAYER_2_SYMBOL 'O'
#define GRID_SIZE 5
#define PLAYER_1_WON 1
#define PLAYER_2_WON 2
#define UNDEFINED_WINNER 0
char board[GRID_SIZE][GRID_SIZE];

void initializeBoard()
{
    for (int row = 0; row < GRID_SIZE; row++)
        for (int col = 0; col < GRID_SIZE; col++)
            board[row][col] = '.';
}

void printBoard()
{
    for (int row = 0; row < GRID_SIZE; row++)
    {
        for (int col = 0; col < GRID_SIZE; col++)
            printf("%c ", board[row][col]);  
        printf("\n");
    }
}

bool canMove(char board[GRID_SIZE][GRID_SIZE],int row,int col){
  if(row<0 || row>=GRID_SIZE || col<0 || col>=GRID_SIZE){
      return 0;
  }
  //check if the cell is already taken//
  if(board[row][col]==PLAYER_1_SYMBOl || board[row][col]==PLAYER_2_SYMBOL){
      return 0;
  }
  return 1;
}

void move(char board[GRID_SIZE][GRID_SIZE],int row,int col,bool player1){
    if(canMove(board,row,col)){
        if(player1==true){
            board[row][col] = PLAYER_1_SYMBOl;
        }
        else{
            board[row][col] = PLAYER_2_SYMBOL;
        }
    }
}

int checkrow(int row){
    int player1Point = 0;
    int player2Point = 0;
    for (int col = 0; col < GRID_SIZE;col++){
        if(board[row][col]==PLAYER_1_SYMBOl){
            player1Point++;
        }
        else if(board[row][col]==PLAYER_2_SYMBOL){
            player2Point++;
        }
       
    }
    if (player1Point == 5)
    {
        return PLAYER_1_WON;
    }
    else if (player2Point == 5)
    {
        return PLAYER_2_WON;
    }
    else
    {
        return UNDEFINED_WINNER;
    }
}

int checkcol(int col){
    int player1Point = 0;
    int player2Point = 0;
    for (int row = 0; row < GRID_SIZE;row++){
        if(board[row][col]==PLAYER_1_SYMBOl){
            player1Point++;
        }
        else if(board[row][col]==PLAYER_2_SYMBOL){
            player2Point++;
        }

    }
    if(player1Point==5){
        return PLAYER_1_WON;
    }
    else if(player2Point==5){
        return PLAYER_2_WON;
    }
    else {
        return UNDEFINED_WINNER;
    }
}

int checkDiagonal(){
    int player1Point = 0;
    int player2point = 0;
    for (int i = 0; i < 5;i++){
        if(board[i][i]==PLAYER_1_SYMBOl){
            player1Point++;
        }
        else if(board[i][i]==PLAYER_2_SYMBOL){
            player2point++;
        }
        
    }
    if(player1Point==5){
        return PLAYER_1_WON;
    }
    if(player2point==5){
        return PLAYER_2_WON;
    }
    else {
        return UNDEFINED_WINNER;
    }
}

int checkSecondDiagonal(){
    int player1Point = 0;
    int player2point = 0;
    for (int i = 0; i < GRID_SIZE;i++){
        if(board[GRID_SIZE-i-1][i]==PLAYER_1_SYMBOl){
            player1Point++;
        }
        else if(board[GRID_SIZE-i-1][i]==PLAYER_2_SYMBOL){
            player2point++;
        }
    }
    if(player1Point==5){
        return PLAYER_1_WON;
    }
    else if(player2point==5){
        return PLAYER_2_WON;
    }
    else{
        return UNDEFINED_WINNER;
    }
}
int checkGameStatus(){
    for (int row = 0; row < GRID_SIZE;row++){
        if(checkrow(row)==PLAYER_1_WON){
            return PLAYER_1_WON;
        }
        else if(checkrow(row)==PLAYER_2_WON){
            return PLAYER_2_WON;
        }
    }
    for (int col = 0; col < GRID_SIZE; col++)
    {
        if (checkcol(col) == PLAYER_1_WON)
        {
            return PLAYER_1_WON;
        }
        else if (checkcol(col) == PLAYER_2_WON)
        {
            return PLAYER_2_WON;
        }
    }
    if(checkDiagonal()==PLAYER_1_WON){
        return PLAYER_1_WON;
    }
    if(checkSecondDiagonal()==PLAYER_2_WON){
        return PLAYER_2_WON;
    }
    return UNDEFINED_WINNER;
}
bool checkfullboard(char board[GRID_SIZE][GRID_SIZE]){
    for (int row = 0; row < GRID_SIZE;row++){
        for (int col = 0; col < GRID_SIZE;col++){
            if(board[row][col]=='.'){
                return 0;
            }
        }
    }
    return 1;
}



int main(){
    initializeBoard();
    bool foundWinner = false;
    printBoard();
    int row;
    int col;
    bool player1Turn = true;

    while(foundWinner==false){
     
       
        //step 1 allow user to enter their row or col//
        if(player1Turn==true){
            printf("It's player 1 turn:\n please enter your row(0-4): \n");
            scanf("%d", &row);
            printf("please enter your column: ");
            scanf("%d", &col);
           
        }
        else{
            printf("It's player 2 turn:\n please enter your row(0-4): \n");
            scanf("%d", &row);
            printf("please enter your column: ");
            scanf("%d", &col);
        }
        
	//step 2 check whether user can move or not //
        if (canMove(board, row, col) == true)
        {
            move(board, row, col,player1Turn);
        }
        else if(canMove(board,row,col)==false){
            printf("Invalid choice please Enter again\n");
        }
        printBoard();

        //step 3 check if there is a winner//
       
        if(checkGameStatus()==PLAYER_1_WON){
            printf("Player 1 Won");
            foundWinner = true;
            break;
        }
        else if(checkGameStatus()==PLAYER_2_WON){
            printf("Player 2 Won");
            foundWinner = true;
            break;
        }

        //step 4// check whether the board is full
        if(checkfullboard(board)==true){
            printf("No winner!");
            foundWinner = true;
            break;
        }

        //step 5 switch the player
        if(player1Turn==true){
            player1Turn = false;
        }
        else{
            player1Turn = true;
        }
    }
    return 0;
}