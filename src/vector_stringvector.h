/** @file
 * StringVector class interface.
 *
 * @author Robert Michna <rm406247@students.mimuw.edu.pl>
 * @copyright Uniwersytet Warszawski
 * @date 25.03.2019
 */

#ifndef DROGI_STRINGVECTOR_H
#define DROGI_STRINGVECTOR_H

typedef struct StringVector StringVector;

/**
 * A vector of strings. Dynamically allocates memory.
 */
struct StringVector {
    char **tab;  /**< An array of strings held by the vector.*/
    int current_size;  /**< The current size of the vector's tab.*/
    int max_size;  /**< The current size of the allocated memory.*/
};

/** @brief Creates new StringVector.
 * Creates new StringVector. Allocated memory has to be freed by
 * @ref freeStringVector.
 * @return A pointer to the newly created StringVector or NULL if the function
 * fails to allocate memory.
 */
StringVector* newStringVector();

/** @brief Pushes the @p value to the end of the @p vector.
 * Pushes the @p value to the @p vector. Resizes the @p vector if necessary.
 * The string pointed by @p value is duplicated.
 * @param[in,out] vector - A pointer to the specified vector.
 * @param[in] value - The pushed value.
 * @return Returns @p ALLOCATION_SUCCESS on successful push. Returns
 * @p ALLOCATION_FAILURE if the memory allocation fails. @see constants.h
 */
int stringVectorPush(StringVector *vector, const char *value);

/** @brief Frees the memory allocated by @p vector.
 * @param[in,out] vector - A pointer to the @p vector we want to free.
 */
void freeStringVector(StringVector *vector);

/** @brief Removes the last pushed value from the vector.
 * Removes the last element of the vector.
 * @param[in,out] vector - A pointer to the vector from which we want to remove.
 */
void stringVectorPop(StringVector *vector);

#endif //DROGI_STRINGVECTOR_H
