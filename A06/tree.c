#include "tree.h"
#include "stdio.h"
#include "stdlib.h"
#include <string.h>

struct tree_node* find(const char* name, struct tree_node* root)
{
    if (root == NULL) {
        return NULL;
    }
    if (strcmp(name, (root->data).name) == 0) {
        return root;
    } 
    if (strcmp(name, (root->data).name) < 0) {
        return find(name, root->left);
    }
    if (strcmp(name, (root->data).name) > 0) {
        return find(name, root->right);
    }

    return NULL;
}

void insertRecursion(const char* name, struct tree_node* newNode,
    struct tree_node* head) 
{
    if (strcmp(name, (head->data).name) < 0) {
        if (head->left == NULL) {
            head->left = newNode;
            return;
        } else {
            return insertRecursion(name, newNode, head->left);
        }
    } else {
        if (head->right == NULL) {
            head->right = newNode;
            return;
        } else {
            return insertRecursion(name, newNode, head->right);
        }
    }
}

 
 
struct tree_node* insert(const char* name, struct tree_node* root)
{
    struct tree_node* newNode = (struct tree_node*)malloc(
        sizeof(struct tree_node));
    strcpy((newNode->data).name, name);
    newNode->left = NULL;
    newNode->right = NULL;

    if (root == NULL) {
        root = newNode;
        return root;
    }

    insertRecursion(name, newNode, root); 
    return root;
}

            
    


void clear(struct tree_node* root)
{
    if (root == NULL) {
        return;
    }
    clear(root->left);
    clear(root->right);
    free(root);
}

void printHelper (struct tree_node* root, int spaces, const char* prefix) 
{
    if (root == NULL) {
        return;
    }
    for (int i = 0; i < spaces; i++) {
        printf(" ");
    }
    printf("%s%s\n", prefix, root->data.name);
    printHelper(root->left, spaces + 1, "l:");
    printHelper(root->right, spaces + 1, "r:");
}

void print(struct tree_node* root)
{
    printHelper(root, 0, "");
}


void printSorted(struct tree_node* root)
{
    if (root == NULL) {
        return;
    }
    printSorted(root->left);
    printf("%s\n", root->data.name);
    printSorted(root->right);
}

