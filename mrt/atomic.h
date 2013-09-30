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

#ifndef M_ATOMIC_H
#define M_ATOMIC_H

#include <mrt/macros.h>
#include <mrt/basictypes.h>

M_BEGIN_CDECLS

#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L)

# define m_atomic_cas32(val_ptr, old_val, new_val) \
  atomic_compare_and_exchange_weak(val_ptr, &old_val, new_val)

#elif defined(__GNUC__) && \
    (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__) > 40100

# define m_atomic_cas32(val_ptr, old_val, new_val) \
  __sync_bool_compare_and_swap(val_ptr, old_val, new_val)

#elif defined(__ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__) && \
    (__ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__ >= 1050)

#include <libkern/OSAtomic.h>

# define m_atomic_cas32(val_ptr, old_val, new_val) \
  OSAtomicCompareAndSwap32(old_val, new_val, val_ptr)

#elif defined(_MSC_VER)

# define WIN32_LEAN_AND_MEAN
# include <windows.h>

# define m_atomic_cas32(val_ptr, old_val, new_val) \
  (InterlockedCompareAndExchange(val_ptr, new_val, old_val) != old_val)

#else // NOT atomic (FIXME)

# define m_atomic_cas32(val_ptr, old_val, new_val) \
  ((bool)((*(val_ptr) = (new_val)) || true))

#endif

#define m_atomic_inc32(val)                      \
  do {                                             \
    uint32_t *vp__ = &(val);                       \
    uint32_t ov__, nv__;                           \
    do {                                           \
      ov__ = *vp__;                                \
      nv__ = ov__ + 1;                             \
    } while (!m_atomic_cas32(vp__, ov__, nv__)); \
  } while (0)

#define m_atomic_dec32(val)                      \
  do {                                             \
    uint32_t *vp__ = &(val);                       \
    uint32_t ov__, nv__;                           \
    do {                                           \
      ov__ = *vp__;                                \
      nv__ = ov__ - 1;                             \
    } while (!m_atomic_cas32(vp__, ov__, nv__)); \
  } while (0)

M_END_CDECLS

#endif // M_ATOMIC_H
