#include <stdio.h>
#include <ctype.h>
void toUpper(char* string){
    int index=0;
    while(*(string+index)!='\0'){
        if(*(string+index)>=97 && *(string+index)<=122){
            *(string+index)=toupper(*(string+index));
        }
        index++;
    }
}
int main() {
    char text[100];
    printf("The text: ");
    scanf("%s",text);
    toUpper(text);
    printf("%s",text);
    return 0;
}