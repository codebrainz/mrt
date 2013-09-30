#ifndef MRT_NONE_IMPL_H
#define MRT_NONE_IMPL_H

#include <mrt/none.h>
#include <mrt/object-impl.h>

MRT_BEGIN_CDECLS

#define MRT_NONE_CLASS(c) ((MRT_NoneClass*)(v))

typedef struct MRT_NoneClass MRT_NoneClass;

struct MRT_None
{
  MRT_Object base_;
};

struct MRT_NoneClass
{
  MRT_ObjectClass base_;
};

MRT_END_CDECLS

#endif // MRT_NONE_IMPL_H
