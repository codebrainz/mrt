#ifndef MRT_REAL_H
#define MRT_REAL_H

#include <mrt/number.h>

MRT_BEGIN_CDECLS

#define MRT_REAL(v) ((MRT_Real*)(v))
#define MRT_IS_REAL(v) mrt_value_is_instance(mrt_real_class(), MRT_VALUE(v))

typedef struct MRT_Real MRT_Real;

const MRT_ValueClass *mrt_real_class(void);

MRT_Value *mrt_real_new(double val);
double mrt_real_get(MRT_Real *r);
void mrt_real_set(MRT_Real *r, double val);

MRT_END_CDECLS

#endif // MRT_REAL_H
