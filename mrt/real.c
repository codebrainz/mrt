#include <mrt/real-impl.h>

static void m_real_ctor(MObject *obj, va_list ap)
{
  MReal *real = M_REAL(obj);
  real->obj = va_arg(ap, double);
}

MObject *m_real_new(double val)
{
  return m_object_construct(m_real_class(), NULL, val);
}

double m_real_get(MReal *r)
{
  m_return_val_if_fail(M_IS_REAL(r), 0.0);
  return r->obj;
}

void m_real_set(MReal *r, double val)
{
  m_return_if_fail(M_IS_REAL(r));
  r->obj = val;
}

M_BEGIN_CLASS_DEF(MReal, real, m_number_class())
{
  M_SET_FIELD(MObjectClass, ctor, m_real_ctor);
}
M_END_CLASS_DEF
