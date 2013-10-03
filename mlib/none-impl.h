#ifndef M_NONE_IMPL_H
#define M_NONE_IMPL_H

#include <mlib/none.h>
#include <mlib/object-impl.h>

M_BEGIN_CDECLS

#define M_NONE_CLASS(c) ((MNoneClass*)(v))

typedef struct MNoneClass MNoneClass;

struct MNone
{
  MObject base_;
};

struct MNoneClass
{
  MObjectClass base_;
};

M_END_CDECLS

#endif // M_NONE_IMPL_H
