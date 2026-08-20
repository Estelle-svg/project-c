#include <stdio.h>
#include <stdbool.h> // Needed to use bool, true, and false!

int main() {
    int score[5];
    bool passedTerm = true; // We assume they passed the term to start

    // --- PART 1: Getting the Input --
    for (int i = 0; i < 5; i++) {
        scanf("%d", &score[i]);
    }
    // --- PART 2: The Checking Algorithm ---
    for (int i = 0; i < 5; i++) {
        // If we find an exam score lower than 50...
        if (score[i] < 50) {
            passedTerm = false; // They failed the term!
            break; // Stop checking. One fail means the whole term is failed.
        }
    }

    // --- PART 3: The Output ---
    if (passedTerm == true) {
        printf("passed\n");
    } else {
        printf("failed\n");
    }
    return 0;
}