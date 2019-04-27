//
// Created by rober on 25.04.2019.
//

#include <stdlib.h>
#include "constants.h"
#include "list_intlist.h"

IntList* newIntList(int val) {
    IntList* list = malloc(sizeof(IntList));
    if (list == NULL) {
        return NULL;
    }
    list->val = val;
    list->next = NULL;
    return list;
}

int addIntAfter(IntList *where, int val) {
    IntList *new_int = newIntList(val);
    if (new_int == NULL)
        return ALLOCATION_FAILURE;

    new_int->next = where->next;
    where->next = new_int;

    return ALLOCATION_SUCCESS;
}

void addIntList(IntList *where, IntList *list) {
    where->next = list;
}

void freeIntList(IntList *list) {
    if (list == NULL)
        return;
    if (list->next != NULL)
        freeIntList(list->next);
    free(list);
}

void removeNextInt(IntList *it) {
    if (it == NULL || it->next == NULL)
        return;
    IntList *save = it->next;
    it->next = save->next;
    save->next = NULL;
    freeIntList(save);
}

IntList* nextInt(IntList *it) {
    if (it == NULL)
        return NULL;
    return it->next;
}

IntList* copy(IntList *old) {
    IntList *ret = newIntList(-1);
    if (ret == NULL)
        return NULL;
    while (old) {
        if (addIntAfter(ret, old->val) == ALLOCATION_FAILURE) {
            freeIntList(ret);
            return NULL;
        }
        nextInt(old);
    }
}