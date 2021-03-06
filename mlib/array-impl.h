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

#ifndef M_ARRAY_IMPL_H
#define M_ARRAY_IMPL_H

#include <mlib/array.h>
#include <mlib/sequence-impl.h>

M_BEGIN_CDECLS

#define M_ARRAY_CLASS(c) ((MArrayClass*)(c))

typedef struct MArrayClass MArrayClass;

struct MArray
{
  MSeq base_;
  MObject **data;
  uint32_t size;
};

struct MArrayClass
{
  MSeqClass base_;
};

M_END_CDECLS

#endif // M_ARRAY_IMPL_H
