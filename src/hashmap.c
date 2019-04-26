//
// Created by rober on 24.04.2019.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "list_citylist.h"
#include "constants.h"
#include "hashmap.h"

struct CityToNumberHashMap {
    int size;
    int current_load;
    CityList **city_list;
};

CityHashMap* newHashMap(int size) {
    CityHashMap *hashmap = malloc(sizeof(CityHashMap));
    if (hashmap == NULL){
        return hashmap;
    }
    hashmap->size = size;
    hashmap->current_load = 0;
    hashmap->city_list = malloc(sizeof(CityList*) * size);
    if (hashmap->city_list == NULL) {
        free(hashmap);
        return NULL;
    }
    for (int i = 0; i < size; i++) {
        hashmap->city_list[i] = newCityList("", -1);
        if (hashmap->city_list[i] == NULL) {
            for (int j = i - 1; j >= 0; j--) {
                freeCityList(hashmap->city_list[j]);
            }
            free(hashmap->city_list);
            free(hashmap);
            return NULL;
        }
    }
    return hashmap;
}

int getHash(const char *key, int size) {
    uint64_t hash = 0, pow = 1;
    int i = 0;
    while (key[i] != 0) {
        unsigned char val = (unsigned char)key[i];
        hash += (uint64_t)val * pow;
        pow *= 256 - 22;
        pow %= MOD;
        hash %= MOD;
        i++;
    }
    return (int)(hash % size);
}

int resize(CityHashMap *hashmap) {
    CityHashMap *new_hashmap = newHashMap(hashmap->size * 2);
    if (new_hashmap == NULL)
        return ALLOCATION_FAILURE;

    for (int i = 0; i < hashmap->size; i++) {
        CityList *iter = hashmap->city_list[i]->next;
        while (iter) {
            if (put(new_hashmap, iter->name, iter->number) == ALLOCATION_FAILURE) {
                freeHashmap(new_hashmap);
                return ALLOCATION_FAILURE;
            }
            iter = nextCity(iter);
        }
    }
    for (int i = 0; i < hashmap->size; i++) {
        freeCityList(hashmap->city_list[i]);
    }
    free(hashmap->city_list);

    hashmap->size = new_hashmap->size;
    hashmap->current_load = new_hashmap->current_load;
    hashmap->city_list = new_hashmap->city_list;
    free(new_hashmap);

    return ALLOCATION_SUCCESS;
}

int put(CityHashMap *hashmap, const char *key, int number) {
    int hash = getHash(key, hashmap->size);
    ///////////////////////////////////////printf("key = %s, hash = %d\n", key, hash);
    // list iterator
    CityList *iter = hashmap->city_list[hash]->next;
    int increase_load = (iter == NULL);

    int key_exists = false;

    while (iter) {
        //////////////////////////printf("key1 = %s , key2 = %s\n", iter->name, key);
        if (strcmp(iter->name, key) == 0) {
            //////////////////////printf("ok\n");
            iter->number = number;
            key_exists = true;
        }
        iter = nextCity(iter);
    }

    if (key_exists == false) {
        if (addCityAfter(hashmap->city_list[hash], key, number) == ALLOCATION_FAILURE) {
            return ALLOCATION_FAILURE;
        }
    }

    hashmap->current_load += increase_load;
    if ((float)hashmap->current_load / (float)hashmap->size >= TRESHHOLD) {
        return resize(hashmap);
    }
    return ALLOCATION_SUCCESS;
}

int find(CityHashMap *hashmap, const char *key) {
    int hash = getHash(key, hashmap->size);
    ///////////////////////printf("key = %s, hash = %d\n", key, hash);
    CityList *iter = hashmap->city_list[hash]->next;
    while (iter) {
        ///////////////////printf("Look at iter = %s, %d\n", iter->name, iter->number);
        if (strcmp(iter->name, key) == 0) {
            return iter->number;
        }
        iter = nextCity(iter);
    }
    return -1;
}

void freeHashmap(CityHashMap *hashmap) {
    for (int i = 0; i < hashmap->size; i++) {
        freeCityList(hashmap->city_list[i]);
    }
    free(hashmap->city_list);
    free(hashmap);
}
