#include <mrt/char-impl.h>

static bool char_ascii_initialized = false;
static MRT_Char char_ascii[128];

static void char_once_init(void)
{
  if (!char_ascii_initialized) {
    uint32_t i;
    for (i = 0; i < 128; i++)
      mrt_value_construct(mrt_char_class(), MRT_VALUE(&char_ascii[i]), i);
    char_ascii_initialized = true;
  }
}

static void mrt_char_ctor(MRT_Value *value, va_list ap)
{
  MRT_Char *c = MRT_CHAR(value);
  c->value = va_arg(ap, uint32_t);
}

static void mrt_char_dtor(MRT_Value *value)
{
  MRT_Char *c = MRT_CHAR(value);
  c->value = 0;
}

MRT_Value *mrt_char_new(uint32_t ch)
{
  char_once_init();
  if (ch < 128)
    return mrt_value_ref(MRT_VALUE(&char_ascii[ch]));
  return mrt_value_construct(mrt_char_class(), NULL, ch);
}

uint32_t mrt_char_get(MRT_Char *c)
{
  mrt_return_val_if_fail(MRT_IS_CHAR(c), 0);
  return c->value;
}

void mrt_char_set(MRT_Char *c, uint32_t ch)
{
  mrt_return_if_fail(MRT_IS_CHAR(c));
  c->value = ch;
}

MRT_BEGIN_CLASS_DEF(MRT_Char, char, mrt_value_class())
{
  MRT_SET_FIELD(MRT_ValueClass, ctor, mrt_char_ctor);
  MRT_SET_FIELD(MRT_ValueClass, dtor, mrt_char_dtor);
}
MRT_END_CLASS_DEF
