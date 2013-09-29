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

#include <mrt/sequence-iter-impl.h>
#include <mrt/memory.h>

MRT_Seq *seq_iter_get_seq(MRT_SeqIter *seq_iter)
{
  mrt_return_val_if_fail(seq_iter, NULL);
  return seq_iter->seq;
}

MRT_Value *seq_iter_prev(MRT_SeqIter *seq_iter)
{
  mrt_return_val_if_fail(seq_iter, NULL);
  if (MRT_SEQ_ITER_CLASS(MRT_VALUE(seq_iter)->class_)->prev)
    return MRT_SEQ_ITER_CLASS(MRT_VALUE(seq_iter)->class_)->prev(seq_iter);
  return NULL;
}

MRT_Value *seq_iter_next(MRT_SeqIter *seq_iter)
{
  mrt_return_val_if_fail(seq_iter, NULL);
  if (MRT_SEQ_ITER_CLASS(MRT_VALUE(seq_iter)->class_)->next)
    return MRT_SEQ_ITER_CLASS(MRT_VALUE(seq_iter)->class_)->next(seq_iter);
  return NULL;
}

MRT_ABSTRACT_CLASS_DEF(MRT_SeqIter, seq_iter, mrt_value_class())
