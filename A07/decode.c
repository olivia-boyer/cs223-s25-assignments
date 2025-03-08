/*----------------------------------------------
 * Author: Olivia Boyer
 * Date: 03/08/25
 * Description: decodes secret messages hidden in least significant
 * bits of .ppm image files.
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"

#define LASTBIT 0x1

void decode(const char *fileName)
{
  int w, h;
  unsigned char *pixels = (unsigned char *)(read_ppm(fileName, &w, &h));
  int size = 3 * (w * h) / 8;

  if (pixels == NULL)
  {
    return;
  }

  printf("Reading %s with width %d and height %d\n", fileName, w, h);

  printf("Max number of characters in the image: %d\n", size);

  unsigned char *code = (unsigned char *)malloc(sizeof(unsigned char) * (size));

  if (code == NULL)
  {
    printf("Error creating array");
    return;
  }

  code[0] = '1'; // intializing value to something != '\0'

  unsigned char *lastChar = &code[0];
  int p = 0; // for indexing pixels array
  int c = 0; // for indexing code array

  while (*lastChar != '\0')
  {

    code[c] = '1';

    for (int j = 0; j < 8; j++)
    {

      code[c] = code[c] << 1;

      if ((pixels[p] & LASTBIT) == LASTBIT)
      {
        code[c] = code[c] | LASTBIT;
      }

      p++;
    }

    lastChar = &code[c];
    c++;
  }

  printf("%s", code);

  free(code);
  free(pixels);
  
  return;
}

int main(int argc, char **argv)
{
  if (argc != 2)
  {
    printf("usage: decode <file.ppm>\n");
    return 0;
  }

  decode(argv[1]);
  return 0;
}
