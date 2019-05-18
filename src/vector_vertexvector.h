/** @file
 * VertexVector class interface.
 *
 * @author Robert Michna <rm406247@students.mimuw.edu.pl>
 * @copyright Uniwersytet Warszawski
 * @date 25.03.2019
 */

#ifndef DROGI_VECTOR_VERTEXVECTOR_H
#define DROGI_VECTOR_VERTEXVECTOR_H

#include "vertex.h"

/// A vector of Vertexes. Dynamically allocates memory.
typedef struct VertexVector VertexVector;

/**
 * A vector of Vertexes. Dynamically allocates memory.
 */
struct VertexVector {
    Vertex **tab;  /**< An array of Vertexes held by the vector.*/
    int current_size;  /**< The current size of the vector's tab.*/
    int max_size;  /**< The current size of the allocated memory.*/
};

/** @brief Creates new VertexVector.
 * Creates new VertexVector. Allocated memory has to be freed by
 * @ref freeVertexVector.
 * @return A pointer to the newly created VertexVector or NULL if the function
 * fails to allocate memory.
 */
VertexVector* newVertexVector();

/** @brief Pushes the @p value to the end of the @p vector.
 * Pushes the @p value to the @p vector. Resizes the @p vector if necessary.
 * @param[in,out] vector - A pointer to the specified vector.
 * @param[in] vertex - The pushed value.
 * @return Returns @p ALLOCATION_SUCCESS on successful push. Returns
 * @p ALLOCATION_FAILURE if the memory allocation fails. @see constants.h
 */
int vertexVectorPush(VertexVector *vector, Vertex *vertex);

/** @brief Frees the memory allocated by @p vector.
 * @param[in,out] vector - A pointer to the @p vector we want to free.
 */
void freeVertexVector(VertexVector *vector);

/** @brief Removes the last pushed value from the vector.
 * Removes the last element of the vector.
 * @param[in,out] vector - A pointer to the vector from which we want to remove.
 */
void vertexVectorPop(VertexVector *vector);

#endif //DROGI_VECTOR_VERTEXVECTOR_H
