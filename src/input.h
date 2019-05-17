//
// Created by rober on 16.05.2019.
//

#ifndef DROGI_INPUT_H
#define DROGI_INPUT_H

#include "constants.h"
#include "vector_charvector.h"

#define FILE_END 3

/** Reads a line from standard input.
 * @param vector - character vector that buffers the input.
 * vector.tab holds correct string representation of the line
 * including potential newline character and null (0) at the end.
 * @return ALLOCATION_SUCCESS on successful read,
 * ALLOCATION_FAILURE when memory allocation fails,
 * FILE_END when there is nothing left to read.
 */
int readLine(CharVector **vector);

#endif //DROGI_INPUT_H
