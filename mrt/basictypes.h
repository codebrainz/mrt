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

#ifndef M_BASIC_TYPES_H
#define M_BASIC_TYPES_H

#include <stddef.h>
#include <mrt/macros.h>

M_BEGIN_CDECLS

#if (defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)) \
      || defined(HAVE_STDBOOL_H)
# include <stdbool.h>
#elif !defined(__cplusplus)
typedef int bool;
# define false 0
# define true !false
#endif

#if (defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)) \
      || defined(HAVE_STDINT_H) || defined(__cplusplus)
# include <stdint.h>
#elif defined(HAVE_INTTYPES_H)
# include <inttypes.h>
#else
# error "Wrappers for standard int types not implemented."
#endif

M_END_CDECLS

#endif // M_BASIC_TYPES_H
