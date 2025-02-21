/*----------------------------------------------
 * Author: 
 * Date: 
 * Description
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include "read_ppm.h"

int main() {
    int w, h;
    const char* fileName = "feep-raw.ppm";
    struct ppm_pixel* pixels = read_ppm(fileName, &w, &h);
    if (pixels == NULL) {
        printf("no pixels!");
        return 0;
    }
    printf("Testing file %s: %d %d\n", fileName, w, h);
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            printf("(%d,%d,%d) ", pixels[(w * i) + j].red, pixels[(w * i) + j].green,
                pixels[(w * i) + j].blue);  
        }
        printf("\n");
    }
    // todo: print out the grid of pixels
    free(pixels);
    return 0;
}

