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

#ifndef M_OBJECT_H
#define M_OBJECT_H 1

#include <mrt/macros.h>
#include <mrt/basictypes.h>

M_BEGIN_CDECLS

#define M_OBJECT(v)       ((MObject*)(v))
#define M_OBJECT_CLASS(c) ((MObjectClass*)(c))
#define M_IS_OBJECT(v) m_object_is_instance(m_object_class(), M_OBJECT(v))
#define M_OBJECT_CLASS_INVALID ((uint32_t)-1)

typedef struct MObject MObject;
typedef struct MObjectClass MObjectClass;

const MObjectClass *m_object_class(void);

MObject *m_object_ref(MObject *obj);
MObject *m_object_ref_sync(MObject *obj);
MObject *m_object_unref(MObject *obj);
MObject *m_object_copy(MObject *obj);
size_t m_object_hash(const MObject *obj);
int m_object_compare(const MObject *obj1, const MObject *obj2);
bool m_object_equal(const MObject *obj1, const MObject *obj2);

bool m_object_is_instance(const MObjectClass *class_, const MObject *obj);

M_END_CDECLS

#endif // M_OBJECT_H
