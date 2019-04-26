//
// Created by rober on 25.04.2019.
//

#ifndef DROGI_EDGE_H
#define DROGI_EDGE_H

#include "list_intlist.h"

struct RoadEdge {
    int where;
    int length;
    int year;
    IntList *routes;
};

typedef struct RoadEdge Edge;

Edge* newEdge(int where, int length, int year);

void freeEdge(Edge *edge);

#endif //DROGI_EDGE_H
