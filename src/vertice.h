/** @file
 * Vertice class interface.
 * @see edge.h
 *
 * @author Robert Michna <rm406247@students.mimuw.edu.pl>
 * @copyright Uniwersytet Warszawski
 * @date 25.03.2019
 */

#ifndef DROGI_VERTICE_H
#define DROGI_VERTICE_H

#include "vector_edgesvector.h"

typedef struct Vertice Vertice;

/**
 * A structure representing a graph's vertice.
 */
struct Vertice {
    int number;  /**< The number of the vertice.*/
    EdgeVector *edges;  /**< A vector of Edges coming out from the Vertice.*/
};

/** @brief Creates new Vertice.
 * Creates new Vertice. Allocated memeory has to be freed by @ref freeVertice.
 * @param[in] number - The number of the vertice.
 * @return Returns a newly created Vertice or NULL if th function fails to
 * allocate memory.
 */
Vertice *newVertice(int number);

/** @brief Frees the memory allocated by Vertice.
 * @param[in] vertice - A pointer to the Vertice we want to free.
 */
void freeVertice(Vertice *vertice);

/** @brief Finds an edge going from @p vertice to city with number @param city.
 * Finds an edge going from @p vertice to city of number @param city. Returns
 * NULL if there is no such edge.
 * @param[in] vertice - A pointer to the vertices from which we search.
 * @param[in] city - The index of the city to which we search for the edge.
 * @return Returns a pointer to the searched @p Edge or NULL if there is no such
 * edge.
 */
Edge* findEdgeTo(Vertice *vertice, int city);

/** @brief Finds an edge with specified route passing through it.
 * Finds an @p Edge going from @p vertice through which @p route travers.
 * Does not include the @p Edge to the city with number @p excluded.
 * @param[in] vertice - A pointer to the vertice from which we search.
 * @param[in] route - The route's ID.
 * @param[in] excluded - An index of a city we want to omit. If it is invalid
 * route value then no city will be omitted.
 * @return Returns a pointer to the searched @p Edge or NULL if there is no such
 * edge.
 */
Edge* findEdgeWithRoute(Vertice *vertice, int route, int excluded);

/** @brief Creates a new @p Edge assigned to the specified @p vertice.
 *
 * @param[in,out] vertice - A pointer to the vertice we want to modify.
 * @param[in] where - An index of the city the @p Edge goes to.
 * @param[in] length - The length of the @p Edge.
 * @param[in] year - The year of the @p Edge.
 * @return Returns @p ALLOCATION_SUCCESS on successful addition. Returns
 * @p ALLOCATION_FAILURE if the memory allocation fails. @see constants.h
 */
int addEdge(Vertice *vertice, int where, int length, int year);

/** @brief Removes the @p Edge going to city with number @p where.
 * @param[in,out] vertice - A pointer to the vertice we want to modify.
 * @param[in] where - An index of the city the @p Edge goes to.
 */
void removeEdge(Vertice *vertice, int where);

#endif //DROGI_VERTICE_H
