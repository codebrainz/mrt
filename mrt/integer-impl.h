#ifndef MRT_INTEGER_IMPL_H
#define MRT_INTEGER_IMPL_H

#include <mrt/integer.h>
#include <mrt/number-impl.h>

MRT_BEGIN_CDECLS

typedef struct MRT_IntegerClass MRT_IntegerClass;

struct MRT_Integer
{
  MRT_Number base_;
  int64_t obj;
};

struct MRT_IntegerClass
{
  MRT_NumberClass class_;
};

MRT_END_CDECLS

#endif // MRT_INTEGER_IMPL_H
