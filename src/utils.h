//
// Created by rober on 26.04.2019.
//

#ifndef DROGI_UTILS_H
#define DROGI_UTILS_H

typedef struct  IntegerPair IntPair;

struct IntegerPair {
    int first, second;
};

int intPairCmp(IntPair a, IntPair b);

IntPair newIntPair(int a, int b);

int min(int a, int b);

char* myStrdup(const char *str);

#endif //DROGI_UTILS_H
