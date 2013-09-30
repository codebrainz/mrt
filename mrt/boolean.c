#include <mrt/boolean-impl.h>

static bool boolean_singletons_initialized = false;
static MRT_Boolean true_singleton;
static MRT_Boolean false_singleton;

static inline void mrt_boolean_once_init(void)
{
  if (!boolean_singletons_initialized) {
    mrt_object_construct(mrt_boolean_class(), MRT_OBJECT(&true_singleton));
    mrt_object_ref_sync(MRT_OBJECT(&true_singleton));
    mrt_object_construct(mrt_boolean_class(), MRT_OBJECT(&false_singleton));
    mrt_object_ref_sync(MRT_OBJECT(&false_singleton));
    boolean_singletons_initialized = true;
  }
}

MRT_Object *mrt_boolean_true(void)
{
  mrt_boolean_once_init();
  return MRT_OBJECT(&true_singleton);
}

MRT_Object *mrt_boolean_false(void)
{
  mrt_boolean_once_init();
  return MRT_OBJECT(&false_singleton);
}

MRT_Object *mrt_boolean_new(bool val)
{
  return val ? mrt_object_ref(mrt_boolean_true()) : mrt_object_ref(mrt_boolean_false());
}

bool mrt_boolean_get(MRT_Boolean *b)
{
  if (!MRT_IS_BOOLEAN(b))
    return false;
  return (b == &true_singleton) ? true : false;
}

MRT_BEGIN_CLASS_DEF(MRT_Boolean, boolean, mrt_number_class())
{
  // No additional methods
}
MRT_END_CLASS_DEF
