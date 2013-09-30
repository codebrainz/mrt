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

#include <mrt/list-iter-impl.h>
#include <mrt/sequence-impl.h>
#include <mrt/memory.h>

MRT_ListIter *mrt_list_iter_new(MRT_List *list, MRT_ListLink *link)
{
  mrt_return_val_if_fail(MRT_IS_LIST(list), NULL);
  mrt_return_val_if_fail(link, NULL);
  return MRT_LIST_ITER(mrt_object_construct(mrt_list_iter_class(),
    NULL, list, link));
}

static void mrt_list_iter_ctor(MRT_Object *obj, va_list ap)
{
  MRT_ListIter *iter = MRT_LIST_ITER(obj);
  MRT_List *list = va_arg(ap, MRT_List*);
  MRT_ListLink *link = va_arg(ap, MRT_ListLink*);
  MRT_SEQ_ITER(iter)->seq =
    MRT_SEQ(mrt_object_ref(MRT_OBJECT(list)));
  iter->link = link;
}

static void mrt_list_iter_dtor(MRT_Object *obj)
{
  //MRT_ListIter *iter = MRT_LIST_ITER(obj);
  (void)obj;
}

static MRT_Object *mrt_list_iter_prev(MRT_SeqIter *iter)
{
  MRT_ListIter *list_iter = MRT_LIST_ITER(iter);
  if (list_iter == NULL || list_iter->link == NULL)
    return NULL;
  list_iter->link = list_iter->link->prev;
  return list_iter->link->obj;
}

static MRT_Object *mrt_list_iter_next(MRT_SeqIter *iter)
{
  MRT_ListIter *list_iter = MRT_LIST_ITER(iter);
  if (list_iter == NULL || list_iter->link == NULL)
    return NULL;
  list_iter->link = list_iter->link->next;
  return list_iter->link->obj;
}

MRT_BEGIN_CLASS_DEF(MRT_ListIter, list_iter, mrt_seq_iter_class())
{
  MRT_SET_FIELD(MRT_ObjectClass, ctor, mrt_list_iter_ctor);
  MRT_SET_FIELD(MRT_ObjectClass, dtor, mrt_list_iter_dtor);
  MRT_SET_FIELD(MRT_SeqIterClass, prev, mrt_list_iter_prev);
  MRT_SET_FIELD(MRT_SeqIterClass, next, mrt_list_iter_next);
}
MRT_END_CLASS_DEF
