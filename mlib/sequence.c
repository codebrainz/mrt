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

#include <mlib/sequence-impl.h>
#include <mlib/memory.h>

MObject *m_seq_get(MSeq *seq, ...)
{
  MObject *obj = NULL;
  m_return_val_if_fail(M_IS_SEQ(seq), NULL);
  if (M_SEQ_CLASS(M_OBJECT(seq)->class_)->get) {
    va_list ap;
    va_start(ap, seq);
    obj = M_SEQ_CLASS(M_OBJECT(seq)->class_)->get(seq, ap);
    va_end(ap);
  }
  return obj;
}

bool m_seq_set(MSeq *seq, ...)
{
  bool result = false;
  m_return_val_if_fail(M_IS_SEQ(seq), false);
  if (M_SEQ_CLASS(M_OBJECT(seq)->class_)->set) {
    va_list ap;
    va_start(ap, seq);
    result = M_SEQ_CLASS(M_OBJECT(seq)->class_)->set(seq, ap);
    va_end(ap);
  }
  return result;
}

bool m_seq_add(MSeq *seq, ...)
{
  bool result = false;
  m_return_val_if_fail(M_IS_SEQ(seq), false);
  if (M_SEQ_CLASS(M_OBJECT(seq)->class_)->add) {
    va_list ap;
    va_start(ap, seq);
    result = M_SEQ_CLASS(M_OBJECT(seq)->class_)->add(seq, ap);
    va_end(ap);
  }
  return result;
}

bool m_seq_del(MSeq *seq, ...)
{
  bool result = false;
  m_return_val_if_fail(M_IS_SEQ(seq), false);
  if (M_SEQ_CLASS(M_OBJECT(seq)->class_)->del) {
    va_list ap;
    va_start(ap, seq);
    result = M_SEQ_CLASS(M_OBJECT(seq)->class_)->del(seq, ap);
    va_end(ap);
  }
  return result;
}

uint32_t m_seq_size(MSeq *seq)
{
  uint32_t result = 0;
  m_return_val_if_fail(M_IS_SEQ(seq), 0);
  if (M_SEQ_CLASS(M_OBJECT(seq)->class_)->size)
    result = M_SEQ_CLASS(M_OBJECT(seq)->class_)->size(seq);
  return result;
}

M_ABSTRACT_CLASS_DEF(MSeq, seq, m_object_class())
