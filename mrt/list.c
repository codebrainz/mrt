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
#include <mrt/value.h>

MRT_Seq *mrt_list_new(void)
{
  return MRT_SEQ(mrt_value_construct(mrt_list_class(), NULL));
}

static void mrt_list_ctor(MRT_Value *value, va_list ap)
{
  (void) value;
  (void) ap;
}

static void mrt_list_dtor(MRT_Value *value)
{
  MRT_List *list = MRT_LIST(value);
  MRT_ListLink *link = list->head;
  while (link) {
    MRT_ListLink *next = link->next;
    mrt_value_unref(MRT_VALUE(link));
    link = next;
  }
}

static MRT_Value *mrt_list_get(MRT_Seq *seq, va_list ap)
{
  MRT_List *list = MRT_LIST(seq);
  MRT_ListLink *link;
  uint32_t count, index = va_arg(ap, uint32_t);
  if (index >= list->size) // bounds check
    return NULL;
  else if (index < (list->size / 2)) { // count from head
    count = 0;
    for (link = list->head; link != NULL; link = link->next) {
      if (count == index)
        return link->value;
      count++;
    }
  } else { // count from tail
    uint32_t back_index = list->size - index;
    count = list->size - 1;
    for (link = list->head; link != NULL; link = link->prev) {
      if (count == back_index)
        return link->value;
      count--;
    }
  }
  return NULL;
}

static bool mrt_list_set(MRT_Seq *seq, va_list ap)
{
  MRT_List *list = MRT_LIST(seq);
  MRT_ListLink *link;
  uint32_t count, index = va_arg(ap, uint32_t);
  MRT_Value *value = va_arg(ap, MRT_Value*);
  mrt_return_val_if_fail(value, false);
  if (index >= list->size) // bounds check
    return false;
  else if (index < (list->size / 2)) { // count from head
    count = 0;
    for (link = list->head; link != NULL; link = link->next) {
      if (count == index) {
        mrt_value_unref(link->value);
        link->value = mrt_value_ref_sync(value);
        return true;
      }
      count++;
    }
  } else { // count from tail
    uint32_t back_index = list->size - index;
    count = list->size - 1;
    for (link = list->tail; link != NULL; link = link->prev) {
      if (count == back_index) {
        mrt_value_unref(link->value);
        link->value = mrt_value_ref_sync(value);
        return true;
      }
      count--;
    }
  }
  return false;
}

static bool mrt_list_add(MRT_Seq *seq, va_list ap)
{
  MRT_List *list = MRT_LIST(seq);
  uint32_t index;
  MRT_Value *value;
  MRT_ListLink *link;

  mrt_return_val_if_fail(MRT_IS_LIST(list), false);

  index = va_arg(ap, uint32_t);
  value = va_arg(ap, MRT_Value*);

  if (index > list->size || !MRT_IS_VALUE(value))
    return false;

  if (index == 0) { // prepend
    link = mrt_list_link_new(value, NULL, list->head);
    list->head = link;
    mrt_value_ref_sync(MRT_VALUE(link));
    list->size++;
    if (list->tail == NULL)
      list->tail = list->head;
    return true;
  } else if (index == list->size) { // append
    link = mrt_list_link_new(value, list->tail, NULL);
    list->tail = link;
    mrt_value_ref_sync(MRT_VALUE(link));
    list->size++;
    if (list->head == NULL)
      list->head = list->tail;
    return true;
  } else { // insert somewhere else
    if (index < (list->size / 2)) { // start from begining
      uint32_t count = 0;
      MRT_ListLink *iter;
      for (iter = list->head; iter != NULL; iter = iter->next) {
        if (count == index) {
          link = mrt_list_link_new(value, iter->prev, iter);
          mrt_value_ref_sync(MRT_VALUE(link));
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
      MRT_ListLink *iter;
      for (iter = list->tail; iter != NULL; iter = iter->prev) {
        if (count == back_index) {
          link = mrt_list_link_new(value, iter->prev, iter);
          mrt_value_ref_sync(MRT_VALUE(link));
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

static bool mrt_list_del(MRT_Seq *seq, va_list ap)
{
  MRT_List *list = MRT_LIST(seq);
  MRT_ListLink *link, *found_link = NULL;
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
    mrt_value_unref(MRT_VALUE(found_link));
    list->size--;
    return true;
  }
  return false;
}

static uint32_t mrt_list_size(MRT_Seq *seq)
{
  return MRT_LIST(seq)->size;
}

static MRT_SeqIter *mrt_list_first(MRT_Seq *seq)
{
  MRT_List *list = MRT_LIST(seq);
  return MRT_SEQ_ITER(mrt_list_iter_new(list, list->head));
}

static MRT_SeqIter *mrt_list_last(MRT_Seq *seq)
{
  MRT_List *list = MRT_LIST(seq);
  return MRT_SEQ_ITER(mrt_list_iter_new(list, list->tail));
}

MRT_BEGIN_CLASS_DEF(MRT_List, list, mrt_seq_class())
{
  MRT_SET_FIELD(MRT_ValueClass, ctor, mrt_list_ctor);
  MRT_SET_FIELD(MRT_ValueClass, dtor, mrt_list_dtor);
  MRT_SET_FIELD(MRT_SeqClass, get, mrt_list_get);
  MRT_SET_FIELD(MRT_SeqClass, set, mrt_list_set);
  MRT_SET_FIELD(MRT_SeqClass, add, mrt_list_add);
  MRT_SET_FIELD(MRT_SeqClass, del, mrt_list_del);
  MRT_SET_FIELD(MRT_SeqClass, size, mrt_list_size);
  MRT_SET_FIELD(MRT_SeqClass, first, mrt_list_first);
  MRT_SET_FIELD(MRT_SeqClass, last, mrt_list_last);
}
MRT_END_CLASS_DEF
