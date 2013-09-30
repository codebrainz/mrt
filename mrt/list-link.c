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

static void mrt_list_link_ctor(MRT_Object *obj, va_list ap)
{
  MRT_ListLink *link = MRT_LIST_LINK(obj);
  link->obj = mrt_object_ref_sync(va_arg(ap, MRT_Object*));
  link->prev = va_arg(ap, MRT_ListLink*);
  link->next = va_arg(ap, MRT_ListLink*);
}

static void mrt_list_link_dtor(MRT_Object *obj)
{
  mrt_object_unref(MRT_LIST_LINK(obj)->obj);
}

MRT_ListLink *mrt_list_link_new(MRT_Object *obj, MRT_ListLink *prev,
  MRT_ListLink *next)
{
  MRT_Object *val = mrt_object_construct(mrt_list_link_class(), obj, prev, next);
  mrt_return_val_if_fail(MRT_IS_LIST_LINK(val), NULL);
  return MRT_LIST_LINK(val);
}

MRT_Object *mrt_list_link_get_obj(MRT_ListLink *link)
{
  mrt_return_val_if_fail(MRT_IS_LIST_LINK(link), NULL);
  return link->obj;
}

void mrt_list_link_set_obj(MRT_ListLink *link, MRT_Object *obj)
{
  mrt_return_if_fail(MRT_IS_LIST_LINK(link));
  mrt_object_unref(link->obj);
  link->obj = mrt_object_ref_sync(obj);
}

MRT_ListLink *mrt_list_link_prev(MRT_ListLink *link)
{
  mrt_return_val_if_fail(MRT_IS_LIST_LINK(link), NULL);
  return link->prev;
}

MRT_ListLink *mrt_list_link_next(MRT_ListLink *link)
{
  mrt_return_val_if_fail(MRT_IS_LIST_LINK(link), NULL);
  return link->next;
}

MRT_BEGIN_CLASS_DEF(MRT_ListLink, list_link, mrt_object_class())
{
  MRT_SET_FIELD(MRT_ObjectClass, ctor, mrt_list_link_ctor);
  MRT_SET_FIELD(MRT_ObjectClass, dtor, mrt_list_link_dtor);
}
MRT_END_CLASS_DEF
