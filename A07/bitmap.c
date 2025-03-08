/*----------------------------------------------
 * Author: Olivia Boyer
 * Date: 03/07/25
 * Description: Reads in an unsigned long and outputs a
 * 64x64 ascii sprite.
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MASK 0x1ul << 63

void print8x8(unsigned long input)
{

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if ((input & MASK) == MASK)
            {
                printf("@ ");
            }
            else
            {
                printf("  ");
            }
            input = input << 1;
        }
        printf("\n");
    }
}

int main()
{
    unsigned long img;
    scanf(" %lx", &img);
    printf("Image (unsigned long): %lx\n", img);

    print8x8(img);
    return 0;
}
