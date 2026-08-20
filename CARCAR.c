#include <stdio.h>
#include <stdlib.h>

// Dimensions for the 2D Game Board Matrix
#define HEIGHT 12
#define WIDTH 11

// 1. STRUCTURES
typedef struct {
    int x;
    int y;
    char sprite[4]; // Array / String placeholder inside a struct
} Car;

typedef struct {
    int x;
    int y;
    char symbol;
} Obstacle;

// Global Variables
char screenBuffer[HEIGHT][WIDTH]; // 2D ARRAY: The game grid
int score = 0;
int gameRunning = 1;

// --- 2. RECURSIVE FUNCTION ---
// Calculates score multipliers/bonus using basic recursion
int calculateBonus(int currentScore) {
    if (currentScore <= 0) {
        return 0; // Base case
    }
    // Recursive case: Adds 10 bonus points for every 3 points scored
    return (currentScore % 3 == 0 ? 10 : 0) + calculateBonus(currentScore - 1);
}

// --- 3. CUSTOM STRCPY FUNCTION (To avoid string.h) ---
// Uses POINTERS to copy a string
void customStringCopy(char *dest, char *src) {
    while (*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
}

// --- 4. CORE GAME FUNCTIONS ---

// Initializes structures using POINTERS
void initGame(Car *player, Obstacle *obs) {
    player->x = WIDTH / 2;
    player->y = HEIGHT - 2;
    
    // STRING usage via our custom pointer function
    customStringCopy(player->sprite, "X"); 

    // Hardcoded initial obstacle path (predictable loop without time.h seeds)
    obs->x = 4;
    obs->y = 0;
    obs->symbol = '*';
}

// Clears and populates the 2D Matrix Array
void updateBuffer(Car *player, Obstacle *obs) {
    // LOOP: Nested loops traversing the 2D array matrix
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            // Draw track side boundaries
            if (j == 0 || j == WIDTH - 1) {
                screenBuffer[i][j] = '|';
            } else {
                screenBuffer[i][j] = ' '; // Empty road space
            }
        }
    }

    // Insert Obstacle into the 2D array
    if (obs->y >= 0 && obs->y < HEIGHT && obs->x >= 0 && obs->x < WIDTH) {
        screenBuffer[obs->y][obs->x] = obs->symbol;
    }

    // Insert Player Car into the 2D array
    if (player->y >= 0 && player->y < HEIGHT) {
        screenBuffer[player->y][player->x] = player->sprite[0]; 
        
        // Give the car wings/width inside the grid
        if (player->x - 1 > 0) screenBuffer[player->y][player->x - 1] = '-';
        if (player->x + 1 < WIDTH - 1) screenBuffer[player->y][player->x + 1] = '-';
    }
}

// Displays the 2D array by clearing screen using standard spacing loops
void render() {
    // Standard trick to push older frames out of sight cleanly
    for (int k = 0; k < 10; k++) {
        putchar('\n');
    }

    printf("=== TEXT ROADWAY ===\n");

    // POINTER TO AN ARRAY: Accessing 2D rows using pointer arithmetic
    for (int i = 0; i < HEIGHT; i++) {
        char *rowPtr = screenBuffer[i]; 
        for (int j = 0; j < WIDTH; j++) {
            putchar(*(rowPtr + j)); // Pointer notation instead of screenBuffer[i][j]
        }
        putchar('\n');
    }

    // Print HUD Metrics
    printf("Score: %d\n", score);
    printf("Bonus (Recursion): %d\n", calculateBonus(score));
    printf("Enter Move [a = Left, d = Right, s = Straight, q = Quit] then press ENTER: ");
}

void processInput(Car *player) {
    char inputChar;
    
    // Read the character entered by user
    scanf(" %c", &inputChar); 

    if (inputChar == 'a' || inputChar == 'A') {
        if (player->x > 2) player->x--;
    } else if (inputChar == 'd' || inputChar == 'D') {
        if (player->x < WIDTH - 3) player->x++;
    } else if (inputChar == 'q' || inputChar == 'Q') {
        gameRunning = 0;
    }
    // 's' does nothing, car just drives straight safely!
}

void updatePhysics(Car *player, Obstacle *obs) {
    // Advance obstacle downwards
    obs->y++;

    // Reset obstacle if it hits bottom edge safely
    if (obs->y >= HEIGHT) {
        obs->y = 0;
        // Pseudo-random movement algorithm based on current score
        obs->x = 2 + ((score * 3) % (WIDTH - 5)); 
        score++;
    }

    // Bounding box collision detection
    if (obs->y == player->y) {
        if (obs->x == player->x || obs->x == player->x - 1 || obs->x == player->x + 1) {
            gameRunning = 0; // Trigger collision crash
        }
    }
}

// --- 5. MAIN EXECUTIVE CONTROL ---
int main() {
    Car player;
    Obstacle obstacle;

    // Pass structures via addresses (Pointers)
    initGame(&player, &obstacle);

    // Main Game Loop
    while (gameRunning) {
        updateBuffer(&player, &obstacle);
        render();
        processInput(&player); // This pauses the game naturally until you type
        updatePhysics(&player, &obstacle);
    }

    // Game Over display segment
    printf("\n\n===========================\n");
    printf("   CRASHED! GAME OVER.\n");
    printf("===========================\n");
    printf("Final Score: %d\n", score);
    printf("Execution Complete.\n\n");

    return 0;
}