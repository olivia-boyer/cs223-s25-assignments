/*----------------------------------------------
 * Author: Olivia Boyer 
 * Date: 02/07/2025
 * Description: Lets user create a snackbar by
 * inputting snack information. Then prints the snackbar.
 ---------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct snack {

    char name[64];
    float cost;
    int quantity;

} snack;

/**
* Adds a new snack to the array stock.
* @param idx The index of array to set
* @param stock pointer to snack array
*/
void addSnack(int idx, snack* stock) {

    printf("\nEnter a name: ");
    scanf("%s", stock[idx].name);

    printf("\nEnter a cost: ");
    scanf("%f", &stock[idx].cost);

    printf("\nEnter a quantity: ");
    scanf("%d",&stock[idx].quantity); 
}

/**
* Prints the snackbar
* @param num The number of snacks in array
* @param stock The array to be printed
*/
void printSnacks(int num, snack* stock) {
    
    for (int i = 0; i < num; i++) {
        printf("\n%d) ", i);
        printf("%-12s\t", stock[i].name);
        printf("cost: $%-.2f\t", stock[i].cost);
        printf("quantity: %d", stock[i].quantity);
    }
}    
 
int main() {

    int snackSize = sizeof(snack);
    printf("Enter a number of snacks: ");

    int numSnacks;
    scanf("%d", &numSnacks);
    
    snack* stock;
    stock = ((snack*)malloc((numSnacks * snackSize)));

    for (int i = 0; i < numSnacks; i++) {

        addSnack(i, stock);

    }    
    printf("\nWelcome to Dynamic Donna's Snack Bar!\n");
  
    printSnacks(numSnacks, stock);
    printf("\n");
  
    free(stock);

    return 0;
}
