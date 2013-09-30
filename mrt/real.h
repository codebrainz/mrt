#ifndef M_REAL_H
#define M_REAL_H

#include <mrt/number.h>

M_BEGIN_CDECLS

#define M_REAL(v) ((MReal*)(v))
#define M_IS_REAL(v) m_object_is_instance(m_real_class(), M_OBJECT(v))

typedef struct MReal MReal;

const MObjectClass *m_real_class(void);

MObject *m_real_new(double val);
double m_real_get(MReal *r);
void m_real_set(MReal *r, double val);

M_END_CDECLS

#endif // M_REAL_H
