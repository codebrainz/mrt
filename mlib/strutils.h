/*
 * Copyright (c) 2013 Matthew Brush <mbrush@codebrainz.ca>
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be
 *   included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/**
 * @file mrt/strutils.h
 * @brief C string-related functions.
 * @copyright 2013 Matthew Brush <mbrush@codebrainz.ca>
 *
 * These functions provide typical API as provided by `string.h` from
 * the stdlib, except that they use the MRT `memory.h` functions and
 * so are slightly safer and interact better with other MRT functions.
 *
 * @note Unless you're interfacing with other libraries that require
 * standard C strings (ie. character arrays, zero-terminated), you
 * are recommended to use the `MString` APIs.
 */

#ifndef M_STR_UTILS_H
#define M_STR_UTILS_H

#include <mlib/macros.h>
#include <mlib/basictypes.h>
#include <stdarg.h>

M_BEGIN_CDECLS

/**
 * Duplicate a zero-terminated string.
 *
 * @param s The zero-terminated string to duplicate.
 * @return A newly allocated zero-terminated string with the same
 * contents as @a s or @c NULL if @a s is @c NULL or no more memory
 * is available. The returned string should be freed with `m_free()`
 * when no longer needed.
 */
char *m_strdup(const char *s);

/**
 * Duplicate the given @a len if a zero-terminated string.
 *
 * @param s The zero-terminated string to duplicate.
 * @param len The number of characters to duplicate.
 * @return A newly allocated zero-terminated string with the same
 * contents as the first @a len characters of @a s or @c NULL if
 * @a s is @c NULL or no more memory is available. The returned
 * string should be freed with `m_free()` when no longer needed.
 */
char *m_strndup(const char *s, size_t len);

/**
 * Create a new string from the given format and arguments.
 *
 * @param fmt The format string, like that of @c printf().
 * @param ... The arguments for the given @fmt format string.
 * @return A newly alloated zero-terminated string with the
 * given arguments formatted with the given format string. Returns
 * @c NULL if an error occurrs or no more memory is available.
 */
char *m_strdup_printf(const char *fmt, ...);

/**
 * Create a new string from the given format and arguments.
 *
 * @param fmt The format string, like that of @c printf().
 * @param ap The arguments for the given @fmt format string.
 * @return A newly alloated zero-terminated string with the
 * given arguments formatted with the given format string. Returns
 * @c NULL if an error occurrs or no more memory is available.
 */
char *m_strdup_vprintf(const char *fmt, va_list ap);

/**
 * Gets the number of bytes in a given string.
 *
 * @param str The zero-terminated string to measure.
 * @return The number of bytes in the given string, not including the
 * zero-terminator byte, or returns 0 if the string is empty or
 * @c NULL is passed in @a str.
 */
size_t m_strlen(const char *str);

/**
 * Compare the two strings.
 *
 * If @a str1 is @c NULL and @a str2 is not, `-1` is returned, if
 * @a str1 is not @c NULL and @a str2 is, `1` is returned, if both
 * @a str1 and @a str2 are @c NULL, `0` is returned. In all other
 * cases the result is the same as the standard `strcmp()` function.
 *
 * @param str1 The first string to compare, must be zero-terminated.
 * @param str2 The second string to compare, must be zero-terminated.
 * @return -1, 0, or 1 if @a str1 is less than, equal to, or greater
 * than @a str2, respectively.
 */
int m_strcmp(const char *str1, const char *str2);

/**
 * Check if the two strings are equal.
 *
 * This is equivalent to `m_strcmp(str1, str2) == 0`.
 *
 * @param str1 The first string to compare.
 * @param str2 The second string to compare.
 * @return @c true if the strings are equal @c false otherwise.
 */
#define m_strequal(str1, str2) (m_strcmp(str1, str2) == 0)

/**
 * Remove leading whitespace from the given string.
 *
 * @param str The string.
 * @return The @a str string with leading whitespace removed. The
 * string is modified in place.
 */
char *m_strchomp(char *str);

/**
 * Remove trailing whitespace from the given string.
 *
 * @param str The string.
 * @return The @a str string with trailing whitespace removed. The
 * string is modified in place.
 */
char *m_strchug(char *str);

/**
 * Remove the leading and trailing whitespace from the given string.
 *
 * @param str The string.
 * @return The @a str string with leading and trailing whitespace
 * removed. The string is modified in place.
 */
#define m_strstrip(str) m_strchomp(m_strchug(str))

M_END_CDECLS

#endif // M_STR_UTILS_H
