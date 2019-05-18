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


typedef struct Map Map;

/**
 * A structure holding the map of routes.
 */
struct Map {
    CityHashMap *name_to_int; /**< Hashmap that converts city names to indexes.*/
    StringVector *int_to_name;  /**< Remembers the name of the city by given id.*/
    int city_number;  /**< The current number of cities.*/
    VerticeVector *graph;  /**< Structure to hold the graph of roads.*/
    RouteDesc *routes;  /**< Structure holding information about current routes.*/
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
 * @param[in] map – A pointer to the structure that this function
 * deletes.
 */
void deleteMap(Map *map);

/** @brief Adds a road to the map that goes between @p city1 and @p city2.
 * If one of the cities does not exist it creates it and adds the edge
 * between them.
 * @param[in,out] map    – A pointer to the structure that stores the
 * map of roads;
 * @param[in] city1      – A pointer to an array of characters that
 * holds the name of city1;
 * @param[in] city2      – A pointer to an array of characters that
 * holds the name of city2;
 * @param[in] length     – The length of the road in kilometers;
 * @param[in] builtYear  – The initial year the road was created at.
 * @return Returns @p true if the road was successfully added.
 * Returns @p false if one of the following occurred: one of the
 * parameters has illegal value, the city names are identical, the road 
 * between the cities already exists, the function failed to allocate memory.
 */
bool addRoad(Map *map, const char *city1, const char *city2,
             unsigned length, int builtYear);

/** @brief Updates the year the road was created at.
 * Updates the year of last modification of a given road edge, or
 * sets it if it hasn't been yet modificated.
 * @param[in,out] map – A pointer to the structure that stores the map of
 * roads;
 * @param[in] city1 – A pointer to an array of characters that holds the name
 * of city1;
 * @param[in] city2 – A pointer to an array of characters that holds the name
 * of city2;
 * @param[in] repairYear – The year of the last modification.
 * @return Returns @p true, if the update succeeded.
 * Returns @p false if one of the following occurred: one of the parameters has
 * illegal value, one of the cities does not exists, there is no existing road
 * edge between the two cities, the specified year if older that the year stored
 * before on the edge, the function failed to allocate memory.
 */
bool repairRoad(Map *map, const char *city1, const char *city2, int repairYear);

/** @brief Creates a route between two cities.
 * Creates a route between two cities and sets it the specified ID.
 * This function searches for the shortest path between the two cities, and
 * if there is more than one option, it picks the path where oldest path
 * is the youngest.
 * @param[in,out] map – A pointer to the structure that stores the map of
 * roads;
 * @param[in] routeId – route ID;
 * @param[in] city1 – A pointer to an array of characters that holds the name
 * of city1;
 * @param[in] city2 – A pointer to an array of characters that holds the name
 * of city2;
 * @return Returns @p true if the route was successfully created.
 * Returns @p false if one of the following occurred: one of the parameters has
 * illegal value, a route of the specified number already exists, at least one
 * of the specified cities does not exist, both city names are identical, the
 * function could not unambiguously choose the path, the function failed to
 * allocate memory.
 */
bool newRoute(Map *map, unsigned routeId,
              const char *city1, const char *city2);

/** @brief Extends the route to the specified city.
 * Adds to the specified route new edges in such a way that the newly created
 * path is the shortest. If there is more that one possible way to do this,
 * it chooses the set of road edges where oldest edge is the youngest.
 * @param[in,out] map – A pointer to the structure that stores the map of
 * roads;
 * @param[in] routeId – route ID;
 * @param[in] city – A pointer to an array of characters that holds the name
 * of city1;
 * @return Returns @p true if the route was successfully extended.
 * Returns @p false if one of the following occurred: one of the specified
 * parameters has illegal value, the city with the specified name does not
 * exist, the route already traverses through the specified city, the specified
 * route ends in the specified city, the function could not unambiguously choose
 * the path, the function failed to allocate memory.
 */
bool extendRoute(Map *map, unsigned routeId, const char *city);

/** @brief Removes a road edge between the two cities.
 * Removes a road edge between specified cities. If the removal creates a split
 * on a path of a route then the function searches for a new path in between
 * the @p city1 and @p city2 and chooses the shortest one. If there is more than
 * one option to pick the shortest path then it chooses the set of road edges
 * where oldest edge is the youngest.
 * @param[in,out] map – A pointer to the structure that stores the map of
 * roads;
 * @param[in] city1 – A pointer to an array of characters that holds the name
 * of city1;
 * @param[in] city2 – A pointer to an array of characters that holds the name
 * of city2;
 * @return Returns @p true if the edge was successfully deleted.
 * Returns @p false if one of the following occurred: one of the specified
 * parameters has illegal value, the city with the specified name does not
 * exist, there is no edge between the cities, the function could not
 * unambiguously choose the path, the function failed to allocate memory.
 */
bool removeRoad(Map *map, const char *city1, const char *city2);

/** @brief Gets the information about currently existing route.
 * Returns a pointer to a string containing information about a route.
 * Allocates memory for this string. Returns an empty string if a route with
 * the specified number does not exist. Allocated memory has to be freed by
 * function free. The information is in the following format:
 * route number;city name;length of the edge;year of the edge;city name;length;
 * year;...;city name.
 * The cities are in the same order the route traverses through them.
 * @param[in,out] map – A pointer to the structure that stores the map of
 * roads;
 * @param[in] routeId – route ID;
 * @return A pointer to the string or NULL if the function fails to allocate
 * memory.
 */
char const* getRouteDescription(Map *map, unsigned routeId);

#endif /* __MAP_H__ */
