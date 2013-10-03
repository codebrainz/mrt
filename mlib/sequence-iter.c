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

#include <mlib/sequence-iter-impl.h>
#include <mlib/memory.h>

MSeq *seq_iter_get_seq(MSeqIter *seq_iter)
{
  m_return_val_if_fail(seq_iter, NULL);
  return seq_iter->seq;
}

MObject *seq_iter_prev(MSeqIter *seq_iter)
{
  m_return_val_if_fail(seq_iter, NULL);
  if (M_SEQ_ITER_CLASS(M_OBJECT(seq_iter)->class_)->prev)
    return M_SEQ_ITER_CLASS(M_OBJECT(seq_iter)->class_)->prev(seq_iter);
  return NULL;
}

MObject *seq_iter_next(MSeqIter *seq_iter)
{
  m_return_val_if_fail(seq_iter, NULL);
  if (M_SEQ_ITER_CLASS(M_OBJECT(seq_iter)->class_)->next)
    return M_SEQ_ITER_CLASS(M_OBJECT(seq_iter)->class_)->next(seq_iter);
  return NULL;
}

M_ABSTRACT_CLASS_DEF(MSeqIter, seq_iter, m_object_class())
