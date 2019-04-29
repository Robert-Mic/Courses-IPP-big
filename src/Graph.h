/** @file
 * Graph functions interface.
 *
 * @author Robert Michna <rm406247@students.mimuw.edu.pl>
 * @copyright Uniwersytet Warszawski
 * @date 25.03.2019
 */

#ifndef DROGI_GRAPH_H
#define DROGI_GRAPH_H

#include <stdint.h>
#include "map.h"
#include "utils.h"

/** @brief Performs Dijkstra's algorithm on map's graph.
 *
 * The function treats a path that goes from routes start to it's end
 * as impassable, if routeId is specified.
 * @param map - A pointer to the map that the algorithm is used on.
 * @param without_route - An ID to the route through which the algorithm
 * will not pass.
 * @param dist - An array of lengths that will be used to perform the algorithm.
 * @param start - The number of city from which the algorithm starts.
 * @param finish - The number of city to which the algorithms calculates
 * the shortest path.
 * @return Returns ALLOCATION_FAILURE if the function fails to allocate
 * enough memory, or ALLOCATION_SUCCESS if it succeeded and all the distances
 * are saved on the @p dist array.
 */
int dijkstra(Map *map, int without_route, uint64_t *dist, int start, int finish);

/** @brief Performs Dijkstra's algorithm on map's graph.
 *
 * The function treats a path that goes from country roads start to it's end
 * as impassable, if routeId is specified. It assumes one of the edges is
 * deleted and will go from both sides to imitate the result of dijkstra1.
 * @param map - A pointer to the map that the algorithm is used on.
 * @param without_route - An ID to the route through which the algorithm
 * will not pass.
 * @param dist - An array of lengths that will be used to perform the algorithm.
 * @param start - The number of city from which the algorithm starts.
 * @param finish - The number of city to which the algorithms calculates
 * the shortest path.
 * @return Returns ALLOCATION_FAILURE if the function fails to allocate
 * enough memory, or ALLOCATION_SUCCESS if it succeeded and all the distances
 * are saved on the @p dist array.
 */
int dijkstra2(Map *map, int without_route, uint64_t *dist, int start, int finish);

/** @brief Updates the information on graphs edges that route traverses through them.
 * The dist array has to be initialised by Dijkstra1 or Dijkstra2 function.
 * @param map - A pointer to the map which graph is used.
 * @param route - ID of route that this function marks.
 * @param dist - An array of lengths calculated by Dijkstra1 or Dijkstra2.
 * @param start - The city number from which the function starts.
 * @param finish - The city number to which the function goes.
 * @return Returns ALLOCATION_FAILURE if the function fails to allocate
 * enough memory, or ALLOCATION_SUCCESS if it succeeded. The information
 * about route is saved to specified @p map.
 */
int markRoute(Map *map, int route, uint64_t *dist, int start, int finish);

/** @brief Checks if it is possible to pick a single best path for a route.
 * This recursive function checks if the possible routes that were found have a single
 * best to pick.
 * @param map - A pointer to the map which graph is used.
 * @param route - ID of route that this function marks.
 * @param dist - An array of lengths calculated by Dijkstra1 or Dijkstra2.
 * @param where - Stores the information about the vertice it is currently on.
 * @param oldest - Stores the information about the oldest edge this path has
 * traversed through.
 * @param finish - Stores the information about the destination.
 * @return IntPair <year, boolean> that holds the newest year the selected
 * path traverses and the information if it was picked unambiguously.
 */
IntPair checkRouteDfs(Map *map, int route, uint64_t *dist, int where, int oldest, int finish);

/** @brief Checks if the city is on the path or route.
 *
 * @param map - A pointer to the map which graph is used.
 * @param route - The ID of a route that this function traverses.
 * @param city - The number of a city this function looks for.
 * @return Returns true if the city is placed on the path the route
 * traverses or false otherwise.
 */
bool isOnRoute(Map *map, int route, int city);

#endif //DROGI_GRAPH_H
