#include <stdio.h>
#include <stdbool.h>
int main ()
{
    // Initial resources
    int wood = 5;
    int wheat = 5;
    int bricks = 5;
    int rocks = 5;
    
    // Initial products
    int roads = 0;
    int houses = 0;
    int cities = 0;
    
    int  choice;
    printf("Welcome to the Resource Management Game!\n");
    do {
        // Display menu
        printf("\nMenu:\n");
        printf("1. Buy Road\n");
        printf("2. Buy House\n");
        printf("3. Buy City\n");
        printf("4. Check Current Products\n");
        printf("5. Exit\n");

        // Get user choice
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: {
                // buy Road 
                bool canBuyRoad = (bricks >= 1 && rocks >= 1);
                if (canBuyRoad) {
                    bricks -= 1;
                    rocks -= 1;
                    roads += 1;
                    printf("You built a road!\n");
                } else {
                    printf ("You cannot buy a road with your current resource!\n");
                }
                break;
            }
            case 2: {
                //  buy House 
                bool canBuyHouse = (wood >= 2 && wheat >=3);
                if (canBuyHouse){
                    wood -= 2;
                    wheat -= 3;
                    houses += 1;
                    printf("You built a house!\n");
                } else {
                    printf ("You cannot buy a road with your current resource!\n");
                }
                break;
            }    
            case 3: {
                // buy City 
                bool canBuyCity = (wood >=3 && bricks >= 3 && rocks >=5);
                if (canBuyCity) {
                    wood -= 3;
                    bricks -= 3;
                    rocks -= 5;
                    cities += 1;
                    printf("You built a city!\n");
                } else {
                    printf ("You cannot buy a road with your current resource!\n");
                }
                break;
            }
            case 4: {
                //  Display resources 
                printf("Check current rescources\n"); 
                printf("wood: %d\nwheat: %d\nbricks: %d\nrocks: %d", wood,wheat,bricks,rocks);           
                //  Display products 
                printf("Product\n");
                printf("cities: %d\nhouses: %d\nroads: %d", cities,houses,roads);
                break;
            }
            case 5:
                printf("Exiting the game. Thank you for playing!\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }while (choice != 5);
    return 0;
}