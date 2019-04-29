/** @file
 * Edge class interface
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
 * The function treats a path that goes from country roads start to it's end
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
 * are saved on the @param dist array.
 */
int dijkstra(Map *map, int without_route, uint64_t *dist, int start, int finish);

int dijkstra2(Map *map, int without_route, uint64_t *dist, int start, int finish);

int markRoute(Map *map, int route, uint64_t *dist, int start, int finish);

IntPair checkRouteDfs(Map *map, int route, uint64_t *dist, int where, int oldest, int finish);

int markRouteDfs(Map *map, int route, uint64_t *dist, int where, int oldest, int from, int finish);

bool isOnRoute(Map *map, int route, int city);

#endif //DROGI_GRAPH_H
