/** @file
 * The interface of the class that stores a map of routes.
 *
 * @author Łukasz Kamiński <kamis@mimuw.edu.pl>,
 * Marcin Peczarski <marpe@mimuw.edu.pl>,
 * Robert Michna <rm406247@students.mimuw.edu.pl>
 * @copyright Uniwersytet Warszawski
 * @date 20.03.2019
 */

#ifndef __MAP_H__
#define __MAP_H__

#include <stdbool.h>
#include "hashmap.h"
#include "vector_stringvector.h"
#include "vector_verticevector.h"
#include "routedescription.h"

/**
 * A structure holding the map of routes.
 */
typedef struct Map Map;

struct Map {
    CityHashMap *name_to_int;
    StringVector *int_to_name;
    int city_number;
    VerticeVector *graph;
    RouteDesc *routes;
    int komenda;
};

/** @brief Creates a new map.
 * Creates new, empty structure, that does not hold any city, roads, nor
 * routes.
 * @return A pointer to the created structure or NULL, if memory
 * allocation failed.
 */
Map* newMap(void);

/** @brief Deletes map structure.
 * Deletes the structure pointed to by @p map.
 * Does nothing if the pointer is NULL.
 * @param[in] map        – A pointer to the structure that this function
 * deletes.
 */
void deleteMap(Map *map);

/** @brief Adds a road to the map that goes between @p city1 and @p city2.
 * If one of the cities does not exist it creates it and adds the edge
 * between them.
 * @param[in,out] map    – A pointer to the structure that stores the
 * map of the roads;
 * @param[in] city1      – A pointer to an array of characters that
 * holds the name of city1;
 * @param[in] city2      – A pointer to an array of characters that
 * holds the name of city2;
 * @param[in] length     – The length of the road in kilometers;
 * @param[in] builtYear  – The initial year the road was created at.
 * @return Returns @p true if the road was successfully added.
 * Returns @p false if one of the following occured: one of the
 * parameters has illegal value, the city names are identical, the road 
 * between the cities already exists, the function failed to allocate memory.
 */
bool addRoad(Map *map, const char *city1, const char *city2,
             unsigned length, int builtYear);

/** @brief Updates the year the road was created at.
 * Updates the year of last modification of a given road edge, or
 * sets it if it hasn't been yet modificated.
 * @param[in,out] map    – A pointer to the structure that stores the map of the roads;
 * @param[in] city1      – A pointer to an array of characters that holds the name of city1;
 * @param[in] city2      – A pointer to an array of characters that holds the name of city2;
 * @param[in] repairYear – The year of the last modification.
 * @return Returns @p true, if the update succeeded.
 * Returns @p false if one of the following occured: one of the parameters has illegal value,
 * one of the cities does not exists, there is no existing road edge between the two cities,
 * the specified year if older that the year stored before on the edge, the function failed
 * to allocate memory.
 */
bool repairRoad(Map *map, const char *city1, const char *city2, int repairYear);

/** @brief Creates a route between two cities.
 * Creates a route between two cities and sets it the specified ID.
 * This function searches for the shortest path between the two cities, and
 * if there is more than one option, it picks the path which's oldest path
 * is the youngest.
 * @param[in,out] map    – A pointer to the structure that stores the map of the roads;
 * @param[in] routeId    – route ID;
 * @param[in] city1      – A pointer to an array of characters that holds the name of city1;
 * @param[in] city2      – A pointer to an array of characters that holds the name of city2;
 * @return Returns @p true if the route was successfully created.
 * Returns @p false if one of the following occured: one of the parameters has illegal value,
 * a route of the specified number already exists, at least one of the specified cities does
 * not exist, both city names are identical, the function could not unambiguously choose the
 * path, the function failed to allocate memory.
 */
bool newRoute(Map *map, unsigned routeId,
              const char *city1, const char *city2);

/** @brief Extends the route to the specified city.
 * Adds to the specified route new edges in such a way that the newly created path
 * is the shortest. If there is more that one possible way to do this, it picks
 * the set of road edges which oldest edge is the youngest.
 * @param[in,out] map    – A pointer to the structure that stores the map of the roads;
 * @param[in] routeId    – route ID;
 * @param[in] city      – A pointer to an array of characters that holds the name of city1;
 * @return Returns @p true if the route was successfully extended.
 * Returns @p false if one of the following occured: one of the specified parameters has
 * illegal value, the city with the specified name does not exist, the route already traverses
 * through the specified city, the specified route ends in the specified city, the function could
 * not unambiguously choose the path, the function failed to allocate memory.
 */
bool extendRoute(Map *map, unsigned routeId, const char *city);

/** @brief Removes a road edge between the two cities.
 * Removes a road edge between specified cities. Jeśli usunięcie tego odcinka drogi
 * powoduje przerwanie ciągu jakiejś drogi krajowej, to uzupełnia ją
 * istniejącymi odcinkami dróg w taki sposób, aby była najkrótsza. Jeśli jest
 * więcej niż jeden sposób takiego uzupełnienia, to dla każdego wariantu
 * wyznacza wśród dodawanych odcinków drogi ten, który był najdawniej wybudowany
 * lub remontowany i wybiera wariant z odcinkiem, który jest najmłodszy.
 * @param[in,out] map    – wskaźnik na strukturę przechowującą mapę dróg;
 * @param[in] city1      – wskaźnik na napis reprezentujący nazwę miasta;
 * @param[in] city2      – wskaźnik na napis reprezentujący nazwę miasta.
 * @return Wartość @p true, jeśli odcinek drogi został usunięty.
 * Wartość @p false, jeśli z powodu błędu nie można usunąć tego odcinka drogi:
 * któryś z parametrów ma niepoprawną wartość, nie ma któregoś z podanych miast,
 * nie istnieje droga między podanymi miastami, nie da się jednoznacznie
 * uzupełnić przerwanego ciągu drogi krajowej lub nie udało się zaalokować
 * pamięci.
 */
bool removeRoad(Map *map, const char *city1, const char *city2);

/** @brief Gets the information about currently existing route.
 * Zwraca wskaźnik na napis, który zawiera informacje o drodze krajowej. Alokuje
 * pamięć na ten napis. Zwraca pusty napis, jeśli nie istnieje droga krajowa
 * o podanym numerze. Zaalokowaną pamięć trzeba zwolnić za pomocą funkcji free.
 * Informacje wypisywane są w formacie:
 * numer drogi krajowej;nazwa miasta;długość odcinka drogi;rok budowy lub
 * ostatniego remontu;nazwa miasta;długość odcinka drogi;rok budowy lub
 * ostatniego remontu;nazwa miasta;…;nazwa miasta.
 * Kolejność miast na liście jest taka, aby miasta @p city1 i @p city2, podane
 * w wywołaniu funkcji @ref newRoute, które utworzyło tę drogę krajową, zostały
 * wypisane w tej kolejności.
 * @param[in,out] map    – wskaźnik na strukturę przechowującą mapę dróg;
 * @param[in] routeId    – numer drogi krajowej.
 * @return Wskaźnik na napis lub NULL, gdy nie udało się zaalokować pamięci.
 */
char const* getRouteDescription(Map *map, unsigned routeId);

#endif /* __MAP_H__ */
