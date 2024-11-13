#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Item {
    int id;
    char name[50];
    float price;
    int quantity;
    char category[30];
    struct Item* next;
} Item;

typedef struct Customer {
    int id;
    char name[50];
    int totalPoints;
    struct Customer* next;
} Customer;

Item* inventoryHead = NULL;
Customer* customerHead = NULL;
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
    while (getchar() != '\n');
}

// Function to add an item to inventory
void addItem() {
    Item* newItem = (Item*)malloc(sizeof(Item));
    if (newItem == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    newItem->id = ++itemCount;
    printf("\nEnter item name: ");
    scanf(" %[^\n]%*c", newItem->name);
    printf("Enter item price: ");
    scanf("%f", &newItem->price);
    printf("Enter item quantity: ");
    scanf("%d", &newItem->quantity);
    printf("Enter item category: ");
    scanf(" %[^\n]%*c", newItem->category);
    newItem->next = inventoryHead;
    inventoryHead = newItem;

    printf("\nItem added successfully with ID %d\n", newItem->id);
}

// Function to display all items
void displayItems() {
    if (inventoryHead == NULL) {
        printf("\nNo items in inventory.\n");
        return;
    }

    printf("\n--- Inventory ---\n");
    Item* current = inventoryHead;
    while (current != NULL) {
        printf("ID: %d | Name: %-20s | Price: %.2f | Quantity: %d | Category: %s\n",
               current->id, current->name, current->price, current->quantity, current->category);
        current = current->next;
    }
}

// Function to search item by ID
Item* searchItem(int id) {
    Item* current = inventoryHead;
    while (current != NULL) {
        if (current->id == id) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Function to search customer by ID
Customer* searchCustomer(int id) {
    Customer* current = customerHead;
    while (current != NULL) {
        if (current->id == id) {
            return current;
        }
        current = current->next;
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
    clearInputBuffer();

    Item* current = inventoryHead;
    switch (choice) {
        case 1:
            printf("Enter name to search: ");
            scanf(" %[^\n]%*c", name);
            while (current != NULL) {
                if (strstr(current->name, name) != NULL) {
                    printf("Found - ID: %d | Name: %-20s | Price: %.2f | Quantity: %d\n",
                           current->id, current->name, current->price, current->quantity);
                }
                current = current->next;
            }
            break;
        case 2:
            printf("Enter category to search: ");
            scanf(" %[^\n]%*c", category);
            while (current != NULL) {
                if (strcmp(current->category, category) == 0) {
                    printf("Found - ID: %d | Name: %-20s | Price: %.2f | Quantity: %d\n",
                           current->id, current->name, current->price, current->quantity);
                }
                current = current->next;
            }
            break;
        case 3:
            printf("Enter min price: ");
            scanf("%f", &minPrice);
            printf("Enter max price: ");
            scanf("%f", &maxPrice);
            while (current != NULL) {
                if (current->price >= minPrice && current->price <= maxPrice) {
                    printf("Found - ID: %d | Name: %-20s | Price: %.2f | Quantity: %d\n",
                           current->id, current->name, current->price, current->quantity);
                }
                current = current->next;
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
        int points = (int)(purchaseAmount / 10);
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

// Main owner menu
void ownerMenu() {
    // ... other owner menu functions
}

// Main customer menu
void customerMenu() {
    // ... other customer menu functions
}

// Main function to run the system
int main() {
    int choice;

    while (1) {
        printf("\n--- Shop Management System ---\n");
        printf("1. Customer 2. Owner\n\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        clearInputBuffer();

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

