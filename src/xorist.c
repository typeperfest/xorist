#ifndef XORIST_CPP_
#define XORIST_CPP_

#include "xorist.h"
#include <stdio.h>
#include <stdlib.h>

void printHelp() {
    printf("\tUsage: xorist -k <key> -i <input_file> -o <output_file>\n");
    printf("\t\tWhere <key> is one byte integer value [0..255]\n");
    printf("\t\tWhere <input_file> name of existing file\n");
    printf("\t\tWhere <output_file> name of file different from <input_file>\n");
}

size_t getFileSize(FILE* filePtr) {
    fseek(filePtr, 0L, SEEK_END);
    size_t size = ftell(filePtr);
    rewind(filePtr);
    return size;
}

char* allocateBuffer(size_t bufSize) {
    char* buffer = malloc(bufSize * sizeof(char));
    if (!buffer) {
        perror("Allocating buffer failed");
        exit(EXIT_FAILURE);
    }
    return buffer;
}

size_t readFileIntoBuffer(char* buffer, size_t fileSize, FILE* filePtr) {
    size_t bytesRead = fread(buffer, sizeof(char), fileSize, filePtr);
    return bytesRead;
}

void encodeBuffer(char* buffer, size_t size, byte_t key) {
    for (size_t i = 0; i < size; ++i) {
        buffer[i] ^= key;
    }
}

void freeBuffer(char* buffer) {
    free(buffer);
}

size_t writeBufferToFile(char* buffer, size_t size, FILE* filePtr) {
    size_t bytesWritten = fwrite(buffer, sizeof(char), size, filePtr);
    return bytesWritten;
}

#endif // XORIST_CPP_
