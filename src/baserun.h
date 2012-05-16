#ifndef __LO_GCC_HEADER
#define __LO_GCC_HEADER
#define _GNU_SOURCE
#include <python2.6/Python.h>
#include <sys/types.h>
#define CALLS_MAX 400
#define MAX_OUTPUT 100000000

enum JUDGE_RESULT {
    AC = 0, //0 Accepted
    PE, //1 Presentation Error
    TLE, //2 Time Limit Exceeded
    MLE, //3 Memory Limit Exceeded
    WA, //4 Wrong Answer
    RE, //5 Runtime Error
    OLE, //6 Output Limit Exceeded
    CE, //7 Compile Error
    SE, //8 System Error
};

struct Result {
    int judge_result; //JUDGE_RESULT
    long time_used, memory_used;
    int re_signum;
    int re_call;
    const char* re_file;
};

struct Runobj {
    PyObject *files;
    u_char inttable[CALLS_MAX];
    char * const * args;

    int fd_in, fd_out, fd_err;
    int time_limit, memory_limit;
    int runner;
    int trace;
};

#define RAISE(msg) PyErr_SetString(PyExc_Exception,msg);

#define RAISE0(msg) \
{PyErr_SetString(PyExc_Exception,msg); return NULL;}

#define RAISE1(msg) \
{PyErr_SetString(PyExc_Exception,msg); return -1;}

#endif
