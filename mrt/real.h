#ifndef MRT_REAL_H
#define MRT_REAL_H

#include <mrt/value.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct MRT_Real MRT_Real;

MRT_ValueClass *mrt_real_get_class(void);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // MRT_REAL_H
