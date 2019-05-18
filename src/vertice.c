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
    free(vertice);
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

int addEdge(Vertice *vertice, int where, unsigned length, int year) {
    Edge *new_edge = newEdge(where, length, year);
    if (new_edge == NULL)
        return ALLOCATION_FAILURE;

    edgeVectorPush(vertice->edges, new_edge);
    return ALLOCATION_SUCCESS;
}

void removeEdge(Vertice *vertice, int where) {
    int size = vertice->edges->current_size;
    for (int i = 0; i < size; i++) {
        Edge *edge = vertice->edges->tab[i];
        if (edge->where == where) {
            vertice->edges->tab[i] = vertice->edges->tab[size - 1];
            vertice->edges->tab[size - 1] = edge;
            edgeVectorPop(vertice->edges);
            return;
        }
    }
}