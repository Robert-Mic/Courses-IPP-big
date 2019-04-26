#include "map.h"
#include "hashmap.h"
#include "routedescription.h"
#include "vector_stringvector.h"
#include "vector_verticevector.h"
#include "vector_charvector.h"
#include "constants.h"
#include "Graph.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

/**
 * Struktura przechowująca mapę dróg krajowych.
 */
typedef struct Map Map;

/** @brief Tworzy nową strukturę.
 * Tworzy nową, pustą strukturę niezawierającą żadnych miast, odcinków dróg ani
 * dróg krajowych.
 * @return Wskaźnik na utworzoną strukturę lub NULL, gdy nie udało się
 * zaalokować pamięci.
 */
Map* newMap(void) {
    Map* map = malloc(sizeof(Map));
    if (!map)
        return NULL;

    map->city_number = 0;

    map->name_to_int = newHashMap(100);
    if (map->name_to_int == NULL) {
        free(map);
        return NULL;
    }

    map->int_to_name = newStringVector();
    if (map->int_to_name == NULL) {
        freeHashmap(map->name_to_int);
        free(map);
        return NULL;
    }

    map->graph = newVerticeVector();
    if (map->graph == NULL) {
        freeHashmap(map->name_to_int);
        freeStringVector(map->int_to_name);
        free(map);
        return NULL;
    }

    map->routes = malloc(sizeof(RouteDesc) * MAX_ROUTES);
    if (map->routes == NULL) {
        freeHashmap(map->name_to_int);
        freeStringVector(map->int_to_name);
        freeVerticeVector(map->graph);
        free(map);
        return NULL;
    }

    for (int i = 0; i < MAX_ROUTES; i++) {
        map->routes[i] = newRouteDesc(-1, -1);
        //map->routes[i] = NULL;
    }

    return map;
}

/** @brief Usuwa strukturę.
 * Usuwa strukturę wskazywaną przez @p map.
 * Nic nie robi, jeśli wskaźnik ten ma wartość NULL.
 * @param[in] map        – wskaźnik na usuwaną strukturę.
 */
void deleteMap(Map *map) {
    freeHashmap(map->name_to_int);
    freeStringVector(map->int_to_name);
    freeVerticeVector(map->graph);
    free(map->routes);
    /*
    for (int i = 0; i < MAX_ROUTES; i++) {
        freeRouteDesc(map->routes[i]);
    }*/
    free(map);
}

bool invalidCityName(const char *city) {
    int i = 0;
    while (city[i]) {
        unsigned char c = (unsigned char)city[i];
        if (c < 32 || c == ';')
            return true;
        i++;
    }
    return i == 0;
}

/** @brief Dodaje do mapy odcinek drogi między dwoma różnymi miastami.
 * Jeśli któreś z podanych miast nie istnieje, to dodaje go do mapy, a następnie
 * dodaje do mapy odcinek drogi między tymi miastami.
 * @param[in,out] map    – wskaźnik na strukturę przechowującą mapę dróg;
 * @param[in] city1      – wskaźnik na napis reprezentujący nazwę miasta;
 * @param[in] city2      – wskaźnik na napis reprezentujący nazwę miasta;
 * @param[in] length     – długość w km odcinka drogi;
 * @param[in] builtYear  – rok budowy odcinka drogi.
 * @return Wartość @p true, jeśli odcinek drogi został dodany.
 * Wartość @p false, jeśli wystąpił błąd: któryś z parametrów ma niepoprawną
 * wartość, obie podane nazwy miast są identyczne, odcinek drogi między tymi
 * miastami już istnieje lub nie udało się zaalokować pamięci.
 */
bool addRoad(Map *map, const char *city1, const char *city2,
             unsigned length, int builtYear) {

    if (strcmp(city1, city2) == 0
        || builtYear == 0
        || invalidCityName(city1)
        || invalidCityName(city2)) {
        return false;
    }

    int city1_num = find(map->name_to_int, city1);
    int city2_num = find(map->name_to_int, city2);

    if (city1_num == -1) {
        if (put(map->name_to_int, city1, map->city_number) == ALLOCATION_FAILURE) {
            return false;
        }

        if (stringVectorPush(map->int_to_name, city1) == ALLOCATION_FAILURE) {
            return false;
        }

        Vertice *city1_vertice = newVertice(map->city_number);
        if (city1_vertice == NULL) {
            stringVectorPop(map->int_to_name);
            return false;
        }

        if (verticeVectorPush(map->graph, city1_vertice) == ALLOCATION_FAILURE) {
            stringVectorPop(map->int_to_name);
            freeVertice(city1_vertice);
            return false;
        }

        city1_num = map->city_number;
        map->city_number++;
    }

    if (city2_num == -1) {
        if (put(map->name_to_int, city2, map->city_number) == ALLOCATION_FAILURE) {
            return false;
        }

        if (stringVectorPush(map->int_to_name, city2) == ALLOCATION_FAILURE) {
            return false;
        }

        Vertice *city2_vertice = newVertice(map->city_number);
        if (city2_vertice == NULL) {
            stringVectorPop(map->int_to_name);
            return false;
        }

        if (verticeVectorPush(map->graph, city2_vertice) == ALLOCATION_FAILURE) {
            stringVectorPop(map->int_to_name);
            freeVertice(city2_vertice);
            return false;
        }

        city2_num = map->city_number;
        map->city_number++;
    }
    if (findEdgeTo(map->graph->tab[city1_num], city2_num)) {
        return false;
    }

    if (addEdge(map->graph->tab[city1_num], city2_num, length, builtYear) == ALLOCATION_FAILURE) {
        return false;
    }

    if (addEdge(map->graph->tab[city2_num], city1_num, length, builtYear) == ALLOCATION_FAILURE) {
        removeEdge(map->graph->tab[city1_num], city2_num);
        return false;
    }

    return true;
}

/** @brief Modyfikuje rok ostatniego remontu odcinka drogi.
 * Dla odcinka drogi między dwoma miastami zmienia rok jego ostatniego remontu
 * lub ustawia ten rok, jeśli odcinek nie był jeszcze remontowany.
 * @param[in,out] map    – wskaźnik na strukturę przechowującą mapę dróg;
 * @param[in] city1      – wskaźnik na napis reprezentujący nazwę miasta;
 * @param[in] city2      – wskaźnik na napis reprezentujący nazwę miasta;
 * @param[in] repairYear – rok ostatniego remontu odcinka drogi.
 * @return Wartość @p true, jeśli modyfikacja się powiodła.
 * Wartość @p false, jeśli wystąpił błąd: któryś z parametrów ma niepoprawną
 * wartość, któreś z podanych miast nie istnieje, nie ma odcinka drogi między
 * podanymi miastami, podany rok jest wcześniejszy niż zapisany dla tego odcinka
 * drogi rok budowy lub ostatniego remontu.
 */
bool repairRoad(Map *map, const char *city1, const char *city2, int repairYear) {
    if (strcmp(city1, city2) == 0
        || repairYear == 0
        || invalidCityName(city1)
        || invalidCityName(city2)) {
        return false;
    }

    int city1_num = find(map->name_to_int, city1);
    int city2_num = find(map->name_to_int, city2);

    if (city1_num == -1 || city2_num == -1) {
        return false;
    }

    Edge *edge1 = findEdgeTo(map->graph->tab[city1_num], city2_num);
    Edge *edge2 = findEdgeTo(map->graph->tab[city2_num], city1_num);

    if (edge1 == NULL || edge1->year > repairYear)
        return false;

    edge1->year = repairYear;
    edge2->year = repairYear;

    return true;
}

/** @brief Łączy dwa różne miasta drogą krajową.
 * Tworzy drogę krajową pomiędzy dwoma miastami i nadaje jej podany numer.
 * Wśród istniejących odcinków dróg wyszukuje najkrótszą drogę. Jeśli jest
 * więcej niż jeden sposób takiego wyboru, to dla każdego wariantu wyznacza
 * wśród wybranych w nim odcinków dróg ten, który był najdawniej wybudowany lub
 * remontowany i wybiera wariant z odcinkiem, który jest najmłodszy.
 * @param[in,out] map    – wskaźnik na strukturę przechowującą mapę dróg;
 * @param[in] routeId    – numer drogi krajowej;
 * @param[in] city1      – wskaźnik na napis reprezentujący nazwę miasta;
 * @param[in] city2      – wskaźnik na napis reprezentujący nazwę miasta.
 * @return Wartość @p true, jeśli droga krajowa została utworzona.
 * Wartość @p false, jeśli wystąpił błąd: któryś z parametrów ma niepoprawną
 * wartość, istnieje już droga krajowa o podanym numerze, któreś z podanych
 * miast nie istnieje, obie podane nazwy miast są identyczne, nie można
 * jednoznacznie wyznaczyć drogi krajowej między podanymi miastami lub nie udało
 * się zaalokować pamięci.
 */
bool newRoute(Map *map, unsigned routeId,
              const char *city1, const char *city2) {
    if (routeId <= 0
        || routeId >= MAX_ROUTES
        || invalidCityName(city1)
        || invalidCityName(city2)
        || map->routes[routeId].start != -1)
        return false;

    int city1_num = find(map->name_to_int, city1);
    int city2_num = find(map->name_to_int, city2);

    if (city1_num == -1 || city2_num == -1) {
        return false;
    }

    uint64_t *dist = malloc(sizeof(uint64_t) * map->city_number);
    if (dist == NULL) {
        return false;
    }

    map->routes[routeId].start = city1_num;
    map->routes[routeId].finish = city2_num;

    if (dijkstra(map, -1, dist, city1_num, city2_num) == ALLOCATION_FAILURE) {
        map->routes[routeId].start = -1;
        free(dist);
        return false;
    }
    if (markRoute(map, routeId, dist) == ALLOCATION_FAILURE) {
        map->routes[routeId].start = -1;
        free(dist);
        return false;
    }

    free(dist);
    return true;
}

/** @brief Wydłuża drogę krajową do podanego miasta.
 * Dodaje do drogi krajowej nowe odcinki dróg do podanego miasta w taki sposób,
 * aby nowy fragment drogi krajowej był najkrótszy. Jeśli jest więcej niż jeden
 * sposób takiego wydłużenia, to dla każdego wariantu wyznacza wśród dodawanych
 * odcinków dróg ten, który był najdawniej wybudowany lub remontowany i wybiera
 * wariant z odcinkiem, który jest najmłodszy.
 * @param[in,out] map    – wskaźnik na strukturę przechowującą mapę dróg;
 * @param[in] routeId    – numer drogi krajowej;
 * @param[in] city       – wskaźnik na napis reprezentujący nazwę miasta.
 * @return Wartość @p true, jeśli droga krajowa została wydłużona.
 * Wartość @p false, jeśli wystąpił błąd: któryś z parametrów ma niepoprawną
 * nazwę, nie istnieje droga krajowa o podanym numerze, nie ma miasta o podanej
 * nazwie, przez podane miasto już przechodzi droga krajowa o podanym numerze,
 * podana droga krajowa kończy się w podanym mieście, nie można jednoznacznie
 * wyznaczyć nowego fragmentu drogi krajowej lub nie udało się zaalokować
 * pamięci.
 */
bool extendRoute(Map *map, unsigned routeId, const char *city) {
    return true;
}

/** @brief Usuwa odcinek drogi między dwoma różnymi miastami.
 * Usuwa odcinek drogi między dwoma miastami. Jeśli usunięcie tego odcinka drogi
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
bool removeRoad(Map *map, const char *city1, const char *city2) {
    return true;
}

/** @brief Udostępnia informacje o drodze krajowej.
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
char const* getRouteDescription(Map *map, unsigned routeId) {
    CharVector *output = newCharVector();
    if (output == NULL)
        return NULL;
    char *buff = malloc(sizeof(char) * 12);
    if (buff == NULL) {
        freeCharVector(output);
    }

    int route = (int)routeId;
    int start = map->routes[route].start;
    int finish = map->routes[route].finish;
    int last = -1;
    Vertice *vertice = map->graph->tab[start];

    sprintf(buff, "%d", route);
    if (charVectorPushString(output, buff) == ALLOCATION_FAILURE) {
        freeCharVector(output);
        free(buff);
        return NULL;
    }
    if (charVectorPush(output, ';') == ALLOCATION_FAILURE) {
        freeCharVector(output);
        free(buff);
        return NULL;
    }

    if (charVectorPushString(output, map->int_to_name->tab[start]) == ALLOCATION_FAILURE) {
        freeCharVector(output);
        free(buff);
        return NULL;
    }

    while (vertice->number != finish) {
        //printf("In vertice %d\n", vertice->number);
        Edge *edge = findEdgeWithRoute(vertice, route, last);
        if (charVectorPush(output, ';') == ALLOCATION_FAILURE) {
            freeCharVector(output);
            free(buff);
            return NULL;
        }
        sprintf(buff, "%d", edge->length);
        if (charVectorPushString(output, buff) == ALLOCATION_FAILURE) {
            freeCharVector(output);
            free(buff);
            return NULL;
        }
        if (charVectorPush(output, ';') == ALLOCATION_FAILURE) {
            freeCharVector(output);
            free(buff);
            return NULL;
        }
        sprintf(buff, "%d", edge->year);
        if (charVectorPushString(output, buff) == ALLOCATION_FAILURE) {
            freeCharVector(output);
            free(buff);
            return NULL;
        }
        if (charVectorPush(output, ';') == ALLOCATION_FAILURE) {
            freeCharVector(output);
            free(buff);
            return NULL;
        }
        last = vertice->number;
        vertice = map->graph->tab[edge->where];
        if (charVectorPushString(output, map->int_to_name->tab[vertice->number]) == ALLOCATION_FAILURE) {
            freeCharVector(output);
            free(buff);
            return NULL;
        }
    }
    char *ret = output->tab;
    free(buff);
    free(output);
    return ret;
}

