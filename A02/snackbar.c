/***************************************************
 * Author: 
 * 
 */
#include <stdio.h>
#include <string.h>

typedef struct snack {
    char name[64];
    float cost;
    int quantity;
} snack;

snack stock[3];
int stockSize = sizeof(stock) / sizeof(stock[0]);

void setup(snack stock[]) {
    strcpy(stock[0].name, "baguette");
    stock[0].cost = 4.50f;
    stock[0].quantity = 5;

    strcpy(stock[1].name, "leek");
    stock[1].cost = 12.25f;
    stock[1].quantity = 2;

    strcpy(stock[2].name, "gummies");
    stock[2].cost = 2.0f;
    stock[2].quantity = 0;
}

void printSnacks(snack stock[]) {
    printf("%d", stockSize);
    for (int i = 0; i < stockSize ; i++) {
        printf("\n%d) ", i);
        printf("%-12s\t", stock[i].name);
        printf("cost: $%-.2f\t", stock[i].cost);
        printf("quantity: %d", stock[i].quantity);
    }
}

float sell(snack choice, float bank) {
    if (choice.quantity == 0) {
        printf("\nSorry, we are out of %s\n", choice.name);
    } else if (choice.cost > bank) {
        printf("\nYou can't afford it!\n");
     }  else {
          printf("\nYou bought %s", choice.name);
          bank = bank - choice.cost;
          printf("\nYou have %-.2f left\n", bank);
             }
    return bank;
}

int main() {
    setup(stock);
    float wallet;
    int snackNum;
    printf("Welcome to Steven Struct's Snack Bar.\n");
    printf("\nHow much money do you have?  $");
    scanf("%f", &wallet);
    
    printSnacks(stock);
    printf("\nWhat snack would you like to buy? [0,1,2] ");
    scanf("%d", &snackNum);
    wallet =  sell(stock[snackNum], wallet); //check price and quantity, deliver appropriate message. 
 return 0;
}
