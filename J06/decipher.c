#include <stdio.h>


int main(int argc, char** argv)
{
    int left = 0x7f;
    if (argc != 2) {
        printf("Error: please enter filename\n");
        return 0;
    }
    char* filename = argv[1];
    FILE* fp = fopen(filename, "r");
    char c = fgetc(fp);
    while (c != EOF)
    {
        c = c >> 1;
        c = c & left;
        printf("%c", c);
        c = fgetc(fp);
    }
    fclose(fp);
    return 0;
}
