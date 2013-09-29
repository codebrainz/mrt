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

#ifndef MRT_LIST_IMPL_H
#define MRT_LIST_IMPL_H

#include <mrt/list.h>
#include <mrt/sequence-impl.h>
#include <mrt/sequence-iter-impl.h>
#include <mrt/list-link-impl.h>

MRT_BEGIN_CDECLS

#define MRT_LIST_CLASS(c) ((MRT_ListClass*)(c))

typedef struct MRT_ListClass MRT_ListClass;

struct MRT_List
{
  MRT_Seq base_;
  uint32_t size;
  MRT_ListLink *head;
  MRT_ListLink *tail;
};

struct MRT_ListClass
{
  MRT_SeqClass base_;
};

MRT_END_CDECLS

#endif // MRT_LIST_IMPL_H
