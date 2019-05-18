/** @file
 * List of vertexes' distance class interface.
 *
 * @author Robert Michna <rm406247@students.mimuw.edu.pl>
 * @copyright Uniwersytet Warszawski
 * @date 10.04.2019
 */

#ifndef DROGI_LIST_VERTEX_DISTANCELIST_H
#define DROGI_LIST_VERTEX_DISTANCELIST_H

#include <stdint.h>
#include "vertex.h"

/// A list of vertexes' distances.
typedef struct VertexDistanceList DistList;

/**
 * A list of vertexes' distances.
 */
struct VertexDistanceList {
    uint64_t dist;  /**< The calculated distance of the vertex.*/
    Vertex *vertex; /**< A pointer to the vertex.*/
    DistList *next;  /**< A pointer to the next element of the list or NULL.*/
};

/** @brief Creates new DistList.
 * Creates new DistList. Has to be freed by @ref freeDistList.
 * @param[in] vertex - A pointer to the graph's vertex.
 * @param[in] distance - The distance associated to the vertex.
 * @return New IntList structure or NULL if memory allocation failed.
 */
DistList* newDistList(Vertex *vertex, uint64_t distance);

/** @brief adds a new DistList element to the list after the specified element.
 *
 * @param[in] where - A pointer to the element after which a new element will be
 * added.
 * @param[in] vertex - A pointer to the vertex.
 * @param[in] distance - The distance to the specified vertex.
 * @return On successful memory allocation returns @p ALLOCATION_SUCCESS.
 * If memory allocation fails it returns @p ALLOCATION_FAILURE.
 */
int addDistAfter(DistList *where, Vertex *vertex, uint64_t distance);

/** @brief Frees the memory allocated by structure pointed by @p list.
 *
 * @param[in] list - A pointer to the DistList structure we want to delete.
 */
void freeDistList(DistList *list);

/** @brief Removes the list element that is after the specified pointer.
 *
 * @param[in,out] it - A pointer to the list.
 */
void removeNextDist(DistList *it);

/** @brief Returns a pointer to the next element of the list.
 *
 * @param[in] it - A pointer to the DistList list.
 * @return A pointer to the next element in the list or NULL if there is no
 * next element.
 */
DistList* nextDist(DistList *it);

/** @brief Checks if list is empty.
 * The list parameter must have it's first value blank.
 * (Returns it->next == NULL)
 * @param[in] it - The list we want to check.
 * @return Returns @p true if the list is empty or @p false otherwise.
 */
int isEmptyDistList(DistList *it);

/** @brief Returns element before the minimal element.
 * Returns the element before the element with lowest distance. The first
 * element is not included.
 * @param[in] it - The list in which we search for the minimal element.
 * @return A pointer to the DistList that holds the minimal element in it's
 * @p next pointer.
 */
DistList* findBeforeMin(DistList *it);

#endif //DROGI_LIST_VERTEX_DISTANCELIST_H
