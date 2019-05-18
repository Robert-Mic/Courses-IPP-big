//
// Created by rober on 16.05.2019.
//

#include <string.h>
#include <stdio.h>
#include <limits.h>
#include <inttypes.h>
#include <stdlib.h>
#include "input_parse.h"
#include "utils.h"
#include "logic.h"


void error(uint64_t nr) {
    fprintf(stderr, "ERROR %"PRId64"\n", nr);
}

/// 0 signales invalid input as it is not a valid argument for map functions
int getNumber(const char *number) {
    int ret = 0;
    int i = 0;
    int mult = 1;

    if (number[0] == '-') {
        mult = -1;
        i = 1;
    }

    for (; number[i] >= '0' && number[i] <= '9'; i++) {

        if (ret > INT_MAX / 10 || ret * 10 > INT_MAX - (number[i] - '0'))
            return 0; //value too big

        ret *= 10;
        ret += number[i] - '0';
    }

    if (number[i] != 0)
        return 0; //input should end null character
    return ret * mult;
}

int parseRouteDescription(Map *map, char **args) {
    int route = getNumber(args[0]);
    if (route <= 0 || route >= MAX_ROUTES || map->routes[route].start != -1)
        return COMMAND_FAILED;

    bool loop = true;
    int i = 1;

    while (loop) {  // The command must be valid
        if (args[i + 1] == NULL || args[i + 2] == NULL || args[i + 3] == NULL)
            return COMMAND_FAILED;
        if (invalidCityName(args[i]))
            return COMMAND_FAILED;
        if (invalidCityName(args[i + 3]))
            return COMMAND_FAILED;
        int length = getNumber(args[i + 1]);
        int date = getNumber(args[i + 2]);
        if (date == 0 || length <= 0)
            return COMMAND_FAILED;

        int city1_num = find(map->name_to_int, args[i]);
        int city2_num = find(map->name_to_int, args[i + 3]);

        if (city1_num != NOT_FOUND && city2_num != NOT_FOUND) {
            Edge *edge = findEdgeTo(map->graph->tab[city1_num], city2_num);
            if (edge) {
                if (edge->length != length || edge->year > date)
                    return COMMAND_FAILED;
            }
        }
        i += 3;
        if (args[i + 1] == NULL)
            loop = false;
    }

    loop = true;
    i = 1;

    while (loop) {
        int length = getNumber(args[i + 1]);
        int date = getNumber(args[i + 2]);
        if (date == 0 || length <= 0)
            return COMMAND_FAILED;

        int city1_num = find(map->name_to_int, args[i]);
        int city2_num = find(map->name_to_int, args[i + 3]);

        if (city1_num == NOT_FOUND || city2_num == NOT_FOUND) {
            if (!addRoad(map, args[i], args[i + 3], (unsigned)length, date))
                return MEMORY_ERROR;
        }
        else {
            Edge *edge = findEdgeTo(map->graph->tab[city1_num], city2_num);
            if (edge) {
                if (!repairRoad(map, args[i], args[i + 3], date))
                    return MEMORY_ERROR;
            }
            else {
                if (!addRoad(map, args[i], args[i + 3], (unsigned)length, date))
                    return MEMORY_ERROR;
            }
        }
        i += 3;
        if (args[i + 1] == NULL)
            loop = false;
    }

    IntList *route_path = newIntList(-1);
    IntList *it = route_path;
    for (int j = 1; j <= i; j += 3) {
        if (addIntAfter(it, find(map->name_to_int, args[j])) == ALLOCATION_FAILURE) {
            freeIntList(route_path);
            return MEMORY_ERROR;
        }
        it = it->next;
    }
    if (markRouteByList(map, route, route_path) == ALLOCATION_FAILURE) {
        freeIntList(route_path);
        return MEMORY_ERROR;
    }

    map->routes[route].start = find(map->name_to_int, args[1]);
    map->routes[route].finish = find(map->name_to_int, args[i]);
    freeIntList(route_path);

    return COMMAND_SUCCEEDED;
}

int parseInput(Map *map, char **args) {
    if (strcmp(args[0], "getRouteDescription") == 0) {
        if (args[1] == NULL || args[2] != NULL)
            return COMMAND_FAILED;

        int route = getNumber(args[1]);
        if (route <= 0 || route >= MAX_ROUTES)
            return COMMAND_FAILED;

        char const *result = getRouteDescription(map, (unsigned)route);
        if (result)
            printf("%s\n", result);
        else
            return COMMAND_FAILED;
        free((void *)result);

        return COMMAND_SUCCEEDED;
    }

    else if (strcmp(args[0], "addRoad") == 0) {
        if (!args[1] || !args[2] || !args[3] || !args[4] || args[5])
            return COMMAND_FAILED;
        int length, year;
        if (
            invalidCityName(args[1])
             || invalidCityName(args[2])
             || (length = getNumber(args[3])) <= 0
             || (year = getNumber(args[4]))  == 0
        )
            return COMMAND_FAILED;

        if (!addRoad(map, args[1], args[2], (unsigned)length, year))
            return COMMAND_FAILED;
        return COMMAND_SUCCEEDED;
    }

    else if (strcmp(args[0], "repairRoad") == 0) {
        if (!args[1] || !args[2] || !args[3] || args[4])
            return COMMAND_FAILED;
        int year;
        if (invalidCityName(args[1])
            || invalidCityName(args[2])
            || (year = getNumber(args[3]))  == 0)
            return COMMAND_FAILED;

        if (!repairRoad(map, args[1], args[2], year))
            return COMMAND_FAILED;
        return COMMAND_SUCCEEDED;
    }

    else if (args[0][0] == '#')
        return COMMAND_SUCCEEDED;

    else if (args[0][0] == 0 && args[1] == NULL)
        return COMMAND_SUCCEEDED;

    else {
        return parseRouteDescription(map, args);
    }
}