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

#include <mrt/list-impl.h>
#include <mrt/list-iter-impl.h>
#include <mrt/sequence.h>
#include <mrt/sequence-iter.h>
#include <mrt/memory.h>
#include <mrt/object.h>

MSeq *m_list_new(void)
{
  return M_SEQ(m_object_construct(m_list_class(), NULL));
}

static void m_list_ctor(MObject *obj, va_list ap)
{
  (void) obj;
  (void) ap;
}

static void m_list_dtor(MObject *obj)
{
  MList *list = M_LIST(obj);
  MListLink *link = list->head;
  while (link) {
    MListLink *next = link->next;
    m_object_unref(M_OBJECT(link));
    link = next;
  }
}

static MObject *m_list_get(MSeq *seq, va_list ap)
{
  MList *list = M_LIST(seq);
  MListLink *link;
  uint32_t count, index = va_arg(ap, uint32_t);
  if (index >= list->size) // bounds check
    return NULL;
  else if (index < (list->size / 2)) { // count from head
    count = 0;
    for (link = list->head; link != NULL; link = link->next) {
      if (count == index)
        return link->obj;
      count++;
    }
  } else { // count from tail
    uint32_t back_index = list->size - index;
    count = list->size - 1;
    for (link = list->head; link != NULL; link = link->prev) {
      if (count == back_index)
        return link->obj;
      count--;
    }
  }
  return NULL;
}

static bool m_list_set(MSeq *seq, va_list ap)
{
  MList *list = M_LIST(seq);
  MListLink *link;
  uint32_t count, index = va_arg(ap, uint32_t);
  MObject *obj = va_arg(ap, MObject*);
  m_return_val_if_fail(obj, false);
  if (index >= list->size) // bounds check
    return false;
  else if (index < (list->size / 2)) { // count from head
    count = 0;
    for (link = list->head; link != NULL; link = link->next) {
      if (count == index) {
        m_object_unref(link->obj);
        link->obj = m_object_ref_sync(obj);
        return true;
      }
      count++;
    }
  } else { // count from tail
    uint32_t back_index = list->size - index;
    count = list->size - 1;
    for (link = list->tail; link != NULL; link = link->prev) {
      if (count == back_index) {
        m_object_unref(link->obj);
        link->obj = m_object_ref_sync(obj);
        return true;
      }
      count--;
    }
  }
  return false;
}

static bool m_list_add(MSeq *seq, va_list ap)
{
  MList *list = M_LIST(seq);
  uint32_t index;
  MObject *obj;
  MListLink *link;

  m_return_val_if_fail(M_IS_LIST(list), false);

  index = va_arg(ap, uint32_t);
  obj = va_arg(ap, MObject*);

  if (index > list->size || !M_IS_OBJECT(obj))
    return false;

  if (index == 0) { // prepend
    link = m_list_link_new(obj, NULL, list->head);
    list->head = link;
    m_object_ref_sync(M_OBJECT(link));
    list->size++;
    if (list->tail == NULL)
      list->tail = list->head;
    return true;
  } else if (index == list->size) { // append
    link = m_list_link_new(obj, list->tail, NULL);
    list->tail = link;
    m_object_ref_sync(M_OBJECT(link));
    list->size++;
    if (list->head == NULL)
      list->head = list->tail;
    return true;
  } else { // insert somewhere else
    if (index < (list->size / 2)) { // start from begining
      uint32_t count = 0;
      MListLink *iter;
      for (iter = list->head; iter != NULL; iter = iter->next) {
        if (count == index) {
          link = m_list_link_new(obj, iter->prev, iter);
          m_object_ref_sync(M_OBJECT(link));
          if (iter->prev)
            iter->prev->next = link;
          iter->prev = link;
          list->size++;
          return true;
        }
        count++;
      }
    } else { // start from end
      uint32_t back_index = list->size - index;
      uint32_t count = list->size - 1;
      MListLink *iter;
      for (iter = list->tail; iter != NULL; iter = iter->prev) {
        if (count == back_index) {
          link = m_list_link_new(obj, iter->prev, iter);
          m_object_ref_sync(M_OBJECT(link));
          if (iter->prev)
            iter->prev->next = link;
          iter->prev = link;
          list->size++;
          return true;
        }
        count--;
      }
    }
  }

  return false;
}

static bool m_list_del(MSeq *seq, va_list ap)
{
  MList *list = M_LIST(seq);
  MListLink *link, *found_link = NULL;
  uint32_t count, index = va_arg(ap, uint32_t);
  if (index >= list->size) // bounds check
    return false;
  else if (index < (list->size / 2)) { // count from head
    count = 0;
    for (link = list->head; link != NULL; link = link->next) {
      if (count == index) {
        found_link = link;
        break;
      }
      count++;
    }
  } else { // count from tail
    uint32_t back_index = list->size - index;
    count = list->size - 1;
    for (link = list->tail; link != NULL; link = link->prev) {
      if (count == back_index) {
        found_link = link;
        break;
      }
      count--;
    }
  }
  if (found_link) {
    if (found_link->prev)
      found_link->prev->next = found_link->next;
    if (found_link->next)
      found_link->next->prev = found_link->prev;
    m_object_unref(M_OBJECT(found_link));
    list->size--;
    return true;
  }
  return false;
}

static uint32_t m_list_size(MSeq *seq)
{
  return M_LIST(seq)->size;
}

static MSeqIter *m_list_first(MSeq *seq)
{
  MList *list = M_LIST(seq);
  return M_SEQ_ITER(m_list_iter_new(list, list->head));
}

static MSeqIter *m_list_last(MSeq *seq)
{
  MList *list = M_LIST(seq);
  return M_SEQ_ITER(m_list_iter_new(list, list->tail));
}

M_BEGIN_CLASS_DEF(MList, list, m_seq_class())
{
  M_SET_FIELD(MObjectClass, ctor, m_list_ctor);
  M_SET_FIELD(MObjectClass, dtor, m_list_dtor);
  M_SET_FIELD(MSeqClass, get, m_list_get);
  M_SET_FIELD(MSeqClass, set, m_list_set);
  M_SET_FIELD(MSeqClass, add, m_list_add);
  M_SET_FIELD(MSeqClass, del, m_list_del);
  M_SET_FIELD(MSeqClass, size, m_list_size);
  M_SET_FIELD(MSeqClass, first, m_list_first);
  M_SET_FIELD(MSeqClass, last, m_list_last);
}
M_END_CLASS_DEF
