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

#ifndef M_LIST_ITER_IMPL_H
#define M_LIST_ITER_IMPL_H

#include <mlib/object-impl.h>
#include <mlib/sequence-iter-impl.h>
#include <mlib/list-iter.h>
#include <mlib/list-link-impl.h>
#include <mlib/list.h>

M_BEGIN_CDECLS

#define M_LIST_ITER_CLASS(c) ((MListIterClass*)(c))

typedef struct MListIterClass MListIterClass;

struct MListIter
{
  MSeqIter base_;
  MListLink *link;
};

struct MListIterClass
{
  MSeqIterClass base_;
};

MListIter *m_list_iter_new(MList *list, MListLink *link);

M_END_CDECLS

#endif // M_LIST_ITER_IMPL_H
