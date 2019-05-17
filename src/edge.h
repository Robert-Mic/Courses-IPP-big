/** @file
 * Edge class interface.
 *
 * @author Robert Michna <rm406247@students.mimuw.edu.pl>
 * @copyright Uniwersytet Warszawski
 * @date 25.03.2019
 */

#ifndef DROGI_EDGE_H
#define DROGI_EDGE_H

#include "list_intlist.h"

/**
 * where - The number in graph this edge leads to.
 * length - The length of the edge.
 * year - The year of last renovation of this edge.
 * routes - List of numbers of routes passing through this edge.
 */
struct RoadEdge {
    int where;
    int length;
    int year;
    IntList *routes;
};

/**
 * Graph Edge structure.
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
