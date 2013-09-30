#ifndef MRT_STRING_ITER_IMPL_H
#define MRT_STRING_ITER_IMPL_H

#include <mrt/string.h>
#include <mrt/string-iter.h>
#include <mrt/sequence-iter-impl.h>

MRT_BEGIN_CDECLS

#define MRT_STRING_ITER_CLASS(c) ((MRT_StringIterClass*)(c))

typedef struct MRT_StringIterClass MRT_StringIterClass;

struct MRT_StringIter
{
  MRT_SeqIter base_;
  long index;
};

struct MRT_StringIterClass
{
  MRT_SeqIterClass base_;
};

MRT_SeqIter *mrt_string_iter_new(MRT_String *str, long index);

MRT_END_CDECLS

#endif // MRT_STRING_ITER_IMPL_H
