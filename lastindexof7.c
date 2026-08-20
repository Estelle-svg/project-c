#include <stdio.h>
int main() {
    int arr[5];
    int store;
    for(int i=4; i>=0; i--){
        printf(" Enter the number:");
        scanf("%d",&arr[i]);
    }
    for(int i=4;i>=0; i-- ){
        if(arr[i]==7){
           store =i;
           break;
        }else {
            store=-1;
        }
    }
     printf("%d  ", store);
   return 0;
}