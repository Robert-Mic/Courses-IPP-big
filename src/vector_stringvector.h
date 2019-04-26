//
// Created by rober on 24.04.2019.
//

#ifndef DROGI_STRINGVECTOR_H
#define DROGI_STRINGVECTOR_H

typedef struct StringVector StringVector;

struct StringVector {
    char **tab;
    int current_size, max_size;
};

StringVector* newStringVector();

int stringVectorPush(StringVector *vector, const char *value);

void freeStringVector(StringVector *vector);

void stringVectorPop(StringVector *vector);

#endif //DROGI_STRINGVECTOR_H
