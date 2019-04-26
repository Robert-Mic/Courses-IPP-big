//
// Created by rober on 25.04.2019.
//

#include <stdlib.h>
#include "edge.h"

Edge* newEdge(int where, int length, int year) {
    Edge *new_edge = malloc(sizeof(Edge));
    if (new_edge == NULL)
        return NULL;
    new_edge->routes = newIntList(-1);
    if (new_edge->routes == NULL)
        return NULL;
    new_edge->where = where;
    new_edge->length = length;
    new_edge->year = year;
}

void freeEdge(Edge *edge) {
    if (edge == NULL)
        return;
    freeIntList(edge->routes);
    free(edge);
}