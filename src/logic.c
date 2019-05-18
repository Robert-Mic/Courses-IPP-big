//
// Created by rober on 26.04.2019.
//

#include <stdlib.h>
#include "logic.h"
#include "constants.h"
#include "vector_charvector.h"

/// checks if city name is valid
bool invalidCityName(const char *city) {
    int i = 0;
    while (city[i]) {
        unsigned char c = (unsigned char)city[i];
        if (c < 32 || c == ';')
            return true;
        i++;
    }
    return i == 0;
}

bool extRoute(Map *map, int route, uint64_t *dist, int start, int finish) {
    if (dijkstra(map, route, dist, start, finish) == ALLOCATION_FAILURE) {
        free(dist);
        return false;
    }
    if (markRoute(map, route, dist, start, finish) == ALLOCATION_FAILURE) {
        free(dist);
        return false;
    }
    if (map->routes[route].finish == start) {
        map->routes[route].finish = finish;
    }
    if (map->routes[route].start == finish) {
        map->routes[route].start = start;
    }
    free(dist);
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

bool recoverEdge(Map *map, int city1_num, int city2_num,
        IntList *routes, unsigned length, int year) {
    Edge *edge1 = newEdge(city2_num, length, year);
    if (edge1 == NULL)
        return false;
    Edge *edge2 = newEdge(city1_num, length, year);
    if (edge2 == NULL) {
        freeEdge(edge1);
        return false;
    }

    freeIntList(edge1->routes);
    freeIntList(edge2->routes);

    edge1->routes = copy(routes->next);
    if (edge1->routes == NULL) {
        freeEdge(edge1);
        freeEdge(edge2);
        return false;
    }

    edge2->routes = copy(routes->next);
    if (edge2->routes == NULL) {
        freeEdge(edge1);
        freeEdge(edge2);
        return false;
    }

    if (edgeVectorPush(map->graph->tab[city1_num]->edges, edge1) == ALLOCATION_FAILURE) {
        freeEdge(edge1);
        freeEdge(edge2);
        return false;
    }
    if (edgeVectorPush(map->graph->tab[city2_num]->edges, edge2) == ALLOCATION_FAILURE) {
        edgeVectorPop(map->graph->tab[city1_num]->edges);
        freeEdge(edge1);
        freeEdge(edge2);
        return false;
    }
    return true;
}

/// Cleans the route info in edges on the path specified by the list
void clearRouteByList(Map *map, int route, IntList *list) {
    IntList *it = list->next;
    while (it->next) {
        Edge *edge1 = findEdgeTo(map->graph->tab[it->val], it->next->val);
        Edge *edge2 = findEdgeTo(map->graph->tab[it->next->val], it->val);
        if (edge1) {
            IntList *it2 = edge1->routes;
            while (it2->next) {
                if (it2->next->val == route)
                    removeNextInt(it2);
                it2 = it2->next;
            }
        }
        if (edge2) {
            IntList *it2 = edge2->routes;
            while (it2->next) {
                if (it2->next->val == route)
                    removeNextInt(it2);
                it2 = it2->next;
            }
        }
        it = it->next;
    }
}

int markRouteByList(Map *map, int route, IntList *list) {
    IntList *it = list->next;
    while (it->next) {
        Edge *edge1 = findEdgeTo(map->graph->tab[it->val], it->next->val);
        Edge *edge2 = findEdgeTo(map->graph->tab[it->next->val], it->val);
        if (edge1 == NULL || addIntAfter(edge1->routes, route) == ALLOCATION_FAILURE) {
            clearRouteByList(map, route, list);
            return ALLOCATION_FAILURE;
        }
        if (edge2 == NULL || addIntAfter(edge2->routes, route) == ALLOCATION_FAILURE) {
            clearRouteByList(map, route, list);
            return ALLOCATION_FAILURE;
        }
        it = it->next;
    }
    return ALLOCATION_SUCCESS;
}