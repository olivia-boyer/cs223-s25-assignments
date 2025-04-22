/*----------------------------------------------
 * Author: Olivia Boyer 
 * Date: 02/19/25
 * Description: Reads in a ppm file and stores pixel data in an array. 
 ---------------------------------------------*/
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include "read_ppm.h"
 
 // Choose *one* to implement (do not remove the other one!)
 
 struct ppm_pixel* read_ppm(const char* filename, int* w, int* h) {
 
     FILE* file;
     struct ppm_pixel* pArray;
     
     file = fopen(filename, "rb");
 
     if (file == NULL) {
         printf("Error opening file");
         return NULL;
     } 
 
     if (fgetc(file) != 'P') {
         if (fgetc(file) != '6') {
             printf("wrong filetype");
             return NULL;
         }
     }
 
     fseek(file, 2, SEEK_CUR); 
 
     while (fgetc(file) != '\n') {
      
     }
 
     int range;
     fscanf(file, "%d %d\n %d\n", w, h, &range);
     pArray = (struct ppm_pixel*)malloc(sizeof(struct ppm_pixel*) * (*w) * (*h));
 
     if (pArray == NULL) {
         printf("Error creating array");
         return NULL;
     }   
 
     fread(pArray, sizeof(struct ppm_pixel), *w * *h, file);     
     fclose(file);    
        
     return pArray;
 }
 
 struct ppm_pixel** read_ppm_2d(const char* filename, int* w, int* h) {
   return NULL;
 }