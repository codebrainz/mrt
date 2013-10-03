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

#ifndef M_MACROS_H
#define M_MACROS_H

#include <stdio.h>

#ifdef __cplusplus
# define M_BEGIN_CDECLS extern "C" {
# define M_END_CDECLS   }
#else
# define M_BEGIN_CDECLS
# define M_END_CDECLS
#endif

M_BEGIN_CDECLS

#ifdef M_DISABLE_CHECKS
# define m_return_if_fail(x)          do { } while (0)
# define m_return_val_if_fail(x, val) do { } while (0)
# define m_warn_if_fail(x)            do { } while (0)
#else
# define m_return_if_fail(x) do {                  \
  if (!(x)) {                                        \
    fprintf(stderr, "warning:" __FILE__              \
            ":%d: assertion `" #x "' failed.\n",     \
            __LINE__);                               \
    return;                                          \
  } } while (0)
# define m_return_val_if_fail(x, val) do {     \
  if (!(x)) {                                    \
    fprintf(stderr, "warning:" __FILE__          \
            ":%d: assertion `" #x "' failed.\n", \
            __LINE__);                           \
    return (val);                                \
  } } while (0)
# define m_warn_if_fail(x) do {                  \
  if (!(x)) {                                      \
      fprintf(stderr, "warning:" __FILE__          \
              ":%d: assertion `" #x "' failed.\n", \
              __LINE__);                           \
  } } while (0)
#endif

M_END_CDECLS

#endif // M_MACROS_H
