//
// Created by rober on 25.04.2019.
//

#ifndef DROGI_VECTOR_VERTICEVECTOR_H
#define DROGI_VECTOR_VERTICEVECTOR_H

#include "vertice.h"

typedef struct VerticeVector VerticeVector;

struct VerticeVector {
    int current_size, max_size;
    Vertice **tab;
};

VerticeVector* newVerticeVector();

int verticeVectorPush(VerticeVector *vector, Vertice *vertice);

void freeVerticeVector(VerticeVector *vector);

void verticeVectorPop(VerticeVector *vector);

#endif //DROGI_VECTOR_VERTICEVECTOR_H
