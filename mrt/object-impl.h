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

#ifndef MRT_OBJECT_IMPL_H
#define MRT_OBJECT_IMPL_H

#include <mrt/object.h>
#include <mrt/memory.h>
#include <stdarg.h>
#include <string.h>

MRT_BEGIN_CDECLS

enum MRT_ObjectFlags
{
  MRT_OBJECT_FLAG_NONE      = (1<<0),
  MRT_OBJECT_FLAG_FLOATING  = (1<<1),
  MRT_OBJECT_FLAG_ALLOCATED = (1<<2),
};

struct MRT_Object
{
  const MRT_ObjectClass *class_;
  uint32_t flags;
  uint32_t ref_count;
};

typedef void (*MRT_ObjectConstructFunc)(MRT_Object*, va_list);
typedef void (*MRT_ObjectDestructFunc)(MRT_Object*);
typedef MRT_Object (*MRT_ObjectCopyFunc)(const MRT_Object*);
typedef size_t (*MRT_ObjectHashFunc)(const MRT_Object*);
typedef int (*MRT_ObjectCompareFunc)(const MRT_Object*, const MRT_Object*);
typedef bool (*MRT_ObjectEqualFunc)(const MRT_Object*, const MRT_Object*);

enum MRT_ObjectClassFlags
{
  MRT_OBJECT_CLASS_FLAG_NONE     = (1<<0),
};

struct MRT_ObjectClass
{
  const struct MRT_ObjectClass *super;
  uint32_t type_id;
  uint32_t size;
  uint32_t flags;
  const char *name;
  MRT_ObjectConstructFunc ctor;
  MRT_ObjectDestructFunc dtor;
  MRT_ObjectCopyFunc copy;
  MRT_ObjectHashFunc hash;
  MRT_ObjectCompareFunc compare;
  MRT_ObjectEqualFunc equal;
};

MRT_Object *mrt_object_construct(const MRT_ObjectClass *class_ptr,
  MRT_Object *obj_ptr, ...);

const MRT_ObjectClass *mrt_object_class_register(const MRT_ObjectClass *class_ptr);

#define MRT_BEGIN_CLASS_DEF(T, name_, super_)            \
const MRT_ObjectClass * mrt_ ## name_ ## _class (void)   \
{                                                        \
  static bool class_initialized_ = false;                \
  static T ## Class obj_class_;                        \
  if (!class_initialized_) {                             \
    memset(&obj_class_, 0, sizeof(T ## Class));        \
    MRT_OBJECT_CLASS(&obj_class_)->super = super_ ;    \
    MRT_OBJECT_CLASS(&obj_class_)->size = sizeof( T ); \
    MRT_OBJECT_CLASS(&obj_class_)->name = #T;          \
    class_initialized_ = true;                           \
  }                                                      \
  do

#define MRT_SET_FIELD(clsT_, memb_, fn_ptr_)         \
  do {                                               \
    clsT_ *cls_temp_ptr__ = (clsT_ *) &obj_class_; \
    cls_temp_ptr__->memb_ = fn_ptr_ ;                \
  } while (0)

#define MRT_END_CLASS_DEF                 \
  while (0);                              \
  return MRT_OBJECT_CLASS(&obj_class_); \
}

#define MRT_ABSTRACT_CLASS_DEF(T, name_, super_)       \
const MRT_ObjectClass * mrt_ ## name_ ## _class (void) \
{                                                      \
  static bool class_initialized_ = false;              \
  static MRT_ObjectClass obj_class_;                 \
  if (!class_initialized_) {                           \
    memset(&obj_class_, 0, sizeof(T ## Class));      \
    obj_class_.super = super_ ;                      \
    obj_class_.size = sizeof( T );                   \
    obj_class_.name = #T;                            \
    class_initialized_ = true;                         \
  }                                                    \
  return &obj_class_ ;                               \
}

MRT_END_CDECLS

#endif // MRT_OBJECT_IMPL_H
