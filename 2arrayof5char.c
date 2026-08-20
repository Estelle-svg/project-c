#include <stdio.h>
int main ()
{
    char arr1[5]={'A','A','B','C','C'};
    char arr2[5]={'B','B','A','A','C'};
    int countA=0,countB=0,countC=0;
    int countA2=0,countB2=0,countC2=0;
    for ( int i=0; i<5; i++){
        if (arr1[i]==65){
            countA++; 
        } else if (arr1[i]==66) {
            countB++;
        }else if (arr1[i]==67) {
            countC++;
        }
    }
    for ( int i=0; i<5; i++){
        if (arr2[i]==65){
            countA2++; 
        } else if (arr2[i]==66) {
            countB2++;
        }else if (arr2[i]==67) {
            countC2++;
        }
    }
    if ((countA==countA2) && (countB==countB2) && (countC==countC2)) {
        printf("Same");
    } else {
        printf ("Different");
    }
    
    return 0;
}
