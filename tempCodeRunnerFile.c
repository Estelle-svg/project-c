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