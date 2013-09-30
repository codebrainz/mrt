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

#include <mrt/list-link-impl.h>
#include <mrt/memory.h>

static void m_list_link_ctor(MObject *obj, va_list ap)
{
  MListLink *link = M_LIST_LINK(obj);
  link->obj = m_object_ref_sync(va_arg(ap, MObject*));
  link->prev = va_arg(ap, MListLink*);
  link->next = va_arg(ap, MListLink*);
}

static void m_list_link_dtor(MObject *obj)
{
  m_object_unref(M_LIST_LINK(obj)->obj);
}

MListLink *m_list_link_new(MObject *obj, MListLink *prev,
  MListLink *next)
{
  MObject *val = m_object_construct(m_list_link_class(), obj, prev, next);
  m_return_val_if_fail(M_IS_LIST_LINK(val), NULL);
  return M_LIST_LINK(val);
}

MObject *m_list_link_get_obj(MListLink *link)
{
  m_return_val_if_fail(M_IS_LIST_LINK(link), NULL);
  return link->obj;
}

void m_list_link_set_obj(MListLink *link, MObject *obj)
{
  m_return_if_fail(M_IS_LIST_LINK(link));
  m_object_unref(link->obj);
  link->obj = m_object_ref_sync(obj);
}

MListLink *m_list_link_prev(MListLink *link)
{
  m_return_val_if_fail(M_IS_LIST_LINK(link), NULL);
  return link->prev;
}

MListLink *m_list_link_next(MListLink *link)
{
  m_return_val_if_fail(M_IS_LIST_LINK(link), NULL);
  return link->next;
}

M_BEGIN_CLASS_DEF(MListLink, list_link, m_object_class())
{
  M_SET_FIELD(MObjectClass, ctor, m_list_link_ctor);
  M_SET_FIELD(MObjectClass, dtor, m_list_link_dtor);
}
M_END_CLASS_DEF
