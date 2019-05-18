/** @file
 * Utility functions and IntPair class.
 *
 * @author Robert Michna <rm406247@students.mimuw.edu.pl>
 * @copyright Uniwersytet Warszawski
 * @date 25.03.2019
 */

#ifndef DROGI_UTILS_H
#define DROGI_UTILS_H

/// Structure that holds a pair of integers.
typedef struct  IntegerPair IntPair;

/**
 * Structure that holds a pair of integers.
 */
struct IntegerPair {
    int first; /**< First value of the pair.*/
    int second; /**< Second value of the pair.*/
};

/** @brief Compares two Pairs.
 * Compares two pairs first checking if the @p first field is greater and then,
 * if they are equal, checking if the @p second field is greater.
 * @param[in] a - First pair.
 * @param[in] b - Second pair.
 * @return Returns int value. If the value is greater than 0 then pair @p a is
 * greater than pair @p b. If the value is equal to 0 then both are equal. If
 * the value is lower than 0 then pair @p b is greater than @p a.
 */
int intPairCmp(IntPair a, IntPair b);

/** @brief Creates new IntPair.
 *
 * @param[in] a - First value.
 * @param[in] b - Second value.
 * @return New IntPair.
 */
IntPair newIntPair(int a, int b);

/** @brief Calculates minimum of a and b.
 * @param[in] a
 * @param[in] b
 * @return min(a,b).
 */
int min(int a, int b);

/** @brief Creates new string with the same values as @p str.
 * Duplicates the specified string. Must be freed by @p free.
 * @param[in] str - A string to duplicate.
 * @return Returns a pointer to the newly created string with same values as str.
 * If the memory allocation fails, NULL is returned.
 */
char* myStrdup(const char *str);

/** @brief Duplicates the characters in a specified range.
 * Duplicates the characters in a specified range. Allocates necessary memory
 * and ends string with 0. Has to be freed by @p free.
 * @param[in] str - A string from which we duplicate with length of at least @p end.
 * @param[in] start - The starting position from which we copy. Inclusive.
 * @param[in] end - The ending position to which we copy. Exclusive.
 * @return Returns a pointer to the newly created string with the same values
 * as from the specified range of the original string. If the memory allocation
 * fails, NULL is returned.
 */
char* strdupRange(const char *str, int start, int end);

/** @brief Splits the string on @param split_char . Returns an array of strings.
 * Splits the string on @param split_char . The returned array ends with a pointer
 * to NULL. All strings end with 0. Has to be freed by @ref freeSplit.
 * @param[in] string - The string we want to split.
 * @param[in] split_char - The character on which we split. (ex. ';')
 * @return Returns an array of strings that does not contain @p split_char.
 * If the memory allocation fails, NULL is returned.
 */
char** split(const char *string, const char split_char);

/** @brief Frees the memory allocated by @ref split.
 *
 * @param[in] split - A pointer to the memory allocated by a call to @ref split.
 */
void freeSplit(char **split);

#endif //DROGI_UTILS_H
