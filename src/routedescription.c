//
// Created by rober on 25.04.2019.
//

#include <stdlib.h>
#include "routedescription.h"

RouteDesc newRouteDesc(int start, int finish) {
    /*RouteDesc *new_route = malloc(sizeof(RouteDesc));
    if (new_route == NULL) {
        return NULL;
    }*/
    RouteDesc new_route;
    new_route.start = start;
    new_route.finish = finish;
    return new_route;
}
/*
void freeRouteDesc(RouteDesc *route) {
    free(route);
}*/