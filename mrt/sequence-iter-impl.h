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

#ifndef MRT_SEQUENCE_ITER_IMPL_H
#define MRT_SEQUENCE_ITER_IMPL_H

#include <mrt/macros.h>
#include <mrt/sequence-iter.h>
#include <mrt/value-impl.h>

MRT_BEGIN_CDECLS

#define MRT_SEQ_ITER_CLASS(c) ((MRT_SeqIterClass*)(c))

typedef struct MRT_SeqIterClass MRT_SeqIterClass;

struct MRT_SeqIter
{
  MRT_Value base_;
  MRT_Seq *seq;
};

typedef MRT_Value* (*MRT_SeqIterNextFunc)(MRT_SeqIter*);
typedef MRT_Value* (*MRT_SeqIterPrevFunc)(MRT_SeqIter*);

struct MRT_SeqIterClass
{
  MRT_ValueClass base_;
  MRT_SeqIterPrevFunc prev;
  MRT_SeqIterNextFunc next;
};

MRT_END_CDECLS

#endif // MRT_SEQUENCE_ITER_IMPL_H
