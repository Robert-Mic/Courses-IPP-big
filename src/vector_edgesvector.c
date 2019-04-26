//
// Created by rober on 24.04.2019.
//

#include <stdlib.h>
#include "constants.h"
#include "vector_edgesvector.h"



EdgeVector* newEdgeVector() {
    EdgeVector *vector = malloc(sizeof(EdgeVector));
    if (vector == NULL)
        return NULL;
    vector->current_size = 0;
    vector->max_size = 4;
    vector->tab = malloc((sizeof(Edge*) * vector->max_size));
    if (vector->tab == NULL) {
        free(vector);
        return NULL;
    }
    return vector;
}

int edgeVectorPush(EdgeVector *vector, Edge *edge) {
    if (vector->current_size + 1 > vector->max_size) {
        vector->max_size *= 2;
        Edge **new_tab = realloc(vector->tab, sizeof(Edge*) * vector->max_size);
        if (new_tab == NULL) {
            return ALLOCATION_FAILURE;
        }
        vector->tab = new_tab;
    }

    vector->tab[vector->current_size++] = edge;
    return ALLOCATION_SUCCESS;
}

void freeEdgeVector(EdgeVector *vector) {
    for (int i = 0; i < vector->current_size; i++) {
        freeEdge(vector->tab[i]);
    }
    free(vector->tab);
    free(vector);
}

void edgeVectorPop(EdgeVector *vector) {
    if (vector->current_size > 0) {
        freeEdge(vector->tab[vector->current_size - 1]);
        vector->current_size -= 1;
    }
}