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

#include <mrt/value-impl.h>
#include <mrt/atomic.h>
#include <mrt/memory.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static void mrt_value_destruct(MRT_Value *value)
{
  bool allocated = (value->flags & MRT_VALUE_FLAG_ALLOCATED);

  if (value->class_->dtor)
    value->class_->dtor(value);

  memset(value, 0, sizeof(value->class_->size));

  if (allocated)
    mrt_free(value);
}

MRT_Value *mrt_value_construct(const MRT_ValueClass *class_ptr, MRT_Value *value_ptr, ...)
{
  uint32_t flags = MRT_VALUE_FLAG_FLOATING;

  mrt_return_val_if_fail(class_ptr, NULL);
  mrt_return_val_if_fail(class_ptr->size >= sizeof(MRT_Value), NULL);

  if (!value_ptr) {
    value_ptr = mrt_malloc(class_ptr->size);
    if (value_ptr == NULL)
      return NULL;
    flags |= MRT_VALUE_FLAG_ALLOCATED;
  }

  //printf("Allocated instance of '%s' of size '%u'\n",
  //       class_ptr->name, class_ptr->size);

  memset(value_ptr, 0, class_ptr->size);
  value_ptr->class_ = class_ptr;
  value_ptr->ref_count = 1;
  value_ptr->flags = flags;

  if (class_ptr->ctor) {
    va_list ap;
    va_start(ap, value_ptr);
    class_ptr->ctor(value_ptr, ap);
    va_end(ap);
  }

  value_ptr->flags |= flags;

  return value_ptr;
}

/**
 * Increase the value's reference count.
 *
 * The reference count is a 32-bit unsigned integer. When 2^32
 * references have been taken, the reference count will overflow
 * resulting in undefined behaviour of the MRT_Value routines.
 *
 * @param value The value.
 * @return The same @a value pointer.
 */
MRT_Value *mrt_value_ref(MRT_Value *value)
{
  mrt_return_val_if_fail(MRT_IS_VALUE(value), NULL);
  mrt_atomic_inc32(value->ref_count);
  return value;
}

/**
 * Increase or take over the value's reference count.
 *
 * Newly allocated values will have a "floating reference" flag and
 * a reference count of one. If a value is then added to a another
 * composite value (ex. adding a value to a list), the composite value
 * will use this function to clear the "floating reference" flag and
 * take ownership of the initial reference.
 *
 * @param value The value.
 * @return The same @a value pointer.
 */
MRT_Value *mrt_value_ref_sync(MRT_Value *value)
{
  uint32_t old_flags, new_flags;
  mrt_return_val_if_fail(MRT_IS_VALUE(value), NULL);
  do {
    old_flags = value->flags;
    if (!(old_flags & MRT_VALUE_FLAG_FLOATING))
      return mrt_value_ref(value);
    new_flags = (old_flags & ~MRT_VALUE_FLAG_FLOATING);
  } while (!mrt_atomic_cas32(&(value->flags), old_flags, new_flags));
  return value;
}

/**
 * Decrease the value's reference count.
 *
 * When the reference count goes to zero, the value will be destructed.
 *
 * @param value The value.
 * @return The same @a value pointer or @c NULL if the @a value was
 * destructed.
 */
MRT_Value *mrt_value_unref(MRT_Value *value)
{
  uint32_t old_val, new_val;
  MRT_Value *ret_value;
  mrt_return_val_if_fail(MRT_IS_VALUE(value), NULL);
  ret_value = value;
  do {
    old_val = value->ref_count;
    if (old_val <= 1) {
      mrt_value_destruct(value);
      ret_value = NULL;
      break;
    }
    new_val = old_val - 1;
  } while (!mrt_atomic_cas32(&(value->ref_count), old_val, new_val));
  return ret_value;
}

/**
 * Make a copy of the value.
 *
 * The type of of value determines which type of copy takes place.
 * In the case of composite values, that is those containing other
 * MRT_Values, a deep referencing of all children will take place.
 * In the case of basic types, the value's payload will be directly
 * copied.
 *
 * @param value The value to copy.
 * @return A newly allocated MRT_Value with a reference count of 1.
 */
MRT_Value *mrt_value_copy(const MRT_Value *value)
{
  mrt_return_val_if_fail(MRT_IS_VALUE(value), NULL);
  return NULL;
}

#if 0
static const MRT_ValueClass *mrt_value_classof(const MRT_Value *value)
{
  mrt_return_val_if_fail(value, NULL);
  return MRT_VALUE_CLASS(value->class_);
}

static const MRT_ValueClass *mrt_value_class_super(const MRT_ValueClass *class_)
{
  mrt_return_val_if_fail(class_, NULL);
  return class_->super;
}
#endif

bool mrt_value_is_instance(const MRT_ValueClass *class_, const MRT_Value *value)
{
  const MRT_ValueClass *cls;

  if (value == NULL)
    return false;

  //cls = mrt_value_classof(value);
  cls = value->class_;
  while ( (cls != class_) && (cls != NULL) ) {
    //cls = mrt_value_class_super(cls);
    cls = cls->super;
  }

  return (cls != NULL);
}

MRT_ABSTRACT_CLASS_DEF(MRT_Value, value, NULL)
