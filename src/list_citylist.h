//
// Created by rober on 24.04.2019.
//

#ifndef DROGI_CITYSLIST_H
#define DROGI_CITYSLIST_H

typedef struct CityList CityList;

struct CityList {
    char *name;
    int number;
    CityList *next;
};

CityList* newCityList(const char *name, int number);

int addCityAfter(CityList *where, const char *name, int number);

void addCityList(CityList *where, CityList *list);

void freeCityList(CityList *list);

CityList* nextCity(CityList *it);

#endif //DROGI_CITYLIST_H
