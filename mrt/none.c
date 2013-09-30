#include <mrt/none-impl.h>

static bool none_singleton_initialized = false;
static MRT_None none_singleton;

MRT_Value *mrt_none(void)
{
  if (!none_singleton_initialized) {
    mrt_value_construct(mrt_none_class(), MRT_VALUE(&none_singleton));
    mrt_value_ref_sync(MRT_VALUE(&none_singleton));
    none_singleton_initialized = true;
  }
  return mrt_value_ref(MRT_VALUE(&none_singleton));
}

MRT_BEGIN_CLASS_DEF(MRT_None, none, mrt_value_class())
{
  // Provides no methods
}
MRT_END_CLASS_DEF
