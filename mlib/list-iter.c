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

#include <mlib/list-iter-impl.h>
#include <mlib/sequence-impl.h>
#include <mlib/memory.h>

MListIter *m_list_iter_new(MList *list, MListLink *link)
{
  m_return_val_if_fail(M_IS_LIST(list), NULL);
  m_return_val_if_fail(link, NULL);
  return M_LIST_ITER(m_object_construct(m_list_iter_class(),
    NULL, list, link));
}

static void m_list_iter_ctor(MObject *obj, va_list ap)
{
  MListIter *iter = M_LIST_ITER(obj);
  MList *list = va_arg(ap, MList*);
  MListLink *link = va_arg(ap, MListLink*);
  M_SEQ_ITER(iter)->seq =
    M_SEQ(m_object_ref(M_OBJECT(list)));
  iter->link = link;
}

static void m_list_iter_dtor(MObject *obj)
{
  //MListIter *iter = M_LIST_ITER(obj);
  (void)obj;
}

static MObject *m_list_iter_prev(MSeqIter *iter)
{
  MListIter *list_iter = M_LIST_ITER(iter);
  if (list_iter == NULL || list_iter->link == NULL)
    return NULL;
  list_iter->link = list_iter->link->prev;
  return list_iter->link->obj;
}

static MObject *m_list_iter_next(MSeqIter *iter)
{
  MListIter *list_iter = M_LIST_ITER(iter);
  if (list_iter == NULL || list_iter->link == NULL)
    return NULL;
  list_iter->link = list_iter->link->next;
  return list_iter->link->obj;
}

M_BEGIN_CLASS_DEF(MListIter, list_iter, m_seq_iter_class())
{
  M_SET_FIELD(MObjectClass, ctor, m_list_iter_ctor);
  M_SET_FIELD(MObjectClass, dtor, m_list_iter_dtor);
  M_SET_FIELD(MSeqIterClass, prev, m_list_iter_prev);
  M_SET_FIELD(MSeqIterClass, next, m_list_iter_next);
}
M_END_CLASS_DEF
