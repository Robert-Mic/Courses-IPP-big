//#include "map.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "hashmap.h"
#include "vector_stringvector.h"
#include "list_intlist.h"
#include "constants.h"
#include "map.h"

#undef NDEBUG

#include <assert.h>

int main() {
    /*
    CityHashMap *hashmap = newHashMap(100);
    if (hashmap == NULL) {
        printf("no hash map");
        return 0;
    }
    StringVector *vector = newStringVector();
    if (vector == NULL) {
        printf(" no vector");
        return 0;
    }

    int dziala = true;
    int iteracja = 0;
    int miasto = 0;
    while (dziala) {
        iteracja++;
        printf("\niteraca %d\n", iteracja);
        int str_len = 2 + rand() % 4;
        char *string = malloc(sizeof(char) * str_len);
        for (int i = 0; i < str_len; i++) {
            string[i] = 'A' + (abs(rand()) % ('Z' - 'A' + 1));
        }
        string[str_len - 1] = 0;
        printf("new string %s\n", string);
        put(hashmap, string, miasto++);
        stringVectorPush(vector, string);
        int i = miasto-1;
        //for (int i = 0; i < vector->current_size; i++) {
        int res;
        printf("\nlookup\n");
            if (i != (res = find(hashmap, vector->tab[i]))) {
                printf ("ERROR i = %d != hashmap[%s] = %d\n", i, vector->tab[i], res);
                dziala = false;
            }
            else {
                printf ("i = %d == hashmap[%s] = %d\n", i, vector->tab[i], res);
            }
        //}
        free(string);

        if (iteracja == 1000) {
            dziala = false;
            printf("KONIEC\n");
        }
    }
    freeHashmap(hashmap);
    freeStringVector(vector);
    */

    char const* str;

    Map* m = newMap();
    assert(m);

    assert(addRoad(m, "Alinów", "Bór", 1, 2020));
    assert(addRoad(m, "Bór", "Cielińsk-Niekłańsk", 2, 2020));
    assert(addRoad(m, "Bór", "Dąb Stary", 3, 2020));
    assert(addRoad(m, "Cielińsk-Niekłańsk", "Emiliew", 4, 2020));
    assert(addRoad(m, "Dąb Stary", "Emiliew", 5, 2020));
    assert(addRoad(m, "Emiliew", "Bór", 8, 2020));
    assert(addRoad(m, "Emiliew", "Fraźnik Nowy", 3, 2020));
    assert(!repairRoad(m, "Emiliew", "Cielińsk-Niekłańsk", 2019));
    assert(repairRoad(m, "Emiliew", "Cielińsk-Niekłańsk", 2021));
    assert(!repairRoad(m, "Emiliew", "Alinów", 2020));
    assert(addRoad(m, "Fraźnik Nowy", "Grzegrzewo", 4, 2020));
    assert(addRoad(m, "Alinów", "Grzegrzewo", 10, 2020));
    assert(addRoad(m, "Homilcin", "Grzegrzewo", 5, 2020));
    assert(addRoad(m, "Fraźnik Nowy", "Cielińsk-Niekłańsk", 2, 2020));
    assert(!addRoad(m, "Fraźnik Nowy", "Cielińsk-Niekłańsk", 2, 2020));
    assert(!addRoad(m, "Cielińsk-Niekłańsk", "Fraźnik Nowy", 2, 2020));
    assert(!repairRoad(m, "Emiliew", "Bór", 2018));
    assert(repairRoad(m, "Emiliew", "Cielińsk-Niekłańsk", 2021));
    assert(repairRoad(m, "Emiliew", "Fraźnik Nowy", 2023));
    assert(addRoad(m, "Homilcin", "Cielińsk-Niekłańsk", 3, 2020));

    assert(newRoute(m, 10, "Alinów", "Emiliew"));

    str = getRouteDescription(m, 10);
    assert(strcmp(str, "10;Alinów;1;2020;Bór;2;2020;Cielińsk-Niekłańsk;4;2021;Emiliew") == 0);
    free((void *)str);

    assert(extendRoute(m, 10, "Homilcin"));

    str = getRouteDescription(m, 10);
    assert(strcmp(str, "10;Alinów;1;2020;Bór;2;2020;Cielińsk-Niekłańsk;4;2021;Emiliew"
                     ";3;2023;Fraźnik Nowy;4;2020;Grzegrzewo;5;2020;Homilcin") == 0);
    free((void *)str);


    assert(addRoad(m, "Dąb Stary", "Alinów", 11, 2022));
    assert(!removeRoad(m, "Bór", "Cielińsk-Niekłańsk"));

    str = getRouteDescription(m, 10);
    assert(strcmp(str, "10;Alinów;1;2020;Bór;2;2020;Cielińsk-Niekłańsk;4;2021;Emiliew"
                       ";3;2023;Fraźnik Nowy;4;2020;Grzegrzewo;5;2020;Homilcin") == 0);
    free((void *)str);


    assert(removeRoad(m, "Alinów", "Bór"));
    str = getRouteDescription(m, 10);
    assert(strcmp(str, "10;Alinów;11;2022;Dąb Stary;3;2020;Bór;2;2020;Cielińsk-Niekłańsk;4;2021;Emiliew"
                       ";3;2023;Fraźnik Nowy;4;2020;Grzegrzewo;5;2020;Homilcin") == 0);
    free((void *)str);

    assert(!extendRoute(m, 10, "Grzegrzewo"));

     deleteMap(m);

    return 0;
}
