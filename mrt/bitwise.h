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

#ifndef M_BITWISE_H
#define M_BITWISE_H

#include <mrt/macros.h>

M_BEGIN_CDECLS

#define M_LO_BYTE(w)   ((uint8_t)(w))
#define M_HI_BYTE(w)   ((uint8_t)(0xFF & (uint16_t)((w) >> 8)))
#define M_LO_WORD(dw)  ((uint16_t)(dw))
#define M_HI_WORD(dw)  ((uint16_t)(0xFFFF & (uint32_t)((dw) >> 16)))
#define M_LO_DWORD(qw) ((uint32_t)(qw))
#define M_HI_DWORD(qw) ((uint32_t)(0xFFFFFFFF & (uint64_t)((qw) >> 32)))

#define M_MAKE_WORD(h,l)  (((uint16_t)((uint16_t)(h) << 8)) | (uint16_t)((uint8_t)(l)))
#define M_MAKE_DWORD(h,l) (((uint32_t)((uint32_t)(h) << 16)) | (uint32_t)((uint16_t)(l)))
#define M_MAKE_QWORD(h,l) (((uint64_t)((uint64_t)(h) << 32)) | (uint64_t)((uint32_t)(l)))

#define M_BIT_CLEAR(data, bit)  ((data) & ~(bit))
#define M_BIT_SET(data, bit)    ((data) | (bit))
#define M_BIT_TOGGLE(data, bit) ((data) ^ (bit))

M_END_CDECLS

#endif // M_BITWISE_H
