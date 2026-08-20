#include<stdio.h>
int  main() {
    int choice;
    float balance = 20;
    do {
        printf("\n Menu \n");
        printf("1. Credit 100$ \n");
        printf("2. Withdraw 50$ \n");
        printf("3. Check Balance \n");
        printf("4. Exit \n");

        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        if(choice == 1){
            balance = balance + 100;
            printf("%f", balance);     
        }
        else if (choice == 2) {
            if ( balance >=50 ){
                balance = balance - 50;    
            } else {
            printf("Your balance is not sufficient");
            }
        }else if ("choice == 3") {
            printf("My balance %.2f", balance);

        }
        } while (choice != 4);
    } 