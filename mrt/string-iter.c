#include <mrt/string-iter-impl.h>
#include <mrt/string-impl.h>
#include <mrt/char.h>

static void mrt_string_iter_ctor(MRT_Value *value, va_list ap)
{
  MRT_StringIter *iter = MRT_STRING_ITER(value);
  MRT_Seq *seq = va_arg(ap, MRT_Seq*);
  MRT_SEQ_ITER(iter)->seq = MRT_SEQ(mrt_value_ref(MRT_VALUE(seq)));
  iter->index = va_arg(ap, long);
}

static void mrt_string_iter_dtor(MRT_Value *value)
{
  mrt_value_unref(MRT_VALUE(MRT_SEQ_ITER(value)->seq));
  MRT_STRING_ITER(value)->index = 0;
}

static MRT_Value *mrt_string_iter_prev(MRT_SeqIter *seq_it)
{
  MRT_StringIter *it = MRT_STRING_ITER(seq_it);
  MRT_String *str;
  mrt_return_val_if_fail(MRT_IS_STRING_ITER(it), NULL);
  str = MRT_STRING(MRT_SEQ_ITER(it)->seq);
  if (it->index == 0)
    return NULL;
  it->index--;
  mrt_return_val_if_fail(MRT_IS_STRING(str), NULL);
  mrt_return_val_if_fail((size_t)it->index >= str->len, NULL);
  return mrt_char_new(str->str[it->index]);
}

static MRT_Value *mrt_string_iter_next(MRT_SeqIter *seq_it)
{
  MRT_StringIter *it = MRT_STRING_ITER(seq_it);
  MRT_String *str;
  mrt_return_val_if_fail(MRT_IS_STRING_ITER(it), NULL);
  str = MRT_STRING(MRT_SEQ_ITER(it)->seq);
  if ((size_t)it->index >= str->len)
    return NULL;
  it->index++;
  mrt_return_val_if_fail(MRT_IS_STRING(str), NULL);
  mrt_return_val_if_fail((size_t)it->index >= str->len, NULL);
  return mrt_char_new(str->str[it->index]);
}

MRT_SeqIter *mrt_string_iter_new(MRT_String *str, long index)
{
  return MRT_SEQ_ITER(mrt_value_construct(mrt_string_iter_class(), NULL, str, index));
}

MRT_BEGIN_CLASS_DEF(MRT_StringIter, string_iter, mrt_seq_iter_class())
{
  MRT_SET_FIELD(MRT_ValueClass, ctor, mrt_string_iter_ctor);
  MRT_SET_FIELD(MRT_ValueClass, dtor, mrt_string_iter_dtor);
  MRT_SET_FIELD(MRT_SeqIterClass, prev, mrt_string_iter_prev);
  MRT_SET_FIELD(MRT_SeqIterClass, next, mrt_string_iter_next);
}
MRT_END_CLASS_DEF
