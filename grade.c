#include<stdio.h>
int main () 
{
    float x; // input x for score
    printf("Enter the score: ");
    scanf("%f", &x);

    if (x >= 90.0f && x <= 100.0f) {
printf("A");
    } else if (x >= 80.0f && x <= 89.0f) {
        printf("B");
        } else if ( x >= 70.0f && x <= 79.0f) {
                    printf("C");
            } else if ( x < 70) {
                printf("F");
    }
return 0;
}