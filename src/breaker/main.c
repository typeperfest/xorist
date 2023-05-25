#include <stdio.h>
#include <stdlib.h>

#include "xorist-breaker.h"

#define MAX_WORD_SIZE 32

int main() {
    FILE* dictf = fopen("dictionary.txt", "r");
    printf("dictionary.txt should contain words less than 32 characnters in size and separated by \\n symbol.\n");
    if (!dictf) {
        fprintf(stderr, "File dictionaty.txt not found. Aborting...");
        exit(EXIT_FAILURE);
    }
    dictionary_t dictionary;
    char wordBuff[MAX_WORD_SIZE];
    size_t lines = getLinesCount(dictf);
    allocateDictionary(&dictionary, lines);
    for (int i = 0; i < lines; ++i) {
        fscanf(dictf, " %31s ", wordBuff);
        dictAddWord(&dictionary, wordBuff);
    }
    fclose(dictf);
    /*
    TODO: read cracking file
    TODO: if cycle [0..255] body: make key as i,
                            apply key to a text
                            check if file contains spaces, 
                            if not - continue, else check word in dictionary,
                            if word founded - out as possible plaintext
                            else continue
    */
    clearDict(&dictionary);
    return 0;
}