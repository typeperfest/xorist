#ifndef XORIST_H_ 
#define XORIST_H_

#include <stdio.h>
#include <stdlib.h>

typedef unsigned char byte_t;

void printHelp();
size_t getFileSize(FILE* filePtr);
char* allocateBuffer(size_t bufSize);
size_t readFileIntoBuffer(char* buffer, size_t fileSize, FILE* filePtr);
void encodeBuffer(char* buffer, size_t size, byte_t key);
void freeBuffer(char* buffer);
size_t writeBufferToFile(char* buffer, size_t size, FILE* filePtr);

#endif // XORIST_H_
