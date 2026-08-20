#include <stdio.h>
int main (){
    int arr[5];;
    for ( int i=0; i<5;i++) {
        scanf("%d", &arr[i]);   
    }
    int max=arr[0];
    for ( int i=0;i<5;i++){
        if ( arr[i]>max) {
            max=arr[i];
        }     
    }
    for ( int i=0;i<5;i++){
        if (arr[i]<=0) {
            arr[i]=max;
        } else if (arr[i]>0) {
            arr[i]=arr[i];
        }
        printf("%d\n");
    }
    return 0;
}