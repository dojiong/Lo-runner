#ifndef __LO_CONVERT_HEADER
#define __LO_CONVERT_HEADER

#include "lorun.h"

int initCalls(PyObject *li, u_char calls[]);
PyObject *genResult(struct Result *rst);
char * const * genRunArgs(PyObject *args_obj);

#endif
