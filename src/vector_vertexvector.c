//
// Created by rober on 25.04.2019.
//

#include <stdlib.h>
#include "constants.h"
#include "vector_vertexvector.h"

VertexVector* newVertexVector() {
    VertexVector *vector = malloc(sizeof(VertexVector));
    if (vector == NULL)
        return NULL;
    vector->current_size = 0;
    vector->max_size = 4;
    vector->tab = malloc((sizeof(Vertex*) * vector->max_size));
    if (vector->tab == NULL) {
        free(vector);
        return NULL;
    }
    return vector;
}

int vertexVectorPush(VertexVector *vector, Vertex *vertex) {
    if (vector->current_size + 1 > vector->max_size) {
        vector->max_size *= 2;
        Vertex **new_tab = realloc(vector->tab, sizeof(Vertex*) * vector->max_size);
        if (new_tab == NULL) {
            return ALLOCATION_FAILURE;
        }
        vector->tab = new_tab;
    }

    vector->tab[vector->current_size++] = vertex;
    return ALLOCATION_SUCCESS;
}

void freeVertexVector(VertexVector *vector) {
    for (int i = 0; i < vector->current_size; i++) {
        freeVertex(vector->tab[i]);
    }
    free(vector->tab);
    free(vector);
}

void vertexVectorPop(VertexVector *vector) {
    if (vector->current_size > 0) {
        freeVertex(vector->tab[vector->current_size - 1]);
        vector->current_size -= 1;
    }
}