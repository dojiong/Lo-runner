/**
 * Loco program runner core
 * Copyright (C) 2011  Lodevil(Du Jiong)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "access.h"
#include <sys/syscall.h>
#include <sys/ptrace.h>
#include <fcntl.h>
#include <string.h>

int fileAccess(PyObject *files, const char *file, long flags) {
    PyObject *perm_obj;
    long perm;

    if ((perm_obj = PyDict_GetItemString(files, file)) == NULL) {
        return 0;
    }
    //printf("%s:%d\n",file,flags);
    #ifdef IS_PY3
    perm = PyLong_AsLong(perm_obj);
    #else
    perm = PyInt_AsLong(perm_obj);
    #endif
    if (perm == flags)
        return 1;

    return 0;
}

static long file_temp[100];
int checkAccess(struct Runobj *runobj, int pid, struct user_regs_struct *regs) {
    if (!runobj->inttable[REG_SYS_CALL(regs)])
        return ACCESS_CALL_ERR;

    switch (REG_SYS_CALL(regs)) {
        case SYS_open: {
            int i, j;

            for (i = 0; i < 100; i++) {
                const char* test;
                long t = ptrace(PTRACE_PEEKDATA, pid,
                    REG_ARG_1(regs) + i * sizeof(long), NULL);
                file_temp[i] = t;
                test = (const char*) &file_temp[i];
                for (j = 0; j < sizeof(long); j++) {
                    if (!test[j]) {
                        goto l_cont;
                    }
                }
            }
            l_cont: file_temp[99] = 0;

            if (fileAccess(runobj->files, (const char*)file_temp,
                    REG_ARG_2(regs))) {
                return ACCESS_OK;
            }

            return ACCESS_FILE_ERR;
        }
    }

    return ACCESS_OK;
}

const char* lastFileAccess(void) {
    file_temp[99] = 0;
    return (const char*) file_temp;
}
