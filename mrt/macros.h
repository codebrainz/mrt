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

#ifndef MRT_MACROS_H
#define MRT_MACROS_H

#include <stdio.h>

#ifdef __cplusplus
# define MRT_BEGIN_CDECLS extern "C" {
# define MRT_END_CDECLS   }
#else
# define MRT_BEGIN_CDECLS
# define MRT_END_CDECLS
#endif

MRT_BEGIN_CDECLS

#ifdef MRT_DISABLE_CHECKS
# define mrt_return_if_fail(x)          do { } while (0)
# define mrt_return_val_if_fail(x, val) do { } while (0)
# define mrt_warn_if_fail(x)            do { } while (0)
#else
# define mrt_return_if_fail(x) do {                  \
  if (!(x)) {                                        \
    fprintf(stderr, "warning:" __FILE__              \
            ":%d: assertion `" #x "' failed.\n",     \
            __LINE__);                               \
    return;                                          \
  } } while (0)
# define mrt_return_val_if_fail(x, val) do {     \
  if (!(x)) {                                    \
    fprintf(stderr, "warning:" __FILE__          \
            ":%d: assertion `" #x "' failed.\n", \
            __LINE__);                           \
    return (val);                                \
  } } while (0)
# define mrt_warn_if_fail(x) do {                  \
  if (!(x)) {                                      \
      fprintf(stderr, "warning:" __FILE__          \
              ":%d: assertion `" #x "' failed.\n", \
              __LINE__);                           \
  } } while (0)
#endif

MRT_END_CDECLS

#endif // MRT_MACROS_H
