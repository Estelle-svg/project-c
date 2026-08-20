#include <stdio.h>
void swap(int* FirstValue, int* SecValue){
	int store;
	store= *FirstValue;
	*FirstValue=*SecValue;
	*SecValue=store;
	printf("X = %d \t", *FirstValue);
	printf("(Address %p)\n", FirstValue);

	printf("Y= %d \t", *SecValue);
	printf("(Address %p)", SecValue);
}
int main () {
	int Xbefore,Ybefore;
	// Before Swap
	printf("Before swap\n");
	printf("X = ", Xbefore);
	scanf("%d", &Xbefore);
	printf("(Address %p)\n", &Xbefore);
	
	printf("Y= ", Ybefore);
	scanf("%d", &Ybefore);
	printf("(Address %p)\n", &Ybefore);
	// After Swap
	printf("After swap\n");
	swap(&Xbefore,&Ybefore);
	return 0;
}