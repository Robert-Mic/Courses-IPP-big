/** @file
 * RouteDescription class interface.
 *
 * @author Robert Michna <rm406247@students.mimuw.edu.pl>
 * @copyright Uniwersytet Warszawski
 * @date 25.03.2019
 */

#ifndef DROGI_ROUTEDESCRIPTION_H
#define DROGI_ROUTEDESCRIPTION_H

#define MAX_ROUTES 1000

typedef struct RouteDescription RouteDesc;

/**
 * Structure describing a route.
 */
struct RouteDescription {
    int start;  /**< Index of the city the route starts at.*/
    int finish;  /**< Index of the city the route ends at.*/
};

/** @brief Creates new RouteDescription
 * @param[in] start - Index of the city the route starts at.
 * @param[in] finish - Index of the city the route ends at.
 * @return RouteDescription with specified values.
 */
RouteDesc newRouteDesc(int start, int finish);

#endif //DROGI_ROUTEDESCRIPTION_H
