/*----------------------------------------------
 * Author: 
 * Date: 
 * Description
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>

int checkRows (int* arra, int magConst, int rows, int cols) {
     int sum;
     for (int i = 1; i < rows; i++) {
         sum = 0;
         for (int j = 0; j < cols; j++) {
            sum += arra[(i * rows) + j];
         }
         if (sum != magConst) {
             return 0;
         }
     }
     return 1;
}

int checkCols (int* arra, int magConst, int rows, int cols) {
     int sum;
     for (int i = 0; i < cols; i++) {
         sum = 0;
         for (int j = 0; j < rows; j++) {
            sum += arra[(j * rows) + i];
         }
         if (sum != magConst) {
             return 0;
         }
     }
     return 1;
}

int checkDiagonal(int* arra, int magConst, int rows, int cols) {
    int sum = 0;
    for (int i = 0; i < rows; i++) {
        sum += arra[(rows + 1) * i];
    } 
    
    if (sum != magConst) {
        return 0;
    } 

    sum = 0;
    
    for (int i = 1; i <= rows; i++) {
        sum += arra[(rows - 1) * i];
    }
    
    if (sum == magConst) {
        return 1;
    }
    
    return 0;
}
             
int main() {
    int rows, cols;
    scanf("%d", &rows);
    scanf("%d", &cols);
    if (rows != cols) {
        printf("M is NOT a magic square!\n");
        return 0;
    } 
    int* array = malloc(sizeof(int) * rows * cols);
    for (int i = 0; i < (rows * cols); i++) {
        scanf("%d",&array[i]);
    }
    int magConst = 0; //magic constant
    for (int i = 0; i < cols; i++) {
        magConst += array[i];
    }
    if (!checkRows(array, magConst, rows, cols) || 
        !checkCols(array, magConst, rows, cols) ||
            !checkDiagonal(array, magConst, rows, cols)) {
        printf("M is NOT a magic square!\n");
    } else {
        printf("M is a magic square (magic constant = %d)\n", magConst);
    }
    free(array);
      
  return 0;
}
