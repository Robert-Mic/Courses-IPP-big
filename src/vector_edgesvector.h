//
// Created by rober on 24.04.2019.
//

#ifndef DROGI_EDGESVECTOR_H
#define DROGI_EDGESVECTOR_H

#include "edge.h"

typedef struct RoadEdgeVector EdgeVector;

struct RoadEdgeVector {
    int current_size, max_size;
    Edge **tab;
};

EdgeVector* newEdgeVector();

int edgeVectorPush(EdgeVector *vector, Edge *edge);

void freeEdgeVector(EdgeVector *vector);

void edgeVectorPop(EdgeVector *vector);

#endif //DROGI_EDGESVECTOR_H
