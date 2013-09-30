#include <mrt/none-impl.h>

static bool none_singleton_initialized = false;
static MRT_None none_singleton;

MRT_Object *mrt_none(void)
{
  if (!none_singleton_initialized) {
    mrt_object_construct(mrt_none_class(), MRT_OBJECT(&none_singleton));
    mrt_object_ref_sync(MRT_OBJECT(&none_singleton));
    none_singleton_initialized = true;
  }
  return mrt_object_ref(MRT_OBJECT(&none_singleton));
}

MRT_BEGIN_CLASS_DEF(MRT_None, none, mrt_object_class())
{
  // Provides no methods
}
MRT_END_CLASS_DEF
