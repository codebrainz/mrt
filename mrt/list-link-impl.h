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

#ifndef M_LIST_LINK_H
#define M_LIST_LINK_H

#include <mrt/object-impl.h>

M_BEGIN_CDECLS

#define M_LIST_LINK(v) ((MListLink*)(v))
#define M_LIST_LINK_CLASS(c) ((MListLinkClass*)(c))
#define M_IS_LIST_LINK(v) m_object_is_instance(m_list_link_class(), M_OBJECT(v))

typedef struct MListLink MListLink;
typedef struct MListLinkClass MListLinkClass;

struct MListLink
{
  MObject base_;
  MObject *obj;
  MListLink *prev;
  MListLink *next;
};

struct MListLinkClass
{
  MObjectClass base_;
};

const MObjectClass *m_list_link_class(void);

MListLink *m_list_link_new(MObject *obj,
  MListLink *prev, MListLink *next);

MObject *m_list_link_get_obj(MListLink *link);
void m_list_link_set_obj(MListLink *link, MObject *obj);

MListLink *m_list_link_prev(MListLink *link);
MListLink *m_list_link_next(MListLink *link);

M_END_CDECLS

#endif // M_LIST_LINK_H
