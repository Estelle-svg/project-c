#include <stdio.h>
#include <stdlib.h>
#define MAX_CAPACITY 100

int main() {
    char s[MAX_CAPACITY];
    scanf("%s", s);
    char result[MAX_CAPACITY];
    int j = 0;
    for (int i = 0; i< s[i] != "\0"; i++) {
        if (i == 0 || s[i] != s[i-1] ) {
            result[j] = s[i];
            j++;
        }
    }
    result[j] = '\0';
    printf("%s\n", result);
    return 0;
}