#ifndef M_FILE_IMPL_H
#define M_FILE_IMPL_H

#include <mlib/file.h>
#include <mlib/object-impl.h>

M_BEGIN_CDECLS

struct MFile
{
  MObject base_;
  FILE *fp;
  int fd;
};

struct MFileClass
{
  MObjectClass base_;
};

M_END_CDECLS

#endif // M_FILE_IMPL_H
