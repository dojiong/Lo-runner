#ifndef __LO_ACCESS_HEADER
#define __LO_ACCESS_HEADER

#include "lorun.h"
#include <sys/user.h>

#define ACCESS_CALL_ERR 1
#define ACCESS_FILE_ERR 2
#define ACCESS_OK 0

int checkAccess(struct Runobj *runobj, int pid, struct user_regs_struct *regs);
const char* lastFileAccess(void);

#endif
