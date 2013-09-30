#ifndef M_NUMBER_IMPL_H
#define M_NUMBER_IMPL_H

#include <mrt/number.h>
#include <mrt/object-impl.h>

M_BEGIN_CDECLS

#define M_NUMBER_CLASS(c) ((MNumberClass*)(c))

typedef struct MNumberClass MNumberClass;

struct MNumber
{
  MObject base_;
};

struct MNumberClass
{
  MObjectClass base_;
};

M_END_CDECLS

#endif // M_NUMBER_IMPL_H
