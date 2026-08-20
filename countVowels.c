#include <stdio.h>
int countVowels(const char* string){
    int index=0;
    int count=0;
    while(*(string+index)!='\0'){
        if(*(string+index)=='a'||*(string+index)=='e'||*(string+index)=='i'||*(string+index)=='o'||*(string+index)=='u'||*(string+index)=='A'
        ||*(string+index)=='E'||*(string+index)=='I'||*(string+index)=='O'||*(string+index)=='U'){
            count++;
        }index++;
    }return count;
}
int main() {
    const char* string="who is the BEst";
    int size= countVowels(string);
    printf("%d", size);
}