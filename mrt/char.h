#ifndef MRT_CHAR_H
#define MRT_CHAR_H

#include <mrt/number.h>

MRT_BEGIN_CDECLS

#define MRT_CHAR(v) ((MRT_Char*)(v))
#define MRT_IS_CHAR(v) mrt_value_is_instance(mrt_char_class(), MRT_VALUE(v))

typedef struct MRT_Char MRT_Char;

const MRT_ValueClass *mrt_char_class(void);

MRT_Value *mrt_char_new(uint32_t ch);
uint32_t mrt_char_get(MRT_Char *c);
void mrt_char_set(MRT_Char *c, uint32_t ch);

MRT_END_CDECLS

#endif // MRT_CHAR_H
