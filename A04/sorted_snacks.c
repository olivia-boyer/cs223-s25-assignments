/*----------------------------------------------
 * Author: 
 * Date: 
 * Description
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>


typedef struct snack {
    char name[64];
    float cost;
    int quantity;
} snack;

typedef struct snackNode {
    snack val;
    struct snackNode* next;
} snackNode;

void insertFront (snack data, snackNode** head) {
    snackNode* newNode = (snackNode*)malloc(sizeof(snackNode));
    if (newNode == NULL) {
        printf("Error: out of space\n");
        exit(1);
    }
    newNode->val = data;
    newNode->next = *head;
    *head = newNode;
}

void clear (snackNode** head) {
    snackNode* nextNode = (*head)->next;
    while (nextNode != NULL) {
        free(*head);
        *head = nextNode;
    }
        
}

void printList (int size, snackNode** head) {
    snackNode* ptr = *head;
    for (int i = 0; i < size; i++) {
        printf("\n%d) ", i);
        printf("%-12s\t", ptr->val.name);
        printf("cost: $%-.2f\t", ptr->val.cost);
        printf("quantity: %d", ptr->val.quantity);
        printf("\n");
        ptr = ptr->next;
    }
}

void sortCost() {
}

void sortQuantity() {
}

void sortName() {
}

void getSnacks(int num, snackNode** head) {
    snack newSnack;
    for (int i = 0; i < num; i++) {
        printf("Enter a name: ");
        scanf("%s", newSnack.name);
        printf("\nEnter a cost: ");
        scanf("%f", &newSnack.cost);
        printf("\nEnter a quantity: ");
        scanf("%d", &newSnack.quantity);
        insertFront(newSnack, head);
    }
}

int main() {
    int numSnacks;
    printf("Enter a number of snacks: ");
    scanf("%d", &numSnacks);
    snackNode* head = NULL;
    getSnacks(numSnacks, &head);
    printList(numSnacks, &head);
    //`clear(&head);
  return 0;
}
