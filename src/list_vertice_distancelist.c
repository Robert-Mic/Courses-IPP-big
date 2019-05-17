//
// Created by rober on 26.04.2019.
//


#include <stdlib.h>
#include "constants.h"
#include "list_vertice_distancelist.h"

DistList* newDistList(Vertice *vertice, uint64_t distance) {
    DistList* list = malloc(sizeof(DistList));
    if (list == NULL) {
        return NULL;
    }
    list->vertice = vertice;
    list->dist = distance;
    list->next = NULL;
    return list;
}

int addDistAfter(DistList *where, Vertice *vertice, uint64_t distance) {
    DistList *new_dist = newDistList(vertice, distance);
    if (new_dist == NULL) {
        return ALLOCATION_FAILURE;
    }

    new_dist->next = where->next;
    where->next = new_dist;
    return ALLOCATION_SUCCESS;
}

void addDistList(DistList *where, DistList *list) {
    where->next = list;
}

void freeDistList(DistList *list) {
    if (list == NULL)
        return;
    if (list->next != NULL)
        freeDistList(list->next);
    free(list);
}

void removeNextDist(DistList *it) {
    if (it == NULL || it->next == NULL)
        return;
    DistList *save = it->next;
    it->next = save->next;
    save->next = NULL;
    freeDistList(save);
}

DistList* nextDist(DistList *it) {
    if (it == NULL)
        return NULL;
    return it->next;
}

int isEmptyDistList(DistList *it) {
    return it->next == NULL;
}

DistList* findMin(DistList *it) {
    DistList *iter = it->next;
    DistList *min = iter;
    while (iter) {
        if (iter->dist < min->dist)
            min = iter;
        iter = nextDist(iter);
    }
    return min;
}

DistList* findBeforeMin(DistList *it) {
    DistList *iter = it->next;
    DistList *prev = it;
    DistList *ret = it;
    DistList *min = iter;
    while (iter) {
        if (iter->dist < min->dist) {
            min = iter;
            ret = prev;
        }
        prev = iter;
        iter = nextDist(iter);
    }
    return ret;
}