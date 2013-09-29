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

#ifndef MRT_VALUE_IMPL_H
#define MRT_VALUE_IMPL_H

#include <mrt/value.h>
#include <mrt/memory.h>
#include <stdarg.h>

MRT_BEGIN_CDECLS

enum MRT_ValueFlags
{
  MRT_VALUE_FLAG_NONE      = (1<<0),
  MRT_VALUE_FLAG_FLOATING  = (1<<1),
  MRT_VALUE_FLAG_ALLOCATED = (1<<2),
};

struct MRT_Value
{
  const MRT_ValueClass *class_;
  uint32_t flags;
  uint32_t ref_count;
};

typedef void (*MRT_ValueConstructFunc)(MRT_Value*, va_list);
typedef void (*MRT_ValueDestructFunc)(MRT_Value*);

enum MRT_ValueClassFlags
{
  MRT_VALUE_CLASS_FLAG_NONE     = (1<<0),
};

struct MRT_ValueClass
{
  const struct MRT_ValueClass *super;
  uint32_t type_id;
  uint32_t size;
  uint32_t flags;
  const char *name;
  MRT_ValueConstructFunc ctor;
  MRT_ValueDestructFunc dtor;
  //...
};

MRT_Value *mrt_value_construct(const MRT_ValueClass *class_ptr,
  MRT_Value *value_ptr, ...);

const MRT_ValueClass *mrt_value_class_register(const MRT_ValueClass *class_ptr);

#define MRT_BEGIN_CLASS_DEF(T, name_, super_)               \
const MRT_ValueClass * mrt_ ## name_ ## _class (void)       \
{                                                           \
  static MRT_ValueClass * value_class_ = NULL;              \
  if ( value_class_ == NULL) {                              \
    value_class_ = mrt_new( T ## Class );                   \
    if ( value_class_ == NULL)                              \
      return NULL;                                          \
    value_class_->super = super_ ;                          \
    value_class_->size = sizeof( T );                       \
    value_class_->name = #T;                                \
    if (mrt_value_class_register( value_class_ ) == NULL) { \
      mrt_free( value_class_ );                             \
      value_class_ = NULL;                                  \
      return NULL;                                          \
    }                                                       \
  }                                                         \
  do

#define MRT_SET_FIELD(clsT_, memb_, fn_ptr_)        \
  do {                                              \
    clsT_ *cls_temp_ptr__ = (clsT_ *) value_class_; \
    cls_temp_ptr__->memb_ = fn_ptr_ ;               \
  } while (0)

#define MRT_END_CLASS_DEF \
  while (0);              \
  return value_class_ ;   \
}

#define MRT_ABSTRACT_CLASS_DEF(T, name_, super_)            \
const MRT_ValueClass * mrt_ ## name_ ## _class (void)       \
{                                                           \
  static MRT_ValueClass * value_class_ = NULL;              \
  if ( value_class_ == NULL) {                              \
    value_class_ = mrt_new( T ## Class );                   \
    if ( value_class_ == NULL)                              \
      return NULL;                                          \
    value_class_->super = super_ ;                          \
    value_class_->size = sizeof( T );                       \
    value_class_->name = #T;                                \
    if (mrt_value_class_register( value_class_ ) == NULL) { \
      mrt_free( value_class_ );                             \
      value_class_ = NULL;                                  \
      return NULL;                                          \
    }                                                       \
  }                                                         \
  return value_class_ ;                                     \
}

MRT_END_CDECLS

#endif // MRT_VALUE_IMPL_H
