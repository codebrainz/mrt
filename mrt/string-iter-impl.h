#ifndef M_STRING_ITER_IMPL_H
#define M_STRING_ITER_IMPL_H

#include <mrt/string.h>
#include <mrt/string-iter.h>
#include <mrt/sequence-iter-impl.h>

M_BEGIN_CDECLS

#define M_STRING_ITER_CLASS(c) ((MStringIterClass*)(c))

typedef struct MStringIterClass MStringIterClass;

struct MStringIter
{
  MSeqIter base_;
  long index;
};

struct MStringIterClass
{
  MSeqIterClass base_;
};

MSeqIter *m_string_iter_new(MString *str, long index);

M_END_CDECLS

#endif // M_STRING_ITER_IMPL_H
