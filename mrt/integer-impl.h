#ifndef MRT_INTEGER_IMPL_H
#define MRT_INTEGER_IMPL_H

#include <stdint.h>
#include <mrt/number-impl.h>

#ifdef __cplusplus
extern "C" {
#endif

struct MRT_Integer
{
  MRT_Number base_;
  uint64_t value;
};

struct MRT_IntegerClass
{
  MRT_NumberClass class_;
};

#ifdef __cplusplus
} // extern "C"
#endif

#endif // MRT_INTEGER_IMPL_H
