#ifndef MRT_NUMBER_IMPL_H
#define MRT_NUMBER_IMPL_H

#include <mrt/number.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct MRT_NumberClass;

struct MRT_Number
{
  MRT_Value base_;
};

struct MRT_NumberClass
{
  MRT_ValueClass base_;
};

#ifdef __cplusplus
} // extern "C"
#endif

#endif // MRT_NUMBER_IMPL_H
