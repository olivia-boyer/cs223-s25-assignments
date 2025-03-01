/*--------------------------------------
 * Author: Olivia Boyer
 * Date: 02/28/2025
 * Description: stores file names in binary
 * search tree and allows user to see 
 * dependencies for each file.
--------------------------------------*/

#include <stdio.h>
#include "tree.h"
#include <stdlib.h>
#include <string.h>


int checkFile(char* fileName) {

    FILE* file;
    file = fopen(fileName, "r");

    if (file == NULL) {

        return 0;

    }

    fclose(file);
    return 1;
}

void listDependencies(char* fileName) { 

    FILE* file;
    file = fopen(fileName, "r");

    if (file == NULL) {
        printf("%s not found\n", fileName);
        return;
    }

    printf("%s has the following dependencies\n", fileName);
    char* curLine = (char*)malloc(sizeof(char) * 64);

    while (!feof(file)) {

        fgets(curLine, 63, file);
        char* ptr = strstr(curLine, "#include");

        if (ptr == NULL) {

            continue;

        }

        curLine = strtok(curLine, "<>; \"");
        ptr = &curLine[9];
        printf("%s", ptr);
    }

    fclose(file);
    free(curLine);

}

int main(int argc, char** argv)
{
    printf("%d\n", argc);
    struct tree_node* root = NULL;

    for (int i = 1; i < argc; i++) {

        if (checkFile(argv[i]) != 0) {

           root = insert(argv[i], root);

        }
    }
    printf("processing %d files\n", argc - 1);
    
    char input[64];

    while(1) {

    printf("$");
    scanf("%s", input);

        if (strcmp(input, "list") == 0) {

            printSorted(root);

        } else if (strcmp(input, "quit") == 0) {

            break;

        } else {

            listDependencies(input);
        }
    }

    clear(root);
    return 0;
}
