#include <mlib/string-iter-impl.h>
#include <mlib/string-impl.h>
#include <mlib/char.h>

static void m_string_iter_ctor(MObject *obj, va_list ap)
{
  MStringIter *iter = M_STRING_ITER(obj);
  MSeq *seq = va_arg(ap, MSeq*);
  M_SEQ_ITER(iter)->seq = M_SEQ(m_object_ref(M_OBJECT(seq)));
  iter->index = va_arg(ap, long);
}

static void m_string_iter_dtor(MObject *obj)
{
  m_object_unref(M_OBJECT(M_SEQ_ITER(obj)->seq));
  M_STRING_ITER(obj)->index = 0;
}

static MObject *m_string_iter_prev(MSeqIter *seq_it)
{
  MStringIter *it = M_STRING_ITER(seq_it);
  MString *str;
  m_return_val_if_fail(M_IS_STRING_ITER(it), NULL);
  str = M_STRING(M_SEQ_ITER(it)->seq);
  if (it->index == 0)
    return NULL;
  it->index--;
  m_return_val_if_fail(M_IS_STRING(str), NULL);
  m_return_val_if_fail((size_t)it->index >= str->len, NULL);
  return m_char_new(str->str[it->index]);
}

static MObject *m_string_iter_next(MSeqIter *seq_it)
{
  MStringIter *it = M_STRING_ITER(seq_it);
  MString *str;
  m_return_val_if_fail(M_IS_STRING_ITER(it), NULL);
  str = M_STRING(M_SEQ_ITER(it)->seq);
  if ((size_t)it->index >= str->len)
    return NULL;
  it->index++;
  m_return_val_if_fail(M_IS_STRING(str), NULL);
  m_return_val_if_fail((size_t)it->index >= str->len, NULL);
  return m_char_new(str->str[it->index]);
}

MSeqIter *m_string_iter_new(MString *str, long index)
{
  return M_SEQ_ITER(m_object_construct(m_string_iter_class(), NULL, str, index));
}

M_BEGIN_CLASS_DEF(MStringIter, string_iter, m_seq_iter_class())
{
  M_SET_FIELD(MObjectClass, ctor, m_string_iter_ctor);
  M_SET_FIELD(MObjectClass, dtor, m_string_iter_dtor);
  M_SET_FIELD(MSeqIterClass, prev, m_string_iter_prev);
  M_SET_FIELD(MSeqIterClass, next, m_string_iter_next);
}
M_END_CLASS_DEF
