#include <string.h>
#include <stdio.h>
#include <stdlib.h>



typedef struct Node {
    char letter;
    struct Node* next;
} Node;


void insertFront (char input, Node** head) {
      Node* newNode = (Node*)malloc(sizeof(Node));
      if (newNode == NULL) {
          printf("Error: out of space\n");
          exit(1);
     }
      newNode->letter = input;
      newNode->next = *head;
      *head = newNode;
}

void printList (Node** head) {
    Node* ptr = *head;
    while (ptr != NULL) {

        printf("%c", ptr->letter);
        ptr = ptr->next;
    }
}

void clear (Node* head) {
    if (head == NULL) {
        return;
    }
    Node* nextNode = (head)->next;
    free(head);
    clear(nextNode);
}


int main()
{
    char* word = (char*)malloc(sizeof(char) * 32);

    if (word == NULL) {
        printf("memory error");
        exit(1);
    }

    printf("Enter a word: ");
    scanf("%s", word);
    int len = strlen(word);
    Node* head = NULL;

    char rem = 'a';
    printf("Enter a character to remove: ");
    scanf(" %c", &rem);

    for (int i = len - 1; i >= 0; i--) {
        if (word[i] != rem) {

            insertFront(word[i], &head);

        }   
    }
    printf("\n");
    printList(&head);
    printf("\n");
    free(word);
    clear(head);

    return 0;
}
