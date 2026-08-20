#include <stdio.h>
int countDigits(int number){
    if(number == 0){
        return 0;
    }
    return 1+countDigits(number/10);
}
int main (){
    int number;
    scanf("%d", &number);
    int digit= countDigits(number);
    printf("%d", digit);
    return 0;
}