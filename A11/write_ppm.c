/*----------------------------------------------
 * Author: Olivia Boyer 
 * Date: 02/21/25
 * Description: writes to a .ppm file with given pixel array. 
 ---------------------------------------------*/
 #include "write_ppm.h"
 #include <stdio.h>
 #include <string.h>
 
 // implement *one* (but do not remove the other one)!
 
 void write_ppm(const char* filename, struct ppm_pixel* pixels, int w, int h) {
     int arraSize = w * h;
     FILE* writeTo = fopen(filename, "wb");
     fprintf(writeTo, "P6\n");
     fprintf(writeTo, "#comment\n");
     fprintf(writeTo, "%d %d\n", w, h);
     fprintf(writeTo, "225\n");
     
     fwrite(pixels, sizeof(struct ppm_pixel), arraSize, writeTo);    
     fclose(writeTo);
 }
 
 void write_ppm_2d(const char* filename, struct ppm_pixel** pixels, int w, int h) {
 
 }
 