#include <mlib/integer-impl.h>

static void m_integer_ctor(MObject *obj, va_list ap)
{
  MInteger *int_ = M_INTEGER(obj);
  int_->obj = va_arg(ap, int64_t);
}

MObject *m_integer_new(int64_t val)
{
  return m_object_construct(m_integer_class(), NULL, val);
}

int64_t m_integer_get(MInteger *i)
{
  m_return_val_if_fail(M_IS_INTEGER(i), 0);
  return i->obj;
}

void m_integer_set(MInteger *i, int64_t val)
{
  m_return_if_fail(M_IS_INTEGER(i));
  i->obj = val;
}

M_BEGIN_CLASS_DEF(MInteger, integer, m_number_class())
{
  M_SET_FIELD(MObjectClass, ctor, m_integer_ctor);
}
M_END_CLASS_DEF
