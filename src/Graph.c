//
// Created by rober on 26.04.2019.
//
#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include <stdlib.h>
#include <assert.h>
#include "Graph.h"
#include "map.h"
#include "constants.h"
#include "utils.h"
#include "list_vertex_distance_list.h"

/// Signalizes a wrongly chosen route path.
#define BAD_ROAD -1

int dixtra(Map *map, uint64_t *dist, int start, int finish) {
    DistList *queue = newDistList(NULL, 0);
    if (queue == NULL)
        return ALLOCATION_FAILURE;

    dist[start] = 0;
    dist[finish] = UINT64_MAX;
    addDistAfter(queue, map->graph->tab[start], 0);

    while (!isEmptyDistList(queue)) {
        DistList *res = findBeforeMin(queue);
        Vertex *vertex = res->next->vertex;
        removeNextDist(res);
        for (int i = 0; i < vertex->edges->current_size; i++) {
            Edge *edge = vertex->edges->tab[i];
            if (dist[edge->where] > dist[vertex->number] + edge->length) {
                dist[edge->where] = dist[vertex->number] + edge->length;
                addDistAfter(queue, map->graph->tab[edge->where], dist[edge->where]);
            }
        }
    }
    freeDistList(queue);
    return ALLOCATION_SUCCESS;
}

int dijkstra(Map *map, int without_route, uint64_t *dist, int start, int finish) {
    int size = map->city_number;
    for (int i = 0; i < size; i++) {
        dist[i] = UINT64_MAX;
    }

    if (without_route > 0) {
        int route_start = map->routes[without_route].start;
        int route_finish = map->routes[without_route].finish;
        Vertex *vertex = map->graph->tab[route_start];
        int last = -1;
        while (vertex->number != route_finish) {
            dist[vertex->number] = 0;
            Edge *edge = findEdgeWithRoute(vertex, without_route, last);
            last = vertex->number;
            vertex = map->graph->tab[edge->where];
        }
    }

    return dixtra(map, dist, start, finish);
}

int dijkstra2(Map *map, int without_route, uint64_t *dist, int start, int finish) {
    int size = map->city_number;
    for (int i = 0; i < size; i++) {
        dist[i] = UINT64_MAX;
    }

    if (without_route > 0) {
        int route_start = map->routes[without_route].start;
        int route_finish = map->routes[without_route].finish;
        int last;
        Vertex *vertex;
        Edge *edge;

        last = -1;
        vertex = map->graph->tab[route_start];
        dist[vertex->number] = 0;
        edge = findEdgeWithRoute(vertex, without_route, last);
        while (edge != NULL) {
            dist[vertex->number] = 0;
            last = vertex->number;
            vertex = map->graph->tab[edge->where];
            edge = findEdgeWithRoute(vertex, without_route, last);
        }

        last = -1;
        vertex = map->graph->tab[route_finish];
        dist[vertex->number] = 0;
        edge = findEdgeWithRoute(vertex, without_route, last);
        while (edge != NULL) {
            dist[vertex->number] = 0;
            last = vertex->number;
            vertex = map->graph->tab[edge->where];
            edge = findEdgeWithRoute(vertex, without_route, last);
        }
    }

    return dixtra(map, dist, start, finish);
}


IntPair checkRouteDfs(Map *map, int route, uint64_t *dist, int where,
        int oldest, int finish) {
    if (finish == where) {
        return newIntPair(oldest, true);
    }
    //printf("where = %d\n", where);

    IntPair result1 = newIntPair(INT_MIN, true);
    IntPair result2 = newIntPair(INT_MIN, true);

    for (int i = 0; i < map->graph->tab[where]->edges->current_size; i++) {
        Edge *edge = map->graph->tab[where]->edges->tab[i];
        if (dist[edge->where] == dist[where] - edge->length
            && (dist[edge->where] != 0) != (edge->where == finish)) {
            IntPair result = checkRouteDfs(
                    map,
                    route,
                    dist,
                    edge->where,
                    min(edge->year, oldest),
                    finish);
            if (intPairCmp(result, result1) > 0) {
                result2 = result1;
                result1 = result;
            }
            else if (intPairCmp(result, result2) > 0){
                result2 = result;
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
    if (from >= 0) {
        Edge *edge = findEdgeTo(map->graph->tab[where], from);
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
            if (addIntAfter(edge->routes, route) == ALLOCATION_FAILURE) {
                if (from >= 0) {
                    Edge *edge2 = findEdgeTo(map->graph->tab[where], from);
                    removeNextInt(edge2->routes);
                }
                return ALLOCATION_FAILURE;
            }
            int result = markRouteDfs(map, route, dist, edge->where, oldest, where, finish);
            if (result == ALLOCATION_FAILURE) {
                removeNextInt(edge->routes);
                if (from >= 0) {
                    Edge *edge2 = findEdgeTo(map->graph->tab[where], from);
                    removeNextInt(edge2->routes);
                }
                return ALLOCATION_FAILURE;
            }
            if (result == BAD_ROAD) {
                removeNextInt(edge->routes);
            }
            if (result == ALLOCATION_SUCCESS)
                return ALLOCATION_SUCCESS;
        }
    }
    assert(from >= 0); //should always be
    Edge *edge2 = findEdgeTo(map->graph->tab[where], from);
    removeNextInt(edge2->routes);
    return BAD_ROAD;
}

int markRoute(Map *map, int route, uint64_t *dist, int start, int finish) {
    IntPair result = checkRouteDfs(map, route, dist, finish, INT_MAX, start);
    if (result.second == true) {
        int res = markRouteDfs(map, route, dist, finish, result.first, -1, start);
        if (res == ALLOCATION_FAILURE)
            return ALLOCATION_FAILURE;
    }
    else
        return ALLOCATION_FAILURE;
    return ALLOCATION_SUCCESS;
}

bool isOnRoute(Map *map, int route, int city) {
    int start = map->routes[route].start;
    int finish = map->routes[route].finish;
    int last = -1;
    Vertex *vertex = map->graph->tab[start];
    while (vertex->number != finish) {
        if (vertex->number == city) {
            return true;
        }
        Edge *edge = findEdgeWithRoute(vertex, route, last);
        last = vertex->number;
        vertex = map->graph->tab[edge->where];
    }
    return city == finish;
}