#include <string.h>
#include <stdlib.h>
#include <stdio.h>
//this is the function we were given.
//you need to edit this to make one more for the quiz (the DNA thing or whatever)
void badcharkicker() {
    //read in the word
    char word[4000 + 1]; //need a character array/string
    scanf("%s", word); //scanf for %s (does not need the &)

    //read number of forbiddens
    int numbForbid; //second input
    scanf("%d", &numbForbid); 

    //read in forbiddens
    char badChars[numbForbid + 1];
    for (int i = 0; i < numbForbid; i++) {
        scanf(" ");
        scanf("%c", &badChars[i]);
    }
    //printf("[%C]\n", badchars[i]);

    //compute length of word
    int length = strlen(word);
    //go through all the letters of the word 
    for (int i = 0; i < length; i++) {//dont need to call string length 
    //check if letter == forbidden 
    int isForbid = 0; //setting up a value of if its forbidden 
    for (int j = 0; j <numbForbid; j++) {
        if (badChars[j] == currentCharacter) {
            isForbid = 1;
        }
    }
    //if not forbidden 
    if (!isForbid) {
    //print the letter out
    printf("%c", currentCharacter);        
    }
}
}