#ifndef MRT_REAL_IMPL_H
#define MRT_REAL_IMPL_H

#include <mrt/real.h>
#include <mrt/number-impl.h>

MRT_BEGIN_CDECLS

#define MRT_REAL_CLASS(c) ((MRT_RealClass*)(c))

typedef struct MRT_RealClass MRT_RealClass;

struct MRT_Real
{
  MRT_Number base_;
  double obj;
};

struct MRT_RealClass
{
  MRT_NumberClass base_;
};

MRT_END_CDECLS

#endif // MRT_REAL_IMPL_H
