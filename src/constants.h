/** @file
 * File containing program's constants.
 *
 * @author Robert Michna <rm406247@students.mimuw.edu.pl>
 * @copyright Uniwersytet Warszawski
 * @date 10.04.2019
 */

#ifndef DROGI_CONSTANTS_H
#define DROGI_CONSTANTS_H

#ifndef true
/// true
#define true 1
#endif
#ifndef  false
/// false
#define false 0
#endif

/// Constant returned by functions that succeeded in allocating memory.
#define ALLOCATION_FAILURE 1

/// Constant returned by functions that failed to allocate memory.
#define ALLOCATION_SUCCESS 0

/// Constant returned by functions parsing input, that signalizes a memory error.
#define MEMORY_ERROR 2

#endif //DROGI_CONSTANTS_H
