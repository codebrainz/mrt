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

static void mrt_list_link_ctor(MRT_Value *value, va_list ap)
{
  MRT_ListLink *link = MRT_LIST_LINK(value);
  link->value = mrt_value_ref_sync(va_arg(ap, MRT_Value*));
  link->prev = va_arg(ap, MRT_ListLink*);
  link->next = va_arg(ap, MRT_ListLink*);
}

static void mrt_list_link_dtor(MRT_Value *value)
{
  mrt_value_unref(MRT_LIST_LINK(value)->value);
}

MRT_ListLink *mrt_list_link_new(MRT_Value *value, MRT_ListLink *prev,
  MRT_ListLink *next)
{
  MRT_Value *val = mrt_value_construct(mrt_list_link_class(), value, prev, next);
  mrt_return_val_if_fail(MRT_IS_LIST_LINK(val), NULL);
  return MRT_LIST_LINK(val);
}

MRT_Value *mrt_list_link_get_value(MRT_ListLink *link)
{
  mrt_return_val_if_fail(MRT_IS_LIST_LINK(link), NULL);
  return link->value;
}

void mrt_list_link_set_value(MRT_ListLink *link, MRT_Value *value)
{
  mrt_return_if_fail(MRT_IS_LIST_LINK(link));
  mrt_value_unref(link->value);
  link->value = mrt_value_ref_sync(value);
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

MRT_BEGIN_CLASS_DEF(MRT_ListLink, list_link, mrt_value_class())
{
  MRT_SET_FIELD(MRT_ValueClass, ctor, mrt_list_link_ctor);
  MRT_SET_FIELD(MRT_ValueClass, dtor, mrt_list_link_dtor);
}
MRT_END_CLASS_DEF
