#include <stdio.h>

int main() {
    // 1. Setup our arrays
    float temps[7];
    char *days[7] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

    // 2. Setup our tracking variables
    float maxTemp, minTemp, sum = 0.0, average;
    int maxIndex = 0, minIndex = 0, hotDaysCount = 0;

    // --- PART 1: Getting the Input ---
    printf("Enter the daily temperatures (in Celsius):\n");
    for (int i = 0; i < 7; i++) {
        printf("%s: ", days[i]);
        scanf("%f", &temps[i]);
    }

    // Assume Monday (Index 0) is both the highest and lowest to start!
    maxTemp = temps[0];
    minTemp = temps[0];

    // --- PART 2: The "Super Loop" Analysis ---
    for (int i = 0; i < 7; i++) {
        
        // A. Check for a new Maximum
        if (temps[i] > maxTemp) {
            maxTemp = temps[i];
            maxIndex = i;
        }
        
        // B. Check for a new Minimum
        if (temps[i] < minTemp) {
            minTemp = temps[i];
            minIndex = i;
        }
        
        // C. Add to our total Sum
        sum = sum + temps[i];
        
        // D. Count if it is a hot day
        if (temps[i] > 30.0) {
            hotDaysCount++;
        }
    }

    // --- PART 3: Calculate Average ---
    // We divide by 7.0 (a float) to make sure we don't trigger the Integer Division trap!
    average = sum / 7.0; 

    // --- PART 4: Output the Report ---
    printf("\n--- WEEKLY WEATHER REPORT ---\n");
    // Notice the %.1f - this tells C to only print 1 decimal place so it looks clean!
    printf("Maximum Temp: %.1f C on %s\n", maxTemp, days[maxIndex]);
    printf("Minimum Temp: %.1f C on %s\n", minTemp, days[minIndex]);
    printf("Average Temp: %.1f C\n", average);
    printf("Days above 30 C: %d\n", hotDaysCount);

    // --- PART 5: The "Creative" Bonus ---
    printf("\n--- BONUS ANALYSIS ---\n");
    float tempSwing = maxTemp - minTemp;
    printf("Temperature Swing: %.1f C (The difference between the hottest and coldest day!)\n", tempSwing);

    return 0;
}