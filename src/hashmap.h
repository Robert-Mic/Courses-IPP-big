//
// Created by rober on 24.04.2019.
//

#ifndef DROGI_HASHMAP_H
#define DROGI_HASHMAP_H

#define MOD 1770134209
#define TRESHHOLD 0.75

/**
 * A hashmap that converts city names to their corresponding numbers.
 */
typedef struct CityToNumberHashMap CityHashMap;

/** @brief Creates new hashmap.
 *  Creates new empty hashmap. The hashmap resizes itself when necessary.
 * @param size  - Initial size of the structure.
 * @return A pointer to new empty hashmap or NULL if memory allocation fails.
 */
CityHashMap* newHashMap(int size);

/** @brief Adds a new <key, value> pair into hashmap.
 *
 * @param hashmap - The hashmap we add key to.
 * @param key - The key we want to add correlation to.
 * @param number - The value that this key returns.
 * @return On successful memory allocation returns ALLOCATION_SUCCESS,
 * return ALLOCATION_FAILURE otherwise.
 */
int put(CityHashMap *hashmap, const char *key, int number);

/** @brief Frees the memory allocated by hashmap
 *
 * @param hashmap - Pointer to the object we want to free.
 */
void freeHashmap(CityHashMap *hashmap);

/** @brief Find the value of specified key.
 *
 * @param hashmap - Pointer to the hashmap we want to search.
 * @param key - The key we use to search for correlated value.
 * @return
 */
int find(CityHashMap *hashmap, const char *key);

#endif //DROGI_HASHMAP_H
