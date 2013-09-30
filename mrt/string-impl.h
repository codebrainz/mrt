#ifndef MRT_STRING_IMPL_H
#define MRT_STRING_IMPL_H

#include <mrt/string.h>
#include <mrt/sequence-impl.h>

MRT_BEGIN_CDECLS

#define MRT_STRING_CLASS(c) ((MRT_StringClass*)(c))

typedef struct MRT_StringClass MRT_StringClass;

struct MRT_String
{
  MRT_Seq base_;
  uint32_t *str;
  uint32_t len;
};

struct MRT_StringClass
{
  MRT_SeqClass base_;
};

MRT_END_CDECLS

#endif // MRT_STRIN_IMPL_H
