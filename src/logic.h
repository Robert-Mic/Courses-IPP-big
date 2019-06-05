/** @file
 * List of vertices' distance class interface.
 *
 * @author Robert Michna <rm406247@students.mimuw.edu.pl>
 * @copyright Uniwersytet Warszawski
 * @date 10.04.2019
 */

#ifndef DROGI_LOGIC_H
#define DROGI_LOGIC_H

#include "map.h"
#include "Graph.h"
#include "vector_charvector.h"

/** @brief Checks if a string is an invalid city name.
 *
 * @param city - The checked string.
 * @return Returns @p true if the string is an invalid city name and @p false
 * otherwise.
 */
bool invalidCityName(const char *city);

/** @brief Validates route number.
 * Route number should fit @p unsigned constrains as it is casted to unsigned.
 * @param routeID
 * @return Returns @p true if the number is invalid and false otherwise.
 */
bool invalidRouteNumber(int64_t routeID);

/** Validates a number representing a road's length.
 * @param routeID
 * @return Returns @p true if the number is invalid and false otherwise.
 */
bool invalidEdgeLength(int64_t length);

/** Validates a number representing a road's build year.
 * @param routeID
 * @return Returns @p true if the number is invalid and false otherwise.
 */
bool invalidBuildYear(int64_t year);

/** @brief Extends route from @p start to @p finish. Used in @ref extendRoute.
 * Extends the route either from new to start or from finish to new.
 * Updates map's routes. Frees the dist array specified in the parameter.
 * @param[in,out] map – A pointer to the structure that stores the map of
 * roads.
 * @param[in] route - route's ID
 * @param[in] dist - An array
 * @param[in] start - The index from which we start extending the route.
 * @param[in] finish - The index towards which we extend the route.
 * @return Returns @p true if the route was extended or @p false otherwise.
 */
bool extRoute(Map *map, int route, uint64_t *dist, int start, int finish);

/** @brief Pushes a string to the @p vector and if it fails it frees the memory.
 *
 * @param[in,out] vector - A pointer to CharVector to which we push the string.
 * @param val - The string which we add to the vector.
 * @param free_buff - The memory we want to free if it fails.
 * @return On success returns @p ALLOCATION SUCCESS, returns
 * @p ALLOCATION_FAILURE otherwise.
 */
int addOrFree(CharVector *vector, char *val, char *free_buff);

/** @brief Rebuilds edge between two cities with it's previously stored routes.
 *
 * @param[in,out] map – A pointer to the structure that stores the map of
 * roads.
 * @param city1_num - Index of the first city.
 * @param city2_num - Index of the second city.
 * @param routes - A pointer to IntList containing the routes.
 * Must start with blank value.
 * @param length - Length of the previously deleted edge.
 * @param year - The year of the previously deleted edge.
 * @return On success returns @p true, returns @p false if memory allocation fails.
 */
bool recoverEdge(Map *map, int city1_num, int city2_num,
        IntList *routes, unsigned length, int year);

/** @brief Marks a route on the edges.
 *
 * @param[in,out] map – A pointer to the structure that stores the map of
 * roads.
 * @param route - Route's ID.
 * @param list - A pointer to IntList containing the indexes of consecutive cities.
 * @return Returns @p ALLOCATION_SUCCESS. If memory allocation fails it retuns
 * @p ALLOCATION_FAILURE.
 */
int markRouteByList(Map *map, int route, IntList *list);

#endif //DROGI_LOGIC_H
