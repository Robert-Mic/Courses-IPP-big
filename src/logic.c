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

bool recoverEdge(Map *map, int city1_num, int city2_num, IntList *routes, int length, int year) {
    Edge *edge1 = newEdge(city2_num, length, year);
    if (edge1 == NULL)
        return false;
    Edge *edge2 = newEdge(city1_num, length, year);
    if (edge2 == NULL)
        return false;
    edge1->routes = routes;
    edge2->routes = copy(routes->next);
    if (edge2->routes == NULL)
        return false;
    if (edgeVectorPush(map->graph->tab[city1_num]->edges, edge1) == ALLOCATION_FAILURE)
        return false;
    if (edgeVectorPush(map->graph->tab[city2_num]->edges, edge1) == ALLOCATION_FAILURE)
        return false;
    return ALLOCATION_SUCCESS;
}