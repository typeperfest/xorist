#ifndef BREAKER_H_
#define BREAKER_H_

#define SEED 524287 // prime Mersenne nubmer
#define TRUE 1
#define FALSE 0

typedef struct {
    char** _items;
    size_t size;
    size_t _reserved_size;
} dictionary_t;

void printHelp();
size_t computeHash(const char* argument, const size_t modulo);
void allocateDictionary(dictionary_t* dict, const size_t size);
void dictAddWord(dictionary_t* const dict, const char* word);
int dictContains(dictionary_t* const dict, const char* word);
size_t getLinesCount(FILE* stream);
void clearDict(dictionary_t* dict);
void moveNextLine(FILE* stream);
size_t getFileSize(FILE* filePtr);
char* allocateBuffer(size_t bufSize);
size_t readFileIntoBuffer(char* buffer, size_t size, FILE* filePtr);
void xorBuffer(char* buffer, size_t size, unsigned char key);
int getSpaces(char* buffer, size_t size);
int checkWordsInbuffer(char* buffer, size_t size, dictionary_t* const dict);

#endif // BREAKER_H_