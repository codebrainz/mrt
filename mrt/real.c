#include <mrt/real-impl.h>

static void mrt_real_ctor(MRT_Object *obj, va_list ap)
{
  MRT_Real *real = MRT_REAL(obj);
  real->obj = va_arg(ap, double);
}

MRT_Object *mrt_real_new(double val)
{
  return mrt_object_construct(mrt_real_class(), NULL, val);
}

double mrt_real_get(MRT_Real *r)
{
  mrt_return_val_if_fail(MRT_IS_REAL(r), 0.0);
  return r->obj;
}

void mrt_real_set(MRT_Real *r, double val)
{
  mrt_return_if_fail(MRT_IS_REAL(r));
  r->obj = val;
}

MRT_BEGIN_CLASS_DEF(MRT_Real, real, mrt_number_class())
{
  MRT_SET_FIELD(MRT_ObjectClass, ctor, mrt_real_ctor);
}
MRT_END_CLASS_DEF
