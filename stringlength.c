#include <stdio.h>
int lengthOf(const char* string){
    int count=0;
    int index=0;
    while (*(string + index) != '\0'){
        count++;
        index++;
    }
    return count;
}
int main(){
    const char* string = "Estelle";
    int size = lengthOf(string);
    printf("%d", size);
    return 0;
}