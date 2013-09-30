#ifndef MRT_CHAR_IMPL_H
#define MRT_CHAR_IMPL_H

#include <mrt/char.h>
#include <mrt/number-impl.h>

MRT_BEGIN_CDECLS

#define MRT_CHAR_CLASS(c)

typedef struct MRT_CharClass MRT_CharClass;

struct MRT_Char
{
  MRT_Number base_;
  uint32_t obj;
};

struct MRT_CharClass
{
  MRT_NumberClass base_;
};

MRT_END_CDECLS

#endif // MRT_CHAR_IMPL_H
