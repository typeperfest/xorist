#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

#include "xorist-breaker.h"

#define MAX_WORD_SIZE 32

int main(int argc, char* argv[]) {
    const char* dictfname = NULL;
    const char* crackfname = NULL;
    int c = 0;

    if (argc != 5) {
        printHelp();
        exit(EXIT_FAILURE);
    }

    while ((c = getopt(argc, argv, "d:c:")) != -1 ) {
        switch(c) {
            case 'd':
                dictfname = strdup(optarg);
                break;
            case 'c':
                crackfname = strdup(optarg);
                break;
            default:
                printHelp();
                exit(EXIT_FAILURE);
                break;
        }
    }

    FILE* dictf = fopen(dictfname, "r");
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

    FILE* crackf = fopen(crackfname, "r");
    size_t fsize = getFileSize(crackf);
    char* textBuffer = allocateBuffer(fsize + 1);
    readFileIntoBuffer(textBuffer, fsize, crackf);

    for (int key = 0; key < 256; ++key) {
        char* tmpBuf = strdup(textBuffer);
        xorBuffer(tmpBuf, fsize, key);
        if (getSpaces(tmpBuf, fsize)) {
            if (checkWordsInbuffer(tmpBuf, fsize, &dictionary)) {
                printf("=== MATCHES FOUNDED ===\n");
                printf("%s", tmpBuf);
                printf("=======================\n");
            }
        }
        free(tmpBuf);
    }
    free(textBuffer);
    clearDict(&dictionary);
    fclose(crackf);
    return 0;
}