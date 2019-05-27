#include "map.h"
#include "hashmap.h"
#include "routedescription.h"
#include "vector_stringvector.h"
#include "vector_vertexvector.h"
#include "vector_charvector.h"
#include "logic.h"
#include "constants.h"
#include "Graph.h"
#include <limits.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>
#include <assert.h>
#include <stdio.h>

Map* newMap(void) {
    Map* map = malloc(sizeof(Map));
    if (!map)
        return NULL;

    map->city_number = 0;

    map->name_to_int = newHashMap(100);
    if (map->name_to_int == NULL) {
        free(map);
        return NULL;
    }

    map->int_to_name = newStringVector();
    if (map->int_to_name == NULL) {
        freeHashmap(map->name_to_int);
        free(map);
        return NULL;
    }

    map->graph = newVertexVector();
    if (map->graph == NULL) {
        freeHashmap(map->name_to_int);
        freeStringVector(map->int_to_name);
        free(map);
        return NULL;
    }

    map->routes = malloc(sizeof(RouteDesc) * MAX_ROUTES);
    if (map->routes == NULL) {
        freeHashmap(map->name_to_int);
        freeStringVector(map->int_to_name);
        freeVertexVector(map->graph);
        free(map);
        return NULL;
    }

    for (int i = 0; i < MAX_ROUTES; i++) {
        map->routes[i] = newRouteDesc(-1, -1);
    }

    return map;
}

void deleteMap(Map *map) {
    if (map == NULL)
        return;
    freeHashmap(map->name_to_int);
    freeStringVector(map->int_to_name);
    freeVertexVector(map->graph);
    free(map->routes);
    free(map);
}

bool addRoad(Map *map, const char *city1, const char *city2,
             unsigned length, int builtYear) {
    if (strcmp(city1, city2) == 0
        || builtYear == 0
        || invalidCityName(city1)
        || invalidCityName(city2)
        || length <= 0) {
        return false;
    }

    int city1_num = find(map->name_to_int, city1);
    int city2_num = find(map->name_to_int, city2);

    if (city1_num == NOT_FOUND) {
        if (put(map->name_to_int, city1, map->city_number) == ALLOCATION_FAILURE) {
            return false;
        }

        if (stringVectorPush(map->int_to_name, city1) == ALLOCATION_FAILURE) {
            return false;
        }

        Vertex *city1_vertex = newVertex(map->city_number);
        if (city1_vertex == NULL) {
            stringVectorPop(map->int_to_name);
            return false;
        }

        if (vertexVectorPush(map->graph, city1_vertex) == ALLOCATION_FAILURE) {
            stringVectorPop(map->int_to_name);
            freeVertex(city1_vertex);
            return false;
        }

        city1_num = map->city_number;
        map->city_number++;
    }

    if (city2_num == NOT_FOUND) {
        if (put(map->name_to_int, city2, map->city_number) == ALLOCATION_FAILURE) {
            return false;
        }

        if (stringVectorPush(map->int_to_name, city2) == ALLOCATION_FAILURE) {
            return false;
        }

        Vertex *city2_vertex = newVertex(map->city_number);
        if (city2_vertex == NULL) {
            stringVectorPop(map->int_to_name);
            return false;
        }

        if (vertexVectorPush(map->graph, city2_vertex) == ALLOCATION_FAILURE) {
            stringVectorPop(map->int_to_name);
            freeVertex(city2_vertex);
            return false;
        }

        city2_num = map->city_number;
        map->city_number++;
    }

    if (findEdgeTo(map->graph->tab[city1_num], city2_num)) {
        return false;
    }

    if (addEdge(map->graph->tab[city1_num], city2_num, length, builtYear) == ALLOCATION_FAILURE) {
        return false;
    }

    if (addEdge(map->graph->tab[city2_num], city1_num, length, builtYear) == ALLOCATION_FAILURE) {
        removeEdge(map->graph->tab[city1_num], city2_num);
        return false;
    }

    return true;
}

bool repairRoad(Map *map, const char *city1, const char *city2, int repairYear) {
    if (strcmp(city1, city2) == 0
        || repairYear == 0
        || invalidCityName(city1)
        || invalidCityName(city2)) {
        return false;
    }

    int city1_num = find(map->name_to_int, city1);
    int city2_num = find(map->name_to_int, city2);

    if (city1_num == NOT_FOUND || city2_num == NOT_FOUND) {
        return false;
    }

    Edge *edge1 = findEdgeTo(map->graph->tab[city1_num], city2_num);
    Edge *edge2 = findEdgeTo(map->graph->tab[city2_num], city1_num);

    if (edge1 == NULL || edge1->year > repairYear)
        return false;

    edge1->year = repairYear;
    edge2->year = repairYear;

    return true;
}

bool newRoute(Map *map, unsigned routeId,
              const char *city1, const char *city2) {
    if (routeId <= 0
        || routeId >= MAX_ROUTES
        || invalidCityName(city1)
        || invalidCityName(city2)
        || map->routes[routeId].start != -1
        || strcmp(city1, city2) == 0)
        return false;

    int city1_num = find(map->name_to_int, city1);
    int city2_num = find(map->name_to_int, city2);

    if (city1_num == NOT_FOUND || city2_num == NOT_FOUND) {
        return false;
    }

    uint64_t *dist = malloc(sizeof(uint64_t) * map->city_number);
    if (dist == NULL) {
        return false;
    }

    map->routes[routeId].start = city1_num;
    map->routes[routeId].finish = city2_num;
    if (dijkstra(map, -1, dist, city1_num, city2_num) == ALLOCATION_FAILURE) {
        map->routes[routeId].start = -1;
        free(dist);
        return false;
    }
    if (dist[city2_num] == UINT64_MAX) {
        map->routes[routeId].start = -1;
        free(dist);
        return false;
    }
    if (markRoute(map, routeId, dist, city1_num, city2_num) == ALLOCATION_FAILURE) {
        map->routes[routeId].start = -1;
        free(dist);
        return false;
    }
    free(dist);
    return true;
}

bool extendRoute(Map *map, unsigned routeId, const char *city) {
    if (routeId <= 0
        || routeId >= MAX_ROUTES
        || invalidCityName(city)
        || map->routes[routeId].start == -1)
        return false;

    int city_num = find(map->name_to_int, city);
    if (city_num == NOT_FOUND) {
        return false;
    }

    if (isOnRoute(map, routeId, city_num)) {
        return false;
    }

    uint64_t *dist = malloc(sizeof(uint64_t) * map->city_number);
    if (dist == NULL) {
        return false;
    }

    int start = map->routes[routeId].start;
    int finish = map->routes[routeId].finish;
    uint64_t distance1, distance2;

    if (dijkstra(map, routeId, dist, finish, city_num) == ALLOCATION_FAILURE) {
        free(dist);
        return false;
    }
    distance1 = dist[city_num];

    if (dijkstra(map, routeId, dist, city_num, start) == ALLOCATION_FAILURE) {
        free(dist);
        return false;
    }
    distance2 = dist[start];
    if (distance1 == UINT64_MAX && distance2 == UINT64_MAX) {
        free(dist);
        return false;
    }

    if (distance1 == UINT64_MAX && distance2 == UINT64_MAX) {
        free(dist);
        return false;
    }

    if (distance1 < distance2) {
        if (dijkstra(map, routeId, dist, finish, city_num) == ALLOCATION_FAILURE) {
            free(dist);
            return false;
        }
        if (markRoute(map, routeId, dist, finish, city_num) == ALLOCATION_FAILURE) {
            free(dist);
            return false;
        }
        map->routes[routeId].finish = city_num;
    }
    else if (distance2 < distance1) {
        if (markRoute(map, routeId, dist, city_num, start) == ALLOCATION_FAILURE) {
            free(dist);
            return false;
        }
        map->routes[routeId].start = city_num;
    }
    else { //both distances are equal and different than UINT64_MAX
        IntPair result2 = checkRouteDfs(map, routeId, dist, start, INT_MAX, city_num);
        if (dijkstra(map, routeId, dist, finish, city_num) == ALLOCATION_FAILURE) {
            free(dist);
            return false;
        }
        IntPair result1 = checkRouteDfs(map, routeId, dist, city_num, INT_MAX, finish);
        if (result1.first > result2.first) {
            if (result1.second == false) {
                free(dist);
                return false;
            }
            return extRoute(map, routeId, dist, finish, city_num);
        }
        else if (result2.first > result1.first) {
            if (result2.second == false) {
                free(dist);
                return false;
            }
            return extRoute(map, routeId, dist, city_num, start);
        }
        else {
            free(dist);
            return false;
        }
    }
    free(dist);
    return true;
}

bool removeRoad(Map *map, const char *city1, const char *city2) {
    if (invalidCityName(city1)
        || invalidCityName(city2))
        return false;

    int city1_num = find(map->name_to_int, city1);
    int city2_num = find(map->name_to_int, city2);

    if (city1_num == NOT_FOUND || city2_num == NOT_FOUND) {
        return false;
    }

    Edge *edge = findEdgeTo(map->graph->tab[city1_num], city2_num);
    if (edge == NULL) {
        return false;
    }

    uint64_t *dist = malloc(sizeof(uint64_t) * map->city_number);
    if (dist == NULL) {
        return false;
    }

    IntList *routes = edge->routes;
    unsigned length = edge->length;
    int year = edge->year;
    edge->routes = NULL;

    IntList *iter = routes->next;
    bool can_be_deleted = true;

    removeEdge(map->graph->tab[city1_num], city2_num);
    removeEdge(map->graph->tab[city2_num], city1_num);

    while (iter) {
        int route = iter->val;
        if (dijkstra2(map, route, dist, city1_num, city2_num) == ALLOCATION_FAILURE) {
            can_be_deleted = false;
        }
        if (dist[city2_num] == UINT64_MAX) {
            can_be_deleted = false;
        }
        IntPair res = checkRouteDfs(map, route, dist, city2_num, INT_MAX, city1_num);
        if (res.second == false) {
            can_be_deleted = false;
        }
        iter = nextInt(iter);
    }
    if (can_be_deleted == false) {
        recoverEdge(map, city1_num, city2_num, routes, length, year); //ignoring value as we return false anyway
        freeIntList(routes);
        free(dist);
        return false;
    }

    iter = routes->next;
    while (iter) {
        int route = iter->val;
        if (dijkstra2(map, route, dist, city1_num, city2_num) == ALLOCATION_FAILURE) {
            free(dist);
            return false;
        }
        int result = markRoute(map, route, dist, city1_num, city2_num);
        if (result == ALLOCATION_FAILURE) {
            free(dist);
            return false;
        }
        iter = nextInt(iter);
    }
    free(dist);
    freeIntList(routes);
    return true;
}

char const* getRouteDescription(Map *map, unsigned routeId) {
    if (routeId <= 0
        || routeId >= MAX_ROUTES
        || map->routes[routeId].start == -1)
        return calloc(1, sizeof(char));

    CharVector *output = newCharVector();
    if (output == NULL)
        return NULL;
    char *buff = malloc(sizeof(char) * 12);
    if (buff == NULL) {
        freeCharVector(output);
        return NULL;
    }

    int route = (int)routeId;
    int start = map->routes[route].start;
    int finish = map->routes[route].finish;
    int last = -1;
    Vertex *vertex = map->graph->tab[start];

    sprintf(buff, "%d", route);
    if (addOrFree(output, buff, buff))
        return NULL;
    if (addOrFree(output, ";", buff))
        return NULL;
    if (addOrFree(output, map->int_to_name->tab[start], buff))
        return NULL;

    while (vertex->number != finish) {
        Edge *edge = findEdgeWithRoute(vertex, route, last);
        if (edge == NULL)
            assert(false);
        if (addOrFree(output, ";", buff))
            return NULL;

        sprintf(buff, "%d", edge->length);
        if (addOrFree(output, buff, buff))
            return NULL;

        if (addOrFree(output, ";", buff))
            return NULL;

        sprintf(buff, "%d", edge->year);
        if (addOrFree(output, buff, buff))
            return NULL;

        if (addOrFree(output, ";", buff))
            return NULL;

        last = vertex->number;
        vertex = map->graph->tab[edge->where];
        if (addOrFree(output, map->int_to_name->tab[vertex->number], buff))
            return NULL;
    }

    if (charVectorPush(output, 0) == ALLOCATION_FAILURE) {
        freeCharVector(output);
        free(buff);
        return NULL;
    }
    char *ret = output->tab;
    free(buff);
    free(output);
    return ret;
}

