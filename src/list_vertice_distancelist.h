//
// Created by rober on 26.04.2019.
//

#ifndef DROGI_LIST_VERTICE_DISTANCELIST_H
#define DROGI_LIST_VERTICE_DISTANCELIST_H

#include <stdint.h>
#include "vertice.h"

typedef struct VerticeDistanceList DistList;

struct VerticeDistanceList {
    uint64_t dist;
    Vertice *vertice;
    DistList *next;
};

DistList* newDistList(Vertice *vertice, uint64_t distance);

int addDistAfter(DistList *where, Vertice *vertice, uint64_t distance);

void addDistList(DistList *where, DistList *list);

void freeDistList(DistList *list);

void removeNextDist(DistList *it);

DistList* nextDist(DistList *it);

int isEmptyDistList(DistList *it);

DistList* findMin(DistList *it);

DistList* findBeforeMin(DistList *it);

#endif //DROGI_LIST_VERTICE_DISTANCELIST_H
