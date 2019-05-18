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
 * A structure representing a road / edge between two cities.
 */
struct RoadEdge {
    int where;  /**< the number in graph this edge leads to.*/
    unsigned length;  /**< the length of the edge.*/
    int year;  /**< the year of last renovation of this edge.*/
    IntList *routes;  /**< list of numbers of routes passing through this edge.*/
};

/**
 * Graph Edge structure.
 */
typedef struct RoadEdge Edge;

/** @brief Creates new edge.
 *
 * @param[in] where - The number in graph this edge leads to.
 * @param[in] length - The length of the edge.
 * @param[in] year - The year of last renovation of this edge.
 * @return Pointer to the new created edge or NULL if memory allocation fails.
 */
Edge* newEdge(int where, unsigned length, int year);

/** @brief Frees the memory under the given Edge pointer.
 *
 * @param[in] edge - A pointer to the Edge to free.
 */
void freeEdge(Edge *edge);

#endif //DROGI_EDGE_H
