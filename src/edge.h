//
// Created by rober on 25.04.2019.
//

#ifndef DROGI_EDGE_H
#define DROGI_EDGE_H

#include "list_intlist.h"

/**
 * @var where - The number in graph this edge leads to.
 * @var length - The length of the edge.
 * @var year - The year of last renovation of this edge.
 */
struct RoadEdge {
    int where;
    int length;
    int year;
    IntList *routes;
};

/**
 *
 */
typedef struct RoadEdge Edge;

/** @brief Creates new edge.
 *
 * @param where - The number in graph this edge leads to.
 * @param length - The length of the edge.
 * @param year - The year of last renovation of this edge.
 * @return Pointer to the new created edge or NULL if memory allocation fails.
 */
Edge* newEdge(int where, int length, int year);

/** @brief Frees the memory under the given Edge pointer.
 *
 * @param edge - A pointer to the Edge to free.
 */
void freeEdge(Edge *edge);

#endif //DROGI_EDGE_H
