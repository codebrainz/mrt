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

#ifndef M_OBJECT_IMPL_H
#define M_OBJECT_IMPL_H

#include <mrt/object.h>
#include <mrt/memory.h>
#include <stdarg.h>
#include <string.h>

M_BEGIN_CDECLS

enum MObjectFlags
{
  M_OBJECT_FLAG_NONE      = (1<<0),
  M_OBJECT_FLAG_FLOATING  = (1<<1),
  M_OBJECT_FLAG_ALLOCATED = (1<<2),
};

struct MObject
{
  const MObjectClass *class_;
  uint32_t flags;
  uint32_t ref_count;
};

typedef void (*MObjectConstructFunc)(MObject*, va_list);
typedef void (*MObjectDestructFunc)(MObject*);
typedef MObject (*MObjectCopyFunc)(const MObject*);
typedef size_t (*MObjectHashFunc)(const MObject*);
typedef int (*MObjectCompareFunc)(const MObject*, const MObject*);
typedef bool (*MObjectEqualFunc)(const MObject*, const MObject*);

enum MObjectClassFlags
{
  M_OBJECT_CLASS_FLAG_NONE     = (1<<0),
};

struct MObjectClass
{
  const struct MObjectClass *super;
  uint32_t type_id;
  uint32_t size;
  uint32_t flags;
  const char *name;
  MObjectConstructFunc ctor;
  MObjectDestructFunc dtor;
  MObjectCopyFunc copy;
  MObjectHashFunc hash;
  MObjectCompareFunc compare;
  MObjectEqualFunc equal;
};

MObject *m_object_construct(const MObjectClass *class_ptr,
  MObject *obj_ptr, ...);

const MObjectClass *m_object_class_register(const MObjectClass *class_ptr);

#define M_BEGIN_CLASS_DEF(T, name_, super_)            \
const MObjectClass * m_ ## name_ ## _class (void)   \
{                                                        \
  static bool class_initialized_ = false;                \
  static T ## Class obj_class_;                        \
  if (!class_initialized_) {                             \
    memset(&obj_class_, 0, sizeof(T ## Class));        \
    M_OBJECT_CLASS(&obj_class_)->super = super_ ;    \
    M_OBJECT_CLASS(&obj_class_)->size = sizeof( T ); \
    M_OBJECT_CLASS(&obj_class_)->name = #T;          \
    class_initialized_ = true;                           \
  }                                                      \
  do

#define M_SET_FIELD(clsT_, memb_, fn_ptr_)         \
  do {                                               \
    clsT_ *cls_temp_ptr__ = (clsT_ *) &obj_class_; \
    cls_temp_ptr__->memb_ = fn_ptr_ ;                \
  } while (0)

#define M_END_CLASS_DEF                 \
  while (0);                              \
  return M_OBJECT_CLASS(&obj_class_); \
}

#define M_ABSTRACT_CLASS_DEF(T, name_, super_)       \
const MObjectClass * m_ ## name_ ## _class (void) \
{                                                      \
  static bool class_initialized_ = false;              \
  static MObjectClass obj_class_;                 \
  if (!class_initialized_) {                           \
    memset(&obj_class_, 0, sizeof(T ## Class));      \
    obj_class_.super = super_ ;                      \
    obj_class_.size = sizeof( T );                   \
    obj_class_.name = #T;                            \
    class_initialized_ = true;                         \
  }                                                    \
  return &obj_class_ ;                               \
}

M_END_CDECLS

#endif // M_OBJECT_IMPL_H
