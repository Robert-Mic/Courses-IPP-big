//
// Created by rober on 25.04.2019.
//

#include <stdlib.h>
#include "constants.h"
#include "vector_verticevector.h"

VerticeVector* newVerticeVector() {
    VerticeVector *vector = malloc(sizeof(VerticeVector));
    if (vector == NULL)
        return NULL;
    vector->current_size = 0;
    vector->max_size = 4;
    vector->tab = malloc((sizeof(Vertice*) * vector->max_size));
    if (vector->tab == NULL) {
        free(vector);
        return NULL;
    }
    return vector;
}

int verticeVectorPush(VerticeVector *vector, Vertice *vertice) {
    if (vector->current_size + 1 > vector->max_size) {
        vector->max_size *= 2;
        Vertice **new_tab = realloc(vector->tab, sizeof(Vertice*) * vector->max_size);
        if (new_tab == NULL) {
            return ALLOCATION_FAILURE;
        }
        vector->tab = new_tab;
    }

    vector->tab[vector->current_size++] = vertice;
    return ALLOCATION_SUCCESS;
}

void freeVerticeVector(VerticeVector *vector) {
    for (int i = 0; i < vector->current_size; i++) {
        freeVertice(vector->tab[i]);
    }
    free(vector->tab);
    free(vector);
}

void verticeVectorPop(VerticeVector *vector) {
    if (vector->current_size > 0) {
        freeVertice(vector->tab[vector->current_size - 1]);
        vector->current_size -= 1;
    }
}