/***************************************************
 * mathgame.c
 * Author: Olivia Boyer
 * Implements a math game
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
    int rounds, userAnswer, correctAnswer;
    int correctNum = 0;
    int numOne, numTwo;
    printf("Welcome to Math Game!\n");
    printf("How many rounds do you want to play? ");
    scanf("%d", &rounds);
    for (int i = 0; i < rounds; i++) {
            numOne = (rand() % 9) + 1;
            numTwo = (rand() % 9) + 1;
            correctAnswer = numOne + numTwo;
            printf("%d + %d = ? ", numOne, numTwo);
            scanf("%d", &userAnswer);
            if (userAnswer == correctAnswer) {
                printf("Correct!\n");
                correctNum += 1;
            } else {
                printf("Incorrect :(\n");
            }
    }
    
    printf("You answered %d/%d correctly.\n", correctNum, rounds);
    return 0;
}
