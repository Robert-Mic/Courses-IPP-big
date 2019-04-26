//
// Created by rober on 26.04.2019.
//

#ifndef DROGI_LOGIC_H
#define DROGI_LOGIC_H

#include "map.h"
#include "Graph.h"
#include "vector_charvector.h"

bool extRoute(Map *map, int route, uint64_t *dist, int start, int finish);

int addOrFree(CharVector *vector, char *val, char *free_buff);

#endif //DROGI_LOGIC_H
