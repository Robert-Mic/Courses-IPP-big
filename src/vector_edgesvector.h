/** @file
 * EdgeVector class interface.
 *
 * @author Robert Michna <rm406247@students.mimuw.edu.pl>
 * @copyright Uniwersytet Warszawski
 * @date 25.03.2019
 */

#ifndef DROGI_EDGESVECTOR_H
#define DROGI_EDGESVECTOR_H

#include "edge.h"
/// A vector of Edges. Dynamically allocates memory.
typedef struct RoadEdgeVector EdgeVector;

/**
 * A vector of Edges. Dynamically allocates memory.
 */
struct RoadEdgeVector {
    Edge **tab;  /**< An array of Edges held by the vector.*/
    int current_size;  /**< The current size of the vector's tab.*/
    int max_size;  /**< The current size of the allocated memory.*/
};

/** @brief Creates new EdgeVector.
 * Creates new EdgeVector. Allocated memory has to be freed by
 * @ref freeEdgeVector.
 * @return A pointer to the newly created EdgeVector or NULL if the function
 * fails to allocate memory.
 */
EdgeVector* newEdgeVector();

/** @brief Pushes the @p value to the end of the @p vector.
 * Pushes the @p value to the @p vector. Resizes the @p vector if necessary.
 * @param[in,out] vector - A pointer to the specified vector.
 * @param[in] edge - The pushed value.
 * @return Returns @p ALLOCATION_SUCCESS on successful push. Returns
 * @p ALLOCATION_FAILURE if the memory allocation fails. @see constants.h
 */
int edgeVectorPush(EdgeVector *vector, Edge *edge);

/** @brief Frees the memory allocated by @p vector.
 * @param[in,out] vector - A pointer to the @p vector we want to free.
 */
void freeEdgeVector(EdgeVector *vector);

/** @brief Removes the last pushed value from the vector.
 * Removes the last element of the vector.
 * @param[in,out] vector - A pointer to the vector from which we want to remove.
 */
void edgeVectorPop(EdgeVector *vector);

#endif //DROGI_EDGESVECTOR_H
