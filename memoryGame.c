#include <stdio.h>
int max(int array[], int size){
    if (size == 1 ){
        return array[0];
    }
    int FindMax= max(array, size-1);
    if ((array[size-1] > FindMax)){
        return array[size-1];
    } else {
        return FindMax;
    }
}
int main(){
    int size;
    scanf("%d", &size);
    int array[size];
    for ( int i=0; i<size;i++){
        scanf("%d", &array[i]);
    }
    int result=max(array,size);
    printf("The maximums number is: %d", result);
    return 0;;
}