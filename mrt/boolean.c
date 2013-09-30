#include <mrt/boolean-impl.h>

static bool boolean_singletons_initialized = false;
static MBoolean true_singleton;
static MBoolean false_singleton;

static inline void m_boolean_once_init(void)
{
  if (!boolean_singletons_initialized) {
    m_object_construct(m_boolean_class(), M_OBJECT(&true_singleton));
    m_object_ref_sync(M_OBJECT(&true_singleton));
    m_object_construct(m_boolean_class(), M_OBJECT(&false_singleton));
    m_object_ref_sync(M_OBJECT(&false_singleton));
    boolean_singletons_initialized = true;
  }
}

MObject *m_boolean_true(void)
{
  m_boolean_once_init();
  return M_OBJECT(&true_singleton);
}

MObject *m_boolean_false(void)
{
  m_boolean_once_init();
  return M_OBJECT(&false_singleton);
}

MObject *m_boolean_new(bool val)
{
  return val ? m_object_ref(m_boolean_true()) : m_object_ref(m_boolean_false());
}

bool m_boolean_get(MBoolean *b)
{
  if (!M_IS_BOOLEAN(b))
    return false;
  return (b == &true_singleton) ? true : false;
}

M_BEGIN_CLASS_DEF(MBoolean, boolean, m_number_class())
{
  // No additional methods
}
M_END_CLASS_DEF
