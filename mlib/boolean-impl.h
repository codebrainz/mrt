#ifndef M_BOOLEAN_IMPL_H
#define M_BOOLEAN_IMPL_H

#include <mlib/boolean.h>
#include <mlib/number-impl.h>

M_BEGIN_CDECLS

#define M_BOOLEAN_CLASS(c) ((MBooleanClass*)(c))

typedef struct MBooleanClass MBooleanClass;

struct MBoolean
{
  MNumber base_;
};

struct MBooleanClass
{
  MNumberClass base_;
};

M_END_CDECLS

#endif // M_BOOLEAN_IMPL_H
