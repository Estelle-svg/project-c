#include <stdio.h>
void reverseString(char* string){
    int index=0;
    int count=0;
    int store;
    while(*(string+index)!='\0'){
    count++;
    index++;
    }
    for(int i=0;i<count/2;i++){
        store=*(string+i);
        *(string+i)=*(string+count-i-1);
        *(string+count-i-1)=store;
    }
}
int main() {
    char text[100];
    printf("Enter the text: ");scanf("%s",text);
    reverseString(text);
    printf("%s", text);
    return 0;
}