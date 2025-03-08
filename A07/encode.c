/*----------------------------------------------
 * Author: 
 * Date: 
 * Description
 ---------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "read_ppm.h"
#include "write_ppm.h"

void encode(const char* fileName){
  int w, h;
  int size = (w*h/8);
  unsigned char* pixels = (unsigned char*)(read_ppm(fileName, &w, &h));

  if (pixels == NULL) {
    return;
  }

  printf("Reading %s with width %d and height %d\n", fileName, w, h);
  printf("Max number of characters in the image: %d\n", size);

}

int main(int argc, char** argv) {
  if (argc != 2) {
    printf("usage: encode <file.ppm>\n");
    return 0;
  }
  encode(argv[1]); 
  return 0;
}

