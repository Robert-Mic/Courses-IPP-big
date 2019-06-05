/** @file
 * Hashmap class interface.
 *
 * @author Robert Michna <rm406247@students.mimuw.edu.pl>
 * @copyright Uniwersytet Warszawski
 * @date 25.03.2019
 */

#ifndef DROGI_HASHMAP_H
#define DROGI_HASHMAP_H

/// The default prime MODULO number.
#define MOD 1770134209
/// The default threshold after which we resize the hashmap.
#define THRESHHOLD 0.75
/// A value signalizing that no value was found.
#define NOT_FOUND -1

/**
 * A hashmap that converts city name strings to their corresponding numbers.
 */
typedef struct CityToNumberHashMap CityHashMap;

/** @brief Creates new hashmap.
 *  Creates new empty hashmap. The hashmap resizes itself when necessary.
 * @param[in] size  - Initial size of the structure.
 * @return A pointer to new empty hashmap or NULL if memory allocation fails.
 */
CityHashMap* newHashMap(int size);

/** @brief Adds a new <key, value> pair into hashmap.
 *
 * @param[in,out] hashmap - The hashmap we add key to.
 * @param[in] key - The key we want to add correlation to.
 * @param[in] number - The value that this key returns.
 * @return On successful memory allocation returns ALLOCATION_SUCCESS,
 * return ALLOCATION_FAILURE otherwise.
 */
int put(CityHashMap *hashmap, const char *key, int number);

/** @brief Frees the memory allocated by hashmap
 *
 * @param[in] hashmap - Pointer to the object we want to free.
 */
void freeHashmap(CityHashMap *hashmap);

/** @brief Find the value of specified key.
 *
 * @param[in] hashmap - Pointer to the hashmap we want to search.
 * @param[in] key - The key we use to search for correlated value.
 * @return Returns an integer paired to the given key or @p NOT_FOUND constant
 * if no such key is contained.
 */
int find(CityHashMap *hashmap, const char *key);

#endif //DROGI_HASHMAP_H
