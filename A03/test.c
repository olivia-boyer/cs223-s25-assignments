#include <stdio.h>
 #include <stdlib.h>
 #include <time.h>



int main(){
 int rows;
     int cols;
     printf("Number of rows: ");
      scanf("%d", &rows);
      printf("\nNumber of columns: ");
    scanf("%d", &cols);
   int* arr = malloc(sizeof(int) * (rows * cols));
    int arrLen = rows * cols;
for (int i = 0; i < arrLen; i++) {
    arr[i] = i;
    printf("%d\n", arr[i]);
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

free(arr);
return 0;
}
