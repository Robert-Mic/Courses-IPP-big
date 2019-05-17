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

char* strdupRange(const char *str, int start, int end) {
    char *ret = malloc(sizeof(char) * (end - start + 1));
    if (ret) {
        for (int i = start; i < end; i++) {
            ret[i - start] = str[i];
        }
        ret[end - start] = 0;
    }
    return ret;
}

char** split(const char *string, const char split_char) {
    int i = 0;
    int size = 2;
    while (string[i] != 0) {
        if (string[i] == split_char)
            size++;
        i++;
    }

    char **ret = malloc(sizeof(char*) * size);
    if (ret == NULL)
        return NULL;

    int num = 0;
    int last = 0;
    ret[size - 1] = NULL;
    i = 0;

    while (string[i] != 0) {
        if (string[i] == split_char) {
            ret[num] = strdupRange(string, last, i);

            if (ret[num] == NULL) { //memory allocation failure
                for (int j = 0; j < num; j++) {
                    free(ret[j]);
                }
                free(ret);
                return NULL;
            }

            last = i + 1;
            num++;
        }
        i++;
    }
    ret[num] = strdupRange(string, last, i);
    if (ret[num] == NULL) {
        for (int j = 0; j < num; j++) {
            free(ret[j]);
        }
        free(ret);
        return NULL;
    }
    return ret;
}

void freeSplit(char **split) {
    int i = 0;
    while (split[i]) {
        free(split[i]);
        i++;
    }
    free(split);
}
