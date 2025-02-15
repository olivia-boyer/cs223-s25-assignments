/*----------------------------------------------
 * Author: 
 * Date: 
 * Description
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void clear (snackNode* head) {         //Borken :(
    if (head == NULL) {
        return;
    }
    snackNode* nextNode = (head)->next;
    free(head);
    clear(nextNode);    
}

void printList (int size, snackNode** head) {
    snackNode* ptr = *head;
    int i = 0;
    while (ptr != NULL) {
        printf("\n%d) ", i);
        printf("%-12s\t", ptr->val.name);
        printf("cost: $%-.2f\t", ptr->val.cost);
        printf("quantity: %d", ptr->val.quantity);
        printf("\n");
        ptr = ptr->next;
        i += 1;
    }
}

snackNode* split(snackNode* head) {
    snackNode* end = head;
    snackNode* middle = head;

    while (end != NULL && end->next != NULL) {
        end = end->next->next;
        if (end != NULL) {
        middle = middle->next;
        }
    }
    snackNode* temp = middle->next;
    middle->next = NULL;
    return temp;
}
    

snackNode* mergeCost(snackNode* headOne, snackNode* headTwo) {
    if (headOne == NULL) {
        return headTwo;
    }
    if (headTwo == NULL) {
        return headOne; 
    }

    if ((headOne->val).cost < (headTwo->val).cost) {
        headOne->next = mergeCost(headOne->next, headTwo);
        return headOne;
    } 
        headTwo->next = mergeCost(headOne, headTwo->next);
        return headTwo;
    
}

snackNode* sortCost(snackNode* head) {
    if (head == NULL || head->next == NULL) {
    return head;
    }

    snackNode* secondHalf = split(head);
    head = sortCost(head);
    secondHalf = sortCost(secondHalf);

    head = mergeCost(head, secondHalf);
    return head;
}

snackNode* mergeQuantity(snackNode* headOne, snackNode* headTwo) {
    if (headOne == NULL) {
        return headTwo;
    }
    if (headTwo == NULL) {
        return headOne; 
    }

    if ((headOne->val).quantity < (headTwo->val).quantity) {
        headOne->next = mergeQuantity(headOne->next, headTwo);
        return headOne;
    } 
        headTwo->next = mergeQuantity(headOne, headTwo->next);
        return headTwo;
    
}

snackNode* sortQuantity(snackNode* head) {
    if (head == NULL || head->next == NULL) {
    return head;
    }

    snackNode* secondHalf = split(head);
    head = sortQuantity(head);
    secondHalf = sortQuantity(secondHalf);

    head = mergeQuantity(head, secondHalf);
    return head;
}

//checks if the first string is alphabetically before second
int firstIsFirst(char* stringOne, char* stringTwo) {
    char* shorty;
    if (strlen(stringOne) < strlen(stringTwo)) {
        shorty = stringOne;
    } else {
        shorty = stringTwo;
    }
    
   for (int i =0; i < strlen(shorty); i++) {
        if (stringOne[i] < stringTwo[i]) {
            return 1;
        } else if (stringTwo[i] < stringOne[i]) {
            return 0;
        }
    }
    
    return (shorty == stringOne);
}


snackNode* mergeName(snackNode* headOne, snackNode* headTwo) {
    if (headOne == NULL) {
        return headTwo;
    }
    if (headTwo == NULL) {
        return headOne; 
    }

    if (firstIsFirst((headOne->val).name, (headTwo->val).name)) {
        headOne->next = mergeName(headOne->next, headTwo);
        return headOne;
    } 
        headTwo->next = mergeName(headOne, headTwo->next);
        return headTwo;
    
}


snackNode* sortName(snackNode* head) {
    if (head == NULL || head->next == NULL) {
    return head;
    }

    snackNode* secondHalf = split(head);
    head = sortName(head);
    secondHalf = sortName(secondHalf);

    head = mergeName(head, secondHalf);
    return head;
}


void getSnacks(int num, snackNode** head) {
    snack newSnack;
    for (int i = 0; i < num; i++) {
        printf("\nEnter a name: ");
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
    head = sortName(head);
    printf("Welcome to Sorted Sally's Snackbar!\n");
    printList(numSnacks, &head);
    clear(head);
  return 0;
}
