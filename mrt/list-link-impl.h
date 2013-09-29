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

#ifndef MRT_LIST_LINK_H
#define MRT_LIST_LINK_H

#include <mrt/value-impl.h>

MRT_BEGIN_CDECLS

#define MRT_LIST_LINK(v) ((MRT_ListLink*)(v))
#define MRT_LIST_LINK_CLASS(c) ((MRT_ListLinkClass*)(c))
#define MRT_IS_LIST_LINK(v) mrt_value_is_instance(mrt_list_link_class(), MRT_VALUE(v))

typedef struct MRT_ListLink MRT_ListLink;
typedef struct MRT_ListLinkClass MRT_ListLinkClass;

struct MRT_ListLink
{
  MRT_Value base_;
  MRT_Value *value;
  MRT_ListLink *prev;
  MRT_ListLink *next;
};

struct MRT_ListLinkClass
{
  MRT_ValueClass base_;
};

const MRT_ValueClass *mrt_list_link_class(void);

MRT_ListLink *mrt_list_link_new(MRT_Value *value,
  MRT_ListLink *prev, MRT_ListLink *next);

MRT_Value *mrt_list_link_get_value(MRT_ListLink *link);
void mrt_list_link_set_value(MRT_ListLink *link, MRT_Value *value);

MRT_ListLink *mrt_list_link_prev(MRT_ListLink *link);
MRT_ListLink *mrt_list_link_next(MRT_ListLink *link);

MRT_END_CDECLS

#endif // MRT_LIST_LINK_H
