/*----------------------------------------------
 * Author: 
 * Date: 
 * Description
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"

#define LASTBIT 0x1

void decode(const char* fileName) {
  int w, h;
  unsigned char* pixels = (unsigned char*)(read_ppm(fileName, &w, &h));
  int size = (w * h)/8;

  if (pixels == NULL) {
    return;
  }
 
  printf("Reading %s with width %d and height %d\n", fileName, w, h );

  printf("Max number of characters in the image: %d", size);

  char* code = (char*)malloc(sizeof(char) * (size));

  if (code == NULL) {
    printf("Error creating array");
    return;
  }

  char* lastChar = NULL;
  int p = 0; //for indexing pixels array
  int c = 0; //for indexing code array
  while (*lastChar != '\0') {
    for (int j = 0; j < 8; j++) {
      if ((pixels[p] & LASTBIT) == LASTBIT) {
        code[c] = code[c] | LASTBIT;
      }
      code[c] = code[c] << 1;
      p++; 
    }
    c++;
    }
    printf("%s", code);
    
    free(code);
    free(pixels);
  }



int main(int argc, char** argv) {
  if (argc != 2) {
    printf("usage: decode <file.ppm>\n");
    return 0;
  }

  decode(argv[1]);
  return 0;
}

