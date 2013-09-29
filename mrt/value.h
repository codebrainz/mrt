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

#ifndef MRT_VALUE_H
#define MRT_VALUE_H 1

#include <mrt/macros.h>
#include <mrt/basictypes.h>

MRT_BEGIN_CDECLS

#define MRT_VALUE(v)       ((MRT_Value*)(v))
#define MRT_VALUE_CLASS(c) ((MRT_ValueClass*)(c))
#define MRT_IS_VALUE(v) mrt_value_is_instance(mrt_value_class(), MRT_VALUE(v))
#define MRT_VALUE_CLASS_INVALID ((uint32_t)-1)

typedef struct MRT_Value MRT_Value;
typedef struct MRT_ValueClass MRT_ValueClass;

const MRT_ValueClass *mrt_value_class(void);

MRT_Value *mrt_value_ref(MRT_Value *value);
MRT_Value *mrt_value_ref_sync(MRT_Value *value);
MRT_Value *mrt_value_unref(MRT_Value *value);
MRT_Value *mrt_value_copy(const MRT_Value *value);

bool mrt_value_is_instance(const MRT_ValueClass *class_, const MRT_Value *value);

MRT_END_CDECLS

#endif // MRT_VALUE_H
