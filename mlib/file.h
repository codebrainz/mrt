#ifndef M_FILE_H
#define M_FILE_H

#include <mlib/object.h>

M_BEGIN_CDECLS

#define M_FILE(v) ((MFile*)(v))
#define M_IS_FILE(v) m_object_is_instance(m_file_class(), M_OBJECT(v))

typedef struct MFile MFile;

const MObjectClass *m_file_class(void);

MObject *m_file_new(const char *filename);
MObject *m_file_new_from_stream(FILE *fp);
MObject *m_file_new_from_fd(int fd);

M_END_CDECLS

#endif // M_FILE_H
