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

#include <mlib/array-impl.h>

static void m_array_ctor(MObject *obj, va_list ap)
{
  MArray *arr = M_ARRAY(obj);
  (void)ap;
  arr->data = NULL;
  arr->size = 0;
}

static void m_array_dtor(MObject *obj)
{
  MArray *arr = M_ARRAY(obj);
  uint32_t i;
  for (i = 0; i < arr->size; i++) {
    m_object_unref(arr->data[i]);
    arr->data[i] = NULL;
  }
  m_free(arr->data);
  arr->data = NULL;
  arr->size = 0;
}

MObject *m_array_new(void)
{
  return m_object_construct(m_array_class(), NULL);
}

M_BEGIN_CLASS_DEF(MArray, array, m_seq_class())
{
  M_SET_FIELD(MObjectClass, ctor, m_array_ctor);
  M_SET_FIELD(MObjectClass, dtor, m_array_dtor);
}
M_END_CLASS_DEF
