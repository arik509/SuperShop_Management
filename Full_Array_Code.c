#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include <time.h>

#define MAX_ITEMS 100
#define MAX_CUSTOMERS 50

typedef struct {
    int id;
    char name[50];
    float price;
    int quantity;
    char category[30];
} Item;

typedef struct {
    int id;
    char name[50];
    int totalPoints;
} Customer;

Item inventory[MAX_ITEMS];
Customer customers[MAX_CUSTOMERS];
int itemCount = 0;
int customerCount = 0;

// Function Prototypes
void addItem();
void displayItems();
Item* searchItem(int id);
Customer* searchCustomer(int id);
void advancedSearch();
void returnItem(int itemId, int quantity);
void applyLoyaltyPoints(int customerId, float purchaseAmount);
void addExpense(float amount, const char* description);
void monthlySalesReport();
void displaySalesGraph(int* monthlySales, int months);
void ownerMenu();
void customerMenu();
void viewProducts();
void searchProducts();
void makePurchase(int customerId, int itemId, int quantity);
void clearInputBuffer();

// Function to clear input buffer after reading input
void clearInputBuffer() {
    while(getchar() != '\n');  // Discard any remaining characters in the buffer
}

// Function to add an item to inventory
void addItem() {
    if (itemCount >= MAX_ITEMS) {
        printf("Inventory full, cannot add more items.\n");
        return;
    }
    Item newItem;
    newItem.id = itemCount + 1;
    printf("\nEnter item name: ");
    scanf(" %[^\n]%*c", newItem.name);
    printf("Enter item price: ");
    scanf("%f", &newItem.price);
    printf("Enter item quantity: ");
    scanf("%d", &newItem.quantity);
    printf("Enter item category: ");
    scanf(" %[^\n]%*c", newItem.category);

    inventory[itemCount++] = newItem;
    printf("\nItem added successfully with ID %d\n", newItem.id);
}

// Function to display all items
void displayItems() {
    if (itemCount == 0) {
        printf("\nNo items in inventory.\n");
        return;
    }
    printf("\n--- Inventory ---\n");
    for (int i = 0; i < itemCount; i++) {
        printf("ID: %d | Name: %-20s | Price: %.2f | Quantity: %d | Category: %s\n",
               inventory[i].id, inventory[i].name, inventory[i].price, inventory[i].quantity, inventory[i].category);
    }
}

// Function to search item by ID
Item* searchItem(int id) {
    for (int i = 0; i < itemCount; i++) {
        if (inventory[i].id == id) {
            return &inventory[i];
        }
    }
    return NULL;
}

// Function to search customer by ID
Customer* searchCustomer(int id) {
    for (int i = 0; i < customerCount; i++) {
        if (customers[i].id == id) {
            return &customers[i];
        }
    }
    return NULL;
}

// Function for advanced search
void advancedSearch() {
    int choice;
    char name[50], category[30];
    float minPrice, maxPrice;

    printf("\n--- Advanced Search ---\n");
    printf("1. Search by Name\n2. Search by Category\n3. Search by Price Range\n");
    printf("Enter search type: ");
    scanf("%d", &choice);
    clearInputBuffer();  // Clear buffer after input

    switch (choice) {
        case 1:
            printf("Enter name to search: ");
            scanf(" %[^\n]%*c", name);
            for (int i = 0; i < itemCount; i++) {
                if (strstr(inventory[i].name, name) != NULL) {
                    printf("Found - ID: %d | Name: %-20s | Price: %.2f | Quantity: %d\n",
                           inventory[i].id, inventory[i].name, inventory[i].price, inventory[i].quantity);
                }
            }
            break;
        case 2:
            printf("Enter category to search: ");
            scanf(" %[^\n]%*c", category);
            for (int i = 0; i < itemCount; i++) {
                if (strcmp(inventory[i].category, category) == 0) {
                    printf("Found - ID: %d | Name: %-20s | Price: %.2f | Quantity: %d\n",
                           inventory[i].id, inventory[i].name, inventory[i].price, inventory[i].quantity);
                }
            }
            break;
        case 3:
            printf("Enter min price: ");
            scanf("%f", &minPrice);
            printf("Enter max price: ");
            scanf("%f", &maxPrice);
            for (int i = 0; i < itemCount; i++) {
                if (inventory[i].price >= minPrice && inventory[i].price <= maxPrice) {
                    printf("Found - ID: %d | Name: %-20s | Price: %.2f | Quantity: %d\n",
                           inventory[i].id, inventory[i].name, inventory[i].price, inventory[i].quantity);
                }
            }
            break;
        default:
            printf("Invalid choice.\n");
    }
}

// Function to handle item returns
void returnItem(int itemId, int quantity) {
    Item* item = searchItem(itemId);
    if (item != NULL && quantity > 0) {
        item->quantity += quantity;
        printf("\nReturn processed: %d of %s returned to inventory.\n", quantity, item->name);
    } else {
        printf("\nReturn failed: Invalid quantity or item not found.\n");
    }
}

// Function to apply loyalty points
void applyLoyaltyPoints(int customerId, float purchaseAmount) {
    Customer* customer = searchCustomer(customerId);
    if (customer != NULL) {
        int points = (int)(purchaseAmount / 10); // 1 point per $10 spent
        customer->totalPoints += points;
        printf("\n%d points added to %s's account. Total points: %d\n", points, customer->name, customer->totalPoints);
    } else {
        printf("\nCustomer not found.\n");
    }
}

// Function to add expense
void addExpense(float amount, const char* description) {
    FILE* file = fopen("expenses.txt", "a");
    if (file != NULL) {
        fprintf(file, "%.2f - %s\n", amount, description);
        fclose(file);
        printf("\nExpense recorded: %.2f for %s\n", amount, description);
    } else {
        printf("\nError recording expense.\n");
    }
}

// Function to generate monthly sales report
void monthlySalesReport() {
    printf("\n--- Monthly Sales Report ---\n");
    printf("This feature would typically aggregate sales data.\n");
}

// Function to display sales graph
void displaySalesGraph(int* monthlySales, int months) {
    printf("\n--- Sales Graph ---\n");
    for (int i = 0; i < months; i++) {
        printf("Month %d: ", i + 1);
        for (int j = 0; j < monthlySales[i] / 1000; j++) {
            printf("*");
        }
        printf("\n");
    }
}

// Owner Menu
void ownerMenu() {
    int choice;

    while (1) {
        printf("\n--- Owner Menu ---\n");
        printf("1. Add Item\n2. Display Items\n3. Advanced Search\n4. Handle Returns\n5. Add Expense\n");
        printf("6. Generate Monthly Sales Report\n7. View Sales Graph\n8. Apply Loyalty Points\n9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        clearInputBuffer();  // Clear buffer after input

        switch (choice) {
            case 1:
                addItem();
                break;
            case 2:
                displayItems();
                break;
            case 3:
                advancedSearch();
                break;
            case 4:
                {
                    int itemId, quantity;
                    printf("Enter item ID to return: ");
                    scanf("%d", &itemId);
                    printf("Enter quantity to return: ");
                    scanf("%d", &quantity);
                    returnItem(itemId, quantity);
                }
                break;
            case 5:
                {
                    float amount;
                    char description[100];
                    printf("Enter expense amount: ");
                    scanf("%f", &amount);
                    printf("Enter expense description: ");
                    scanf(" %[^\n]%*c", description);
                    addExpense(amount, description);
                }
                break;
            case 6:
                monthlySalesReport();
                break;
            case 7:
                {
                    int salesData[12] = {5000, 10000, 15000, 20000, 25000, 30000, 35000, 40000, 45000, 50000, 55000, 60000};
                    displaySalesGraph(salesData, 12);
                }
                break;
            case 8:
                {
                    int customerId;
                    float purchaseAmount;
                    printf("Enter customer ID: ");
                    scanf("%d", &customerId);
                    printf("Enter purchase amount: ");
                    scanf("%f", &purchaseAmount);
                    applyLoyaltyPoints(customerId, purchaseAmount);
                }
                break;
            case 9:
                printf("\nExiting Owner Menu.\n");
                return;
            default:
                printf("\nInvalid choice. Please try again.\n");
        }
    }
}

// Customer Menu
void customerMenu() {
    int choice;

    while (1) {
        printf("\n--- Customer Menu ---\n");
        printf("1. View Products\n2. Search Products\n3. Make Purchase\n4. View Loyalty Points\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        clearInputBuffer();  // Clear buffer after input

        switch (choice) {
            case 1:
                viewProducts();
                break;
            case 2:
                searchProducts();
                break;
            case 3:
                {
                    int customerId, itemId, quantity;
                    printf("Enter customer ID: ");
                    scanf("%d", &customerId);
                    printf("Enter item ID: ");
                    scanf("%d", &itemId);
                    printf("Enter quantity: ");
                    scanf("%d", &quantity);
                    makePurchase(customerId, itemId, quantity);
                }
                break;
            case 4:
                {
                    int customerId;
                    printf("Enter customer ID: ");
                    scanf("%d", &customerId);
                    Customer* customer = searchCustomer(customerId);
                    if (customer != NULL) {
                        printf("\nCustomer %s has %d loyalty points.\n", customer->name, customer->totalPoints);
                    } else {
                        printf("\nCustomer not found.\n");
                    }
                }
                break;
            case 5:
                printf("\nExiting Customer Menu.\n");
                return;
            default:
                printf("\nInvalid choice. Please try again.\n");
        }
    }
}

// Function to view products (for customers)
void viewProducts() {
    if (itemCount == 0) {
        printf("\nNo items available.\n");
        return;
    }
    printf("\n--- Products ---\n");
    for (int i = 0; i < itemCount; i++) {
        printf("ID: %d | Name: %-20s | Price: %.2f | Quantity: %d\n",
               inventory[i].id, inventory[i].name, inventory[i].price, inventory[i].quantity);
    }
}

// Function to search for products (for customers)
void searchProducts() {
    int choice;
    printf("\n--- Search Products ---\n");
    printf("1. Search by Name\n2. Search by Category\n3. Search by Price Range\n");
    printf("Enter search type: ");
    scanf("%d", &choice);
    clearInputBuffer();  // Clear buffer after input

    switch (choice) {
        case 1:
            advancedSearch();
            break;
        case 2:
            advancedSearch();
            break;
        case 3:
            advancedSearch();
            break;
        default:
            printf("\nInvalid search choice.\n");
    }
}

// Function to make a purchase (for customers)
void makePurchase(int customerId, int itemId, int quantity) {
    Item* item = searchItem(itemId);
    if (item == NULL || item->quantity < quantity) {
        printf("\nPurchase failed: Item not found or insufficient quantity.\n");
        return;
    }

    float purchaseAmount = item->price * quantity;
    item->quantity -= quantity;
    applyLoyaltyPoints(customerId, purchaseAmount);
    printf("\nPurchase successful! Total amount: %.2f\n", purchaseAmount);
}

// Main function to run the system
int main() {
    int choice;

    while (1) {
        printf("\n--- Shop Management System ---\n");
        printf("1. Customer                                   2. Owner\n\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        clearInputBuffer();  // Clear buffer after input

        switch (choice) {
            case 1:
                customerMenu();
                break;
            case 2:
                ownerMenu();
                break;
            default:
                printf("\nInvalid choice. Please try again.\n");
        }
    }

    return 0;
}
