#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <pthread.h>
#include "read_ppm.h"
#include "write_ppm.h"

int findAverage(struct ppm_pixel* brightMap, int r, int c, int w, int h) {

//  printf("%d \n", r);

  int highW, lowW, highH, lowH;
  int div = 0;
  int sum = 0;

  if ((w - c) <= 12) {
    highW = w;
  } else { 
    highW = c + 12;
  }

  if ((h - r) <= 12) {
    highH = h;
  } else { 
    highH = r + 12;
  }

  if ((c) <= 12) {
    lowW = 0;
  } else { 
    lowW = c - 12;
  }

  if ((r) <= 12) {
    lowH = 0;
  } else { 
    lowH = r - 12;
  }

  for (int i = lowH; i < highH; i++) {
    for (int j = lowW; j < highW; j++) {
      sum += brightMap[(w * i) + j].red;
      div += 1;
    }
  }
    
  //printf("%d %d\n", r, c);
return sum/div;
}

int main(int argc, char* argv[]) {
  int w, h;
 
  const char* fileName = "earth-small.ppm";
  struct ppm_pixel* pixels = read_ppm(fileName, &w, &h);

  //printf("%d \n", h);
  struct ppm_pixel* newPixels = (struct ppm_pixel*) malloc(
    sizeof(struct ppm_pixel) * w * h);

  struct ppm_pixel* blurred = (struct ppm_pixel*) malloc(
    sizeof(struct ppm_pixel) * w * h); 

  if (pixels == NULL || newPixels == NULL || blurred == NULL) {
    printf("Error: failed to create array.");
    return 0;
  }

  unsigned char brightness = 0;

  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {

      brightness = (pixels[(w * i) + j].red + pixels[(w * i) + j].blue + pixels[(w * i) + j].green)/3;

      if (brightness > 200) {
          newPixels[(w * i) + j].red = brightness;
          newPixels[(w * i) + j].blue = brightness; 
          newPixels[(w * i) + j].green = brightness;
      } else {
        newPixels[(w * i) + j].red = 0;
        newPixels[(w * i) + j].blue = 0; 
        newPixels[(w * i) + j].green = 0; 
      }
      
    }
  }

  int blurVal = 0;

  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      blurVal = findAverage(newPixels, i, j, w, h);
      blurred[(w*i) + j].blue = blurVal;
      blurred[(w*i) + j].red =  blurVal;
      blurred[(w*i) + j].green =  blurVal;
    }
  }

  int index;
  int sum;
  //write_ppm("check2.ppm", newPixels, w, h);

  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      index = (w * i) + j;
      sum = pixels[index].red + blurred[index].red;

      if (sum > 255) {
        newPixels[index].red = 255; 
      } else {
        newPixels[index].red = sum;
      }

      sum = pixels[index].blue + blurred[index].blue;

      if (sum > 255) {
        newPixels[index].blue = 255; 
      } else {
        newPixels[index].blue = sum;
      }

      sum = pixels[index].green + blurred[index].green;

      if (sum > 255) {
        newPixels[index].green = 255; 
      } else {
        newPixels[index].green = sum;
      }

    }
  }

  write_ppm("glow.ppm", newPixels, w, h);
  //write_ppm("check.ppm", blurred, w, h);
  
  
  free(pixels);
  free(newPixels);
  free(blurred);

  return 0;
  }

