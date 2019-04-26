//
// Created by rober on 26.04.2019.
//
#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include "Graph.h"
#include "map.h"
#include "constants.h"
#include "utils.h"
#include "list_vertice_distancelist.h"

int dijkstra(Map *map, int without_route, uint64_t *dist, int start, int finish) {
    int size = map->city_number;
    for (int i = 0; i < size; i++) {
        dist[i] = UINT64_MAX;
    }

    if (without_route > 0) {
        int route_start = map->routes[without_route].start;
        int route_finish = map->routes[without_route].finish;
        Vertice *vertice = map->graph->tab[route_start];
        int last = -1;
        while (vertice->number != route_finish) {
            dist[vertice->number] = 0;
            Edge *edge = findEdgeWithRoute(vertice, without_route, last);
            last = vertice->number;
            vertice = map->graph->tab[edge->where];
        }
    }

    DistList *queue = newDistList(NULL, 0);
    if (queue == NULL)
        return ALLOCATION_FAILURE;

    dist[start] = 0;
    dist[finish] = UINT64_MAX;
    addDistAfter(queue, map->graph->tab[start], 0);

    while (!isEmptyDistList(queue)) {
        DistList *res = findBeforeMin(queue);
        Vertice *vertice = res->next->vertice;
        removeNextDist(res);
        for (int i = 0; i < vertice->edges->current_size; i++) {
            Edge *edge = vertice->edges->tab[i];
            if (dist[edge->where] > dist[vertice->number] + edge->length) {
                dist[edge->where] = dist[vertice->number] + edge->length;
                addDistAfter(queue, map->graph->tab[edge->where], dist[edge->where]);
            }
        }
    }
    return ALLOCATION_SUCCESS;
}

IntPair checkRouteDfs(Map *map, int route, uint64_t *dist, int where, int oldest, int finish) {
    if (finish == where) {
        return newIntPair(oldest, true);
    }

    IntPair result1 = newIntPair(INT_MIN, true);
    IntPair result2 = newIntPair(INT_MIN, true);

    for (int i = 0; i < map->graph->tab[where]->edges->current_size; i++) {
        Edge *edge = map->graph->tab[where]->edges->tab[i];
        if (dist[edge->where] == dist[where] - edge->length
            && (dist[edge->where] != 0) != (edge->where == finish)) {
            IntPair result = checkRouteDfs(map, route, dist, edge->where, min(edge->year, oldest), finish);
            if (intPairCmp(result, result1) ) {
                result2 = result1;
                result1 = result;
            }
        }
    }

    if (result1.first == result2.first) {
        return newIntPair(result1.first, false);
    }
    else {
        return result1;
    }
}

int markRouteDfs(Map *map, int route, uint64_t *dist, int where, int oldest, int from, int finish) {
    //printf("In %d\n", where);
    if (from >= 0) {
        Edge *edge = findEdgeTo(map->graph->tab[where], from);
        //printf("Marked edge to %d\n", edge->where);
        if (addIntAfter(edge->routes, route) == ALLOCATION_FAILURE)
            return ALLOCATION_FAILURE;
    }

    if (finish == where) {
        return ALLOCATION_SUCCESS;
    }

    for (int i = 0; i < map->graph->tab[where]->edges->current_size; i++) {
        Edge *edge = map->graph->tab[where]->edges->tab[i];

        if (dist[edge->where] == dist[where] - edge->length
            && (dist[edge->where] != 0) != (edge->where == finish)
            && edge->year >= oldest) {

            //printf("Marked edge to %d\n", edge->where);
            addIntAfter(edge->routes, route);
            int result = markRouteDfs(map, route, dist, edge->where, oldest, where, finish);
            if (result == ALLOCATION_FAILURE) {
                removeNextInt(edge->routes);
                Edge *edge2 = findEdgeTo(map->graph->tab[where], from);
                removeNextInt(edge2->routes);
                return ALLOCATION_FAILURE;
            }
            return ALLOCATION_SUCCESS;
        }
    }
    return ALLOCATION_SUCCESS;
}

int markRoute(Map *map, int route, uint64_t *dist) {
    IntPair result = checkRouteDfs(map, route, dist, map->routes[route].finish,
            INT_MAX, map->routes[route].start);
    if (result.second == true) {
        int res = markRouteDfs(map, route, dist, map->routes[route].finish,
                result.first, -1, map->routes[route].start);
        if (res == ALLOCATION_FAILURE)
            return ALLOCATION_FAILURE;
    }
    return ALLOCATION_SUCCESS;
}