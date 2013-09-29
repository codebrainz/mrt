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

// FIXME: move type registration to other file and optimize it better
// since it's used all over the place indirectly.
#define MRT_MAX_CLASSES 32

static uint32_t next_available_class_id = 0;
static MRT_ValueClass *registered_classes[MRT_MAX_CLASSES] = { NULL };

static void on_exit_unreg_classes(void)
{
  size_t i;
  for (i = 0; i < MRT_MAX_CLASSES; i++) {
    if (registered_classes[i]) {
      mrt_free(registered_classes[i]);
      registered_classes[i] = NULL;
    }
  }
}

const MRT_ValueClass *mrt_value_class_register(const MRT_ValueClass *class_ptr)
{
  uint32_t id;

  if (class_ptr == NULL)
    return NULL;

  if (next_available_class_id == 0)
    atexit(on_exit_unreg_classes);

  if (next_available_class_id > MRT_MAX_CLASSES) {
    MRT_VALUE_CLASS(class_ptr)->type_id = MRT_VALUE_CLASS_INVALID; // eek
    return NULL;
  }

  id = next_available_class_id++;
  registered_classes[id] = MRT_VALUE_CLASS(class_ptr); // eek
  registered_classes[id]->type_id = id;

  printf("Registered class '%s' (%p) [id:%u]\n", registered_classes[id]->name,
    registered_classes[id], id);

  return registered_classes[id];
}

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

  printf("Allocated instance of '%s' of size '%u'\n",
         class_ptr->name, class_ptr->size);

  //memset(value_ptr, 0, class_ptr->size);
  value_ptr->class_ = class_ptr;

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
  old_val = value->ref_count;
  ret_value = value;
  if (old_val <= 1) {
    mrt_value_destruct(value);
    ret_value = NULL;
  } else {
    do { new_val = old_val - 1; }
    while (!mrt_atomic_cas32(&(value->ref_count), old_val, new_val));
  }
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
    MRT_ValueClass *cls_cur = MRT_VALUE_CLASS(cls);
    MRT_ValueClass *cls_test = MRT_VALUE_CLASS(class_);
    printf("Class '%s' (%p) != '%s' (%p)\n",
           cls_cur->name, cls_cur, cls_test->name, cls_test);
    //cls = mrt_value_class_super(cls);
    cls = cls->super;
  }

  if (cls == class_) {
    MRT_ValueClass *cls_cur = MRT_VALUE_CLASS(cls);
    MRT_ValueClass *cls_test = MRT_VALUE_CLASS(class_);
    printf("Class '%s' (%p) == '%s' (%p)\n",
           cls_cur->name, cls_cur, cls_test->name, cls_test);
  }

  if (cls == NULL) {
    printf("Unable to tell is instance\n");
  }

  printf("-----------------------\n");

  return (cls != NULL);
}

MRT_ABSTRACT_CLASS_DEF(MRT_Value, value, NULL)
