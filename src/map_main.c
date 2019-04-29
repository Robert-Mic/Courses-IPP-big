#include "map.h"

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

    assert(!extendRoute(m, 10, "Alinów"));

    assert(addRoad(m, "Cielińsk-Niekłańsk", "Slima", 5, 2021));
    assert(!extendRoute(m, 10, "Slima"));
    assert(removeRoad(m, "Slima", "Cielińsk-Niekłańsk"));

    str = getRouteDescription(m, 10);
    assert(strcmp(str, "10;Alinów;11;2022;Dąb Stary;3;2020;Bór;2;2020;Cielińsk-Niekłańsk;4;2021;Emiliew"
                       ";3;2023;Fraźnik Nowy;4;2020;Grzegrzewo;5;2020;Homilcin") == 0);
    free((void *)str);

    assert(!extendRoute(m, 10, "Homilcin"));

    assert(!removeRoad(m, "Homilcin", "Grzegrzewo"));

    assert(!extendRoute(m, 10, "Slima"));


    assert(addRoad(m, "AA" , "AB", 2, 11));
    assert(addRoad(m, "AA" , "AC", 3, 10));
    assert(addRoad(m, "AB" , "AD", 2, 12));
    assert(addRoad(m, "AC" , "AD", 1, 9));

    assert(addRoad(m, "AD" , "AE", 3, 3));
    assert(addRoad(m, "AD" , "AF", 2, 1));
    assert(addRoad(m, "AE" , "AG", 1, 4));
    assert(addRoad(m, "AF" , "AG", 2, 2));

    assert(!newRoute(m, 41, "AA", "AG"));

    assert(repairRoad(m, "AA", "AB", 13));
    assert(repairRoad(m, "AB", "AD", 14));
    assert(repairRoad(m, "AD", "AE", 12));
    assert(repairRoad(m, "AE", "AG", 11));

    assert(newRoute(m, 42, "AA", "AG"));

    assert(addRoad(m, "BA", "BB", 1, 7));
    assert(addRoad(m, "BB", "BC", 1, 7));
    assert(addRoad(m, "BD", "BA", 3, 7));
    assert(addRoad(m, "BD", "BC", 4, 7));

    assert(newRoute(m, 20, "BA", "BC"));
    assert(extendRoute(m, 20, "BD"));

    str = getRouteDescription(m, 20);
    assert(strcmp(str, "20;BD;3;7;BA;1;7;BB;1;7;BC") == 0);
    free((void *)str);

    assert(addRoad(m, "BA", "BE", 5, 7));
    assert(addRoad(m, "BE", "BB", 5, 7));

    assert(removeRoad(m, "BA", "BB"));

    assert(!removeRoad(m, "BB", "BC"));

    assert(!extendRoute(m, 20, "Homilcin"));

    printf("%s", getRouteDescription(m, 20));


    deleteMap(m);

    return 0;
}
