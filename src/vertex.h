/** @file
 * Vertex class interface.
 * @see edge.h
 *
 * @author Robert Michna <rm406247@students.mimuw.edu.pl>
 * @copyright Uniwersytet Warszawski
 * @date 25.03.2019
 */

#ifndef DROGI_VERTEX_H
#define DROGI_VERTEX_H

#include "vector_edgesvector.h"

/// A structure representing a graph's vertex.
typedef struct Vertex Vertex;

/**
 * A structure representing a graph's vertex.
 */
struct Vertex {
    int number;  /**< The number of the vertex.*/
    EdgeVector *edges;  /**< A vector of Edges coming out from the Vertex.*/
};

/** @brief Creates new Vertex.
 * Creates new Vertex. Allocated memory has to be freed by @ref freeVertex.
 * @param[in] number - The number of the vertex.
 * @return Returns a newly created Vertex or NULL if th function fails to
 * allocate memory.
 */
Vertex *newVertex(int number);

/** @brief Frees the memory allocated by Vertex.
 * @param[in] vertex - A pointer to the Vertex we want to free.
 */
void freeVertex(Vertex *vertex);

/** @brief Finds an edge going from @p vertex to city with number @param city .
 * Finds an edge going from @p vertex to city of number @param city . Returns
 * NULL if there is no such edge.
 * @param[in] vertex - A pointer to the vertexes from which we search.
 * @param[in] city - The index of the city to which we search for the edge.
 * @return Returns a pointer to the searched @p Edge or NULL if there is no such
 * edge.
 */
Edge* findEdgeTo(Vertex *vertex, int city);

/** @brief Finds an edge with specified route passing through it.
 * Finds an @p Edge going from @p vertex through which @p route travers.
 * Does not include the @p Edge to the city with number @p excluded.
 * @param[in] vertex - A pointer to the vertex from which we search.
 * @param[in] route - The route's ID.
 * @param[in] excluded - An index of a city we want to omit. If it is invalid
 * route value then no city will be omitted.
 * @return Returns a pointer to the searched @p Edge or NULL if there is no such
 * edge.
 */
Edge* findEdgeWithRoute(Vertex *vertex, int route, int excluded);

/** @brief Creates a new @p Edge assigned to the specified @p vertex.
 *
 * @param[in,out] vertex - A pointer to the vertex we want to modify.
 * @param[in] where - An index of the city the @p Edge goes to.
 * @param[in] length - The length of the @p Edge.
 * @param[in] year - The year of the @p Edge.
 * @return Returns @p ALLOCATION_SUCCESS on successful addition. Returns
 * @p ALLOCATION_FAILURE if the memory allocation fails. @see constants.h
 */
int addEdge(Vertex *vertex, int where, unsigned length, int year);

/** @brief Removes the @p Edge going to city with number @p where.
 * @param[in,out] vertex - A pointer to the vertex we want to modify.
 * @param[in] where - An index of the city the @p Edge goes to.
 */
void removeEdge(Vertex *vertex, int where);

#endif //DROGI_VERTEX_H
