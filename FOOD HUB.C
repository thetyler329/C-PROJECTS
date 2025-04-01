#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITEMS 10
#define TAX_RATE 0.07
#define MAX_NAME 50

struct MenuItem {
    int code;
    char name[MAX_NAME];
    float price;
};

struct Order {
    struct MenuItem items[MAX_ITEMS];
    int quantities[MAX_ITEMS];
    int itemCount;
    float subtotal;
    float tax;
    float total;
};

struct MenuItem menu[] = {
    {101, "Burger", 9.99},
    {102, "Pizza", 12.99},
    {103, "Salad", 7.99},
    {104, "Fries", 4.99},
    {105, "Soda", 2.99}
};

void displayMenu() {
    printf("\n=== MENU ===\n");
    for(int i = 0; i < sizeof(menu)/sizeof(menu[0]); i++) {
        printf("%d - %s: $%.2f\n", menu[i].code, menu[i].name, menu[i].price);
    }
    printf("===========\n");
}

struct MenuItem* findMenuItem(int code) {
    for(int i = 0; i < sizeof(menu)/sizeof(menu[0]); i++) {
        if(menu[i].code == code) {
            return &menu[i];
        }
    }
    return NULL;
}

void calculateTotal(struct Order* order) {
    order->subtotal = 0;
    for(int i = 0; i < order->itemCount; i++) {
        order->subtotal += order->items[i].price * order->quantities[i];
    }
    order->tax = order->subtotal * TAX_RATE;
    order->total = order->subtotal + order->tax;
}

void printReceipt(struct Order* order) {
    printf("\n=== RECEIPT ===\n");
    for(int i = 0; i < order->itemCount; i++) {
        printf("%s x%d: $%.2f\n", 
               order->items[i].name, 
               order->quantities[i],
               order->items[i].price * order->quantities[i]);
    }
    printf("-------------\n");
    printf("Subtotal: $%.2f\n", order->subtotal);
    printf("Tax (7%%): $%.2f\n", order->tax);
    printf("Total: $%.2f\n", order->total);
    printf("=============\n");
}

int main() {
    struct Order order = {0};
    int code, quantity;
    char continue_order;

    printf("Welcome to Food Ordering System\n");

    do {
        displayMenu();
        printf("\nEnter item code: ");
        scanf("%d", &code);

        struct MenuItem* item = findMenuItem(code);
        if(item == NULL) {
            printf("Invalid item code!\n");
            continue;
        }

        printf("Enter quantity: ");
        scanf("%d", &quantity);

        if(quantity <= 0) {
            printf("Invalid quantity!\n");
            continue;
        }

        if(order.itemCount >= MAX_ITEMS) {
            printf("Maximum order size reached!\n");
            break;
        }

        order.items[order.itemCount] = *item;
        order.quantities[order.itemCount] = quantity;
        order.itemCount++;

        printf("Add another item? (y/n): ");
        scanf(" %c", &continue_order);

    } while(continue_order == 'y' || continue_order == 'Y');

    calculateTotal(&order);
    printReceipt(&order);

    return 0;
}