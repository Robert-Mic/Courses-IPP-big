//
// Created by rober on 24.04.2019.
//

#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "constants.h"
#include "list_citylist.h"

CityList* newCityList(const char *name, int number) {
    char *new_mem = myStrdup(name);
    if (new_mem == NULL)
        return NULL;

    CityList* list = malloc(sizeof(CityList));
    if (list == NULL) {
        return NULL;
    }
    list->name = new_mem;
    list->number = number;
    list->next = NULL;
    return list;
}

int addCityAfter(CityList *where, const char *name, int number) {
    CityList *new_city = newCityList(name, number);
    if (new_city == NULL) {
        return ALLOCATION_FAILURE;
    }

    new_city->next = where->next;
    where->next = new_city;
    return ALLOCATION_SUCCESS;
}

void addCityList(CityList *where, CityList *list) {
    where->next = list;
}

void freeCityList(CityList *list) {
    if (list == NULL)
        return;
    if (list->next != NULL)
        freeCityList(list->next);
    free(list->name);
    free(list);
}

void removeNextCity(CityList *it) {
    if (it == NULL || it->next == NULL)
        return;
    CityList *save = it->next;
    it->next = save->next;
    save->next = NULL;
    freeCityList(save);
}

CityList* nextCity(CityList *it) {
    if (it == NULL)
        return NULL;
    return it->next;
}