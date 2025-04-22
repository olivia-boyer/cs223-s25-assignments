#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 32

int main(int argc, char** argv)
{
    int bool, num;
    printf("Boolean: ");
    scanf("%d", &bool);
    printf("Number: ");
    scanf("%d", &num);
    char** adjs = (char**) malloc(sizeof(char) * num * 32);

    
    for (int i = 0; i < num; i++) { //not reading into array
        
        printf("Adjective: ");
        scanf("%s\n", adjs[i]);
      
    
    }

    printf("You are the most ");

    for (int i = num - 1; i > 0; i--) {
        printf("%s, ", adjs[i]);
    }

    printf("and %s person that I know, and you know it's ", adjs[0]);
    if (bool) {
        printf("true!\n");
    } else {
        printf("false!\n");
    }

    free(adjs);

    return 0;
}
