#ifndef M_PROCESS_IMPL_H
#define M_PROCESS_IMPL_H

#include <mlib/process.h>
#include <mlib/object-impl.h>

M_BEGIN_CDECLS

#define M_PROCESS_CLASS(c) ((MProcessClass*)(c))

typedef struct MProcessClass MProcessClass;

struct MProcess
{
  MObject base_;
  int child_pid;
  int return_code;
};

struct MProcessClass
{
  MObjectClass base_;
};

M_END_CDECLS

#endif // M_PROCESS_IMPL_H
