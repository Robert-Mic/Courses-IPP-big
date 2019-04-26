//
// Created by rober on 25.04.2019.
//

#include <stdlib.h>
#include "vertice.h"
#include "constants.h"

Vertice *newVertice(int number) {
    Vertice *vertice = malloc(sizeof(Vertice));
    if (vertice == NULL)
        return NULL;
    vertice->edges = newEdgeVector();
    if (vertice->edges == NULL) {
        free(vertice);
        return NULL;
    }
    vertice->number = number;
    return vertice;
}

void freeVertice(Vertice *vertice) {
    freeEdgeVector(vertice->edges);
}

Edge* findEdgeTo(Vertice *vertice, int city) {
    for (int i = 0; i < vertice->edges->current_size; i++) {
        if (vertice->edges->tab[i]->where == city) {
            return vertice->edges->tab[i];
        }
    }
    return NULL;
}

Edge* findEdgeWithRoute(Vertice *vertice, int route, int excluded) {
    for (int i = 0; i < vertice->edges->current_size; i++) {
        if (vertice->edges->tab[i]->where != excluded) {
            IntList *int_list = vertice->edges->tab[i]->routes;
            while (int_list) {
                if (int_list->val == route) {
                    return vertice->edges->tab[i];
                }
                int_list = nextInt(int_list);
            }
        }
    }
    return NULL;
}

int addEdge(Vertice *vertice, int where, int length, int year) {
    Edge *new_edge = newEdge(where, length, year);
    if (new_edge == NULL)
        return ALLOCATION_FAILURE;

    edgeVectorPush(vertice->edges, new_edge);
    return ALLOCATION_SUCCESS;
}

void removeEdge(Vertice *vertice, int where) {
    Edge *to_delete = findEdgeTo(vertice, where);
    if (to_delete == NULL)
        return;
    freeEdge(to_delete);
    if (vertice->edges->current_size - 1 >= 0) {
        to_delete = vertice->edges->tab[vertice->edges->current_size - 1];
        vertice->edges->tab[vertice->edges->current_size - 1] = NULL;
        edgeVectorPop(vertice->edges);
    }
}