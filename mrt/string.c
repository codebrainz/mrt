#include <mrt/string-impl.h>
#include <mrt/strutils.h>
#include <mrt/string-iter-impl.h>
#include <mrt/char.h>

static void mrt_string_ctor(MRT_Value *value, va_list ap)
{
  MRT_String *str = MRT_STRING(value);
  (void)ap;
  str->len = 0;
  str->str = mrt_calloc(1, sizeof(uint32_t));
}

static void mrt_string_dtor(MRT_Value *value)
{
  MRT_String *str = MRT_STRING(value);
  str->len = 0;
  mrt_free(str->str);
  str->str = NULL;
}

static MRT_Value *mrt_string_get(MRT_Seq *seq, va_list ap)
{
  MRT_String *str = MRT_STRING(seq);
  uint32_t index = va_arg(ap, uint32_t);
  if (index >= str->len)
    return NULL;
  return mrt_char_new(str->str[index]);
}

static bool mrt_string_set(MRT_Seq *seq, va_list ap)
{
  MRT_String *str = MRT_STRING(seq);
  uint32_t index = va_arg(ap, uint32_t);
  uint32_t ch = va_arg(ap, uint32_t);

  if (index >= str->len)
    return false;

  str->str[index] = ch;

  return true;
}

static bool mrt_string_add(MRT_Seq *seq, va_list ap)
{
  MRT_String *str = MRT_STRING(seq);
  uint32_t index = va_arg(ap, uint32_t);
  uint32_t ch = va_arg(ap, uint32_t);
  uint32_t new_len;
  uint32_t *tmp;

  if (index > str->len)
    return false;

  new_len = str->len + 1;
  tmp = mrt_realloc(str->str, (new_len + 1) * sizeof(uint32_t));
  if (tmp == NULL)
    return false;

  str->str = tmp;
  str->len = new_len;

  if (index == str->len) // at end
    str->str[index] = ch;
  else {
    memmove(str->str + index + 1, str->str + index,
      (str->len - 1) * sizeof(uint32_t));
    str->str[index] = ch;
    str->str[str->len] = '\0';
  }

  return true;
}

static bool mrt_string_del(MRT_Seq *seq, va_list ap)
{
  (void)seq; (void) ap;
  return false;
}

static uint32_t mrt_string_size(MRT_Seq *seq)
{
  MRT_String *str = MRT_STRING(seq);
  mrt_return_val_if_fail(MRT_IS_STRING(str), 0);
  return str->len;
}

static MRT_SeqIter *mrt_string_first(MRT_Seq *seq)
{
  MRT_String *str = MRT_STRING(seq);
  mrt_return_val_if_fail(MRT_IS_STRING(str), NULL);
  return mrt_string_iter_new(str, 0);
}

static MRT_SeqIter *mrt_string_last(MRT_Seq *seq)
{
  MRT_String *str = MRT_STRING(seq);
  mrt_return_val_if_fail(MRT_IS_STRING(str), NULL);
  return mrt_string_iter_new(str, str->len);
}

MRT_Value *mrt_string_new(void)
{
  return mrt_value_construct(mrt_string_class(), NULL);
}

char *mrt_string_to_utf8(MRT_String *str)
{
  (void)str;
  return NULL;
}

void mrt_string_assign_utf8_length(MRT_String *str, const char *s, size_t len)
{
  mrt_return_if_fail(MRT_IS_STRING(str));
  mrt_return_if_fail(s);
  (void)len;
}

void mrt_string_assign_utf8(MRT_String *str, const char *s)
{
  mrt_string_assign_utf8_length(str, s, mrt_strlen(s));
}

MRT_BEGIN_CLASS_DEF(MRT_String, string, mrt_seq_class())
{
  MRT_SET_FIELD(MRT_ValueClass, ctor, mrt_string_ctor);
  MRT_SET_FIELD(MRT_ValueClass, dtor, mrt_string_dtor);
  MRT_SET_FIELD(MRT_SeqClass, get, mrt_string_get);
  MRT_SET_FIELD(MRT_SeqClass, set, mrt_string_set);
  MRT_SET_FIELD(MRT_SeqClass, add, mrt_string_add);
  MRT_SET_FIELD(MRT_SeqClass, del, mrt_string_del);
  MRT_SET_FIELD(MRT_SeqClass, size, mrt_string_size);
  MRT_SET_FIELD(MRT_SeqClass, first, mrt_string_first);
  MRT_SET_FIELD(MRT_SeqClass, last, mrt_string_last);
}
MRT_END_CLASS_DEF
