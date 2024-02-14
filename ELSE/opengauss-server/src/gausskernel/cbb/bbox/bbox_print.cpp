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
 * bbox_print.cpp
 *
 * IDENTIFICATION
 *    src/gausskernel/cbb/bbox/bbox_print.cpp
 *
 * -------------------------------------------------------------------------
 */
#include <stdarg.h>
#include "bbox_syscall_support.h"
#include "bbox_print.h"
#include "../../src/include/securec.h"
#include "../../src/include/securec_check.h"

char g_acBBoxLog[BBOX_LOG_SIZE];
char* g_pcCurWriteLogPos = g_acBBoxLog;
int g_iLastLogLen = BBOX_LOG_SIZE;

static EN_PRINT_TYPE g_enLogLevel = PRINT_LOG;
static EN_PRINT_TYPE g_enScreenLogLeven = PRINT_TIP;

static int g_iLogScreen = 0;
static int g_isLogInitialed = 0;

typedef int (*BBOX_vnprintCallBack)(char c, void* pPtr, s32* piCount, s32 iSize);

/*
 * init log
 */
void bbox_initlog(int iLogScreen)
{
    if (g_isLogInitialed) {
        return;
    }

    errno_t rc = memset_s(g_acBBoxLog, sizeof(g_acBBoxLog), 0, sizeof(g_acBBoxLog));
    securec_check_c(rc, "\0", "\0");
    g_pcCurWriteLogPos = g_acBBoxLog;
    g_iLastLogLen = BBOX_LOG_SIZE;
    g_iLogScreen = (iLogScreen) ? 1 : 0;

    g_isLogInitialed = 1;
}

/*
function name: bbox_itoc
description: Convert an integer to a character.
arguments: An integer needed to be converted.
return value: An character that corresponds to the function's integer argument.
note: The integer argument can be converted in radices more than decimalism.
date: 2022/8/2
contact tel: 18720816902
*/
inline char bbox_itoc(u8 sNum)
{
    return (char)((sNum < 10) ? (sNum + 48) : (sNum + 87));
}

/*
function name: bbox_put_dox
description: Conversion of number systems.
arguments: The first argument pCallback is a pointer to a callback function, we
				   use it to reverse the final result. The second argument is a pointer of
                   type void* used as a argument of function pCallback. The third argument
                   piCount is a pointer of type int, an offset pointer, also be used as a argument
                   of pCallback. The fourth argument is an integer of 32 bits, it indicates the buffer
                   size pCallback uses.The fifth argument uNum is a decimal integer that will
                   be converted to an integer in another radix. The sixth argument is used as
                   base to conversion of number systems. The last argument indicates the integer
                   after converted is a negative integer or not.
return value: An integer, indicating if the function pCallback work successfully.
note: The argument uNum should be a positive integer, after conversion of number systems
		 the sign will be appended to string's tail.
date: 2022/8/2
contact tel: 18720816902
*/
s32 bbox_put_dox(BBOX_vnprintCallBack pCallback, void* ptr, s32* piCount, u32 iSize, u64 uNum, s32 sSys, s32 isNeg)
{
    s64 i = 0;
    s64 j = 0;
    char Tmp[32];
    s32 iRet = 0;

    if (0 == uNum) {
        return pCallback('0', ptr, piCount, iSize);
    }

    /* convert */
    while (uNum) {
        j = uNum % sSys;
        Tmp[i] = bbox_itoc((u8)j);
        uNum /= sSys;
        i++;
    }

    /* is negative */
    if (isNeg) {
        Tmp[i] = '-';
        i++;
    }

    /* reverse copy result */
    i--;
    while (i >= 0 && iRet == 0) {
        iRet = pCallback(Tmp[i], ptr, piCount, iSize);
        i--;
    }

    return iRet;
}

/*
function name: bbox_vsnprintf
description: The function is used to print string in corresponding array.
arguments: The first argument is a pointer to a callback function, the next is a
				   pointer to private data to call this function, also to buffer. 
                   The third is used to destine buffer size. The forth is used to destine 
                   the print format of deferent string, the last is a pointer to variable parameter list.
return value: An integer, if iSize is big enough, then the return value is the length of
					 string been written in destined memory successfully, not include '\0', 
                     if function makes errors, the return value is a negative integer.
note: none
date: 2022/8/3
contact tel: 18720816902
*/
s32 bbox_vsnprintf(BBOX_vnprintCallBack pCallback, void* ptr, s32 iSize, const char* pFmt, va_list ap)
{

    s32 iCount = 0;
    char c;
    s32 iCheckFmt = 0;
    s32 iQualifier = 0;
    s32 iSizeTConv = 0;
    s32 iRet = 0;

    if (iSize <= 0) {
        return 0;
    }

    /* traversal handles formatting strings */
    while (0 == iRet) {
        c = *(pFmt++);
        if (!c) {
            break;
        }
        /* judge format type if % */
        if (c == '%' && 0 == iCheckFmt) {
            iQualifier = 0;
            iSizeTConv = 0;
            iCheckFmt = 1;
            continue;
        } else if (0 == iCheckFmt) {
            /* copy */
            iRet = pCallback(c, ptr, &iCount, iSize);
            continue;
        }

        /* check whether the parameter has l */
        if (c == 'l' && iQualifier == 0) {
            iQualifier = 1;
            continue;
        } else if (c == 'z') {
            iSizeTConv = 1;
            continue;
        }

        switch (c) {
            case 'c': {
                char ch = (char)va_arg(ap, int);
                iRet = pCallback(ch, ptr, &iCount, iSize);
            } break;
            case 'd': {
                signed long long n = 0;
                if (iSizeTConv) {
#if (defined(__x86_64__)) || (defined(__aarch64__))
                    n = va_arg(ap, signed long int);
#else
                    n = va_arg(ap, signed int);
#endif
                } else {
                    n = (iQualifier) ? va_arg(ap, signed long int) : va_arg(ap, signed int);
                }

                s32 isNeg = (n < 0) ? 1 : 0;
                n = (isNeg) ? (-1 * n) : (n);
                iRet = bbox_put_dox(pCallback, ptr, &iCount, iSize, (u64)n, 10, isNeg);
            } break;
            case 'l': {
                signed long long n = (iQualifier) ? va_arg(ap, long long) : va_arg(ap, long);
                s32 isNeg = (n < 0) ? 1 : 0;
                n = (isNeg) ? (-1 * n) : (n);
                iRet = bbox_put_dox(pCallback, ptr, &iCount, iSize, (u64)n, 10, isNeg);
            } break;
            case 'x': {
                unsigned long long n = (iQualifier) ? va_arg(ap, unsigned long int) : va_arg(ap, unsigned int);
                iRet = bbox_put_dox(pCallback, ptr, &iCount, iSize, (u64)n, 16, 0);
            } break;
            case 'u': {
                unsigned long long n = 0;
                if (iSizeTConv) {
#if (defined(__x86_64__)) || (defined(__aarch64__))
                    n = va_arg(ap, unsigned long long);
#else
                    n = va_arg(ap, unsigned int);
#endif
                } else {
                    n = (iQualifier) ? va_arg(ap, unsigned long long) : va_arg(ap, unsigned int);
                }

                iRet = bbox_put_dox(pCallback, ptr, &iCount, iSize, (u64)n, 10, 0);
            } break;
            case 'p': {
                unsigned long long n = va_arg(ap, unsigned long);
                iRet = bbox_put_dox(pCallback, ptr, &iCount, iSize, (u64)n, 16, 0);
            } break;
            case 's': {
                char* p = va_arg(ap, char*);

                if (p == NULL) {
                    p = "<NULL>";
                }
                while (*p && (!iRet)) {
                    iRet = pCallback(*p, ptr, &iCount, iSize);
                    p++;
                }
            } break;
            default:
                iRet = pCallback(c, ptr, &iCount, iSize);
                break;
        }

        iQualifier = 0;
        iCheckFmt = 0;
    }

    if (iRet != RET_OK || pCallback(0, ptr, &iCount, iSize) != RET_OK) {
        return RET_ERR;
    }

    return iCount;
}

/*
function name: bbox_SnprintCallback
description: The function is used to print string in corresponding array, usually
				    used as the first argument of function bbox_vsnprintf.
arguments: The first argument is a character waited to be written into buffer that 
				   pPtr directs, the second argument directs a buffer area, the third is a
                   pointer to an integera used to record the count to call this callback function,
                   at the same time, it represents the count of characters written into buffer, it's
                   a pointer so that we can conveniently modify data storedin it. The last 
                   argument destines the size of buffer, it represents the limit of length.
return value: An integer, if written successfully, it's RET_OK, else it's RET_ERR.
note: none
date: 2022/8/3
contact tel: 18720816902
*/
s32 bbox_SnprintCallback(char c, void* pPtr, s32* piCount, s32 iSize)
{
    char** pszBuff = (char**)pPtr;

    /* return if the buffer length is exceeded */
    if (*piCount >= iSize - 1) {
        /* set the last bit to 0 and return err, means that exit snprintf_s function. */
        **pszBuff = 0;
        return RET_ERR;
    }

    **pszBuff = c;
    (*pszBuff)++;
    (*piCount)++;

    return RET_OK;
}

/*
 * simple signal-safe function snprintf_s
 * in      : pstBuff - buffer pointer
 *           iSize - buffer size
 *           pFmt - string format
 * return  : string length
 */
s32 bbox_snprintf(char* pszBuff, s32 iSize, const char* pFmt, ...)
{
    va_list ap;
    s32 iRet = 0;

    va_start(ap, pFmt);
    iRet = bbox_vsnprintf(bbox_SnprintCallback, &pszBuff, iSize, pFmt, ap);
    va_end(ap);

    return iRet;
}

/* call back function of printf
 * in      : c - charactor to calculate
 *           pPtr - buffer pointer
 *           piCount - count of character read
 *           iSize - length limit
 * return  : string length
 */
s32 bbox_PrintCallback(char c, void* pPtr, s32* piCount, s32 iSize)
{
    s32* fd = (s32*)pPtr;

    if ('\0' == c) {
        return RET_OK;
    }

    /* write */
    if (fd != 0 && *fd >= 0) {
        sys_write(*fd, &c, 1);
    }

    /* return if the buffer length is exceeded */
    if (g_iLastLogLen <= 1) {
        /* set the last bit to 0 and return err, means that exit snprintf_s function. */
        *g_pcCurWriteLogPos = 0;
        if (g_iLogScreen) {
            return RET_OK;
        }

        return RET_ERR;
    }

    *g_pcCurWriteLogPos = c;
    (g_pcCurWriteLogPos)++;
    (g_iLastLogLen)--;

    return RET_OK;
}

/*
 * simple signal-safe function printf
 */
void bbox_printf(const char* pFmt, ...)
{
    s32 fd = 1;
    va_list ap;

    va_start(ap, pFmt);
    (void)bbox_vsnprintf(bbox_PrintCallback, &fd, 0xFFFF, pFmt, ap);
    va_end(ap);
}

/*
 * simple signal-safe function print
 */
void bbox_print(EN_PRINT_TYPE enType, const char* pFmt, ...)
{
    s32 fd = 1;
    va_list ap;

    if (enType < g_enLogLevel) {
        return;
    }

    if (g_iLogScreen && enType >= g_enScreenLogLeven) {
        fd = 1;
    } else {
        fd = -1;
    }

    va_start(ap, pFmt);
    (void)bbox_vsnprintf(bbox_PrintCallback, &fd, 0xFFFF, pFmt, ap);
    va_end(ap);
}

/*
 * set print level
 */
s32 bbox_set_log_level(EN_PRINT_TYPE enLevel)
{
    if (enLevel < PRINT_DBG || enLevel > PRINT_ERR) {
        return RET_ERR;
    }

    g_enLogLevel = enLevel;

    return RET_OK;
}

/*
 * set screen print level
 */
s32 bbox_set_screen_log_level(EN_PRINT_TYPE enLevel)
{
    if (enLevel < PRINT_DBG || enLevel > PRINT_ERR) {
        return RET_ERR;
    }

    g_enScreenLogLeven = enLevel;

    return RET_OK;
}
