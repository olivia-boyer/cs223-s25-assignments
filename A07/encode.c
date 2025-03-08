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

#define LAST 0x1
#define FIRST 0x80
#define NOTLAST 0xFE

void encode(const char* fileName){
  int w, h;
  unsigned char* pixels = (unsigned char*)(read_ppm(fileName, &w, &h));
  int size = ((3 * w * h)/8);

  if (pixels == NULL) {
    return;
  }

  printf("Reading %s with width %d and height %d\n", fileName, w, h);
  printf("Max number of characters in the image: %d\n", size - 1);

  char* secretPhrase = (char*)malloc(sizeof(char) * size);
  printf("Enter a phrase: ");

  if (fgets(secretPhrase, size, stdin) != NULL) {
    printf("You entered: %s", secretPhrase);
  } else {
    printf("Error reading input");
  }

  char* lastChar = &secretPhrase[0];
  int p = 0; //for indexing pixels array
  int s = 0; //for indexing secretPhrase array
  while (*lastChar != '\0') {
    for (int i = 0; i < 8; i++) {
      if ((secretPhrase[s] & FIRST) == FIRST) {
        pixels[p] = pixels[p] | LAST;
      } else {
        pixels[p] = pixels[p] & NOTLAST;
      }
      secretPhrase[s] = secretPhrase[s] << 1;
      p++;
    }
    lastChar = &secretPhrase[s];
    s++;
  }
  char* newName = malloc((sizeof(char)) * (strlen(fileName) + 8));
    strcpy(newName, fileName);
      newName[strlen(newName) - 4] = '\0';
     strcat(newName, "-encoded.ppm");
     write_ppm(newName, (struct ppm_pixel*)pixels, w, h);

     free(pixels);
     free(secretPhrase);
     free(newName);
  return;
}

int main(int argc, char** argv) {
  if (argc != 2) {
    printf("usage: encode <file.ppm>\n");
    return 0;
  }
  
  encode(argv[1]); 
  return 0;
}

