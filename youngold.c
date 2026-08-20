#include <stdio.h>
int main()
{
    int year1, month1, day1;
    int year2, month2, day2;

    printf("Enter the first person's date of birth: ");
    scanf("%d %d %d", &year1, &month1, &day1);

    printf("Enter the second person's date of birth: ");
    scanf("%d %d %d", &year2, &month2, &day2);

    if( year1 > year2) {
        printf("the first one is the youngest.\n");
    } else if ( year1 < year2) {
        printf("The second one is the youngest.\n");
        } else {
        // compare month
        if ( month1 > month2) {
            printf("the first one is the youngest.\n");
        } else if ( month1 < month2) {
            printf("The second one is the youngest.\n");
        } else {
            // compare day
            if ( day1 > day2) {
                printf("the first one is the youngest.\n");
            } else if ( day1 < day2) {
                printf("The second one is the youngest.\n");
            } else {
                // if days are equal too, they are the same age.
                printf("Both people arae the same age.\n");
            }
        }
    }
return 0;
}