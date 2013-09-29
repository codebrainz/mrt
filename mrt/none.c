#include <mrt/none-impl.h>
#include <stdlib.h>

static MRT_None *none_singleton = NULL;

static void on_exit_cleanup_none(void)
{
  if (none_singleton != NULL) {
    mrt_value_unref(MRT_VALUE(none_singleton));
    none_singleton = NULL;
  }
}

MRT_Value *mrt_none(void)
{
  if (none_singleton == NULL) {
    none_singleton = MRT_NONE(mrt_value_construct(mrt_none_class(), NULL));
    if (none_singleton != NULL) {
      mrt_value_ref_sync(MRT_VALUE(none_singleton));
      atexit(on_exit_cleanup_none);
    }
  }
  return mrt_value_ref(MRT_VALUE(none_singleton));
}

MRT_BEGIN_CLASS_DEF(MRT_None, none, mrt_value_class())
{
  // Provides no methods
}
MRT_END_CLASS_DEF
