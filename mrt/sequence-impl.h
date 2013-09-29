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

#ifndef MRT_SEQUENCE_IMPL_H
#define MRT_SEQUENCE_IMPL_H

#include <mrt/value-impl.h>
#include <mrt/sequence.h>
#include <stdarg.h>

MRT_BEGIN_CDECLS

#define MRT_SEQ_CLASS(c) ((MRT_SeqClass*)(c))

typedef struct MRT_SeqClass MRT_SeqClass;

struct MRT_Seq
{
  MRT_Value base_;
};

typedef MRT_Value* (*MRT_SeqGetFunc)(MRT_Seq*, va_list);
typedef bool (*MRT_SeqSetFunc)(MRT_Seq*, va_list);
typedef bool (*MRT_SeqAddFunc)(MRT_Seq*, va_list);
typedef bool (*MRT_SeqDelFunc)(MRT_Seq*, va_list);
typedef uint32_t (*MRT_SeqSizeFunc)(MRT_Seq*);
typedef MRT_SeqIter* (*MRT_SeqIterFirst)(MRT_Seq*);
typedef MRT_SeqIter* (*MRT_SeqIterLast)(MRT_Seq*);

struct MRT_SeqClass
{
  MRT_ValueClass base_;
  MRT_SeqGetFunc get;
  MRT_SeqSetFunc set;
  MRT_SeqAddFunc add;
  MRT_SeqDelFunc del;
  MRT_SeqSizeFunc size;
  MRT_SeqIterFirst first;
  MRT_SeqIterLast last;
};

MRT_END_CDECLS

#endif // MRT_SEQUENCE_IMPL_H
