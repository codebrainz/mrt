#ifndef M_NUMBER_H
#define M_NUMBER_H

#include <mrt/object.h>

M_BEGIN_CDECLS

#define M_NUMBER(v) ((MNumber*)(v))
#define M_IS_NUMBER(v) m_object_is_instance(m_number_class(), M_OBJECT(v))

typedef struct MNumber MNumber;

const MObjectClass *m_number_class(void);

M_END_CDECLS

#endif // M_NUMBER_H
