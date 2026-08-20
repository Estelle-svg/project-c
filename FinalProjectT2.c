#include <stdio.h>
#include <string.h>

#define MAX_PRODUCTS    50
#define MAX_NAME_LEN    50
#define MAX_CAT_LEN     30
#define MAX_CART_ITEMS  20
#define MONTHS          12

// i put all my structs here at the top so its easier to find
typedef struct {
    int day;
    int month;
    int year;
} Date;

typedef struct {
    int   id;
    char  name[MAX_NAME_LEN];
    char  category[MAX_CAT_LEN];
    float price;
    int   stock;
    Date  dateAdded;
} Product;

typedef struct {
    char  name[MAX_NAME_LEN];
    int   isMember;    /* 1 = member, 0 = not member */
    float balance;
} Buyer;

typedef struct {
    Product items[MAX_CART_ITEMS];
    int     quantities[MAX_CART_ITEMS];
    int     itemCount;
} Cart;

/* global stuff */
Product inventory[MAX_PRODUCTS];
int     productCount = 0;
int     salesRecord[MONTHS][MAX_PRODUCTS];

//I want to add some product sample so it don't look empty//
void  initializeInventory(void);

//seller functions //
void  sellerMenu(void);
void  addProduct(void);
void  updateProductStock(int index, int amount);
void  removeProductById(int id);
void  displayInventory(void);
void  displaySalesReport(void);

// buyer functions //
void  buyerMenu(void);
void  registerMembership(Buyer *buyer);
void  displayProducts(Product list[], int count);
void  filterByPrice(void);
void  addToCart(Cart *cart);
void  viewCart(Cart *cart);
void  checkout(Cart *cart, Buyer *buyer);

// the main logic functions //
int   findProductIndexById(Product list[], int count, int id, int index);
void  sortLowToHigh(Product list[], int count);
void  sortHighToLow(Product list[], int count);
float calculateCartTotal(Cart *cart);
float applyMembershipDiscount(float total, int isMember);
int   hasEnoughMoney(float balance, float total);
void  processPurchase(Cart *cart);
void  printReceipt(Cart *cart, Buyer *buyer, float finalPrice);

// some functions i use to help //
void  toUpperCase(char *str);
void  printLine(void);
int   getValidInt(const char *userchoice);
float getValidFloat(const char *userchoice);

int main(void) {
    int choice;

    initializeInventory();

    do {
        printLine();
        printf("                    ESTELLE'S STATIONARY SHOP\n");
        printLine();
        printf("1. Buyer Interface\n");
        printf("2. Seller Interface\n");
        printf("0. Exit\n");
        choice = getValidInt("Enter your choice: ");

        switch (choice) {
            case 1: buyerMenu();  break;
            case 2: sellerMenu(); break;
            case 0: printf("\nThank you for using the system. Goodbye!\n"); break;
            default: printf("\nInvalid choice. Please try again.\n");
        }
    } while (choice != 0);

    return 0;
}
//just some sample products i add//
void initializeInventory(void) {
    productCount = 15;

    inventory[0]  = (Product){1,  "Ballpoint Pen",    "Writing",   0.50,  100, {20, 4, 2026}};
    inventory[1]  = (Product){2,  "Notebook A5",      "Paper",     2.50,   50, {20, 4, 2026}};
    inventory[2]  = (Product){3,  "Stapler",          "Tools",     4.00,   20, {20, 4, 2026}};
    inventory[3]  = (Product){4,  "Highlighter Set",  "Writing",   4.00,   30, {20, 4, 2026}};
    inventory[4]  = (Product){5,  "A4 Paper Ream",    "Paper",     5.75,   40, {20, 4, 2026}};
    inventory[5]  = (Product){6,  "Red Pen",          "Writing",   0.25,   20, {22, 6, 2026}};
    inventory[6]  = (Product){7,  "Sarasa Blue Pen",  "Writing",   1.50,   25, {20, 6, 2026}};
    inventory[7]  = (Product){8,  "Sarasa Red Pen",   "Writing",   1.50,   15, {20, 6, 2026}};
    inventory[8]  = (Product){9,  "Sarasa Black Pen", "Writing",   1.50,   20, {20, 6, 2026}};
    inventory[9]  = (Product){10, "Folder",           "Organizer", 2.00,   10, {19, 6, 2026}};
    inventory[10] = (Product){11, "Stickers 50pcs",   "Decorate",  1.50,   20, {22, 6, 2026}};
    inventory[11] = (Product){12, "Novel Book",       "Book",     10.75,   15, {22, 6, 2026}};
    inventory[12] = (Product){13, "Motivation Book",  "Book",      5.00,   15, {22, 6, 2026}};
    inventory[13] = (Product){14, "Notepad",          "Tools",     0.75,   10, {21, 6, 2026}};
    inventory[14] = (Product){15, "Correction Tape",  "Tools",     1.25,   18, {22, 6, 2026}};

    // set all sales to 0 at the start which is good for report at the of the month // 
    for (int i = 0; i < MONTHS; i++) {
        for (int j = 0; j < MAX_PRODUCTS; j++) {
            salesRecord[i][j] = 0;
        }
    }
}
void printLine(void) {
    printf("------------------------------------------------------------------------\n");
}

void toUpperCase(char *str) {
    while (*str != '\0') {
        if (*str >= 'a' && *str <= 'z') {
            *str = (char)(*str - 'a' + 'A');
        }
        str++;
    }
}

int getValidInt(const char *userchoice) {
    int value;
    printf("%s", userchoice);
    // i want the code to keep ask user to enter new choice until user enter valid number//
    while (scanf("%d", &value) != 1) { // 1 = successful, 0 = invalid must run code again //
        char trash[100];
        scanf("%s", trash); // delete wrong user input
        printf("Invalid input. Please enter a whole number: ");
    }
    return value;
}
float getValidFloat(const char *userchoice) {
    float value;
    printf("%s", userchoice);
    // this function is the same as getValidInt but focus on decimal number
    while (scanf("%f", &value) != 1) {
        char trash[100];
        scanf("%s", trash); //delete wrong user input
        printf("Invalid input. Please enter a number: ");
    }
    return value;
}

int findProductIndexById(Product list[], int count, int id, int index) {
    if (index >= count) {
        return -1;
    }
    if (list[index].id == id) {
        return index;
    }
    return findProductIndexById(list, count, id, index + 1);
}

// filter the price range 
void sortLowToHigh(Product list[], int count) {
    Product temporary;
    for ( int i = 0;i< count -1; i++){
        int minIndex = i;
        for (int j= i+1; j<count; j++){
            if ( list[j].price < list[minIndex].price){
                minIndex = j;
            }
        }
        if (minIndex != i){
            temporary = list[i];
            list[i] = list[minIndex];
            list[minIndex] = temporary;
        }
    }
}

void sortHighToLow(Product list[], int count) {
    Product temporary;
    int maxIndex;
    for ( int i = 0;i< count-1; i++){
        maxIndex = i;
        for (int j= i+1; j<count; j++){
            if ( list[j].price > list[maxIndex].price){
                maxIndex = j;
            }
        }
        if (maxIndex != i){
            temporary = list[i];
            list[i] = list[maxIndex];
            list[maxIndex] = temporary;
        }
    }
}

void sellerMenu(void) {
    int choice;
    do {
        printLine();
        printf("                        SELLER INTERFACE\n");
        printLine();
        printf("1. View Inventory\n");
        printf("2. Add New Product\n");
        printf("3. Update Stock Quantity\n");
        printf("4. Remove a Product\n");
        printf("5. View Monthly Sales Report\n");
        printf("0. Back to Main Menu\n");
        choice = getValidInt("Enter your choice: ");

        switch (choice) {
            case 1:
                displayInventory();
                break;

            case 2:
                addProduct();
                break;

            case 3: {
                int id = getValidInt("Enter Product ID to update: ");
                int index = findProductIndexById(inventory, productCount, id, 0);
                if (index == -1) {
                    printf("Product not found.\n");
                } else {
                    int amount = getValidInt("Enter quantity to ADD (use negative to reduce): ");
                    updateProductStock(index, amount);
                }
                break;
            }

            case 4: {
                int id = getValidInt("Enter Product ID to remove: ");
                removeProductById(id);
                break;
            }

            case 5:
                displaySalesReport();
                break;

            case 0:
                printf("Returning to main menu...\n");
                break;

            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 0);
}

void addProduct(void) {
    if (productCount >= MAX_PRODUCTS) {
        printf("Inventory is full! Cannot add more products.\n");
        return;
    }

    Product newProduct;

    newProduct.id = getValidInt("Enter Product ID: ");

    printf("Enter Product Name: ");
    scanf("%s", newProduct.name);

    printf("Enter Category: ");
    scanf("%s", newProduct.category);

    newProduct.price = getValidFloat("Enter Price: $");
    newProduct.stock = getValidInt("Enter Stock Quantity: ");
    newProduct.dateAdded.day   = getValidInt("Enter Day Added (1-31): ");
    newProduct.dateAdded.month = getValidInt("Enter Month Added (1-12): ");
    newProduct.dateAdded.year  = getValidInt("Enter Year Added: ");

    inventory[productCount] = newProduct;
    productCount++;

    printf("\nProduct \"%s\" added successfully!\n", newProduct.name);
}

void updateProductStock(int index, int amount) {
    Product *p = &inventory[index];
    p->stock += amount;
    if (p->stock < 0) {
        p->stock = 0;
    }
    printf("New stock for \"%s\": %d unit(s)\n", p->name, p->stock);
}

void removeProductById(int id) {
    int index = findProductIndexById(inventory, productCount, id, 0);

    if (index == -1) {
        printf("Product not found.\n");
        return;
    }

    // shift everything left to fill the gap after remove the product
    for (int i = index; i < productCount - 1; i++) {
        inventory[i] = inventory[i + 1];
    }
    productCount--;

    printf("Product removed successfully.\n");
}

void displayInventory(void) {
    if (productCount == 0) {
        printf("\nInventory is empty.\n");
        return;
    }

    printf("\n%-5s %-18s %-12s %-8s %-6s %-12s\n",
           "ID", "Name", "Category", "Price", "Stock", "Date Added");
    printLine();

    for (int i = 0; i < productCount; i++) {
        printf("%-5d %-18s %-12s $%-7.2f %-6d %02d/%02d/%04d\n",
            inventory[i].id,
            inventory[i].name,
            inventory[i].category,
            inventory[i].price,
            inventory[i].stock,
            inventory[i].dateAdded.day,
            inventory[i].dateAdded.month,
            inventory[i].dateAdded.year);
    }
}

void displaySalesReport(void) {
    const char *monthNames[MONTHS] = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};

    if (productCount == 0) {
        printf("\nNo products to report.\n");
        return;
    }

    printf("\n%-18s", "Product");
    for (int i = 0; i< MONTHS; i++) {
        printf("%-4s", monthNames[i]);
    }
    printf("| %-6s\n", "Total");
    printLine();
    
    for (int j = 0; j < productCount; j++) {
        int total = 0;
        printf("%-18s", inventory[j].name);
        for (int k = 0; k < MONTHS; k++) {
            printf("%-4d", salesRecord[k][j]);
            total += salesRecord[k][j];
        }
        printf("| %-12d\n", total);
    }
}

void buyerMenu(void) {
    Buyer buyer;
    Cart  cart;
    int   choice;
    char  existingMember;

    cart.itemCount = 0;
    buyer.isMember = 0;

    printf("\n      Welcome to the Buyer Interface!\n");
    printf("Please use underscore (_)instead of space\n");
    printf("Enter your name: ");
    scanf("%s", buyer.name);

    // ask if user already have membership
    printf("\nDo you already have a membership? (y/n): ");
    scanf(" %c", &existingMember);

    if (existingMember == 'y' || existingMember == 'Y') {
        buyer.isMember = 1;
        printf("Welcome back, Member %s! You'll enjoy a 20%% discount.\n", buyer.name);
    } else {
        printf("\nYou are not a member yet.\n");
        registerMembership(&buyer);
    }

    buyer.balance = getValidFloat("\nEnter the amount of money you have: $");

    do {
        printLine();
        printf("                        BUYER INTERFACE\n");
        printf("                        Hello, %s!\n", buyer.name);
        printf("    Balance: $%.2f\n", buyer.balance);
        printf("    Member : %s\n", buyer.isMember ? "Yes (20% discount applies)" : "No");
        printLine();
        printf("1. View All Products\n");
        printf("2. Filter by Price Range\n");
        printf("3. Add Product to Cart\n");
        printf("4. View Cart\n");
        printf("5. Checkout\n");
        printf("6. Register / Cancel Membership\n");
        printf("0. Back to Main Menu\n");
        choice = getValidInt("Enter your choice: ");

        switch (choice) {
            case 1:
                displayProducts(inventory, productCount);
                break;
            case 2:
                filterByPrice();
                break;
            case 3:
                addToCart(&cart);
                break;
            case 4:
                viewCart(&cart);
                break;
            case 5:
                checkout(&cart, &buyer);
                break;
            case 6:
                registerMembership(&buyer);
                break;
            case 0:
                printf("Returning to main menu...\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 0);
}

void registerMembership(Buyer *buyer) {
    printLine();

    if (buyer->isMember == 0) {
        printf("  MEMBERSHIP REGISTRATION\n");
        printLine();
        printf("Benefits of membership:\n");
        printf("  * 20%% discount on every purchase\n");
        printf("  * Exclusive member pricing on all products\n");
        printf("  * Cancel any time from the buyer menu\n");
        printLine();

        char answer;
        printf("Would you like to register as a member? (y/n): ");
        scanf(" %c", &answer);

        if (answer == 'y' || answer == 'Y') {
            buyer->isMember = 1;
            printf("\nCongratulations, %s! You are now a member.\n", buyer->name);
            printf("A 20%% discount will be applied at checkout.\n");
        } else {
            printf("\nNo problem! You can register any time from the menu.\n");
        }
    } else {
        printf("  MEMBERSHIP MANAGEMENT\n");
        printLine();
        printf("You are currently an active member (20%% discount).\n");

        char answer;
        printf("Do you want to CANCEL your membership? (y/n): ");
        scanf(" %c", &answer);

        if (answer == 'y' || answer == 'Y') {
            buyer->isMember = 0;
            printf("\nYour membership has been cancelled, %s.\n", buyer->name);
            printf("You will no longer receive the discount.\n");
        } else {
            printf("\nMembership kept. Enjoy your 20%% discount!\n");
        }
    }

    printLine();
}

void displayProducts(Product list[], int count) {
    if (count == 0) {
        printf("\nNo products available.\n");
        return;
    }

    printf("\n%-5s %-18s %-12s %-8s %-6s\n",
           "ID", "Name", "Category", "Price", "Stock");
    printLine();

    for (int i = 0; i < count; i++) {
        char catUpper[MAX_CAT_LEN];
        strcpy(catUpper, list[i].category);
        toUpperCase(catUpper);
        char ProductUpper[MAX_NAME_LEN];
        strcpy(ProductUpper, list[i].name);
        toUpperCase(ProductUpper);


        printf("%-5d %-18s %-12s $%-7.2f %-6d\n",
               list[i].id, ProductUpper, catUpper,
               list[i].price, list[i].stock);
    }
}

// filter function - just asks how to sort and shows the list
void filterByPrice(void) {
    if (productCount == 0) {
        printf("\nNo products available.\n");
        return;
    }

    // i copy the inventory so i dont mess up the original order
    Product temporaryList[MAX_PRODUCTS];
    for (int i = 0; i < productCount; i++) {
        temporaryList[i] = inventory[i];
    }

    printLine();
    printf("               FILTER BY PRICE\n");
    printLine();
    printf("1. Low to High  (cheapest first)\n");
    printf("2. High to Low  (most expensive first)\n");
    int choice = getValidInt("Enter your choice: ");

    if (choice == 1) {
        sortLowToHigh(temporaryList, productCount);
        printf("\n--- Products: Low to High ---\n");
        displayProducts(temporaryList, productCount);

    } else if (choice == 2) {
        sortHighToLow(temporaryList, productCount);
        printf("\n--- Products: High to Low ---\n");
        displayProducts(temporaryList, productCount);

    } else {
        printf("Invalid choice.\n");
    }
}

void addToCart(Cart *cart) {
    if (cart->itemCount >= MAX_CART_ITEMS) {
        printf("Your cart is full!\n");
        return;
    }

    displayProducts(inventory, productCount);

    int id = getValidInt("\nEnter Product ID to add to cart: ");
    int index = findProductIndexById(inventory, productCount, id, 0);

    if (index == -1) {
        printf("Product not found.\n");
        return;
    }

    int quantity = getValidInt("Enter quantity: ");
    if (quantity <= 0) {
        printf("Quantity must be greater than zero.\n");
        return;
    }
    if (quantity > inventory[index].stock) {
        printf("Not enough stock! Only %d unit(s) left.\n", inventory[index].stock);
        return;
    }

    cart->items[cart->itemCount] = inventory[index];
    cart->quantities[cart->itemCount] = quantity;
    cart->itemCount++;

    printf("\"%s\" x%d added to cart.\n", inventory[index].name, quantity);
}

void viewCart(Cart *cart) {
    if (cart->itemCount == 0) {
        printf("\nYour cart is empty.\n");
        return;
    }

    printf("\n--- YOUR CART ---\n");
    for (int i = 0; i < cart->itemCount; i++) {
        printf("%2d x %-18s @ $%-6.2f = $%.2f\n",
               cart->quantities[i],
               cart->items[i].name,
               cart->items[i].price,
               cart->items[i].price * cart->quantities[i]);
    }
    printf("Subtotal: $%.2f\n", calculateCartTotal(cart));
}

float calculateCartTotal(Cart *cart) {
    float total = 0.0f;
    for (int i = 0; i < cart->itemCount; i++) {
        total += cart->items[i].price * cart->quantities[i];
    }
    return total;
}

// members get 20% off
float applyMembershipDiscount(float total, int isMember) {
    if (isMember) {
        return total * 0.80f;
    }
    return total;
}

int hasEnoughMoney(float balance, float total) {
    return balance >= total;
}

void processPurchase(Cart *cart) {
    int currentMonth = 6;

    for (int i = 0; i < cart->itemCount; i++) {
        int index = findProductIndexById(inventory, productCount, cart->items[i].id, 0);
        if (index != -1) {
            inventory[index].stock -= cart->quantities[i];
            if (inventory[index].stock < 0) {
                inventory[index].stock = 0;
            }
            if (cart->quantities[i] > 0) {
                salesRecord[currentMonth - 1][index] += cart->quantities[i];
            }
        }
    }
}

void printReceipt(Cart *cart, Buyer *buyer, float finalPrice) {
    printf("\n============ RECEIPT ============\n");
    printf("Buyer   : %s\n", buyer->name);
    printf("Member  : %s\n", buyer->isMember ? "Yes" : "No");
    printLine();
    for (int i = 0; i < cart->itemCount; i++) {
        printf("%2d x %-18s $%.2f\n",
               cart->quantities[i],
               cart->items[i].name,
               cart->items[i].price * cart->quantities[i]);
    }
    printLine();
    printf("Amount Paid       : $%.2f\n", finalPrice);
    printf("Remaining Balance : $%.2f\n", buyer->balance);
    printf("==================================\n");
    printf("Thank you for shopping with us!\n");
}

void checkout(Cart *cart, Buyer *buyer) {
    if (cart->itemCount == 0) {
        printf("\nYour cart is empty. Nothing to checkout.\n");
        return;
    }

    float subtotal   = calculateCartTotal(cart);
    float finalPrice = applyMembershipDiscount(subtotal, buyer->isMember);

    printf("\nSubtotal           : $%.2f\n", subtotal);
    if (buyer->isMember) {
        printf("Membership Discount: -$%.2f (20%%)\n", subtotal - finalPrice);
    }
    printf("Total to Pay       : $%.2f\n", finalPrice);
    printf("Your Balance       : $%.2f\n", buyer->balance);

    if (hasEnoughMoney(buyer->balance, finalPrice)) {
        buyer->balance -= finalPrice;
        processPurchase(cart);
        printReceipt(cart, buyer, finalPrice);
        cart->itemCount = 0; // clear cart after buying
    } else {
        printf("\nInsufficient funds! You need $%.2f more.\n", finalPrice - buyer->balance);
        printf("Purchase cancelled. Please remove items or add more money.\n");
    }
}