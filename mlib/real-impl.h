#ifndef M_REAL_IMPL_H
#define M_REAL_IMPL_H

#include <mlib/real.h>
#include <mlib/number-impl.h>

M_BEGIN_CDECLS

#define M_REAL_CLASS(c) ((MRealClass*)(c))

typedef struct MRealClass MRealClass;

struct MReal
{
  MNumber base_;
  double obj;
};

struct MRealClass
{
  MNumberClass base_;
};

M_END_CDECLS

#endif // M_REAL_IMPL_H
