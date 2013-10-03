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

#include <mlib/pointer-impl.h>

static void m_pointer_ctor(MObject *obj, va_list ap)
{
  MPointer *p = M_POINTER(obj);
  p->ptr = va_arg(ap, void*);
  p->copy = va_arg(ap, MPointerCopyFunc);
  p->free = va_arg(ap, MPointerFreeFunc);
}

static void m_pointer_dtor(MObject *obj)
{
  MPointer *p = M_POINTER(obj);
  if (p->free)
    p->free(p->ptr);
}

static MObject *m_pointer_copy(const MObject *obj)
{
  MPointer *p = M_POINTER(obj);
  MPointer *np = M_POINTER(m_pointer_new(p->ptr, p->copy, p->free));
  if (p->copy)
    np->ptr = p->copy(p->ptr);
  return M_OBJECT(np);
}

MObject *m_pointer_new(void *ptr, MPointerCopyFunc copy, MPointerFreeFunc free)
{
  return m_object_construct(m_pointer_class(), NULL, ptr, copy, free);
}

void *m_pointer_get(MPointer *p)
{
  m_return_val_if_fail(M_IS_POINTER(p), NULL);
  return p->ptr;
}

void m_pointer_set(MPointer *p, void *ptr)
{
  m_return_if_fail(M_IS_POINTER(p));
  p->ptr = ptr;
}

M_BEGIN_CLASS_DEF(MPointer, pointer, m_object_class())
{
  M_SET_FIELD(MObjectClass, ctor, m_pointer_ctor);
  M_SET_FIELD(MObjectClass, dtor, m_pointer_dtor);
  M_SET_FIELD(MObjectClass, copy, m_pointer_copy);
}
M_END_CLASS_DEF
