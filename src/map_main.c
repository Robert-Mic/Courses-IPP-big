#include "map.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "hashmap.h"
#include "list_intlist.h"
#include "constants.h"
#include "map.h"
#include "vector_charvector.h"
#include "input.h"
#include "utils.h"
#include "input_parse.h"

#undef NDEBUG

int main() {
    Map* m = newMap();
    if (m == NULL)
        return 0;
    int read_code = 0;
    uint64_t line = 1;
    CharVector *vector = NULL;

    do {
        read_code = readLine(&vector);

        if (read_code == ALLOCATION_SUCCESS) {
            if (vector->tab[vector->current_size - 2] == '\n') {
                vector->tab[vector->current_size - 2] = 0;
            }
            char **args = split(vector->tab, ';');
            int result = parseInput(m, args);
            freeSplit(args);
            if (result == COMMAND_SUCCEEDED) {
                //do nothing
            }
            else {
                error(line);
            }
        }

        if (read_code == ALLOCATION_FAILURE) {
            deleteMap(m);
            freeCharVector(vector);
            return 0;
        }

        if (read_code == FILE_END) {
            if (vector->tab[0] != 0)
                error(line);
        }
        line++;
    } while (read_code == ALLOCATION_SUCCESS);

    freeCharVector(vector);
    deleteMap(m);
    return 0;
}
