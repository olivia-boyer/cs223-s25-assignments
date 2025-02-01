/***************************************************
 * Author: Olivia Boyer 
 * asks user for a word at prints a shift cypher of 
 * it using a shift number given by user.
 */
#include <stdio.h>
#include <string.h>

/*implements the shift cypher, editing the char array*/
void cypherfy(char input[], int shift) {

    int length = strlen(input);
    for (int i = 0; i < length; i++) {

        input[i] = (((input[i] % 97) + shift + 26) % 26) + 97;
      
    }
}

int main() {
    int shift;
    char word[100];
    
    printf("Enter a word: ");
    scanf("%s", word);
    
    printf("\nEnter a shift: ");
    scanf("%d", &shift);
    
    cypherfy(word, shift);  
    
    printf("Your cypher is %s\n", word); 
    return 0;
}
