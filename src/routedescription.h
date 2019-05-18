/** @file
 * RouteDescription class interface.
 *
 * @author Robert Michna <rm406247@students.mimuw.edu.pl>
 * @copyright Uniwersytet Warszawski
 * @date 25.03.2019
 */

#ifndef DROGI_ROUTEDESCRIPTION_H
#define DROGI_ROUTEDESCRIPTION_H

/**
 * A constant limiting the possible route's IDs. Route ID must be greater
 * than 0 and lower @p than MAX_ROUTES.
 */
#define MAX_ROUTES 1000

/// Structure describing a route.
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
