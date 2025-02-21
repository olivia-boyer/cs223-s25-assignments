/*----------------------------------------------
 * Author: 
 * Date: 
 * Description
 ---------------------------------------------*/
#include <stdio.h>
#include "read_ppm.h"
#include "write_ppm.h"
#include <string.h>
#include <stdlib.h>

void glitch(struct ppm_pixel* pixel, int rows, int cols) {
    int size = rows * cols;
    for (int i = 0; i < size; i++) {
        pixel[i].red = pixel[i].red << (rand() % 10);
        pixel[i].green = pixel[i].green << (rand() % 10);
        pixel[i].blue = pixel[i].blue << (rand() % 10);
    }
}

int main(int argc, char** argv) {
    int cols, rows;
    struct ppm_pixel* pixels = read_ppm(argv[1], &cols, &rows);
    glitch(pixels, rows, cols);
    char* newName = malloc((sizeof(char)) * (strlen(argv[1]) + 8));
    argv[1][strlen(argv[1]) - 4] = '\0';
    strcpy(newName, argv[1]);
    strcat(newName, "-glitch.ppm");
    write_ppm(newName, pixels, cols, rows);
    free(pixels);
    free(newName);
    return 0;
}
