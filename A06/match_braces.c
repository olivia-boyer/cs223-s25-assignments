#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct braceNode {
    int rowNum;
    int colNum;
    struct braceNode* next;
} braceNode;

void push (int row, int col, braceNode** head) {
    braceNode* newNode = (braceNode*)malloc(sizeof(braceNode));
    if (newNode == NULL) {
        printf("error: out of space\n");
        exit(1);
    }
    newNode->rowNum = row;
    newNode->colNum = col;
    newNode->next = *head;
    *head = newNode;
}

void pop (braceNode** head, int row, int col) {
    if (*head == NULL) {
        return;
    }
    printf("Found matching braces: (%d, %d) -> (%d, %d)\n", (*head)->rowNum,
        (*head)->colNum, row, col); 
    
    braceNode* newHead = (*head)->next;
    free(*head);
    *head = newHead;
        
}

void clear (braceNode* head) {
    if (head == NULL) {
        return;
    }
    printf("Unmatched brace on Line %d and Column %d\n",head->rowNum, 
        head->colNum);
    braceNode* nextNode = (head)->next;
    free(head);
    clear(nextNode);
}

void printList (braceNode* head) {
}

int main(int argc, char** argv)
{
    int row, col;
    braceNode* head = NULL;
    FILE* input;
    input = fopen(argv[1], "r");
    if (input == NULL) {
        printf("Cannot open file: %s\n", argv[1]);
        return 0;
    }
    int curChar = fgetc(input);
    row = 1;
    col = 1;
    while (curChar != EOF) {
        if (curChar == '{') {
            push(row, col, &head);
        } else if (curChar == '}') {
            pop(&head, row, col);
        }
        if (curChar == '\n') {
            row += 1;
            col = 1;
        } else {
            col += 1;
        } 
        curChar = fgetc(input); 
    }
    clear(head);
    fclose(input);
    return 0;
}

