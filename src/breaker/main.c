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
    int a = dictContains(&dictionary, "123");
    int b = dictContains(&dictionary, "fffff");
    int c = dictContains(&dictionary, "aaa");
    int d = dictContains(&dictionary, "3123");
    int e = dictContains(&dictionary, "fa");
    int f = dictContains(&dictionary, "tg");
    int g = dictContains(&dictionary, "kkl");
    int h = dictContains(&dictionary, "k");
    int i = dictContains(&dictionary, "qre");

    int af = dictContains(&dictionary, "4314");
    int bf = dictContains(&dictionary, "4ds");
    int cf = dictContains(&dictionary, "aaaf");
    int df = dictContains(&dictionary, "df");
    int ef = dictContains(&dictionary, "rrt");
    int ff = dictContains(&dictionary, "bvbc");
    int gf = dictContains(&dictionary, "54sdf");
    int hf = dictContains(&dictionary, "nfdg");
    int fi = dictContains(&dictionary, "oo1");
    printf("a = %d\n", a);
    printf("b = %d\n", b);
    printf("c = %d\n", c);
    printf("d = %d\n", d);
    printf("e = %d\n", e);
    printf("f = %d\n", f);
    printf("g = %d\n", g);
    printf("h = %d\n", h);
    printf("i = %d\n", i);

    printf("af = %d\n", af);
    printf("bf = %d\n", bf);
    printf("cf = %d\n", cf);
    printf("df = %d\n", df);
    printf("ef = %d\n", ef);
    printf("ff = %d\n", ff);
    printf("gf = %d\n", gf);
    printf("hf = %d\n", hf);
    printf("fi = %d\n", fi);

    clearDict(&dictionary);
    return 0;
}