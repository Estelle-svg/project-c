#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// ==========================================
// 1. STRUCTURES
// ==========================================
struct Item {
    int id;
    char name[50];
    float price;
    int qty;
};

// ==========================================
// FUNCTION PROTOTYPES
// ==========================================
// Menus
void sellerInterface(struct Item *inventory, int *itemCount);
void buyerInterface(struct Item *inventory, int itemCount, struct Item *cart, int *cartCount);

// Core Functions
void addItem(struct Item *inventory, int *count); 
void viewItems(struct Item *inventory, int count);
void searchItemByName(struct Item *inventory, int count, char *searchName);
void buyItem(struct Item *inventory, int itemCount, struct Item *cart, int *cartCount);

// Recursive Function
float calculateCartTotal(struct Item *cart, int n); 

// ==========================================
// MAIN FUNCTION
// ==========================================
int main() {
    struct Item shopInventory[100]; 
    int itemCount = 0; 
    
    struct Item buyerCart[50];
    int cartCount = 0;

    int roleChoice;

    while (1) {
        system("cls"); // Use "clear" if on Mac/Linux
        printf("=========================================\n");
        printf("      WELCOME TO THE STATIONARY SHOP     \n");
        printf("=========================================\n");
        printf("Select Your Role:\n");
        printf("1. Seller (Admin)\n");
        printf("2. Buyer (Customer)\n");
        printf("3. Exit System\n");
        printf("-----------------------------------------\n");
        printf("Enter choice (1-3): ");
        scanf("%d", &roleChoice);

        switch (roleChoice) {
            case 1:
                sellerInterface(shopInventory, &itemCount);
                break;
            case 2:
                buyerInterface(shopInventory, itemCount, buyerCart, &cartCount);
                break;
            case 3:
                printf("\nShutting down the system. Goodbye!\n");
                exit(0);
            default:
                printf("\nInvalid choice! Press Enter to try again.");
                getchar(); getchar();
        }
    }
    return 0;
}

// INTERFACE LOGIC

void sellerInterface(struct Item *inventory, int *itemCount) {
    int choice;
    while (1) {
        system("cls");
        printf("=========================================\n");
        printf("           🤍SELLER DASHBOARD🤍         \n");
        printf("=========================================\n");
        printf("1. Add New Item to Stock\n");
        printf("2. View Master Inventory\n");
        printf("3. Return to Main Menu\n");
        printf("-----------------------------------------\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addItem(inventory, itemCount);
                break;
            case 2:
                viewItems(inventory, *itemCount);
                break;
            case 3:
                return; 
            default:
                printf("\nInvalid choice!");
        }
        printf("\nPress Enter to continue...");
        getchar(); getchar();
    }
}

void buyerInterface(struct Item *inventory, int itemCount, struct Item *cart, int *cartCount) {
    int choice;
    char searchStr[50];

    while (1) {
        system("cls");
        printf("=========================================\n");
        printf("              BUYER STOREFRONT           \n");
        printf("=========================================\n");
        printf("1. View Available Items\n");
        printf("2. Search for an Item\n");
        printf("3. Add Item to Cart\n");
        printf("4. Checkout & Pay\n");
        printf("5. Return to Main Menu\n");
        printf("-----------------------------------------\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                viewItems(inventory, itemCount);
                break;
            case 2:
                printf("\nEnter the exact name of the item: ");
                scanf("%s", searchStr);
                searchItemByName(inventory, itemCount, searchStr);
                break;
            case 3:
                buyItem(inventory, itemCount, cart, cartCount);
                break;
            case 4:
                if (*cartCount == 0) {
                    printf("\nYour cart is empty!\n");
                } else {
                    printf("\n--- CHECKOUT RECEIPT ---\n");
                    viewItems(cart, *cartCount); // Reusing the view function for the cart!
                    
                    // Recursive function call
                    float totalBill = calculateCartTotal(cart, *cartCount);
                    printf("-----------------------------------------\n");
                    printf("GRAND TOTAL: $%.2f\n", totalBill);
                    printf("Thank you for your purchase!\n");
                    
                    *cartCount = 0; // Empty the cart after checkout
                }
                break;
            case 5:
                return;
            default:
                printf("\nInvalid choice!");
        }
        printf("\nPress Enter to continue...");
        getchar(); getchar();
    }
}

// ==========================================
// CORE FUNCTIONS
// ==========================================

void addItem(struct Item *inventory, int *count) {
    if (*count >= 100) {
        printf("\nInventory is full!\n");
        return;
    }

    printf("\n--- ADD NEW ITEM ---\n");
    printf("Enter Item ID: ");
    scanf("%d", &inventory[*count].id);
    
    printf("Enter Item Name (use_underscores_for_spaces): ");
    scanf("%s", inventory[*count].name);
    
    printf("Enter Price: ");
    scanf("%f", &inventory[*count].price);
    
    printf("Enter Quantity to Stock: ");
    scanf("%d", &inventory[*count].qty);

    (*count)++;
    printf("\nItem added to stock successfully!\n");
}

void viewItems(struct Item *inventory, int count) {
    if (count == 0) {
        printf("\nNo items to display!\n");
        return;
    }

    printf("\nID    | Name                 | Price   | Qty \n");
    printf("---------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%-5d | %-20s | $%-6.2f | %-5d\n", 
               inventory[i].id, inventory[i].name, inventory[i].price, inventory[i].qty);
    }
}

void searchItemByName(struct Item *inventory, int count, char *searchName) {
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(inventory[i].name, searchName) == 0) {
            printf("\n--- ITEM FOUND ---\n");
            printf("ID: %d | Name: %s | Price: $%.2f | In Stock: %d\n", 
                   inventory[i].id, inventory[i].name, inventory[i].price, inventory[i].qty);
            found = 1;
            break;
        }
    }
    if (!found) printf("\nItem '%s' not found.\n", searchName);
}

// Handles buying logic: Deducts from inventory, adds to cart
void buyItem(struct Item *inventory, int itemCount, struct Item *cart, int *cartCount) {
    int searchId, buyQty, found = 0;
    
    printf("\nEnter the ID of the item you want to buy: ");
    scanf("%d", &searchId);

    for (int i = 0; i < itemCount; i++) {
        if (inventory[i].id == searchId) {
            found = 1;
            printf("Found: %s ($%.2f) - In Stock: %d\n", inventory[i].name, inventory[i].price, inventory[i].qty);
            printf("How many would you like to buy? ");
            scanf("%d", &buyQty);

            if (buyQty > inventory[i].qty) {
                printf("\nSorry, we don't have enough stock!\n");
            } else if (buyQty <= 0) {
                printf("\nInvalid quantity.\n");
            } else {
                // Deduct from shop inventory
                inventory[i].qty -= buyQty;

                // Add to buyer's cart array
                cart[*cartCount].id = inventory[i].id;
                strcpy(cart[*cartCount].name, inventory[i].name); // Copy string to cart
                cart[*cartCount].price = inventory[i].price;
                cart[*cartCount].qty = buyQty;
                
                (*cartCount)++;
                printf("\nSuccessfully added %d %s(s) to your cart!\n", buyQty, inventory[i].name);
            }
            break;
        }
    }
    if (!found) printf("\nItem ID %d not found in the shop.\n", searchId);
}

// ==========================================
// RECURSIVE FUNCTION
// ==========================================

// Recursively adds up the total value of items in the cart
float calculateCartTotal(struct Item *cart, int n) {
    if (n <= 0) {
        return 0.0; // Base Case: No items left to calculate
    }
    
    // Recursive Step: (Price * Qty of current item) + (Total of remaining items)
    float currentItemValue = cart[n - 1].price * cart[n - 1].qty;
    return currentItemValue + calculateCartTotal(cart, n - 1);
}