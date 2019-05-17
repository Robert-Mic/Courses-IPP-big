//
// Created by rober on 16.05.2019.
//

#ifndef DROGI_INPUT_PARSE_H
#define DROGI_INPUT_PARSE_H

#include <stdint.h>
#include "map.h"
#include "constants.h"

#define COMMAND_FAILED 11
#define COMMAND_SUCCEEDED 12

void error(uint64_t nr);

int parseInput(Map *map, char **args);

#endif //DROGI_INPUT_PARSE_H
