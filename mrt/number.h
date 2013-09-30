#ifndef MRT_NUMBER_H
#define MRT_NUMBER_H

#include <mrt/value.h>

MRT_BEGIN_CDECLS

#define MRT_NUMBER(v) ((MRT_Number*)(v))
#define MRT_IS_NUMBER(v) mrt_value_is_instance(mrt_number_class(), MRT_VALUE(v))

typedef struct MRT_Number MRT_Number;

const MRT_ValueClass *mrt_number_class(void);

MRT_END_CDECLS

#endif // MRT_NUMBER_H
