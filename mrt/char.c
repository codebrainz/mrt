#include <mrt/char-impl.h>

static bool char_ascii_initialized = false;
static MChar char_ascii[128];

static void char_once_init(void)
{
  if (!char_ascii_initialized) {
    uint32_t i;
    for (i = 0; i < 128; i++)
      m_object_construct(m_char_class(), M_OBJECT(&char_ascii[i]), i);
    char_ascii_initialized = true;
  }
}

static void m_char_ctor(MObject *obj, va_list ap)
{
  MChar *c = M_CHAR(obj);
  c->obj = va_arg(ap, uint32_t);
}

static void m_char_dtor(MObject *obj)
{
  MChar *c = M_CHAR(obj);
  c->obj = 0;
}

MObject *m_char_new(uint32_t ch)
{
  char_once_init();
  if (ch < 128)
    return m_object_ref(M_OBJECT(&char_ascii[ch]));
  return m_object_construct(m_char_class(), NULL, ch);
}

uint32_t m_char_get(MChar *c)
{
  m_return_val_if_fail(M_IS_CHAR(c), 0);
  return c->obj;
}

void m_char_set(MChar *c, uint32_t ch)
{
  m_return_if_fail(M_IS_CHAR(c));
  c->obj = ch;
}

M_BEGIN_CLASS_DEF(MChar, char, m_object_class())
{
  M_SET_FIELD(MObjectClass, ctor, m_char_ctor);
  M_SET_FIELD(MObjectClass, dtor, m_char_dtor);
}
M_END_CLASS_DEF
