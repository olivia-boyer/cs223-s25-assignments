/*----------------------------------------------
 * Author: 
 * Date: 
 * Description
 ---------------------------------------------*/
#include <stdio.h>
#include "read_ppm.h"
#include "write_ppm.h"
#include <stdlib.h>

char* asciify(struct ppm_pixel* pixels, int size) {
    char* ascii = malloc(sizeof(char) * size);
    int avg, sum;
    for (int i = 0; i < size; i++) {
        sum =((int)pixels[i].red + (int)pixels[i].green +
             (int)pixels[i].blue);
        avg = sum / 3;
        if (avg <= 125) {  //start from middle and work out
            if (avg <= 75) {
                if (avg <= 50) {
                    if (avg <= 25) {
                        ascii[i] = '@';
                    } else {
                        ascii[i] = '#';
                    }
                } else {
                    ascii[i] = '%';
                }
            } else if (avg <= 100) {
                ascii[i] = '*';
            } else {
                ascii[i] = 'o';
            }
        } else {
            if (avg >= 176) {
                if (avg >= 201) {
                    if (avg >= 226) {
                        ascii[i] = ' ';
                    } else {
                        ascii[i] =  '.';
                    }
                } else {
                    ascii[i] = ',';
                }
            } else if (avg >= 151) {
                ascii[i] = ':';
            } else {
                ascii[i] = ';';
            } 
        }                                                                  
    }
    return ascii;
}

void printArray(char* array, int cols, int rows) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%c", array[(i * cols) + j]);
        }
        printf("\n");
    }

}

int main(int argc, char** argv) {
    int cols, rows;
    struct ppm_pixel* pixels = read_ppm(argv[1], &cols, &rows);
    printf("reading %s with width %d and height %d\n", argv[1], cols, rows);
    char* asciiArray = asciify(pixels, (cols * rows));
    free(pixels);
    printArray(asciiArray, cols, rows);
    free(asciiArray);
    return 0;
}
