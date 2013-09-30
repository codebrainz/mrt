#ifndef M_STRING_ITER_H
#define M_STRING_ITER_H

#include <mrt/sequence-iter.h>

M_BEGIN_CDECLS

#define M_STRING_ITER(v) ((MStringIter*)(v))
#define M_IS_STRING_ITER(v) m_object_is_instance(m_string_iter_class(), M_OBJECT(v))

typedef struct MStringIter MStringIter;

const MObjectClass *m_string_iter_class(void);

M_END_CDECLS

#endif // M_STRING_ITER_H
