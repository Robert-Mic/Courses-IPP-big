//
// Created by rober on 26.04.2019.
//

#ifndef DROGI_GRAPH_H
#define DROGI_GRAPH_H

#include <stdint.h>
#include "map.h"
#include "utils.h"

int dijkstra(Map *map, int without_route, uint64_t *dist, int start, int finish);

int markRoute(Map *map, int route, uint64_t *dist, int start, int finish);

IntPair checkRouteDfs(Map *map, int route, uint64_t *dist, int where, int oldest, int finish);

int markRouteDfs(Map *map, int route, uint64_t *dist, int where, int oldest, int from, int finish);


#endif //DROGI_GRAPH_H
