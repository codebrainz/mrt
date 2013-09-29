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

#ifndef MRT_SEQUENCE_H
#define MRT_SEQUENCE_H

#include <mrt/value.h>
#include <mrt/sequence-iter.h>

MRT_BEGIN_CDECLS

#define MRT_SEQ(v) ((MRT_Seq*)(v))
#define MRT_IS_SEQ(v) mrt_value_is_instance(mrt_seq_class(), MRT_VALUE(v))

typedef struct MRT_Seq MRT_Seq;

const MRT_ValueClass *mrt_seq_class(void);

MRT_Value *mrt_seq_get(MRT_Seq*, ...);
bool mrt_seq_set(MRT_Seq*, ...);
bool mrt_seq_add(MRT_Seq*, ...);
bool mrt_seq_del(MRT_Seq*, ...);
uint32_t mrt_seq_size(MRT_Seq*);
struct MRT_SeqIter *mrt_seq_first(MRT_Seq*);
struct MRT_SeqIter *mrt_seq_last(MRT_Seq*);

MRT_END_CDECLS

#endif // MRT_SEQUENCE_H
