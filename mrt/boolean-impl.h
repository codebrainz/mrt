#ifndef MRT_BOOLEAN_IMPL_H
#define MRT_BOOLEAN_IMPL_H

#include <mrt/boolean.h>
#include <mrt/number-impl.h>

MRT_BEGIN_CDECLS

#define MRT_BOOLEAN_CLASS(c) ((MRT_BooleanClass*)(c))

typedef struct MRT_BooleanClass MRT_BooleanClass;

struct MRT_Boolean
{
  MRT_Number base_;
};

struct MRT_BooleanClass
{
  MRT_NumberClass base_;
};

MRT_END_CDECLS

#endif // MRT_BOOLEAN_IMPL_H
