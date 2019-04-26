//
// Created by rober on 25.04.2019.
//

#ifndef DROGI_VECTOR_CHARVECTOR_H
#define DROGI_VECTOR_CHARVECTOR_H

typedef struct CharVector CharVector;

struct CharVector {
    char *tab;
    int current_size, max_size;
};

CharVector* newCharVector();

int charVectorPush(CharVector *vector, char value);

int charVectorPushString(CharVector *vector, char *value);

void freeCharVector(CharVector *vector);

void charVectorPop(CharVector *vector);

#endif //DROGI_VECTOR_CHARVECTOR_H
