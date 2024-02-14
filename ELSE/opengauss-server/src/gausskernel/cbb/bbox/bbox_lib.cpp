/*
 * Copyright (c) 2020 Huawei Technologies Co.,Ltd.
 *
 * openGauss is licensed under Mulan PSL v2.
 * You can use this software according to the terms and conditions of the Mulan PSL v2.
 * You may obtain a copy of Mulan PSL v2 at:
 *
 *          http://license.coscl.org.cn/MulanPSL2
 *
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 * See the Mulan PSL v2 for more details.
 * -------------------------------------------------------------------------
 *
 * bbox_lib.cpp
 *
 * IDENTIFICATION
 *    src/gausskernel/cbb/bbox/bbox_lib.cpp
 *
 * -------------------------------------------------------------------------
 */
#include "bbox_syscall_support.h"
#include "bbox_lib.h"
#include "bbox_print.h"
#include "../../src/include/securec.h"
#include "../../src/include/securec_check.h"

#define PAGE_SIZE 4096
#define BBOX_MAX_PIDS 32
#define BBOX_TMP_LEN_32 32

#define container_of(ptr, type, member)                   \
    ({                                                    \
        const typeof(((type*)0)->member)* __mptr = (ptr); \
        (type*)((char*)__mptr - offsetof(type, member));  \
    })

#define typeof decltype

struct PIPE_ID {
    s32 iFd;
    pid_t pid;
};

struct PIPE_IDS {
    struct PIPE_ID stPid;
    s32 isUsed;
};

static struct PIPE_IDS astPipeIds[BBOX_MAX_PIDS];

/*
function name: bbox_strncmp
description: To compare two substrings, the pointers pszSrc and pszTarget store their host strings'addresses.
arguments: Two pointers of type const char*, pointing to two strings needed to be compared.
				   An integer indicates the number of characters at the former of two strings that  
                   will be compared.
return value: Type s32, an interger.
					 If it's zero, then the former substrings of string pszSrc and pszTarget are same,
                     else it indicates the difference between the first two characters that these two 
                     strings can't match.
note：The two pointers shouldn't be null. The last argument shouldn't less than zero.
date: 2022/8/2
contact tel: 18720816902
*/
s32 bbox_strncmp(const char* pszSrc, const char* pszTarget, s32 count)
{
    signed char cRes = 0;

    while (count) {
        if ((cRes = *pszSrc - *pszTarget++) != 0 || !*pszSrc++) {
            break;
        }
        count--;
    }

    return cRes;
}

/*
function name: bbox_strcmp
description: compare two strings, the pointer pszSrc and pszTarget store their addresses.
arguments: Two pointers of type const char*, pointing to two strings needed to be compared.
				   An integer indicates the number of characters at the former of two strings that  
                   will be compared.
return value: Type s32, an interger.
					 If it's zero, then the former substrings of string pszSrc and pszTarget are same,
                     else if it's 1, then it indicates between first two characters that these two 
                     strings can't match, the character of first string that pszSrc points is greater,
                     else if it's -1, the character of second string that pszTarget points is greater.
note：The two pointers shouldn't be null. The last argument shouldn't less than zero.
date: 2022/8/2
contact tel:same
*/
s32 bbox_strcmp(const char* pszSrc, const char* pszTarget)
{
    unsigned char c1, c2;

    while (1) {
        c1 = *pszSrc++;
        c2 = *pszTarget++;

        if (c1 != c2) {
            return c1 < c2 ? -1 : 1;
        }

        if (c1 == 0) {
            break;
        }
    }
    return 0;
}

/*
function name: bbox_strlen
description: Calculate the length of string.
arguments: An pointer that indicates the address of a string.
return value: Type s32, an integer indicating the length of string.
note: the length of string=(address of the last character not '\0'-address of the first character)/sizeof(char), and sizeof(char) 
		 equals to 1, so the length of string=(address of the last character not '\0'-address of the first character).
date: 2022/8/2
contact tel:same
*/
s32 bbox_strlen(const char* pszString)
{
    const char* pszTemp = NULL;

    for (pszTemp = pszString; *pszTemp != '\0'; ++pszTemp) {
        /* nothing */;
        continue;
    }

    return pszTemp - pszString;
}

/*
function name: bbox_strnlen
description: Calculate the length of string, but having some restrictive conditions.
arguments: An pointer that indicates the address of a string.
				   And an integer that indicates the maxlenth.
return value: Type s32, an integer indicating the length of string.
note: If the length of string exceed the argument count, then return the length of string,
		 else return the argument count.
date: 2022/8/2
contact tel:same
*/
s32 bbox_strnlen(const char* pszString, s32 count)
{
    const char* pszTemp = NULL;

    for (pszTemp = pszString; count-- && *pszTemp != '\0'; ++pszTemp) {
        /* nothing */;
    }

    return pszTemp - pszString;
}

/*
function name: bbox_atoi
description: Convert a string that includes continuous digital characters to an integer,
					if the first character of the string is '-', then we will return a negative result.
arguments: An pointer that indicates the address of a string.
return value: Type s32, an integer indicating the result of string converted.
note: I think the function isn't perfect, though it's not a core function. For example, what about
		 the condition that the first character of the string is '+'?
date: 2022/8/2
contact tel:same
*/
s32 bbox_atoi(const char* pszString)
{
    s32 n = 0;
    s32 iNeg = 0;

    if (*pszString == '-') {
        iNeg = 1;
    }

    if (iNeg) {
        pszString++;
    }

    while (*pszString >= '0' && *pszString <= '9') {
        n = 10 * n + (*pszString++ - '0');
    }

    return iNeg ? -n : n;
}
/*
function name: bbox_memcmp
description: Compare former count bytes in ASCII of data stored in two areas that pointers cs and ct direct.  
arguments: Two pointers to areas of memory, and an integer indicating the max counts compared.
return value: Type s32, an integer.
					 If the value returned is 0, then the data stored in two areas destined are same,
                     else if is 1, then between two first data in ASCII of byte different, cs's is greater,
                     else if is -1, then ct's is greater.
note: The two pointers should not be null, it's dangerous.
date: 2022/8/2
contact tel: same
*/
s32 bbox_memcmp(const void* cs, const void* ct, s32 count)
{
    const unsigned char *su1 = NULL;
    const unsigned char *su2 = NULL;

    for (su1 = (const unsigned char*)cs, su2 = (const unsigned char*)ct; count > 0; ++su1, ++su2, count--) {
        if (*su1 != *su2) {
            return *su1 < *su2 ? -1 : +1;
        }
    }

    return 0;
}

/*
function name: bbox_strstr
description: Judge if the string s2 directs is substring of string s1 directs.
arguments: Two pointers of type const char*, pointing to two strings.
return value: Type char*, a pointer. Actually it's a address, if s2 directs a 
					 null string, then return the address of the first character of s1,
                     if the string s2 directs isn't substring of string s1 directs, return 
                     null, if the string s2 directs is substring of string s1 directs, then return
                     the address of first character matched.
note: The two pointers should not be null, it's dangerous.
date: 2022/8/2
contact tel: same
*/
char* bbox_strstr(const char* s1, const char* s2)
{
    int l1, l2;

    l2 = bbox_strlen(s2);
    if (!l2) {
        return (char*)s1;
    }

    l1 = bbox_strlen(s1);
    while (l1 >= l2) {
        l1--;
        if (!bbox_memcmp(s1, s2, l2)) {
            return (char*)s1;
        }
        s1++;
    }
    return NULL;
}

/*
function name: bbox_mkdir
description: We distinguish parent directory and child directory through character '/',
					normally through a for loop, we can make sure all directories above the directory
                    we want to creat exist, finally we will creat the flag directory after its parent.
arguments: A pointers of type const char*, pointing to one strings, which indicates the filename and its full path.
return value: An integer of type s32, if it's RET_ERR, then we fail to make a directory, else if it's RET_OK then we succeed.
note: Take care the last non-null character of the string needed to be '/', and once if flag directory's
		 ancestors aren't exist, the function return RET_ERR.
date: 2022/8/2
contact tel: same
*/
s32 bbox_mkdir(const char* pszDir)
{
    char szDirName[BBOX_TMP_LEN_32 * 16];
    char* p = NULL;
    s32 len;

    if (bbox_snprintf(szDirName, sizeof(szDirName), "%s", pszDir) <= 0) {
        return RET_ERR;
    }

    len = bbox_strnlen(szDirName, sizeof(szDirName));
    if (szDirName[len - 1] == '/') {
        if (len == 1) {
            return RET_OK;
        }

        szDirName[len - 1] = 0;
    }

    for (p = szDirName + 1; *p; p++) {
        if (*p != '/') {
            continue;
        }

        *p = 0;
        if (sys_mkdir(szDirName, S_IRWXU) < 0) {
            if (errno != EEXIST) {
                return RET_ERR;
            }
        }

        *p = '/';
    }

    if (sys_mkdir(szDirName, S_IRWXU) < 0) {
        if (errno != EEXIST) {
            return RET_ERR;
        }
    }

    return RET_OK;
}

/*
function name: bbox_GetFreePid
description: Through a for loop, we search a free pipe in a structure array, to an array element if its 
					member variable isUsed's value is 0, we return the array element's another member variable
                    stPid's address.
arguments: void
return value: An pointer of type struct PIPE_ID* or NULL.
note: none
date: 2022/8/2
contact tel: same
*/
struct PIPE_ID* bbox_GetFreePid(void)
{
    u32 i;

    for (i = 0; i < BBOX_MAX_PIDS; i++) {
        if (astPipeIds[i].isUsed == 0) {
            astPipeIds[i].isUsed = 1;
            return &(astPipeIds[i].stPid);
        }
    }

    return NULL;
}

/*
function name: bbox_PutPid
description: Release the occupied pipe.
arguments: A pointer of type struct PIPE_ID*.
return value: void
note: If the argument pointer is null, then there is no need to free the storage, the function ends.
date: 2022/8/2
contact tel: same
*/
void bbox_PutPid(struct PIPE_ID* pstPid)
{
    struct PIPE_IDS* pstPids = NULL;
    if (pstPid == NULL) {
        return;
    }

    pstPids = container_of(pstPid, struct PIPE_IDS, stPid);

    errno_t rc = memset_s(pstPids, sizeof(struct PIPE_IDS), 0, sizeof(struct PIPE_IDS));
    securec_check_c(rc, "\0", "\0");
}

/*
function name: bbox_FindPid
description: In all occupied pipes, the function search the flag pipe through compare all structure
					array elements's member variable stPid's member variable iFd with the function 
                    argument iFd, if they are equal, then return the addres of this array elements.
arguments: An integer that indicates a file's file handle.
return value: A pointer of type struct PIPE_ID* or NULL.
note: none
date: 2022/8/2
contact tel: same
*/
struct PIPE_ID* bbox_FindPid(int iFd)
{
    u32 i;

    for (i = 0; i < BBOX_MAX_PIDS; i++) {
        if (astPipeIds[i].isUsed == 0) {
            continue;
        }

        if (astPipeIds[i].stPid.iFd == iFd) {
            return &(astPipeIds[i].stPid);
        }
    }

    return NULL;
}

/*
function name: sys_popen
description: The function gets a free pipe by function bbox_GetFreePid, if normally, then creat a pipe
					through sys_pipe, andcreat a child process through function sys_fork, execute a  shell command
                    to run a process.
arguments: One pointer to a string that represents command line, another pointer of type const char* 
				   indicates that the file file handle directs is used in the this mode.
return value: A pointer of type struct PIPE_ID* or NULL.
note: The string that indicates pszMode should only be "r" or "w",
date: 2022/8/2
contact tel: same
*/
s32 sys_popen(char* pszCmd, const char* pszMode)
{
    struct PIPE_ID* volatile stCurPid = NULL;
    s32 iFd;
    s32 saIpedes[2] = {0};
    pid_t pid;

    if (NULL == pszCmd || NULL == pszMode) {
        errno = EINVAL;
        return -1;
    }

    /* determine whether the read-write mode is correct */
    if ((*pszMode != 'r' && *pszMode != 'w') || pszMode[1] != '\0') {
        errno = EINVAL;
        return -1;
    }

    /* get free pipe id */
    stCurPid = bbox_GetFreePid();
    if (NULL == stCurPid) {
        return -1;
    }

    /* create pipe */
    if (sys_pipe(saIpedes) < 0) {
        return -1;
    }

    /* create child prosess */
    pid = sys_fork();
    if (pid < 0) {
        /* close fd if error */
        sys_close(saIpedes[0]);
        sys_close(saIpedes[1]);
        bbox_PutPid(stCurPid);
        return -1;
    } else if (pid == 0) { /* Child. */
        /* child prosess */
        s32 i = 0;
        char* pArgv[4];
        pArgv[0] = "sh";
        pArgv[1] = "-c";
        pArgv[2] = pszCmd;
        pArgv[3] = 0;

        /* Restore signal function */
        sys_signal(SIGQUIT, SIG_DFL);
        sys_signal(SIGTSTP, SIG_IGN);
        sys_signal(SIGTERM, SIG_DFL);
        sys_signal(SIGINT, SIG_DFL);

        for (i = STDERR_FILENO + 1; i < 1024; i++) {
            /* do not close pipe. */
            if (i == saIpedes[0] || i == saIpedes[1]) {
                continue;
            }

            sys_close((int)i);
        }

        if (*pszMode == 'r') {
            int tpipedes1 = saIpedes[1];

            sys_close(saIpedes[0]);
            /*
             * We must NOT modify saIpedes, due to the
             * semantics of vfork.
             */
            if (tpipedes1 != STDOUT_FILENO) {
                sys_dup2(tpipedes1, STDOUT_FILENO);
                sys_close(tpipedes1);
                tpipedes1 = STDOUT_FILENO;
            }
        } else {
            sys_close(saIpedes[1]);
            if (saIpedes[0] != STDIN_FILENO) {
                sys_dup2(saIpedes[0], STDIN_FILENO);
                sys_close(saIpedes[0]);
            }
        }

        sys_execve("/bin/sh", pArgv, environ);
        bbox_print(PRINT_ERR, "exec '%s' failed, errno = %d, pid = %d\n", pszCmd, errno, pid);
        sys_exit(127);
        /* NOTREACHED */
    }

    /* Parent; assume fdopen can't fail. */
    if (*pszMode == 'r') {
        iFd = saIpedes[0];
        sys_close(saIpedes[1]);
    } else {
        iFd = saIpedes[1];
        sys_close(saIpedes[0]);
    }

    /* Link into list of file descriptors. */
    stCurPid->iFd = iFd;
    stCurPid->pid = pid;
    return iFd;
}

/*
function name: sys_pclose
description: The function has an contrary action to function sys_popen, it close the pipe
					that sys_popen open.
arguments: iFd, an integer that indicates a file handle.
return value: An integer that indicates the final status of the process working before. 
note: none
date: 2022/8/2
contact tel: same
*/
int sys_pclose(s32 iFd)
{
    struct PIPE_ID* pstCur = NULL;
    s32 iStat = -1;
    pid_t pid;

    pstCur = bbox_FindPid(iFd);
    if (pstCur == NULL) {
        return -1;
    }

    sys_close(iFd);

    do {
        pid = sys_waitpid(pstCur->pid, &iStat, 0);
    } while (pid == -1 && errno == EINTR);

    bbox_PutPid(pstCur);
    return (pid == -1 ? -1 : iStat);
}

/*
function name: bbox_listdir
description: The function list all files below this path in directory.
arguments: The first argument is a pointer to a string representing a file path, all files below 
				   this path will be listed in directory. The second argument is a pointer to a callback 
                   function. The last is a pointer of type void*, it indicates a command line. 
return value: An integer that indicates the result of function, if normal, it's RET_OK, else 
					 it's RET_ERR.
note: The path that the first argument represents should be absolute path, take care.
date: 2022/8/2
contact tel: same
*/
s32 bbox_listdir(const char* pstPath, BBOX_LIST_DIR_CALLBACK callback, void* pArgs)
{
    struct linux_dirent* pstEntry = NULL;
    s32 iDir;
    char szBuff[PAGE_SIZE];
    ssize_t nBytes;
    s32 iRet = RET_OK;

    if (callback == NULL || pstPath == NULL) {
        return RET_ERR;
    }

    iDir = sys_open(pstPath, O_RDONLY | O_DIRECTORY, 0);
    if (iDir < 0) {
        bbox_print(PRINT_ERR, "open directory failed, errno = %d\n", errno);
        return RET_ERR;
    }

    /* get the file in directory */
    do {
        nBytes = sys_getdents(iDir, (struct linux_dirent*)szBuff, sizeof(szBuff));
        if (nBytes < 0) {
            bbox_print(PRINT_ERR, "get directory ents failed, errno = %d\n", errno);
            sys_close(iDir);
            return RET_ERR;
        } else if (nBytes == 0) {
            /* break when there is no file not read */
            break;
        }

        for (pstEntry = (struct linux_dirent*)szBuff;
             (pstEntry < (struct linux_dirent*)&szBuff[nBytes]) && iRet == RET_OK;
             pstEntry = (struct linux_dirent*)((char*)pstEntry + pstEntry->d_reclen)) {
            if (pstEntry->d_ino == 0) {
                continue;
            }

            iRet = callback(pstPath, pstEntry->d_name, pArgs);
        }
    } while (nBytes > 0 && iRet == RET_OK);

    sys_close(iDir);

    return iRet;
}
