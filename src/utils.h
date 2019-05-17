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

char* strdupRange(const char *str, int start, int end);

char** split(const char *string, const char split_char);

void freeSplit(char **split);

#endif //DROGI_UTILS_H
