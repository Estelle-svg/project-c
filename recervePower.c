#include <stdio.h>
int power(int a, int b){
    if(b==0){
        return 1;
    }
    return a*power(a,b-1);
}
int main(){
    int pow= power(2,9);
    printf("%d", pow);
    return 0;
}