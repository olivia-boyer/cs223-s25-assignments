/*----------------------------------------------
 * Author: Olivia Boyer 
 * Date: 02/07/2025
 * Description: repeats the inputted word a given number of times.
 ---------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {

    char word[33];
    int wordlen;
    printf("Enter a word: ");
    scanf("%s", word);
    wordlen = strlen(word);    

    int count;
    printf("Enter a count: ");
    scanf("%d", &count);
    char* bigword;
    bigword = ((char*)malloc((count * wordlen * sizeof(char)) + 1));

    if (bigword == NULL) {
        printf("memory allocation error");
        exit(0);
    } 
    
    for (int i = 0; i < (count * wordlen); i += wordlen) {
        for(int j = 0; j < wordlen; j++) {
            bigword[i+j] = word[j];
        }
    }

    bigword[count * wordlen] = '\0';    

    printf("%s\n", bigword);
    free(bigword);
    return 0;
}
