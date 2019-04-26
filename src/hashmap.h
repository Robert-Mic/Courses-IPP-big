//
// Created by rober on 24.04.2019.
//

#ifndef DROGI_HASHMAP_H
#define DROGI_HASHMAP_H

#define MOD 1770134209
#define TRESHHOLD 0.75

typedef struct CityToNumberHashMap CityHashMap;

CityHashMap* newHashMap(int size);

int put(CityHashMap *hashmap, const char *key, int number);

void freeHashmap(CityHashMap *hashmap);

int find(CityHashMap *hashmap, const char *key);

#endif //DROGI_HASHMAP_H
