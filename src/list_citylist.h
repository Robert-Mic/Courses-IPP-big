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
    char *name;
    int number;
    CityList *next;
};

/** @brief Creates new CityList.
 * Creates new CityList. Keeps a deep copy of city name. Has to be freed
 * by freeCityList().
 * @param name - String containing the name of the city.
 * @param number - The number assigned to this city's name.
 * @return New CityList structure.
 */
CityList* newCityList(const char *name, int number);

int addCityAfter(CityList *where, const char *name, int number);

void addCityList(CityList *where, CityList *list);

void freeCityList(CityList *list);

CityList* nextCity(CityList *it);

#endif //DROGI_CITYLIST_H
