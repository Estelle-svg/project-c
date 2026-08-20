#include <stdio.h>
void Log(int* array,int size){
    for(int i=0;i<size;i++){
        printf("%d ",*(array+i));
        printf("(Address: %p)\n",(array+i));
    }
}
int main(){
    int size;
    printf("Enter size of array: ");
    scanf("%d",&size);
    // user enter array
    int array[size];
    for(int i=0;i<size;i++){
        scanf("%d",&array[i]);
    }
    Log(array,size);
    return 0;
}