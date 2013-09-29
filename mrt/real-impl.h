#ifndef MRT_REAL_IMPL_H
#define MRT_REAL_IMPL_H

#ifdef __cplusplus
extern "C" {
#endif

struct MRT_Real
{
  MRT_Number base_;
  long double value;
};

struct MRT_RealClass
{
  MRT_NumberClass base_;
};

#ifdef __cplusplus
} // extern "C"
#endif

#endif // MRT_REAL_IMPL_H
