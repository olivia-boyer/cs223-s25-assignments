/***************************************************
 * Author: Olivia Boyer 
 * creates a bad password from inputted word.
 */
#include <stdio.h>
#include <string.h>

void makePassword(char word[]) {
    for (int i = 0; i < strlen(word); i++) {
        if (word[i] == 'e') {
            word[i] = '3';
        } else if (word[i] == 'l') {
            word[i] = '1';
        } else if (word[i] == 'a') {
            word[i] = '@';
        }
        }
    return;
}   
        

int main() {

    char word[100];
    printf("Enter a word: ");
    scanf("%s", word);
    makePassword(word);
    printf("\nYour bad password is %s\n", word);    
    return 0;
}
