#ifndef M_STRING_IMPL_H
#define M_STRING_IMPL_H

#include <mlib/string.h>
#include <mlib/sequence-impl.h>

M_BEGIN_CDECLS

#define M_STRING_CLASS(c) ((MStringClass*)(c))

typedef struct MStringClass MStringClass;

struct MString
{
  MSeq base_;
  uint32_t *str;
  uint32_t len;
};

struct MStringClass
{
  MSeqClass base_;
};

M_END_CDECLS

#endif // M_STRIN_IMPL_H
