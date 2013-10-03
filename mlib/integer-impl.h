#ifndef M_INTEGER_IMPL_H
#define M_INTEGER_IMPL_H

#include <mlib/integer.h>
#include <mlib/number-impl.h>

M_BEGIN_CDECLS

typedef struct MIntegerClass MIntegerClass;

struct MInteger
{
  MNumber base_;
  int64_t obj;
};

struct MIntegerClass
{
  MNumberClass class_;
};

M_END_CDECLS

#endif // M_INTEGER_IMPL_H
