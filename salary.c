#include <stdio.h>

int main() 
{
    float salary,bonusrate, finalSalary;

    // Ask for user input
    printf("Enter employee's salary: ");
    scanf("%f", &salary);

    if (salary < 1000) {
        bonusrate = 10;   // Apply 10% bonus
    } else {
        bonusrate = 5;    // Apply 5% bonus
    }

    finalSalary = salary + (salary * (bonusrate / 100.0));

    printf("Final salary after applying %.2f", finalSalary);

    return 0;
}