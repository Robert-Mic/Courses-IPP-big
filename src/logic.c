//
// Created by rober on 26.04.2019.
//

#include <stdlib.h>
#include "logic.h"
#include "constants.h"
#include "vector_charvector.h"

bool extRoute(Map *map, int route, uint64_t *dist, int start, int finish) {
    if (dijkstra(map, route, dist, start, finish) == ALLOCATION_FAILURE) {
        free(dist);
        return false;
    }
    free(dist);
    if (markRoute(map, route, dist, start, finish) == ALLOCATION_FAILURE)
        return false;
    if (map->routes[route].finish == start) {
        map->routes[route].finish = finish;
    }
    if (map->routes[route].start == finish) {
        map->routes[route].start = start;
    }
    return true;
}

int addOrFree(CharVector *vector, char *val, char *free_buff) {
    if (charVectorPushString(vector, val) == ALLOCATION_FAILURE) {
        freeCharVector(vector);
        free(free_buff);
        return ALLOCATION_FAILURE;
    }
    return ALLOCATION_SUCCESS;
}