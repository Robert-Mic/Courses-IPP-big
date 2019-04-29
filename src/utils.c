//
// Created by rober on 26.04.2019.
//

#include <stdlib.h>
#include <string.h>
#include "utils.h"

int min(int a, int b) {
    return a < b ? a : b;
}

int intPairCmp(IntPair a, IntPair b) {
    if (a.first < b.first)
        return -1;
    else if (a.first == b.first) {
        return a.second - b.second;
    }
    else
        return 1;
}

IntPair newIntPair(int a, int b) {
    IntPair new_pair;
    new_pair.first = a;
    new_pair.second = b;
    return new_pair;
}

char* myStrdup(const char *str) {
    char *p = malloc(strlen(str) + 1);
    if (p)
        strcpy(p, str);
    return p;
}