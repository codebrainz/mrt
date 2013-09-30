#ifndef MRT_NUMBER_IMPL_H
#define MRT_NUMBER_IMPL_H

#include <mrt/number.h>
#include <mrt/value-impl.h>

MRT_BEGIN_CDECLS

#define MRT_NUMBER_CLASS(c) ((MRT_NumberClass*)(c))

typedef struct MRT_NumberClass MRT_NumberClass;

struct MRT_Number
{
  MRT_Value base_;
};

struct MRT_NumberClass
{
  MRT_ValueClass base_;
};

MRT_END_CDECLS

#endif // MRT_NUMBER_IMPL_H
