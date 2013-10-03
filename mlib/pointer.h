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

#ifndef M_POINTER_H
#define M_POINTER_H

#include <mlib/object.h>

M_BEGIN_CDECLS

#define M_POINTER(v) ((MPointer*)(v))
#define M_IS_POINTER(v) m_object_is_instance(m_pointer_class(), M_OBJECT(v))

typedef struct MPointer MPointer;

typedef void* (*MPointerCopyFunc)(const void*);
typedef void (*MPointerFreeFunc)(void*);

const MObjectClass *m_pointer_class(void);

MObject *m_pointer_new(void *ptr, MPointerCopyFunc copy, MPointerFreeFunc free);
void *m_pointer_get(MPointer *p);
void m_pointer_set(MPointer *p, void *ptr);

M_END_CDECLS

#endif // M_POINTER_H
