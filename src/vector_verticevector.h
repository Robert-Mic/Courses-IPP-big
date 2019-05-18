/** @file
 * VerticeVector class interface.
 *
 * @author Robert Michna <rm406247@students.mimuw.edu.pl>
 * @copyright Uniwersytet Warszawski
 * @date 25.03.2019
 */

#ifndef DROGI_VECTOR_VERTICEVECTOR_H
#define DROGI_VECTOR_VERTICEVECTOR_H

#include "vertice.h"

/// A vector of Vertices. Dynamically allocates memory.
typedef struct VerticeVector VerticeVector;

/**
 * A vector of Vertices. Dynamically allocates memory.
 */
struct VerticeVector {
    Vertice **tab;  /**< An array of Vertices held by the vector.*/
    int current_size;  /**< The current size of the vector's tab.*/
    int max_size;  /**< The current size of the allocated memory.*/
};

/** @brief Creates new VerticeVector.
 * Creates new VerticeVector. Allocated memory has to be freed by
 * @ref freeVerticeVector.
 * @return A pointer to the newly created VerticeVector or NULL if the function
 * fails to allocate memory.
 */
VerticeVector* newVerticeVector();

/** @brief Pushes the @p value to the end of the @p vector.
 * Pushes the @p value to the @p vector. Resizes the @p vector if necessary.
 * @param[in,out] vector - A pointer to the specified vector.
 * @param[in] vertice - The pushed value.
 * @return Returns @p ALLOCATION_SUCCESS on successful push. Returns
 * @p ALLOCATION_FAILURE if the memory allocation fails. @see constants.h
 */
int verticeVectorPush(VerticeVector *vector, Vertice *vertice);

/** @brief Frees the memory allocated by @p vector.
 * @param[in,out] vector - A pointer to the @p vector we want to free.
 */
void freeVerticeVector(VerticeVector *vector);

/** @brief Removes the last pushed value from the vector.
 * Removes the last element of the vector.
 * @param[in,out] vector - A pointer to the vector from which we want to remove.
 */
void verticeVectorPop(VerticeVector *vector);

#endif //DROGI_VECTOR_VERTICEVECTOR_H
