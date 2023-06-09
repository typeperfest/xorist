#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "xorist-breaker.h"

void printHelp() {
    printf("\tUsage: ./breaker -d <path_to_dictionary_file> -c <path_to_cracking_file>");
}

// requirement: argument is null-termitated string
size_t computeHash(const char* argument, const size_t modulo) {
    size_t hash = 0;
    size_t argSize = strlen(argument);
    for (unsigned int i = 0; i < argSize; ++i) {
        hash += *argument + i;
    }
    hash *= SEED;
    hash %= modulo;
    return hash;
}

void allocateDictionary(dictionary_t* dict, const size_t size) {
    dict->_reserved_size = 2 * size * sizeof(char*);
    dict->_items = (char**)calloc(sizeof(char*), dict->_reserved_size); // fill factor 1/2
    dict->size = size;
}

// requirement: word is null-terminated srting
void dictAddWord(dictionary_t* const dict, const char* word) {
    size_t index = computeHash(word, dict->_reserved_size);
    while(dict->_items[index]) {
        ++index;
        index %= dict->_reserved_size;
    }
    size_t wordSize = strlen(word) * sizeof(char);
    dict->_items[index] = (char*)malloc(wordSize);
    strncpy(dict->_items[index], word, wordSize);
}

// requirement: word is null-terminated string
int dictContains(dictionary_t* const dict, const char* word) {
    size_t index = computeHash(word, dict->_reserved_size);
    if (!dict->_items[index]) return FALSE;
    while (dict->_items[index]) {
        if (!strcmp(dict->_items[index], word)) {
            return TRUE;
        }
        ++index;
    }
    return FALSE;
}

size_t getLinesCount(FILE* stream) {
    size_t count = 0;
    while(!feof(stream)) {
        char c = fgetc(stream);
        if (c == '\n') {
            ++count;
        }
    }
    rewind(stream);
    return count;
}

void clearDict(dictionary_t* dictionary) {
    char** wptr = dictionary->_items;
    for (size_t i = 0; i < dictionary->_reserved_size; ++i) {
        if (*wptr) {
            free(*wptr);
        }
        ++wptr;
    }
}

size_t getFileSize(FILE* filePtr) {
    fseek(filePtr, 0L, SEEK_END);
    size_t size = ftell(filePtr);
    rewind(filePtr);
    return size;
}

char* allocateBuffer(size_t bufSize) {
    char* buffer = (char*)calloc(bufSize, sizeof(char));
    if (!buffer) {
        perror("Allocating buffer failed");
        exit(EXIT_FAILURE);
    }
    return buffer;
}

size_t readFileIntoBuffer(char* buffer, size_t size, FILE* filePtr) {
    size_t bytesRead = fread(buffer, sizeof(char), size, filePtr);
    return bytesRead;
}

void xorBuffer(char* buffer, size_t size, unsigned char key) {
    for (size_t i = 0; i < size; ++i) {
        buffer[i] ^= key;
    }
}

int getSpaces(char* buffer, size_t size) {
    unsigned int count = 0;
    for (size_t i = 0; i < size; ++i) {
        if (buffer[i] == 32) ++count;
    }
    return count;
}

int checkWordsInbuffer(char* buffer, size_t size, dictionary_t* const dict) {
    int lastSpace = -1;
    char* currentWord = NULL;
    for (size_t i = 0; i < size - 1; ++i) {
        if (buffer[i] == ' ' || buffer[i] == '\n') {
            // if lastSpace == -1 => -lastSpace - 1 == 0 
            currentWord = strndup(buffer + lastSpace + 1, i - lastSpace - 1);
            lastSpace = i;
            if (dictContains(dict, currentWord)) return 1;
            free(currentWord);
        }
    }
    return 0;
}
