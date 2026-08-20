#include <stdio.h>
int main () 
{
    //input i for rows and j for columns
    int rows;
    int columns; 
    printf("Enter the number of rows: ");
    scanf("%d", &rows);
    printf("Enter the number of columns: ");
    scanf("%d", &columns);

    int i;
    int j;
    for ( i=0; i < rows;i++) {
        for ( j=0; j<columns; j++) {
                printf("*");
        }
        printf("\n");
    }
    return 0;
}