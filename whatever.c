#include <stdio.h>
int main ()
{
   int secret_number = 5;
   int attempts= 3;
   int user_input;
   
    while ( attempts > 0) {
        printf("Guess the number: ");
        scanf("%d", &user_input);
        if (user_input != secret_number) { 
            attempts=attempts-1;
            if (user_input < secret_number) {
                printf("Too low ! %d tries left\n", attempts);
            } else if (user_input > secret_number) {
                printf("Too high! %d tries left\n", attempts);
            }
        } else {
            printf("You win!");
            break;
        }
    }
    
    if ( attempts == 0){
        printf("You lost!");
    }
    return 0;
}