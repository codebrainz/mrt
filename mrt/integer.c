#include <mrt/integer-impl.h>

static void mrt_integer_ctor(MRT_Value *value, va_list ap)
{
  MRT_Integer *int_ = MRT_INTEGER(value);
  int_->value = va_arg(ap, int64_t);
}

MRT_Value *mrt_integer_new(int64_t val)
{
  return mrt_value_construct(mrt_integer_class(), NULL, val);
}

int64_t mrt_integer_get(MRT_Integer *i)
{
  mrt_return_val_if_fail(MRT_IS_INTEGER(i), 0);
  return i->value;
}

void mrt_integer_set(MRT_Integer *i, int64_t val)
{
  mrt_return_if_fail(MRT_IS_INTEGER(i));
  i->value = val;
}

MRT_BEGIN_CLASS_DEF(MRT_Integer, integer, mrt_number_class())
{
  MRT_SET_FIELD(MRT_ValueClass, ctor, mrt_integer_ctor);
}
MRT_END_CLASS_DEF
