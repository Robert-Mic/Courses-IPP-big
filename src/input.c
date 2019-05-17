//
// Created by rober on 16.05.2019.
//

#include <stdio.h>
#include <stdlib.h>
#include "input.h"
#include "utils.h"

int readLine(CharVector **vector) {
    int i_char;

    freeCharVector(*vector);
    *vector = newCharVector();
    if (*vector == NULL)
        return ALLOCATION_FAILURE;

    do {
        i_char = getchar();
        if (charVectorPush(*vector, (char)i_char) == ALLOCATION_FAILURE) {
            return ALLOCATION_FAILURE;
        }
    } while (i_char != EOF && (char)i_char != '\n');

    if (i_char == EOF)
        charVectorPop(*vector);
    if (charVectorPush(*vector, 0) == ALLOCATION_FAILURE) {
        return ALLOCATION_FAILURE;
    }

    if (i_char == EOF)
        return FILE_END;
    return ALLOCATION_SUCCESS;
}
