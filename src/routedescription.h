//
// Created by rober on 25.04.2019.
//

#ifndef DROGI_ROUTEDESCRIPTION_H
#define DROGI_ROUTEDESCRIPTION_H

#define MAX_ROUTES 1000

typedef struct RouteDescription RouteDesc;

struct RouteDescription {
    int start;
    int finish;
};

RouteDesc newRouteDesc(int start, int finish);

//void freeRouteDesc(RouteDesc *route);

#endif //DROGI_ROUTEDESCRIPTION_H
