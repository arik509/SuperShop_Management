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