/** @file
 * IntList class interface.
 *
 * @author Robert Michna <rm406247@students.mimuw.edu.pl>
 * @copyright Uniwersytet Warszawski
 * @date 10.04.2019
 */

#ifndef DROGI_INTLIST_H
#define DROGI_INTLIST_H

typedef struct IntegerList IntList;

/**
 * A list of integers.
 */
struct IntegerList {
    int val; /**< Element of the list */
    IntList *next;  /**< A pointer to the next element or NULL */
};

/** @brief Creates new IntList.
 * Creates new IntList. Has to be freed by @ref freeIntList.
 * @param[in] val - The value of the first element.
 * @return New IntList structure or NULL if memory allocation failed.
 */
IntList* newIntList(int val);

/** @brief adds an integer to the list after the specified element.
 *
 * @param[in] val - new elements value.
 * @return On successful memory allocation returns @p ALLOCATION_SUCCESS.
 * If memory allocation fails it returns @p ALLOCATION_FAILURE.
 */
int addIntAfter(IntList *where, int val);

/** @brief Frees the memory allocated by structure pointed by @p list.
 *
 * @param[in] list - A pointer to the IntList structure we want to delete.
 */
void freeIntList(IntList *list);

/** @brief Removes the list element that is after the specified pointer.
 *
 * @param[in,out] it - A pointer to the list.
 */
void removeNextInt(IntList *it);

/** @brief Returns a pointer to the next element of the list.
 *
 * @param[in] it - A pointer to the IntList list.
 * @return A pointer to the next element in the list or NULL if there is no
 * next element.
 */
IntList* nextInt(IntList *it);

/** @brief copies the list.
 *  Copies the list. The returned pointer has to be freed with @ref freeIntList.
 * @param[in] old - A pointer to the list we want to copy.
 * @return Returns a pointer to a new list with the same values as in the
 * specified parameter.
 */
IntList* copy(IntList *old);

#endif //DROGI_INTLIST_H
