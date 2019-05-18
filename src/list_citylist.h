/** @file
 * CityList class interface.
 *
 * @author Robert Michna <rm406247@students.mimuw.edu.pl>
 * @copyright Uniwersytet Warszawski
 * @date 10.04.2019
 */

#ifndef DROGI_CITYSLIST_H
#define DROGI_CITYSLIST_H

typedef struct CityList CityList;

/**
 * Structure holding <key, value> pairs for hashmap as well as a pointer to next
 * list element. @see hashmap.h
 */
struct CityList {
    char *name; /**< a string key.*/
    int number;  /**< an int value paired to the key. Must be positive.*/
    CityList *next; /**< pointer to the next <key,value> pair or NULL.*/
};

/** @brief Creates new CityList.
 * Creates new CityList. Keeps a deep copy of city name. Has to be freed
 * by @ref freeCityList.
 * @param[in] name - String containing the name of the city.
 * @param[in] number - The number assigned to this city's name.
 * @return New CityList structure or NULL if memory allocation failed.
 */
CityList* newCityList(const char *name, int number);

/** @brief adds a @p <key,value> pair to the list after the specified element.
 *
 * @param[in] where - A pointer to the list element after which we insert the pair.
 * @param[in] name - The string key.
 * @param[in] number - The paired int value.
 * @return On successful memory allocation returns @p ALLOCATION_SUCCESS.
 * If memory allocation fails it returns @p ALLOCATION_FAILURE.
 */
int addCityAfter(CityList *where, const char *name, int number);

/** @brief Frees the memory allocated by structure pointed by @p list.
 *
 * @param[in] list - A pointer to the CityList structure we want to delete.
 */
void freeCityList(CityList *list);

/** @brief Returns a pointer to the next element of the list.
 *
 * @param[in] it - A pointer to the CityList list.
 * @return A pointer to the next CityList in the list or NULL if there is no
 * next CityList.
 */
CityList* nextCity(CityList *it);

#endif //DROGI_CITYLIST_H
