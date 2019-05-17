//
// Created by rober on 24.04.2019.
//

#ifndef DROGI_CONSTANTS_H
#define DROGI_CONSTANTS_H

#ifdef NDEBUG
#define DEBUG 1
#else
#define DEBUG 0
#endif

#ifndef true
#define true 1
#endif
#ifndef  false
#define false 0
#endif

/// Constant returned by functions that succeeded in allocating memory.
#define ALLOCATION_FAILURE 1
/// Constant returned by functions that failed to allocate memory.
#define ALLOCATION_SUCCESS 0
/// Constant signalizing to stop the program completly
#define MEMORY_ERROR 2

#endif //DROGI_CONSTANTS_H
