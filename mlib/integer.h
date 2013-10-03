#ifndef M_INTEGER_H
#define M_INTEGER_H

#include <mlib/number.h>

M_BEGIN_CDECLS

#define M_INTEGER(v) ((MInteger*)(v))
#define M_IS_INTEGER(v) m_object_is_instance(m_integer_class(), M_OBJECT(v))

typedef struct MInteger MInteger;

const MObjectClass *m_integer_class(void);

MObject *m_integer_new(int64_t val);
int64_t m_integer_get(MInteger *i);
void m_integer_set(MInteger *i, int64_t val);

M_END_CDECLS

#endif // M_INTEGER_H
