/*----------------------------------------------
 * Author: Olivia Boyer 
 * Date: 02/21/25
 * Description: tests reading in feep-raw.ppm and writing to new file.
 ---------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "read_ppm.h"
#include "write_ppm.h"

int main(int argc, char** argv) {

    int w, h;
    struct ppm_pixel* pixels = read_ppm("feep-raw.ppm", &w, &h);
    write_ppm("test.ppm", pixels, w, h);
        
    free(pixels);

    pixels = read_ppm("test.ppm", &w, &h);

    if (pixels == NULL) {
        printf("no pixels!");
        return 0;
    }

    printf("Testing file feep-raw.ppm: %d %d\n", w, h);

    for (int i = 0; i < h; i++) {

        for (int j = 0; j < w; j++) {

            printf("(%d,%d,%d) ", pixels[(w * i) + j].red, pixels[(w * i) + j].green,
            pixels[(w * i) + j].blue);
        }

        printf("\n");
    }
    free(pixels);
    return 0;
}
