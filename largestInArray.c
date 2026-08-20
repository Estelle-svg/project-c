#include <stdio.h>
int max(int array[], int size ){
    if(size==0){
        return 0;
    }
    return + max(-1);
}
int main(){
    int size;
    int array[size];
    for(int i=0;i<size;i++){
        scanf("%d", array[i]);
    }
    int findmax= max(array,size);
    printf("%d", findmax);
    return 0;
}