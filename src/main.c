#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include "xorist.h"

typedef unsigned char byte_t;

int main(int argc, char* argv[]) {
    byte_t key = 0;
    char* inFileName = NULL;
    char* outFileName = NULL;
    int c;

    opterr = 0;

    while ((c = getopt(argc, argv, "k:i:o::")) != -1) {
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

    int a = sum(1, 2);

    exit(EXIT_SUCCESS);
}