#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include "xorist.h"

int main(int argc, char* argv[]) {
    byte_t key = 0;
    char* inFileName = NULL;
    char* outFileName = NULL;
    int c;

    if (argc != 3) {
        printHelp();
        exit(EXIT_FAILURE);
    }

    opterr = 0;

    while ((c = getopt(argc, argv, "k:i:o:")) != -1) {
        switch (c) {
            case 'k':
                key = atoi(optarg);
                break;
            case 'i':
                inFileName = optarg;
                break;
            case 'o':
                outFileName = optarg;
                break;
            case '?':
                if (optopt == 'k' || optopt == 'i' || optopt == 'o') {
                    fprintf(stderr, "Option -%c reqieres an argument.\n Aborting...", optopt);
                } else if (isprint(optopt)) {
                    fprintf(stderr, "Unknown option -%c. Aborting...\n", optopt);
                } else {
                    fprintf(stderr, "Unknown option characher. Aborting...");
                }
                exit(EXIT_FAILURE);
            default:
                abort();
        }
    }

    printf("Read key is %d\n", key);
    printf("Read input file is %s\n", inFileName);
    printf("Read output file is %s\n", outFileName);

    if (strcmp(inFileName, outFileName) == 0) {
        fprintf(stderr, "Existring file overwrite protection. Input file name is equal to output file name");
        exit(EXIT_FAILURE);
    }

    FILE* inputFilePtr = openFile(inFileName);
    size_t fileSize = getFileSize(inputFilePtr);
    if (fileSize == 0) {
        exit(EXIT_SUCCESS);
    }

    char* buffer = allocateBuffer(fileSize);
    size_t bytesRead = readFileIntoBuffer(buffer, fileSize, inputFilePtr);
    if (bytesRead != fileSize) {
        fprintf(stderr, "Error reading whole contetns of file");
        exit(EXIT_FAILURE);
    }
    encodeBuffer(buffer, bytesRead, key);

    FILE* outputFilePtr = openFile(outFileName);
    size_t bytesWritten = writeBufferToFile(buffer, bytesRead, outputFilePtr);

    if(bytesWritten != bytesRead) {
        fprintf(stderr, "Error writing whole buffer to file");
        exit(EXIT_FAILURE);
    }

    freeBuffer(buffer);
    exit(EXIT_SUCCESS);
}
