#include <stdio.h>
#include <stdbool.h> 
int main () 
{
int year;
printf("Enter a year: ");
scanf("%d", &year);
 
bool isLeap = (( year % 4 == 0 && year % 100 !=0) || year % 400 ==0);		

(isLeap)
? printf("%d is a leap year.\n", year)
: printf("%d is a not leap year.\n", year);
 return 0;
}