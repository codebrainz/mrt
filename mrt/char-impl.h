#ifndef M_CHAR_IMPL_H
#define M_CHAR_IMPL_H

#include <mrt/char.h>
#include <mrt/number-impl.h>

M_BEGIN_CDECLS

#define M_CHAR_CLASS(c)

typedef struct MCharClass MCharClass;

struct MChar
{
  MNumber base_;
  uint32_t obj;
};

struct MCharClass
{
  MNumberClass base_;
};

M_END_CDECLS

#endif // M_CHAR_IMPL_H
