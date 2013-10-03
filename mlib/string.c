#include <mlib/string-impl.h>
#include <mlib/strutils.h>
#include <mlib/string-iter-impl.h>
#include <mlib/char.h>

static void m_string_ctor(MObject *obj, va_list ap)
{
  MString *str = M_STRING(obj);
  (void)ap;
  str->len = 0;
  str->str = m_calloc(1, sizeof(uint32_t));
}

static void m_string_dtor(MObject *obj)
{
  MString *str = M_STRING(obj);
  str->len = 0;
  m_free(str->str);
  str->str = NULL;
}

static MObject *m_string_get(MSeq *seq, va_list ap)
{
  MString *str = M_STRING(seq);
  uint32_t index = va_arg(ap, uint32_t);
  if (index >= str->len)
    return NULL;
  return m_char_new(str->str[index]);
}

static bool m_string_set(MSeq *seq, va_list ap)
{
  MString *str = M_STRING(seq);
  uint32_t index = va_arg(ap, uint32_t);
  uint32_t ch = va_arg(ap, uint32_t);

  if (index >= str->len)
    return false;

  str->str[index] = ch;

  return true;
}

static bool m_string_add(MSeq *seq, va_list ap)
{
  MString *str = M_STRING(seq);
  uint32_t index = va_arg(ap, uint32_t);
  uint32_t ch = va_arg(ap, uint32_t);
  uint32_t new_len;
  uint32_t *tmp;

  if (index > str->len)
    return false;

  new_len = str->len + 1;
  tmp = m_realloc(str->str, (new_len + 1) * sizeof(uint32_t));
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

static bool m_string_del(MSeq *seq, va_list ap)
{
  (void)seq; (void) ap;
  return false;
}

static uint32_t m_string_size(MSeq *seq)
{
  MString *str = M_STRING(seq);
  m_return_val_if_fail(M_IS_STRING(str), 0);
  return str->len;
}

static MSeqIter *m_string_first(MSeq *seq)
{
  MString *str = M_STRING(seq);
  m_return_val_if_fail(M_IS_STRING(str), NULL);
  return m_string_iter_new(str, 0);
}

static MSeqIter *m_string_last(MSeq *seq)
{
  MString *str = M_STRING(seq);
  m_return_val_if_fail(M_IS_STRING(str), NULL);
  return m_string_iter_new(str, str->len);
}

MObject *m_string_new(void)
{
  return m_object_construct(m_string_class(), NULL);
}

char *m_string_to_utf8(MString *str)
{
  (void)str;
  return NULL;
}

void m_string_assign_utf8_length(MString *str, const char *s, size_t len)
{
  m_return_if_fail(M_IS_STRING(str));
  m_return_if_fail(s);
  (void)len;
}

void m_string_assign_utf8(MString *str, const char *s)
{
  m_string_assign_utf8_length(str, s, m_strlen(s));
}

M_BEGIN_CLASS_DEF(MString, string, m_seq_class())
{
  M_SET_FIELD(MObjectClass, ctor, m_string_ctor);
  M_SET_FIELD(MObjectClass, dtor, m_string_dtor);
  M_SET_FIELD(MSeqClass, get, m_string_get);
  M_SET_FIELD(MSeqClass, set, m_string_set);
  M_SET_FIELD(MSeqClass, add, m_string_add);
  M_SET_FIELD(MSeqClass, del, m_string_del);
  M_SET_FIELD(MSeqClass, size, m_string_size);
  M_SET_FIELD(MSeqClass, first, m_string_first);
  M_SET_FIELD(MSeqClass, last, m_string_last);
}
M_END_CLASS_DEF
