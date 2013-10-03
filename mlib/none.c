#include <mlib/none-impl.h>

static bool none_singleton_initialized = false;
static MNone none_singleton;

MObject *m_none(void)
{
  if (!none_singleton_initialized) {
    m_object_construct(m_none_class(), M_OBJECT(&none_singleton));
    m_object_ref_sync(M_OBJECT(&none_singleton));
    none_singleton_initialized = true;
  }
  return m_object_ref(M_OBJECT(&none_singleton));
}

M_BEGIN_CLASS_DEF(MNone, none, m_object_class())
{
  // Provides no methods
}
M_END_CLASS_DEF
