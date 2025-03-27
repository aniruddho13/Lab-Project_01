#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ORDERS 100
#define MAX_ITEMS 7
#define MAX_ITEM_NAME 20
#define MAX_ORDER_ITEMS 10

typedef struct {
    char itemName[MAX_ITEM_NAME];
    float price; // Price in Taka
} MenuItem;

typedef struct {
    int orderId;
    char items[MAX_ORDER_ITEMS][MAX_ITEM_NAME];
    int quantity[MAX_ORDER_ITEMS];
    int itemCount;
    float totalAmount; // Total amount in Taka
    char paymentMethod;
} Order;

MenuItem menu[MAX_ITEMS] = {
    {"Burger", 80.0},
    {"Sandwich", 60.0},
    {"Hot Dog", 110.0},
    {"Pasta", 100.0},
    {"Momo", 70.0},
    {"Shawarma", 90.0},
    {"Drinks", 30.0}
};

Order orders[MAX_ORDERS];
int orderCount = 0;

void displayMenu() {
    printf("\n--- Restaurant Menu (Prices in Taka) ---\n");
    for (int i = 0; i < MAX_ITEMS; i++) {
        printf("%d. %-10s: %.2f Taka\n", i + 1, menu[i].itemName, menu[i].price);
    }
    printf("\n");
}

void takeOrder() {
    if (orderCount >= MAX_ORDERS) {
        printf("Maximum order limit reached.\n");
        return;
    }

    Order newOrder;
    newOrder.orderId = orderCount + 1;
    newOrder.itemCount = 0;
    newOrder.totalAmount = 0;

    printf("--- Place Your Order (Prices in Taka) ---\n");
    displayMenu();

    int choice, quantity;
    char input[100];

    while (1) {
        printf("Enter item number (0 to finish): ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("Error reading input.\n");
            return;
        }
        input[strcspn(input, "\n")] = 0; // Remove newline character

        if (sscanf(input, "%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            continue;
        }

        if (choice == 0) {
            break;
        }

        if (choice < 1 || choice > MAX_ITEMS) {
            printf("Invalid item number.\n");
            continue;
        }

        printf("Enter quantity: ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("Error reading input.\n");
            return;
        }
        input[strcspn(input, "\n")] = 0;

        if (sscanf(input, "%d", &quantity) != 1) {
            printf("Invalid input. Please enter a number.\n");
            continue;
        }

        if (newOrder.itemCount < MAX_ORDER_ITEMS) {
            strcpy(newOrder.items[newOrder.itemCount], menu[choice - 1].itemName);
            newOrder.quantity[newOrder.itemCount] = quantity;
            newOrder.totalAmount += menu[choice - 1].price * quantity;
            newOrder.itemCount++;
        } else {
            printf("Maximum items per order reached.\n");
            break;
        }
    }

    printf("Total Amount: %.2f Taka\n", newOrder.totalAmount);

    while (1) {
        printf("Payment Method (C for Cash, O for Online): ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("Error reading input.\n");
            return;
        }
        input[strcspn(input, "\n")] = 0;

        if (sscanf(input, "%c", &newOrder.paymentMethod) == 1) {
            if (newOrder.paymentMethod == 'C' || newOrder.paymentMethod == 'O') {
                break;
            } else {
                printf("Invalid payment method. Enter 'C' for Cash or 'O' for Online.\n");
            }
        } else {
            printf("Invalid input.\n");
        }
    }

    orders[orderCount++] = newOrder;
    printf("Order placed successfully. Order ID: %d\n", newOrder.orderId);
    printf("Thank you for your order!\n");
}

void viewOrders() {
    if (orderCount == 0) {
        printf("No orders to display.\n");
        return;
    }

    printf("\n--- Orders ---\n");
    for (int i = 0; i < orderCount; i++) {
        printf("Order ID: %d\n", orders[i].orderId);
        printf("Items:\n");
        for (int j = 0; j < orders[i].itemCount; j++) {
            printf("  - %s (%d)\n", orders[i].items[j], orders[i].quantity[j]);
        }
        printf("Total Amount: %.2f Taka\n", orders[i].totalAmount);
        printf("Payment Method: %c\n", orders[i].paymentMethod);
        printf("--------------\n");
    }
}

int main() {
    int choice;
    char input[100];

    do {
        printf("\n--- Restaurant Management System ---\n");
        printf("1. View Menu\n");
        printf("2. Place Order\n");
        printf("3. View Orders\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");

        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("Error reading input.\n");
            continue;
        }
        input[strcspn(input, "\n")] = 0;

        if (sscanf(input, "%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            choice = 0;
            continue;
        }

        switch (choice) {
            case 1:
                displayMenu();
                break;
            case 2:
                takeOrder();
                break;
            case 3:
                viewOrders();
                break;
            case 4:
                printf("Thank you for using the system!\n");
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (1);

    return 0;
}

