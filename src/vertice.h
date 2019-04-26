//
// Created by rober on 25.04.2019.
//

#ifndef DROGI_VERTICE_H
#define DROGI_VERTICE_H

#include "vector_edgesvector.h"

typedef struct Vertice Vertice;

struct Vertice {
    int number;
    EdgeVector *edges;
};

Vertice *newVertice(int number);

void freeVertice(Vertice *vertice);

Edge* findEdgeTo(Vertice *vertice, int city);

Edge* findEdgeWithRoute(Vertice *vertice, int route, int excluded);

int addEdge(Vertice *vertice, int where, int length, int year);

void removeEdge(Vertice *vertice, int where);

#endif //DROGI_VERTICE_H
