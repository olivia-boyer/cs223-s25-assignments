/*----------------------------------------------
 * Author: 
 * Date: 
 * Description
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));
    int rows;
    int cols;
    printf("Number of rows: ");
    scanf("%d", &rows);
    printf("\nNumber of columns: ");
    scanf("%d", &cols);
    int* arr = malloc(sizeof(int) * (rows * cols));
    int arrLen = rows * cols;
    int wampusi = (rand() % (rows));
    int wampusj = (rand() % (cols));
    //int wampusLoc = (wampusj * wampusi) + 1;
    for (int i = 0; i < arrLen; i++) {
     
        arr[i] = abs((i / rows) - wampusi);
        arr[i] += abs((i % (rows)) - wampusj);
    }
    
    for (int i = 0; i < rows; i++) {
        printf("\n");
        for (int j = 0; j < cols; j++) {
            if(arr[(i * cols) + j] == 0) {
                printf("W ");
            } else {
                printf("%d ", arr[(i * cols) + j]);
            } 
        }
    }
    printf("\n");
    free(arr); 
    return 0;
}
