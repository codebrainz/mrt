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

#ifndef MRT_OBJECT_H
#define MRT_OBJECT_H 1

#include <mrt/macros.h>
#include <mrt/basictypes.h>

MRT_BEGIN_CDECLS

#define MRT_OBJECT(v)       ((MRT_Object*)(v))
#define MRT_OBJECT_CLASS(c) ((MRT_ObjectClass*)(c))
#define MRT_IS_OBJECT(v) mrt_object_is_instance(mrt_object_class(), MRT_OBJECT(v))
#define MRT_OBJECT_CLASS_INVALID ((uint32_t)-1)

typedef struct MRT_Object MRT_Object;
typedef struct MRT_ObjectClass MRT_ObjectClass;

const MRT_ObjectClass *mrt_object_class(void);

MRT_Object *mrt_object_ref(MRT_Object *obj);
MRT_Object *mrt_object_ref_sync(MRT_Object *obj);
MRT_Object *mrt_object_unref(MRT_Object *obj);
MRT_Object *mrt_object_copy(const MRT_Object *obj);
size_t mrt_object_hash(const MRT_Object *obj);
int mrt_object_compare(const MRT_Object *obj1, const MRT_Object *obj2);
bool mrt_object_equal(const MRT_Object *obj1, const MRT_Object *obj2);

bool mrt_object_is_instance(const MRT_ObjectClass *class_, const MRT_Object *obj);

MRT_END_CDECLS

#endif // MRT_OBJECT_H
