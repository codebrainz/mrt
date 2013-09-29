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

#ifndef MRT_LIST_ITER_IMPL_H
#define MRT_LIST_ITER_IMPL_H

#include <mrt/value-impl.h>
#include <mrt/sequence-iter-impl.h>
#include <mrt/list-iter.h>
#include <mrt/list-link-impl.h>
#include <mrt/list.h>

MRT_BEGIN_CDECLS

#define MRT_LIST_ITER_CLASS(c) ((MRT_ListIterClass*)(c))

typedef struct MRT_ListIterClass MRT_ListIterClass;

struct MRT_ListIter
{
  MRT_SeqIter base_;
  MRT_ListLink *link;
};

struct MRT_ListIterClass
{
  MRT_SeqIterClass base_;
};

MRT_ListIter *mrt_list_iter_new(MRT_List *list, MRT_ListLink *link);

MRT_END_CDECLS

#endif // MRT_LIST_ITER_IMPL_H
