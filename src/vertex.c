//
// Created by rober on 25.04.2019.
//

#include <stdlib.h>
#include "vertex.h"
#include "constants.h"

Vertex *newVertex(int number) {
    Vertex *vertex = malloc(sizeof(Vertex));
    if (vertex == NULL)
        return NULL;
    vertex->edges = newEdgeVector();
    if (vertex->edges == NULL) {
        free(vertex);
        return NULL;
    }
    vertex->number = number;
    return vertex;
}

void freeVertex(Vertex *vertex) {
    freeEdgeVector(vertex->edges);
    free(vertex);
}

Edge* findEdgeTo(Vertex *vertex, int city) {
    for (int i = 0; i < vertex->edges->current_size; i++) {
        if (vertex->edges->tab[i]->where == city) {
            return vertex->edges->tab[i];
        }
    }
    return NULL;
}

Edge* findEdgeWithRoute(Vertex *vertex, int route, int excluded) {
    for (int i = 0; i < vertex->edges->current_size; i++) {
        if (vertex->edges->tab[i]->where != excluded) {
            IntList *int_list = vertex->edges->tab[i]->routes;
            while (int_list) {
                if (int_list->val == route) {
                    return vertex->edges->tab[i];
                }
                int_list = nextInt(int_list);
            }
        }
    }
    return NULL;
}

int addEdge(Vertex *vertex, int where, unsigned length, int year) {
    Edge *new_edge = newEdge(where, length, year);
    if (new_edge == NULL)
        return ALLOCATION_FAILURE;

    edgeVectorPush(vertex->edges, new_edge);
    return ALLOCATION_SUCCESS;
}

void removeEdge(Vertex *vertex, int where) {
    int size = vertex->edges->current_size;
    for (int i = 0; i < size; i++) {
        Edge *edge = vertex->edges->tab[i];
        if (edge->where == where) {
            vertex->edges->tab[i] = vertex->edges->tab[size - 1];
            vertex->edges->tab[size - 1] = edge;
            edgeVectorPop(vertex->edges);
            return;
        }
    }
}