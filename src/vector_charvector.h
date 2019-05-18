/** @file
 * CharVector class interface.
 *
 * @author Robert Michna <rm406247@students.mimuw.edu.pl>
 * @copyright Uniwersytet Warszawski
 * @date 25.03.2019
 */

#ifndef DROGI_VECTOR_CHARVECTOR_H
#define DROGI_VECTOR_CHARVECTOR_H

typedef struct CharVector CharVector;

/**
 * A vector of characters. Dynamically allocates memory.
 */
struct CharVector {
    char *tab;  /**< An array of characters held by the vector.*/
    int current_size;  /**< The current size of the vector's tab.*/
    int max_size;  /**< The current size of the allocated memory.*/
};

/** @brief Creates new CharVector.
 * Creates new CharVector. Allocated memory has to be freed by
 * @ref freeCharVector.
 * @return A pointer to the newly created CharVector or NULL if the function
 * fails to allocate memory.
 */
CharVector* newCharVector();

/** @brief Pushes the @p value to the end of the @p vector.
 * Pushes the @p value to the @p vector. Resizes the @p vector if necessary.
 * @param[in,out] vector - A pointer to the specified vector.
 * @param[in] value - The pushed value.
 * @return Returns @p ALLOCATION_SUCCESS on successful push. Returns
 * @p ALLOCATION_FAILURE if the memory allocation fails. @see constants.h
 */
int charVectorPush(CharVector *vector, char value);

/** @brief Pushes the string pointed by @p value to the end of the vector.
 * Pushes the @p value to the @p vector. Resizes the @p vector if necessary.
 * @param[in,out] vector - A pointer to the specified vector.
 * @param[in] value - A string ending with 0.
 * @return Returns @p ALLOCATION_SUCCESS on successful push. Returns
 * @p ALLOCATION_FAILURE if the memory allocation fails. @see constants.h
 */
int charVectorPushString(CharVector *vector, char *value);

/** @brief Frees the memory allocated by @p vector.
 * @param[in,out] vector - A pointer to the @p vector we want to free.
 */
void freeCharVector(CharVector *vector);

/** @brief Removes the last pushed value from the vector.
 * Removes the last element of the vector.
 * @param[in,out] vector - A pointer to the vector from which we want to remove.
 */
void charVectorPop(CharVector *vector);

#endif //DROGI_VECTOR_CHARVECTOR_H
