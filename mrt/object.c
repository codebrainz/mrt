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

#include <mrt/object-impl.h>
#include <mrt/atomic.h>
#include <mrt/memory.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static void m_object_destruct(MObject *obj)
{
  bool allocated = (obj->flags & M_OBJECT_FLAG_ALLOCATED);

  if (obj->class_->dtor)
    obj->class_->dtor(obj);

  memset(obj, 0, sizeof(obj->class_->size));

  if (allocated)
    m_free(obj);
}

MObject *m_object_construct(const MObjectClass *class_ptr, MObject *obj_ptr, ...)
{
  uint32_t flags = M_OBJECT_FLAG_FLOATING;

  m_return_val_if_fail(class_ptr, NULL);
  m_return_val_if_fail(class_ptr->size >= sizeof(MObject), NULL);

  if (!obj_ptr) {
    obj_ptr = m_malloc(class_ptr->size);
    if (obj_ptr == NULL)
      return NULL;
    flags |= M_OBJECT_FLAG_ALLOCATED;
  }

  //printf("Allocated instance of '%s' of size '%u'\n",
  //       class_ptr->name, class_ptr->size);

  memset(obj_ptr, 0, class_ptr->size);
  obj_ptr->class_ = class_ptr;
  obj_ptr->ref_count = 1;
  obj_ptr->flags = flags;

  if (class_ptr->ctor) {
    va_list ap;
    va_start(ap, obj_ptr);
    class_ptr->ctor(obj_ptr, ap);
    va_end(ap);
  }

  obj_ptr->flags |= flags;

  return obj_ptr;
}

/**
 * Increase the obj's reference count.
 *
 * The reference count is a 32-bit unsigned integer. When 2^32
 * references have been taken, the reference count will overflow
 * resulting in undefined behaviour of the MObject routines.
 *
 * @param obj The obj.
 * @return The same @a obj pointer.
 */
MObject *m_object_ref(MObject *obj)
{
  m_return_val_if_fail(M_IS_OBJECT(obj), NULL);
  m_atomic_inc32(obj->ref_count);
  return obj;
}

/**
 * Increase or take over the obj's reference count.
 *
 * Newly allocated objs will have a "floating reference" flag and
 * a reference count of one. If a obj is then added to a another
 * composite obj (ex. adding a obj to a list), the composite obj
 * will use this function to clear the "floating reference" flag and
 * take ownership of the initial reference.
 *
 * @param obj The obj.
 * @return The same @a obj pointer.
 */
MObject *m_object_ref_sync(MObject *obj)
{
  uint32_t old_flags, new_flags;
  m_return_val_if_fail(M_IS_OBJECT(obj), NULL);
  do {
    old_flags = obj->flags;
    if (!(old_flags & M_OBJECT_FLAG_FLOATING))
      return m_object_ref(obj);
    new_flags = (old_flags & ~M_OBJECT_FLAG_FLOATING);
  } while (!m_atomic_cas32(&(obj->flags), old_flags, new_flags));
  return obj;
}

/**
 * Decrease the obj's reference count.
 *
 * When the reference count goes to zero, the obj will be destructed.
 *
 * @param obj The obj.
 * @return The same @a obj pointer or @c NULL if the @a obj was
 * destructed.
 */
MObject *m_object_unref(MObject *obj)
{
  uint32_t old_val, new_val;
  MObject *ret_obj;
  m_return_val_if_fail(M_IS_OBJECT(obj), NULL);
  ret_obj = obj;
  do {
    old_val = obj->ref_count;
    if (old_val <= 1) {
      m_object_destruct(obj);
      ret_obj = NULL;
      break;
    }
    new_val = old_val - 1;
  } while (!m_atomic_cas32(&(obj->ref_count), old_val, new_val));
  return ret_obj;
}

/**
 * Make a copy of the obj.
 *
 * The type of of obj determines which type of copy takes place.
 * In the case of composite objs, that is those containing other
 * MObjects, a deep referencing of all children will take place.
 * In the case of basic types, the obj's payload will be directly
 * copied.
 *
 * @param obj The obj to copy.
 * @return A newly allocated MObject with a reference count of 1.
 */
MObject *m_object_copy(const MObject *obj)
{
  m_return_val_if_fail(M_IS_OBJECT(obj), NULL);
  return NULL;
}

size_t m_object_hash(const MObject *obj)
{
  m_return_val_if_fail(M_IS_OBJECT(obj), 0);
  if (obj->class_->hash)
    return obj->class_->hash(obj);
  return (size_t) obj; // use address
}

int m_object_compare(const MObject *obj1, const MObject *obj2)
{
  m_return_val_if_fail(M_IS_OBJECT(obj1), 0);
  m_return_val_if_fail(M_IS_OBJECT(obj2), 0);
  if (obj1->class_->compare)
    return obj1->class_->compare(obj1, obj2);
  else if (obj2->class_->compare) {
    int res = obj2->class_->compare(obj2, obj1);
    if (res < 0)
      return 1;
    else if (res > 0)
      return -1;
    else
      return 0;
  } else {
    return m_object_hash(obj1) - m_object_hash(obj2);
  }
}

bool m_object_equal(const MObject *obj1, const MObject *obj2)
{
  m_return_val_if_fail(M_IS_OBJECT(obj1), false);
  m_return_val_if_fail(M_IS_OBJECT(obj2), false);
  if (obj1->class_->equal)
    return obj1->class_->equal(obj1, obj2);
  else if (obj2->class_->equal)
    return obj2->class_->equal(obj1, obj2);
  else
    return (m_object_compare(obj1, obj2) == 0);
}

bool m_object_is_instance(const MObjectClass *class_, const MObject *obj)
{
  const MObjectClass *cls;

  if (obj == NULL)
    return false;

  //cls = m_object_classof(obj);
  cls = obj->class_;
  while ( (cls != class_) && (cls != NULL) ) {
    //cls = m_object_class_super(cls);
    cls = cls->super;
  }

  return (cls != NULL);
}

M_ABSTRACT_CLASS_DEF(MObject, object, NULL)
