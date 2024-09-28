/****************************
 * Program 5: Weaver Solver
 *
 * Course: CS 211, Spring 2023
 * System: WindowsOS using Clion
 * Student Author: Zaid Khan Mohammed
 * *** **********************/


/*
* Instructions:
* 1. Upon running the program, you will be prompted to enter the number of letters 
*    in the words you want to use.
* 2. The program will read valid words of that length from the "words.txt" file.
* 3. You can choose to provide a starting and ending word, or request a random word 
*    by entering 'r'.
* 4. The program will find a solution path from the starting word to the ending word 
*    and display it.
* 5. After the solution is shown, you can choose to:
*    - Solve another puzzle with the same number of letters
*    - Change the number of letters and solve another puzzle
*    - Exit the program
*
* Note: Ensure the "words.txt" file is present in the same directory as the 
*       executable to load words correctly.
*/ 


// including libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct wordNode{
    char word[99];
    int parent;
};


int oneLetterDiff(char *word1, char *word2) {
    int len1 = strlen(word1);
    int len2 = strlen(word2);
    if (len1 != len2) {
        return 0;
    }
    int n = 0;
    for (int i = 0; i < len1; i++) {
        if (word1[i] != word2[i]) {
            n++;
        }
    }
    return (n == 1);
}


int checkInArray(int size, char *word,struct wordNode wordScanArray[]){
    for (int i=0;i<size;++i){
        if (strcmp(wordScanArray[i].word,word)==0){
            return 1;
        }
    }
    return 0;
}


void option1Or2(int *numLetters,int *numWords,char** wordArrayPtr,struct wordNode wordScanArray[*numWords]){
    printf("Enter starting and ending words, or 'r' for either for a random word: ");
    // accepting starting and ending values from user
    char startingWord[81];
    char endingWord[81];
    scanf("%s", startingWord);
    scanf("%s", endingWord);
    while (1) {
        // checking if it is a dictionary word
        if (strlen(startingWord) != *numLetters && strcmp(startingWord,"r")!=0) {
            printf("Your word, '%s', is not a %d-letter word. Try again.\n", startingWord, *numLetters);
            printf("Enter starting and ending words, or 'r' for either for a random word: ");
            scanf("%s", startingWord);
            scanf("%s", endingWord);
            continue;
        }
        // checking if it is of correct length
        if (strlen(endingWord) != *numLetters && strcmp(endingWord,"r")!=0) {
            printf("Your word, '%s', is not a %d-letter word. Try again.\n", endingWord, *numLetters);
            printf("Enter starting and ending words, or 'r' for either for a random word: ");
            scanf("%s", startingWord);
            scanf("%s", endingWord);
            continue;
        }
        // setting a flag for checking if it is a dictionary word
        int dictionaryWord1 = 0;
        for (int i = 0; i < (*numWords); ++i) {
            if (strcmp(startingWord, wordArrayPtr[i]) == 0) {
                dictionaryWord1 = 1;
            }
        }
        if (dictionaryWord1 == 0 && strcmp(startingWord,"r")!=0) {
            printf("Your word, '%s', is not a valid dictionary word. Try again.\n", startingWord);
            printf("Enter starting and ending words, or 'r' for either for a random word: ");
            scanf("%s", startingWord);
            scanf("%s", endingWord);
            continue;
        }
        int dictionaryWord2 = 0;
        for (int i = 0; i < *numWords; ++i) {
            if (strcmp(endingWord, wordArrayPtr[i]) == 0) {
                dictionaryWord2 = 1;
            }
        }
        if (dictionaryWord2 == 0 && strcmp(endingWord,"r")!=0) {
            printf("Your word, '%s', is not a valid dictionary word. Try again.\n", endingWord);
            printf("Enter starting and ending words, or 'r' for either for a random word: ");
            scanf("%s", startingWord);
            scanf("%s", endingWord);
            continue;
        }
        break;
    }
    if (strcmp(startingWord,"r")==0){
        strcpy(startingWord,wordArrayPtr[rand()%(*numWords)]);
    }
    if (strcmp(endingWord,"r")==0){
        strcpy(endingWord,wordArrayPtr[rand()%(*numWords)]);
    }
    printf("Your starting word is: %s.\n", startingWord);
    printf("Your ending word is: %s.\n\n", endingWord);


    strcpy(wordScanArray[0].word,startingWord);
    wordScanArray[0].parent=-1;
    int currIndex=0;
    int lastIndex=0;
    while (strcmp(wordScanArray[currIndex-1].word,endingWord)!=0) {
        for (int i = 0; i < *numWords; ++i) {
            /*if (currIndex==882){
                int index=0;
                for (int i=0;i<lastIndex;++i){
                    printf("%d word: %s parent: %d\n",index,wordScanArray[i].word,wordScanArray[i].parent);
                    ++index;
                }
            }*/
            if (oneLetterDiff(wordScanArray[currIndex].word,wordArrayPtr[i]) && !checkInArray(lastIndex+1,wordArrayPtr[i],wordScanArray)){
                strcpy(wordScanArray[lastIndex+1].word,wordArrayPtr[i]);
                wordScanArray[lastIndex+1].parent=currIndex;
                lastIndex++;
            }
        }
        currIndex++;
    }

    if (strcmp(wordScanArray[currIndex-1].word,endingWord)==0){
        char foundReverse[*numWords][*numLetters];
        int index=0;
        int prev=wordScanArray[currIndex].parent;
        strcpy(foundReverse[index],endingWord);
        index++;
        while (wordScanArray[prev].parent!=-1){
            strcpy(foundReverse[index],wordScanArray[prev].word);
            index++;
            prev=wordScanArray[prev].parent;
        }
        prev=wordScanArray[prev].parent;
        strcpy(foundReverse[index],startingWord);
        printf("The solution path is:\n");
        for (int i=index;i>=0;--i){
            printf("\t%.*s\n", *numLetters, foundReverse[i]);
        }
    }

    printf("\nEnter: \t1 to have another puzzle solved,\n");
    printf("\t2 to change the number of letters in the words and then have another puzzle solved, or\n");
    printf("\t3 to exit the program.\n");
    printf("Your choice --> ");
}
int main() {
    setbuf( stdout, 0);
    srand(1);
    int numLetters=0;
    int numWords=0;
    printf("Weaver is a game where you try to find a way to get from the starting word to the ending word.\n");
    printf("You can change only one letter at a time, and each word along the way must be a valid word.\n");
    printf("Enjoy!\n\n");
    int userChoice=2;
    // creating array of words on the heap
    char **wordArrayPtr = (char **) malloc(sizeof(char *));
    while (1) {
        if (userChoice == 2) {
            for (int i=0;i<numWords;++i){
                free(wordArrayPtr[i]);
            }
            numLetters=0;
            numWords=0;
            printf("How many letters do you want to have in the words? ");
            scanf("%d", &numLetters);
            // reading text from file
            char filename[] ="words.txt";
            FILE *filePtr = fopen(filename, "r");

            // Check that the file was able to be opened
            if (filePtr == NULL) {
                printf("Error: could not open %s for reading\n", filename);
                exit(-1);
            }
            char inputString[81];
            while (fscanf(filePtr, "%s", inputString) != EOF) {
                if (strlen(inputString) == numLetters) {
                    // incrementing numWords
                    numWords++;
                    wordArrayPtr = (char **) realloc(wordArrayPtr, sizeof(char *) * (numLetters + 1) * numWords);
                    wordArrayPtr[numWords - 1] = (char *) malloc(sizeof(char) * (numLetters + 1));
                    strcpy(wordArrayPtr[numWords - 1], inputString);
                }
            }
            // Close the file
            fclose(filePtr);
            printf("Number of %d-letter words found: %d.\n\n", numLetters, numWords);
            if (numWords==0){
                break;
            }
        }
        struct wordNode wordScanArray[numWords];

        if (userChoice == 1 || userChoice==2) {
            option1Or2(&numLetters,&numWords,wordArrayPtr,wordScanArray);
            scanf("%d", &userChoice);
        }
        if (userChoice==3){
            break;
        }
        if (userChoice!=1 && userChoice!=2 && userChoice!=3){
            break;
        }
    }
    printf("\nThanks for playing!\nExiting...\n\n");
    for(int i=0;i<numWords;++i){
        free(wordArrayPtr[i]);
    }
    free(wordArrayPtr);
    return 0;
}