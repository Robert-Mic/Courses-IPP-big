//
// Created by rober on 24.04.2019.
//

#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "vector_stringvector.h"
#include "constants.h"

StringVector* newStringVector() {
    StringVector *vector = malloc(sizeof(StringVector));
    if (vector == NULL)
        return NULL;
    vector->current_size = 0;
    vector->max_size = 4;
    vector->tab = malloc((sizeof(char*) * vector->max_size));
    if (vector->tab == NULL) {
        free(vector);
        return NULL;
    }
    return vector;
}

int stringVectorPush(StringVector *vector, const char *value) {
    char *new_mem = myStrdup(value);
    if (new_mem == NULL)
        return ALLOCATION_FAILURE;
    if (vector->current_size + 1 > vector->max_size) {
        vector->max_size *= 2;
        char **new_tab = realloc(vector->tab, sizeof(char*) * vector->max_size);
        if (new_tab == NULL) {
            return ALLOCATION_FAILURE;
        }
        vector->tab = new_tab;
    }

    vector->tab[vector->current_size++] = new_mem;
    return ALLOCATION_SUCCESS;
}

void freeStringVector(StringVector *vector) {
    for (int i = 0; i < vector->current_size; i++) {
        free(vector->tab[i]);
    }
    free(vector->tab);
    free(vector);
}

void stringVectorPop(StringVector *vector) {
    if (vector->current_size > 0) {
        free(vector->tab[vector->current_size - 1]);
        vector->current_size -= 1;
    }
}
