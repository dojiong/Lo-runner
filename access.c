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

int fileAccess(PyObject *files, const char *file, long flags)
{
    PyObject *perm_obj;
    long perm;
    
    if((perm_obj = PyDict_GetItemString(files, file)) == NULL)
    {
        return 0;
    }
    //printf("%s:%d\n",file,flags);
    perm = PyInt_AsLong(perm_obj);
    if(perm == flags)
        return 1;
    
    return 0;
}

static int file_temp[100];
int checkAccess(struct Runobj *runobj, int pid, struct user_regs_struct *regs)
{//printf("call:%d\n",regs->orig_eax);
	if (!runobj->inttable[regs->orig_eax])
	    return ACCESS_CALL_ERR;
	
	switch (regs->orig_eax)
	{
	    case SYS_open:
	    {
		    int i;
		
		    for (i = 0; i < 100; i++)
		    {
			    int t = ptrace(PTRACE_PEEKDATA, pid, regs->ebx + i * 4, NULL);
			    file_temp[i] = t;
			    if (!(t&0xFF000000) || !(t&0x00FF0000)
			        || !(t&0x0000FF00) || !(t&0x000000FF))
			        break;
		    }
		    file_temp[99] = 0;
                        
		    if(fileAccess(runobj->files, (const char *)file_temp, regs->ecx))
		        return ACCESS_OK;
		    return ACCESS_FILE_ERR;
	    }
	}
	
	return ACCESS_OK;
}

const char* lastFileAccess(void)
{
    file_temp[99] = 0;
    return (const char*)file_temp;
}
