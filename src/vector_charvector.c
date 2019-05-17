//
// Created by rober on 25.04.2019.
//
#include <stdio.h>

#include <stdlib.h>
#include <string.h>
#include "vector_charvector.h"
#include "constants.h"

CharVector* newCharVector() {
    CharVector *vector = malloc(sizeof(CharVector));
    if (vector == NULL)
        return NULL;
    vector->current_size = 0;
    vector->max_size = 4;
    vector->tab = malloc((sizeof(char) * vector->max_size));
    if (vector->tab == NULL) {
        free(vector);
        return NULL;
    }
    return vector;
}

int charVectorPush(CharVector *vector, const char value) {
    if (vector->current_size + 1 > vector->max_size) {
        vector->max_size *= 2;
        char *new_tab = realloc(vector->tab, sizeof(char) * vector->max_size);
        if (new_tab == NULL) {
            return ALLOCATION_FAILURE;
        }
        vector->tab = new_tab;
    }

    vector->tab[vector->current_size++] = value;
    return ALLOCATION_SUCCESS;
}

int charVectorPushString(CharVector *vector, char *value) {
    //printf("s >%s<\n", value);
    for (int i = 0; value[i] != 0; i++) {
        if (charVectorPush(vector, value[i]) == ALLOCATION_FAILURE)
            return ALLOCATION_FAILURE;
    }
    return ALLOCATION_SUCCESS;
}

void freeCharVector(CharVector *vector) {
    if (vector == NULL)
        return;
    free(vector->tab);
    free(vector);
}

void charVectorPop(CharVector *vector) {
    if (vector->current_size > 0) {
        vector->current_size -= 1;
    }
}

