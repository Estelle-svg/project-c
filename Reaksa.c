#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

// ==================== STRUCTURES ====================

// Nested structure for item details
typedef struct {
    float small;
    float medium;
    float large;
} SizePrice;

// Main Item structure with nested SizePrice
typedef struct {
    int itemId;
    char itemName[50];
    SizePrice sizes;
    int quantitySold;
    float totalRevenue;
} MenuItem;

// Order structure
typedef struct {
    int orderId;
    char buyerName[50];
    char itemName[50];
    char size[10];
    float price;
    float discount;
    float finalAmount;
    char orderDate[20];
    char orderTime[10];
} Order;

// Nested structure for customer profile
typedef struct {
    float balance;
    float totalSpent;
    int totalOrders;
} BuyerProfile;

// Customer/Buyer structure
typedef struct {
    int buyerId;
    char buyerName[50];
    char email[50];
    BuyerProfile profile;
} Buyer;

// Daily Sales Report structure
typedef struct {
    char date[20];
    float totalRevenue;
    int totalOrders;
    int drinks;
    int bakeryItems;
} DailySalesReport;

// ==================== GLOBAL VARIABLES ====================

MenuItem drinks[20];
MenuItem bakeryItems[20];
Order orderHistory[1000];
Buyer buyers[100];
DailySalesReport dailySales[365];

int drinkCount = 0;
int bakeryCount = 0;
int orderCount = 0;
int buyerCount = 0;
int dailySalesCount = 0;

// ==================== FUNCTION DECLARATIONS ====================

// Seller Functions
void displaySellerMenu(void);
void addMenuItems(void);
void displayMenu(void);
void displayDrinkMenu(void);
void displayBakeryMenu(void);
void viewDailyRevenue(void);
void viewBestSellingItem(void);
void addDiscountToItem(void);
void recordOrder(char *name, char *itemName, char *size, float price, float discount);
void updateItemSales(char *itemName, float price);
void displayOrderHistory(void);

// Buyer Functions
void displayBuyerMenu(void);
void registerBuyer(void);
void buyerPurchase(int buyerId);
void viewBuyerHistory(int buyerId);
void checkBuyerBalance(int buyerId);
void recommendDrinks(int buyerId);
void addBalance(int buyerId);

// Utility Functions
void initializeMenu(void);
MenuItem* findMenuItem(char *name);
void getFormattedDate(char *buffer);
void getFormattedTime(char *buffer);
float calculateTotal(float price, float discount);
int searchBuyerById(int buyerId);
void updateDailySalesReport(char *itemName, float amount, int type);
void displayAllBuyers(void);
int searchMenuByName(char *name);
void bubbleSortByRevenue(MenuItem arr[], int n);  // Sorting function
int countOrders(char *itemName);  // Recursive function to count items
void printItemDetails(MenuItem *item);  // Pointer function
void displayMenuRecursive(int index, int type);  // Recursive function

// ==================== MAIN FUNCTION ====================

int main() {
    int choice;
    int userType;
    int buyerId;
    
    initializeMenu();
    
    printf("\n");
    printf("========================================\n");
    printf("  WELCOME TO CAFE & BAKERY SYSTEM\n");
    printf("========================================\n\n");
    
    while (1) {
        printf("\n--- Main Menu ---\n");
        printf("1. Seller Interface\n");
        printf("2. Buyer Interface\n");
        printf("3. Exit\n");
        printf("Enter your choice (1-3): ");
        scanf("%d", &userType);
        getchar();  // Clear buffer
        
        switch (userType) {
            case 1:
                displaySellerMenu();
                break;
            case 2:
                displayBuyerMenu();
                break;
            case 3:
                printf("\nThank you for using Cafe & Bakery System! Goodbye!\n");
                return 0;
            default:
                printf("\nInvalid choice! Please try again.\n");
        }
    }
    
    return 0;
}

// ==================== INITIALIZATION FUNCTION ====================

void initializeMenu(void) {
    // Initialize Drinks (Using nested structure SizePrice)
    strcpy(drinks[0].itemName, "Coffee");
    drinks[0].itemId = 1;
    drinks[0].sizes.small = 2.50;
    drinks[0].sizes.medium = 3.50;
    drinks[0].sizes.large = 4.50;
    drinks[0].quantitySold = 0;
    drinks[0].totalRevenue = 0;
    drinkCount++;
    
    strcpy(drinks[1].itemName, "Tea");
    drinks[1].itemId = 2;
    drinks[1].sizes.small = 2.00;
    drinks[1].sizes.medium = 2.80;
    drinks[1].sizes.large = 3.60;
    drinks[1].quantitySold = 0;
    drinks[1].totalRevenue = 0;
    drinkCount++;
    
    strcpy(drinks[2].itemName, "Latte");
    drinks[2].itemId = 3;
    drinks[2].sizes.small = 3.50;
    drinks[2].sizes.medium = 4.50;
    drinks[2].sizes.large = 5.50;
    drinks[2].quantitySold = 0;
    drinks[2].totalRevenue = 0;
    drinkCount++;
    
    strcpy(drinks[3].itemName, "Cappuccino");
    drinks[3].itemId = 4;
    drinks[3].sizes.small = 3.50;
    drinks[3].sizes.medium = 4.50;
    drinks[3].sizes.large = 5.50;
    drinks[3].quantitySold = 0;
    drinks[3].totalRevenue = 0;
    drinkCount++;
    
    strcpy(drinks[4].itemName, "Orange Juice");
    drinks[4].itemId = 5;
    drinks[4].sizes.small = 3.00;
    drinks[4].sizes.medium = 4.00;
    drinks[4].sizes.large = 5.00;
    drinks[4].quantitySold = 0;
    drinks[4].totalRevenue = 0;
    drinkCount++;
    
    // Initialize Bakery Items
    strcpy(bakeryItems[0].itemName, "Croissant");
    bakeryItems[0].itemId = 6;
    bakeryItems[0].sizes.small = 2.50;
    bakeryItems[0].sizes.medium = 3.50;
    bakeryItems[0].sizes.large = 4.50;
    bakeryItems[0].quantitySold = 0;
    bakeryItems[0].totalRevenue = 0;
    bakeryCount++;
    
    strcpy(bakeryItems[1].itemName, "Donut");
    bakeryItems[1].itemId = 7;
    bakeryItems[1].sizes.small = 1.50;
    bakeryItems[1].sizes.medium = 2.50;
    bakeryItems[1].sizes.large = 3.50;
    bakeryItems[1].quantitySold = 0;
    bakeryItems[1].totalRevenue = 0;
    bakeryCount++;
    
    strcpy(bakeryItems[2].itemName, "Cake Slice");
    bakeryItems[2].itemId = 8;
    bakeryItems[2].sizes.small = 3.00;
    bakeryItems[2].sizes.medium = 5.00;
    bakeryItems[2].sizes.large = 7.00;
    bakeryItems[2].quantitySold = 0;
    bakeryItems[2].totalRevenue = 0;
    bakeryCount++;
    
    strcpy(bakeryItems[3].itemName, "Bread");
    bakeryItems[3].itemId = 9;
    bakeryItems[3].sizes.small = 2.00;
    bakeryItems[3].sizes.medium = 3.50;
    bakeryItems[3].sizes.large = 5.00;
    bakeryItems[3].quantitySold = 0;
    bakeryItems[3].totalRevenue = 0;
    bakeryCount++;
    
    strcpy(bakeryItems[4].itemName, "Muffin");
    bakeryItems[4].itemId = 10;
    bakeryItems[4].sizes.small = 2.50;
    bakeryItems[4].sizes.medium = 3.50;
    bakeryItems[4].sizes.large = 4.50;
    bakeryItems[4].quantitySold = 0;
    bakeryItems[4].totalRevenue = 0;
    bakeryCount++;
}

// ==================== SELLER INTERFACE FUNCTIONS ====================

void displaySellerMenu(void) {
    int choice;
    
    while (1) {
        printf("\n========== SELLER INTERFACE ==========\n");
        printf("1. Display Menu\n");
        printf("2. View Order History\n");
        printf("3. View Daily Revenue\n");
        printf("4. View Best Selling Item\n");
        printf("5. Add Discount to Item\n");
        printf("6. Back to Main Menu\n");
        printf("=====================================\n");
        printf("Enter your choice (1-6): ");
        scanf("%d", &choice);
        getchar();
        
        switch (choice) {
            case 1:
                displayMenu();
                break;
            case 2:
                displayOrderHistory();
                break;
            case 3:
                viewDailyRevenue();
                break;
            case 4:
                viewBestSellingItem();
                break;
            case 5:
                addDiscountToItem();
                break;
            case 6:
                return;
            default:
                printf("\nInvalid choice! Please try again.\n");
        }
    }
}

// Display entire menu with 2D array concept using nested loops
void displayMenu(void) {
    printf("\n========== CAFE & BAKERY MENU ==========\n\n");
    
    displayDrinkMenu();
    printf("\n");
    displayBakeryMenu();
    printf("\n==========================================\n");
}

// Display drinks menu - recursive function
void displayDrinkMenu(void) {
    printf("--- DRINKS ---\n");
    printf("%-5s %-20s %-12s %-12s %-12s\n", "ID", "Name", "Small", "Medium", "Large");
    printf("----------------------------------------------------------\n");
    displayMenuRecursive(0, 0);  // 0 for drinks
}

// Display bakery menu - recursive function
void displayBakeryMenu(void) {
    printf("\n--- BAKERY ITEMS ---\n");
    printf("%-5s %-20s %-12s %-12s %-12s\n", "ID", "Name", "Small", "Medium", "Large");
    printf("----------------------------------------------------------\n");
    displayMenuRecursive(0, 1);  // 1 for bakery
}

// Recursive function to display menu items
void displayMenuRecursive(int index, int type) {
    if (type == 0) {  // Drinks
        if (index >= drinkCount) return;
        printItemDetails(&drinks[index]);
        displayMenuRecursive(index + 1, type);
    } else {  // Bakery items
        if (index >= bakeryCount) return;
        printItemDetails(&bakeryItems[index]);
        displayMenuRecursive(index + 1, type);
    }
}

// Pointer function to print item details
void printItemDetails(MenuItem *item) {
    printf("%-5d %-20s $%-11.2f $%-11.2f $%-11.2f\n", 
           item->itemId, 
           item->itemName, 
           item->sizes.small,    // Accessing nested structure
           item->sizes.medium,
           item->sizes.large);
}

void displayOrderHistory(void) {
    printf("\n========== ORDER HISTORY ==========\n");
    
    if (orderCount == 0) {
        printf("No orders yet.\n");
        return;
    }
    
    printf("%-8s %-20s %-20s %-10s %-8s %-8s %-10s %-10s\n",
           "OrderID", "Buyer", "Item", "Size", "Price", "Discount", "Final Amt", "Date");
    printf("=====================================================================================\n");
    
    // Loop through order history
    for (int i = 0; i < orderCount; i++) {
        printf("%-8d %-20s %-20s %-10s $%-7.2f $%-7.2f $%-9.2f %s\n",
               orderHistory[i].orderId,
               orderHistory[i].buyerName,
               orderHistory[i].itemName,
               orderHistory[i].size,
               orderHistory[i].price,
               orderHistory[i].discount,
               orderHistory[i].finalAmount,
               orderHistory[i].orderDate);
    }
    printf("=====================================================================================\n");
}

void viewDailyRevenue(void) {
    printf("\n========== DAILY REVENUE REPORT ==========\n");
    
    if (dailySalesCount == 0) {
        printf("No sales data available.\n");
        return;
    }
    
    float totalRevenue = 0;
    int totalOrders = 0;
    
    printf("%-12s %-15s %-12s %-10s %-12s\n", "Date", "Revenue", "Orders", "Drinks", "Bakery");
    printf("==========================================================\n");
    
    // Loop through daily sales and calculate totals
    for (int i = 0; i < dailySalesCount; i++) {
        printf("%-12s $%-14.2f %-12d %-10d %-12d\n",
               dailySales[i].date,
               dailySales[i].totalRevenue,
               dailySales[i].totalOrders,
               dailySales[i].drinks,
               dailySales[i].bakeryItems);
        
        totalRevenue += dailySales[i].totalRevenue;
        totalOrders += dailySales[i].totalOrders;
    }
    
    printf("==========================================================\n");
    printf("TOTAL REVENUE: $%.2f\n", totalRevenue);
    printf("TOTAL ORDERS: %d\n", totalOrders);
    printf("==========================================\n");
}

// Sorting function using bubble sort to find best seller
void bubbleSortByRevenue(MenuItem arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].totalRevenue < arr[j + 1].totalRevenue) {
                MenuItem temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void viewBestSellingItem(void) {
    printf("\n========== BEST SELLING ITEMS ==========\n");
    
    if (orderCount == 0) {
        printf("No sales data available.\n");
        return;
    }
    
    // Create copies and sort them
    MenuItem drinksCopy[20];
    MenuItem bakeryItemsCopy[20];
    
    // Copy drinks
    for (int i = 0; i < drinkCount; i++) {
        drinksCopy[i] = drinks[i];
    }
    
    // Copy bakery items
    for (int i = 0; i < bakeryCount; i++) {
        bakeryItemsCopy[i] = bakeryItems[i];
    }
    
    // Sort both arrays
    bubbleSortByRevenue(drinksCopy, drinkCount);
    bubbleSortByRevenue(bakeryItemsCopy, bakeryCount);
    
    printf("\n--- TOP SELLING DRINKS ---\n");
    printf("%-20s %-12s %-10s\n", "Item Name", "Revenue", "Qty Sold");
    printf("==========================================\n");
    
    for (int i = 0; i < drinkCount; i++) {
        printf("%-20s $%-11.2f %-10d\n",
               drinksCopy[i].itemName,
               drinksCopy[i].totalRevenue,
               drinksCopy[i].quantitySold);
    }
    
    printf("\n--- TOP SELLING BAKERY ITEMS ---\n");
    printf("%-20s %-12s %-10s\n", "Item Name", "Revenue", "Qty Sold");
    printf("==========================================\n");
    
    for (int i = 0; i < bakeryCount; i++) {
        printf("%-20s $%-11.2f %-10d\n",
               bakeryItemsCopy[i].itemName,
               bakeryItemsCopy[i].totalRevenue,
               bakeryItemsCopy[i].quantitySold);
    }
    printf("==========================================\n");
}

void addDiscountToItem(void) {
    char itemName[50];
    float discountPercent;
    int found = 0;
    
    printf("\nEnter item name to add discount: ");
    fgets(itemName, sizeof(itemName), stdin);
    itemName[strcspn(itemName, "\n")] = 0;  // Remove newline
    
    printf("Enter discount percentage (0-100): ");
    scanf("%f", &discountPercent);
    getchar();
    
    // Search in drinks
    for (int i = 0; i < drinkCount; i++) {
        if (strcmp(drinks[i].itemName, itemName) == 0) {
            printf("\n--- Discount Applied to %s ---\n", itemName);
            printf("Original Prices:\n");
            printf("Small: $%.2f -> $%.2f\n", 
                   drinks[i].sizes.small, 
                   drinks[i].sizes.small * (1 - discountPercent / 100));
            printf("Medium: $%.2f -> $%.2f\n", 
                   drinks[i].sizes.medium, 
                   drinks[i].sizes.medium * (1 - discountPercent / 100));
            printf("Large: $%.2f -> $%.2f\n", 
                   drinks[i].sizes.large, 
                   drinks[i].sizes.large * (1 - discountPercent / 100));
            found = 1;
            break;
        }
    }
    
    // Search in bakery items
    for (int i = 0; i < bakeryCount; i++) {
        if (strcmp(bakeryItems[i].itemName, itemName) == 0) {
            printf("\n--- Discount Applied to %s ---\n", itemName);
            printf("Original Prices:\n");
            printf("Small: $%.2f -> $%.2f\n", 
                   bakeryItems[i].sizes.small, 
                   bakeryItems[i].sizes.small * (1 - discountPercent / 100));
            printf("Medium: $%.2f -> $%.2f\n", 
                   bakeryItems[i].sizes.medium, 
                   bakeryItems[i].sizes.medium * (1 - discountPercent / 100));
            printf("Large: $%.2f -> $%.2f\n", 
                   bakeryItems[i].sizes.large, 
                   bakeryItems[i].sizes.large * (1 - discountPercent / 100));
            found = 1;
            break;
        }
    }
    
    if (!found) {
        printf("\nItem not found!\n");
    }
}

void recordOrder(char *name, char *itemName, char *size, float price, float discount) {
    orderHistory[orderCount].orderId = orderCount + 1;
    strcpy(orderHistory[orderCount].buyerName, name);
    strcpy(orderHistory[orderCount].itemName, itemName);
    strcpy(orderHistory[orderCount].size, size);
    orderHistory[orderCount].price = price;
    orderHistory[orderCount].discount = discount;
    orderHistory[orderCount].finalAmount = calculateTotal(price, discount);
    getFormattedDate(orderHistory[orderCount].orderDate);
    getFormattedTime(orderHistory[orderCount].orderTime);
    
    orderCount++;
}

void updateItemSales(char *itemName, float price) {
    // Update drinks
    for (int i = 0; i < drinkCount; i++) {
        if (strcmp(drinks[i].itemName, itemName) == 0) {
            drinks[i].quantitySold++;
            drinks[i].totalRevenue += price;
            return;
        }
    }
    
    // Update bakery items
    for (int i = 0; i < bakeryCount; i++) {
        if (strcmp(bakeryItems[i].itemName, itemName) == 0) {
            bakeryItems[i].quantitySold++;
            bakeryItems[i].totalRevenue += price;
            return;
        }
    }
}

// ==================== BUYER INTERFACE FUNCTIONS ====================

void displayBuyerMenu(void) {
    int choice;
    int buyerId;
    
    printf("\n========== BUYER INTERFACE ==========\n");
    printf("1. Register as New Buyer\n");
    printf("2. View All Buyers\n");
    printf("3. Purchase Items\n");
    printf("4. View Purchase History\n");
    printf("5. Check Balance\n");
    printf("6. Add Balance\n");
    printf("7. Get Drink Recommendations\n");
    printf("8. Back to Main Menu\n");
    printf("=====================================\n");
    
    while (1) {
        printf("Enter your choice (1-8): ");
        scanf("%d", &choice);
        getchar();
        
        switch (choice) {
            case 1:
                registerBuyer();
                break;
            case 2:
                displayAllBuyers();
                break;
            case 3:
                printf("\nEnter your Buyer ID: ");
                scanf("%d", &buyerId);
                getchar();
                if (searchBuyerById(buyerId) != -1) {
                    buyerPurchase(buyerId);
                } else {
                    printf("\nBuyer not found! Please register first.\n");
                }
                break;
            case 4:
                printf("\nEnter your Buyer ID: ");
                scanf("%d", &buyerId);
                getchar();
                if (searchBuyerById(buyerId) != -1) {
                    viewBuyerHistory(buyerId);
                } else {
                    printf("\nBuyer not found!\n");
                }
                break;
            case 5:
                printf("\nEnter your Buyer ID: ");
                scanf("%d", &buyerId);
                getchar();
                if (searchBuyerById(buyerId) != -1) {
                    checkBuyerBalance(buyerId);
                } else {
                    printf("\nBuyer not found!\n");
                }
                break;
            case 6:
                printf("\nEnter your Buyer ID: ");
                scanf("%d", &buyerId);
                getchar();
                if (searchBuyerById(buyerId) != -1) {
                    addBalance(buyerId);
                } else {
                    printf("\nBuyer not found!\n");
                }
                break;
            case 7:
                printf("\nEnter your Buyer ID: ");
                scanf("%d", &buyerId);
                getchar();
                if (searchBuyerById(buyerId) != -1) {
                    recommendDrinks(buyerId);
                } else {
                    printf("\nBuyer not found!\n");
                }
                break;
            case 8:
                return;
            default:
                printf("\nInvalid choice! Please try again.\n");
        }
    }
}

void registerBuyer(void) {
    if (buyerCount >= 100) {
        printf("\nBuyer limit reached!\n");
        return;
    }
    
    printf("\n========== BUYER REGISTRATION ==========\n");
    
    buyers[buyerCount].buyerId = buyerCount + 1000;
    
    printf("Enter your name: ");
    fgets(buyers[buyerCount].buyerName, sizeof(buyers[buyerCount].buyerName), stdin);
    buyers[buyerCount].buyerName[strcspn(buyers[buyerCount].buyerName, "\n")] = 0;
    
    printf("Enter your email: ");
    fgets(buyers[buyerCount].email, sizeof(buyers[buyerCount].email), stdin);
    buyers[buyerCount].email[strcspn(buyers[buyerCount].email, "\n")] = 0;
    
    printf("Enter initial balance ($): ");
    scanf("%f", &buyers[buyerCount].profile.balance);
    getchar();
    
    buyers[buyerCount].profile.totalSpent = 0;
    buyers[buyerCount].profile.totalOrders = 0;
    
    printf("\n✓ Registration successful!\n");
    printf("Your Buyer ID: %d\n", buyers[buyerCount].buyerId);
    printf("Keep this ID safe for future transactions.\n");
    
    buyerCount++;
}

void displayAllBuyers(void) {
    printf("\n========== REGISTERED BUYERS ==========\n");
    
    if (buyerCount == 0) {
        printf("No buyers registered yet.\n");
        return;
    }
    
    printf("%-8s %-20s %-20s %-12s %-12s\n", "ID", "Name", "Email", "Balance", "Total Spent");
    printf("========================================================================================\n");
    
    for (int i = 0; i < buyerCount; i++) {
        printf("%-8d %-20s %-20s $%-11.2f $%-11.2f\n",
               buyers[i].buyerId,
               buyers[i].buyerName,
               buyers[i].email,
               buyers[i].profile.balance,
               buyers[i].profile.totalSpent);
    }
    printf("========================================================================================\n");
}

void buyerPurchase(int buyerId) {
    int buyerIndex = searchBuyerById(buyerId);
    if (buyerIndex == -1) {
        printf("\nBuyer not found!\n");
        return;
    }
    
    printf("\n========== PURCHASE ITEMS ==========\n");
    displayMenu();
    
    char itemName[50];
    char size[10];
    float price;
    float discount = 0;
    
    printf("\nEnter item name to purchase: ");
    fgets(itemName, sizeof(itemName), stdin);
    itemName[strcspn(itemName, "\n")] = 0;
    
    MenuItem *item = findMenuItem(itemName);
    
    if (item == NULL) {
        printf("\nItem not found!\n");
        return;
    }
    
    printf("\nEnter size (small/medium/large): ");
    fgets(size, sizeof(size), stdin);
    size[strcspn(size, "\n")] = 0;
    
    // Convert to lowercase for comparison
    for (int i = 0; size[i]; i++) {
        size[i] = tolower(size[i]);
    }
    
    // Get price based on size
    if (strcmp(size, "small") == 0) {
        price = item->sizes.small;
    } else if (strcmp(size, "medium") == 0) {
        price = item->sizes.medium;
    } else if (strcmp(size, "large") == 0) {
        price = item->sizes.large;
    } else {
        printf("\nInvalid size!\n");
        return;
    }
    
    // Check if discount is available
    printf("\nApply discount? (0-100, 0 for no discount): ");
    scanf("%f", &discount);
    getchar();
    
    float finalAmount = calculateTotal(price, discount);
    
    // Check balance before purchase
    printf("\n========== PURCHASE SUMMARY ==========\n");
    printf("Item: %s (%s)\n", itemName, size);
    printf("Price: $%.2f\n", price);
    printf("Discount: %.1f%%\n", discount);
    printf("Final Amount: $%.2f\n", finalAmount);
    printf("Your Current Balance: $%.2f\n", buyers[buyerIndex].profile.balance);
    
    if (buyers[buyerIndex].profile.balance < finalAmount) {
        printf("\n✗ Insufficient balance! Cannot complete purchase.\n");
        printf("You need $%.2f more.\n", finalAmount - buyers[buyerIndex].profile.balance);
        return;
    }
    
    // Complete purchase
    buyers[buyerIndex].profile.balance -= finalAmount;
    buyers[buyerIndex].profile.totalSpent += finalAmount;
    buyers[buyerIndex].profile.totalOrders++;
    
    recordOrder(buyers[buyerIndex].buyerName, itemName, size, price, discount);
    updateItemSales(itemName, finalAmount);
    updateDailySalesReport(itemName, finalAmount, 0);
    
    printf("\n✓ Purchase successful!\n");
    printf("Remaining Balance: $%.2f\n", buyers[buyerIndex].profile.balance);
    printf("Thank you for shopping!\n");
}

MenuItem* findMenuItem(char *name) {
    // Search in drinks
    for (int i = 0; i < drinkCount; i++) {
        if (strcmp(drinks[i].itemName, name) == 0) {
            return &drinks[i];
        }
    }
    
    // Search in bakery items
    for (int i = 0; i < bakeryCount; i++) {
        if (strcmp(bakeryItems[i].itemName, name) == 0) {
            return &bakeryItems[i];
        }
    }
    
    return NULL;
}

void viewBuyerHistory(int buyerId) {
    int buyerIndex = searchBuyerById(buyerId);
    
    printf("\n========== PURCHASE HISTORY FOR %s ==========\n", 
           buyers[buyerIndex].buyerName);
    
    int count = 0;
    printf("%-8s %-20s %-10s %-8s %-10s %-10s\n",
           "OrderID", "Item", "Size", "Price", "Discount", "Final Amt");
    printf("==============================================================\n");
    
    for (int i = 0; i < orderCount; i++) {
        if (strcmp(orderHistory[i].buyerName, buyers[buyerIndex].buyerName) == 0) {
            printf("%-8d %-20s %-10s $%-7.2f $%-9.2f $%-9.2f\n",
                   orderHistory[i].orderId,
                   orderHistory[i].itemName,
                   orderHistory[i].size,
                   orderHistory[i].price,
                   orderHistory[i].discount,
                   orderHistory[i].finalAmount);
            count++;
        }
    }
    
    if (count == 0) {
        printf("No purchase history found.\n");
    }
    printf("==============================================================\n");
    printf("Total Purchases: %d\n", buyers[buyerIndex].profile.totalOrders);
    printf("Total Amount Spent: $%.2f\n", buyers[buyerIndex].profile.totalSpent);
}

void checkBuyerBalance(int buyerId) {
    int buyerIndex = searchBuyerById(buyerId);
    
    printf("\n========== BALANCE INFORMATION ==========\n");
    printf("Buyer Name: %s\n", buyers[buyerIndex].buyerName);
    printf("Current Balance: $%.2f\n", buyers[buyerIndex].profile.balance);
    printf("Total Spent: $%.2f\n", buyers[buyerIndex].profile.totalSpent);
    printf("Total Orders: %d\n", buyers[buyerIndex].profile.totalOrders);
    printf("==========================================\n");
}

void addBalance(int buyerId) {
    int buyerIndex = searchBuyerById(buyerId);
    float amount;
    
    printf("\n========== ADD BALANCE ==========\n");
    printf("Current Balance: $%.2f\n", buyers[buyerIndex].profile.balance);
    printf("Enter amount to add: $");
    scanf("%f", &amount);
    getchar();
    
    if (amount <= 0) {
        printf("\nInvalid amount!\n");
        return;
    }
    
    buyers[buyerIndex].profile.balance += amount;
    printf("\n✓ Balance updated successfully!\n");
    printf("New Balance: $%.2f\n", buyers[buyerIndex].profile.balance);
}

void recommendDrinks(int buyerId) {
    printf("\n========== DRINK RECOMMENDATIONS ==========\n");
    printf("\nBased on our most popular items, we recommend:\n\n");
    
    MenuItem recommendedDrinks[20];
    for (int i = 0; i < drinkCount; i++) {
        recommendedDrinks[i] = drinks[i];
    }
    
    bubbleSortByRevenue(recommendedDrinks, drinkCount);
    
    printf("%-20s %-12s %-12s %-12s\n", "Item Name", "Small", "Medium", "Large");
    printf("========================================================\n");
    
    int recCount = (drinkCount < 3) ? drinkCount : 3;
    for (int i = 0; i < recCount; i++) {
        printf("%-20s $%-11.2f $%-11.2f $%-11.2f\n",
               recommendedDrinks[i].itemName,
               recommendedDrinks[i].sizes.small,
               recommendedDrinks[i].sizes.medium,
               recommendedDrinks[i].sizes.large);
    }
    printf("========================================================\n");
}

// ==================== UTILITY FUNCTIONS ====================

float calculateTotal(float price, float discount) {
    return price * (1 - discount / 100);
}

void getFormattedDate(char *buffer) {
    time_t now = time(NULL);
    struct tm *timeinfo = localtime(&now);
    strftime(buffer, 20, "%Y-%m-%d", timeinfo);
}

void getFormattedTime(char *buffer) {
    time_t now = time(NULL);
    struct tm *timeinfo = localtime(&now);
    strftime(buffer, 10, "%H:%M:%S", timeinfo);
}

int searchBuyerById(int buyerId) {
    for (int i = 0; i < buyerCount; i++) {
        if (buyers[i].buyerId == buyerId) {
            return i;
        }
    }
    return -1;
}

int searchMenuByName(char *name) {
    for (int i = 0; i < drinkCount; i++) {
        if (strcmp(drinks[i].itemName, name) == 0) {
            return i;
        }
    }
    
    for (int i = 0; i < bakeryCount; i++) {
        if (strcmp(bakeryItems[i].itemName, name) == 0) {
            return i;
        }
    }
    
    return -1;
}

void updateDailySalesReport(char *itemName, float amount, int type) {
    char currentDate[20];
    getFormattedDate(currentDate);
    
    // Find today's report
    int reportIndex = -1;
    for (int i = 0; i < dailySalesCount; i++) {
        if (strcmp(dailySales[i].date, currentDate) == 0) {
            reportIndex = i;
            break;
        }
    }
    
    // Create new report if not found
    if (reportIndex == -1) {
        strcpy(dailySales[dailySalesCount].date, currentDate);
        dailySales[dailySalesCount].totalRevenue = 0;
        dailySales[dailySalesCount].totalOrders = 0;
        dailySales[dailySalesCount].drinks = 0;
        dailySales[dailySalesCount].bakeryItems = 0;
        reportIndex = dailySalesCount;
        dailySalesCount++;
    }
    
    // Update report
    dailySales[reportIndex].totalRevenue += amount;
    dailySales[reportIndex].totalOrders++;
    
    // Check if item is drink or bakery
    for (int i = 0; i < drinkCount; i++) {
        if (strcmp(drinks[i].itemName, itemName) == 0) {
            dailySales[reportIndex].drinks++;
            return;
        }
    }
    
    for (int i = 0; i < bakeryCount; i++) {
        if (strcmp(bakeryItems[i].itemName, itemName) == 0) {
            dailySales[reportIndex].bakeryItems++;
            return;
        }
    }
}

// Recursive function to count orders for an item
int countOrders(char *itemName) {
    static int count = 0;
    static int index = 0;
    
    if (index >= orderCount) {
        int result = count;
        count = 0;
        index = 0;
        return result;
    }
    
    if (strcmp(orderHistory[index].itemName, itemName) == 0) {
        count++;
    }
    
    index++;
    return countOrders(itemName);
}
