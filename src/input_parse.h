/** @file
 * Input parsing functions interface.
 *
 * @author Robert Michna <rm406247@students.mimuw.edu.pl>
 * @copyright Uniwersytet Warszawski
 * @date 10.04.2019
 */
#ifndef DROGI_INPUT_PARSE_H
#define DROGI_INPUT_PARSE_H

#include <stdint.h>
#include "map.h"
#include "constants.h"

/// Value signalizing wrong command.
#define COMMAND_FAILED 11
/// Value signalizing that the command ended successfully.
#define COMMAND_SUCCEEDED 12

/** @brief Prints "ERROR @p num" to stderr.
 * @param nr - number of line where the error occurred.
 */
void error(uint64_t nr);

/** @brief Parses the input converted by @ref split function.
 * Parses the input passed in the array of strings. The last element
 * of @p args must point to NULL. When parsing routeDescription the function
 * first checks if every parameter is legal and if the route does not have
 * re-occurring cities and then tries to add the changes.
 * @param[in,out] map - A pointer to map structure to which the changes will be
 * applied.
 * @param[in] args - An array of strings containing function arguments.
 * @return If the parsed command is valid ir returns COMMAND_SUCCEEDED constant.
 * If the command is invalid COMMAND_FAILED is returned. In some cases if memory
 * allocation fails MEMORY_ERROR constant is returned.
 */
int parseInput(Map *map, char **args);

#endif //DROGI_INPUT_PARSE_H
