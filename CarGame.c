#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

// Define screen dimensions
#define SCREEN_WIDTH 15
#define SCREEN_HEIGHT 20

// Game variables
int carPos;
int enemyX, enemyY;
int score;
int gameOver;

// Setup the initial state of the game
void Setup() {
    gameOver = 0;
    score = 0;
    carPos = SCREEN_WIDTH / 2; // Start player in the middle
    
    srand(time(NULL)); // Seed random number generator
    enemyY = 0;
    enemyX = 1 + rand() % (SCREEN_WIDTH - 2); // Random X position inside borders
}

// Render the game screen in the console
void Draw() {
    system("cls"); // Clear the console screen
    
    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        for (int j = 0; j < SCREEN_WIDTH; j++) {
            // Draw left and right borders
            if (j == 0 || j == SCREEN_WIDTH - 1) {
                printf("|");
            } 
            // Draw Player Car
            else if (i == SCREEN_HEIGHT - 2 && j == carPos) {
                printf("A");
            } 
            // Draw Enemy Car
            else if (i == enemyY && j == enemyX) {
                printf("X");
            } 
            // Draw empty track space
            else {
                printf(" ");
            }
        }
        printf("\n");
    }
    
    // Display UI
    printf("====================\n");
    printf(" SCORE: %d\n", score);
    printf("====================\n");
    printf("Controls: [A] Left  [D] Right  [Q] Quit\n");
}

// Handle non-blocking user input
void Input() {
    if (kbhit()) { // Check if a key has been pressed
        switch (getch()) {
            case 'a':
            case 'A':
                if (carPos > 1) carPos--; // Move left if inside border
                break;
            case 'd':
            case 'D':
                if (carPos < SCREEN_WIDTH - 2) carPos++; // Move right if inside border
                break;
            case 'q':
            case 'Q':
                gameOver = 1;
                break;
        }
    }
}

// Update game physics and logic
void Logic() {
    enemyY++; // Move enemy down the screen

    // If enemy reaches the bottom, reset it to the top and increase score
    if (enemyY >= SCREEN_HEIGHT) {
        enemyY = 0;
        enemyX = 1 + rand() % (SCREEN_WIDTH - 2);
        score += 10;
    }

    // Collision Detection
    // Checks if the enemy coordinates match the player's car coordinates
    if (enemyY == SCREEN_HEIGHT - 2 && enemyX == carPos) {
        gameOver = 1;
    }
}

int main() {
    Setup();
    
    // Main Game Loop
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        Sleep(100); // Slows down the loop (100 milliseconds) to make it playable
    }
    
    // Game Over Screen
    system("cls");
    printf("\n\n\n");
    printf("   ###########################\n");
    printf("   #        GAME OVER        #\n");
    printf("   ###########################\n\n");
    printf("   Your Final Score: %d XP\n\n", score);
    printf("   Thanks for playing!\n\n");
    
    return 0;
}