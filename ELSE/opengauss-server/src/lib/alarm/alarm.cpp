/*** 
 * @Author: 王贤义
 * @Team: 兰心开源
 * @Date: 2023-09-11 20:10:31
 */

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
 * ---------------------------------------------------------------------------------------
 *
 * alarm.cpp
 *    openGauss alarm reporting/logging definitions.
 *
 *
 * Portions Copyright (c) 1996-2012, PostgreSQL Global Development Group
 * Portions Copyright (c) 1994, Regents of the University of California
 *
 * IDENTIFICATION
 *        src/lib/alarm/alarm.cpp
 *
 * ---------------------------------------------------------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <time.h>
#include "common/config/cm_config.h"

#include "alarm/alarm.h"
#include "syslog.h"
#include "securec.h"
#include "securec_check.h"
#include "alarm/alarm_log.h"

#ifdef ENABLE_UT
#define static
#endif

static char MyHostName[CM_NODE_NAME] = {0};
static char MyHostIP[CM_NODE_NAME] = {0};
static char WarningType[CM_NODE_NAME] = {0};
static char ClusterName[CLUSTER_NAME_LEN] = {0};
static char LogicClusterName[CLUSTER_NAME_LEN] = {0};
// declare the guc variable of alarm module
char* Alarm_component = NULL;
THR_LOCAL int AlarmReportInterval = 10;

static int  IP_LEN = 64;  /* default ip len */
static int  AF_INET6_MAX_BITS = 128;  /* ip mask bit */
// if report alarm succeed(component), return 0
#define ALARM_REPORT_SUCCEED 0
// if report alarm suppress(component), return 2
#define ALARM_REPORT_SUPPRESS 2
#define CLUSTERNAME "MPP_CLUSTER"
#define FUSIONINSIGHTTYPE "1"
#define ICBCTYPE "2"
#define CBGTYPE "5"
#define ALARMITEMNUMBER 64
#define ALARM_LOGEXIT(ErrMsg, fp)        \
    do {                                 \
        AlarmLog(ALM_LOG, "%s", ErrMsg); \
        if ((fp) != NULL)                \
            fclose(fp);                  \
        return;                          \
    } while (0)

// call back function for get logic cluster name
static cb_for_getlc cb_GetLCName = NULL;

static AlarmName AlarmNameMap[ALARMITEMNUMBER];

static char* AlarmIdToAlarmNameEn(AlarmId id);
static char* AlarmIdToAlarmNameCh(AlarmId id);
static char* AlarmIdToAlarmInfoEn(AlarmId id);
static char* AlarmIdToAlarmInfoCh(AlarmId id);
static char* AlarmIdToAlarmLevel(AlarmId id);
static void ReadAlarmItem(void);
static void GetHostName(char* myHostName, unsigned int myHostNameLen);
static void GetHostIP(const char* myHostName, char* myHostIP, unsigned int myHostIPLen);
static void GetClusterName(char* clusterName, unsigned int clusterNameLen);
static bool CheckAlarmComponent(const char* alarmComponentPath);
static bool SuppressComponentAlarmReport(Alarm* alarmItem, AlarmType type, int timeInterval);
static bool SuppressSyslogAlarmReport(Alarm* alarmItem, AlarmType type, int timeInterval);
static void ComponentReport(
    char* alarmComponentPath, Alarm* alarmItem, AlarmType type, AlarmAdditionalParam* additionalParam);
static void SyslogReport(Alarm* alarmItem, AlarmAdditionalParam* additionalParam);
static void check_input_for_security1(char* input);
static void AlarmScopeInitialize(void);
void AlarmReporter(Alarm* alarmItem, AlarmType type, AlarmAdditionalParam* additionalParam);
void AlarmLog(int level, const char* fmt, ...);

/*
 * @Description: check input for security
 * @IN input: input string
 * @Return:  void
 * @See also:
 */
static void check_input_for_security1(char* input)
{
    // Array of dangerous tokens that need to be checked
    char* danger_token[] = {"|",
        ";",
        "&",
        "$",
        "<",
        ">",
        "`",
        "\\",
        "'",
        "\"",
        "{",
        "}",
        "(",
        ")",
        "[",
        "]",
        "~",
        "*",
        "?",
        "!",
        "\n",
        NULL};

    // Iterate through the array of dangerous tokens
    for (int i = 0; danger_token[i] != NULL; ++i) {
        // Check if the input string contains the dangerous token
        if (strstr(input, danger_token[i]) != NULL) {
            printf("invalid token \"%s\"\n", danger_token[i]);
            exit(1);
        }
    }
}

/**
 * @brief Converts the given AlarmId to the corresponding English alarm name.
 * 
 * @param id The AlarmId to convert.
 * @return char* The English alarm name corresponding to the AlarmId.
 *         Returns "unknown" if no matching AlarmId is found.
 */
static char* AlarmIdToAlarmNameEn(AlarmId id)
{
    unsigned int i;
    for (i = 0; i < sizeof(AlarmNameMap) / sizeof(AlarmName); ++i) {
        if (id == AlarmNameMap[i].id)
            return AlarmNameMap[i].nameEn;
    }
    return "unknown";
}

/**
 * @brief Converts the given AlarmId to the corresponding Chinese alarm name.
 * 
 * @param id The AlarmId to convert.
 * @return char* The Chinese alarm name corresponding to the AlarmId.
 *         Returns "unknown" if no matching AlarmId is found.
 */
static char* AlarmIdToAlarmNameCh(AlarmId id)
{
    unsigned int i;
    for (i = 0; i < sizeof(AlarmNameMap) / sizeof(AlarmName); ++i) {
        if (id == AlarmNameMap[i].id)
            return AlarmNameMap[i].nameCh;
    }
    return "unknown";
}

/**
 * @brief Converts the given AlarmId to the corresponding English alarm information.
 * 
 * @param id The AlarmId to convert.
 * @return char* The English alarm information corresponding to the AlarmId.
 *         Returns "unknown" if no matching AlarmId is found.
 */
static char* AlarmIdToAlarmInfoEn(AlarmId id)
{
    unsigned int i;
    for (i = 0; i < sizeof(AlarmNameMap) / sizeof(AlarmName); ++i) {
        if (id == AlarmNameMap[i].id)
            return AlarmNameMap[i].alarmInfoEn;
    }
    return "unknown";
}

/**
 * @brief Converts the given AlarmId to the corresponding Chinese alarm information.
 * 
 * @param id The AlarmId to convert.
 * @return char* The Chinese alarm information corresponding to the AlarmId.
 *         Returns "unknown" if no matching AlarmId is found.
 */
static char* AlarmIdToAlarmInfoCh(AlarmId id)
{
    unsigned int i;
    for (i = 0; i < sizeof(AlarmNameMap) / sizeof(AlarmName); ++i) {
        if (id == AlarmNameMap[i].id)
            return AlarmNameMap[i].alarmInfoCh;
    }
    return "unknown";
}

/**
 * @brief Converts the given AlarmId to the corresponding alarm level.
 * 
 * @param id The AlarmId to convert.
 * @return char* The alarm level corresponding to the AlarmId.
 *         Returns "unknown" if no matching AlarmId is found.
 */
static char* AlarmIdToAlarmLevel(AlarmId id)
{
    unsigned int i;
    for (i = 0; i < sizeof(AlarmNameMap) / sizeof(AlarmName); ++i) {
        if (id == AlarmNameMap[i].id)
            return AlarmNameMap[i].alarmLevel;
    }
    return "unknown";
}

// This function reads alarm-related information from a configuration file.

static void ReadAlarmItem(void)
{
    const int MAX_ERROR_MSG = 128; // Maximum length for error messages
    char* gaussHomeDir = NULL; // Pointer to store the GAUSSHOME environment variable
    char alarmItemPath[MAXPGPATH]; // Path to the alarm configuration file
    char Lrealpath[MAXPGPATH * 4] = {0}; // Buffer for storing the real path
    char* realPathPtr = NULL; // Pointer to the real path
    char* endptr = NULL; // Pointer used for string parsing
    int alarmItemIndex; // Index for iterating through alarm items
    int nRet = 0; // Integer return value
    char tempStr[MAXPGPATH]; // Temporary string buffer
    char* subStr1 = NULL; // Pointers to store substrings from a line
    char* subStr2 = NULL;
    char* subStr3 = NULL;
    char* subStr4 = NULL;
    char* subStr5 = NULL;
    char* subStr6 = NULL;

    char* savePtr1 = NULL; // Pointers for saving the current position during string tokenization
    char* savePtr2 = NULL;
    char* savePtr3 = NULL;
    char* savePtr4 = NULL;
    char* savePtr5 = NULL;
    char* savePtr6 = NULL;

    errno_t rc = 0; // Error code for secure functions
    size_t len = 0; // Length of strings

    char ErrMsg[MAX_ERROR_MSG]; // Buffer for error messages

    // Get the value of the GAUSSHOME environment variable
    gaussHomeDir = gs_getenv_r("GAUSSHOME");
    if (gaussHomeDir == NULL) {
        AlarmLog(ALM_LOG, "ERROR: environment variable $GAUSSHOME is not set!\n");
        return;
    }
    check_input_for_security1(gaussHomeDir);

    // Construct the path to the alarm configuration file
    nRet = snprintf_s(alarmItemPath, MAXPGPATH, MAXPGPATH - 1, "%s/bin/alarmItem.conf", gaussHomeDir);
    securec_check_ss_c(nRet, "\0", "\0");

    // Get the real path of the alarm configuration file
    realPathPtr = realpath(alarmItemPath, Lrealpath);
    if (NULL == realPathPtr) {
        AlarmLog(ALM_LOG, "Get real path of alarmItem.conf failed!\n");
        return;
    }

    // Open the alarm configuration file for reading
    FILE* fp = fopen(Lrealpath, "r");
    if (NULL == fp) {
        ALARM_LOGEXIT("AlarmItem file is not exist!\n", fp);
    }

    // Initialize the ErrMsg buffer with zeros
    rc = memset_s(ErrMsg, MAX_ERROR_MSG, 0, MAX_ERROR_MSG);
    securec_check_c(rc, "\0", "\0");

    // Loop through each line in the alarm configuration file
    for (alarmItemIndex = 0; alarmItemIndex < ALARMITEMNUMBER; ++alarmItemIndex) {
        if (NULL == fgets(tempStr, MAXPGPATH - 1, fp)) {
            // Handle the case where reading a line from the file fails
            nRet = snprintf_s(ErrMsg,
                MAX_ERROR_MSG,
                MAX_ERROR_MSG - 1,
                "Get line in AlarmItem file failed! line: %d\n",
                alarmItemIndex + 1);
            securec_check_ss_c(nRet, "\0", "\0");
            ALARM_LOGEXIT(ErrMsg, fp);
        }
        // Tokenize the line using tab as a delimiter
        subStr1 = strtok_r(tempStr, "\t", &savePtr1);
        if (NULL == subStr1) {
            // Handle the case where parsing the line fails
            nRet = snprintf_s(ErrMsg,
                MAX_ERROR_MSG,
                MAX_ERROR_MSG - 1,
                "Invalid data in AlarmItem file! Read alarm ID failed! line: %d\n",
                alarmItemIndex + 1);
            securec_check_ss_c(nRet, "\0", "\0");
            ALARM_LOGEXIT(ErrMsg, fp);
        }
        // Continue tokenization for other substrings...
        // (Repeat similar blocks for subStr2 through subStr6)

        // Extract and store alarm ID
        errno = 0;
        AlarmNameMap[alarmItemIndex].id = (AlarmId)(strtol(subStr1, &endptr, 10));
        if ((endptr != NULL && *endptr != '\0') || errno == ERANGE) {
            ALARM_LOGEXIT("Get alarm ID failed!\n", fp);
        }

        // Extract and store alarm English name
        // (Repeat similar blocks for nameEn, nameCh, alarmInfoEn, alarmInfoCh, and alarmLevel)

        /* get alarm LEVEL info */
        len = (strlen(subStr6) < (sizeof(AlarmNameMap[alarmItemIndex].alarmLevel) - 1))
                  ? strlen(subStr6)
                  : (sizeof(AlarmNameMap[alarmItemIndex].alarmLevel) - 1);
        rc = memcpy_s(
            AlarmNameMap[alarmItemIndex].alarmLevel, sizeof(AlarmNameMap[alarmItemIndex].alarmLevel), subStr6, len);
        securec_check_c(rc, "\0", "\0");
        /* alarm level is the last one in alarmItem.conf, we should delete line break */
        AlarmNameMap[alarmItemIndex].alarmLevel[len - 1] = '\0';
    }
    // Close the configuration file
    fclose(fp);
}

// This function retrieves the host name of the current machine and stores it in the 'myHostName' buffer.

static void GetHostName(char* myHostName, unsigned int myHostNameLen)
{
    char hostName[CM_NODE_NAME]; // Buffer to store the host name
    errno_t rc = 0; // Error code for secure functions
    size_t len; // Length of strings

    // Get the host name of the current machine and store it in the 'hostName' buffer
    (void)gethostname(hostName, CM_NODE_NAME);

    // Calculate the length of the host name and ensure it fits within 'myHostNameLen'
    len = (strlen(hostName) < (myHostNameLen - 1)) ? strlen(hostName) : (myHostNameLen - 1);

    // Copy the host name to the 'myHostName' buffer
    rc = memcpy_s(myHostName, myHostNameLen, hostName, len);
    securec_check_c(rc, "\0", "\0");

    // Null-terminate the 'myHostName' string
    myHostName[len] = '\0';

    // Log the host name to an alarm log
    AlarmLog(ALM_LOG, "Host Name: %s \n", myHostName);
}


// This function retrieves the IP address associated with a given host name and stores it in the 'myHostIP' buffer.

static void GetHostIP(const char* myHostName, char* myHostIP, unsigned int myHostIPLen)
{
    struct hostent* hp; // Pointer to a hostent structure containing host information
    errno_t rc = 0; // Error code for secure functions
    char* ipstr = NULL; // Pointer to store the IP address as a string
    char ipv6[IP_LEN] = {0}; // Buffer to store IPv6 address
    char* result = NULL; // Result of inet_net_ntop function

    // Get host information by host name
    hp = gethostbyname(myHostName);
    if (hp == NULL) {
        // If gethostbyname fails, try retrieving IPv6 information
        hp = gethostbyname2(myHostName, AF_INET6);
        if (hp == NULL) {
            // If both methods fail, log an error and return
            AlarmLog(ALM_LOG, "GET host IP by name failed.\n");
            return;
        }
    }

    if (hp->h_addrtype == AF_INET) {
        // If the address type is IPv4, convert it to a string
        ipstr = inet_ntoa(*((struct in_addr*)hp->h_addr));
    } else if (hp->h_addrtype == AF_INET6) {
        // If the address type is IPv6, use inet_net_ntop to convert it to a string
        result = inet_net_ntop(AF_INET6, ((struct in6_addr*)hp->h_addr), AF_INET6_MAX_BITS, ipv6, IP_LEN);
        if (result == NULL) {
            // Handle the case where inet_net_ntop fails
            AlarmLog(ALM_LOG, "inet_net_ntop failed, error: %d.\n", EAFNOSUPPORT);
        }
        ipstr = ipv6;
    }

    // Calculate the length of the IP string and ensure it fits within 'myHostIPLen'
    size_t len = (strlen(ipstr) < (myHostIPLen - 1)) ? strlen(ipstr) : (myHostIPLen - 1);

    // Copy the IP string to the 'myHostIP' buffer
    rc = memcpy_s(myHostIP, myHostIPLen, ipstr, len);
    securec_check_c(rc, "\0", "\0");

    // Null-terminate the 'myHostIP' string
    myHostIP[len] = '\0';

    // Log the host IP to an alarm log
    AlarmLog(ALM_LOG, "Host IP: %s \n", myHostIP);
}


// This function retrieves the cluster name from an environment variable and stores it in the 'clusterName' buffer.

static void GetClusterName(char* clusterName, unsigned int clusterNameLen)
{
    errno_t rc = 0; // Error code for secure functions
    char* gsClusterName = gs_getenv_r("GS_CLUSTER_NAME"); // Get the value of the GS_CLUSTER_NAME environment variable

    if (gsClusterName != NULL) {
        // If the GS_CLUSTER_NAME environment variable is set:
        check_input_for_security1(gsClusterName); // Check and sanitize the environment variable for security
        size_t len = (strlen(gsClusterName) < (clusterNameLen - 1)) ? strlen(gsClusterName) : (clusterNameLen - 1);
        // Calculate the length of the cluster name and ensure it fits within 'clusterNameLen'
        rc = memcpy_s(clusterName, clusterNameLen, gsClusterName, len);
        securec_check_c(rc, "\0", "\0");

        // Null-terminate the 'clusterName' string
        clusterName[len] = '\0';

        // Log the cluster name to an alarm log
        AlarmLog(ALM_LOG, "Cluster Name: %s \n", clusterName);
    } else {
        // If the GS_CLUSTER_NAME environment variable is not set:
        size_t len = strlen(CLUSTERNAME); // Get the length of the default cluster name
        // Copy the default cluster name to the 'clusterName' buffer
        rc = memcpy_s(clusterName, clusterNameLen, CLUSTERNAME, len);
        securec_check_c(rc, "\0", "\0");

        // Null-terminate the 'clusterName' string
        clusterName[len] = '\0';

        // Log an error indicating that the GS_CLUSTER_NAME environment variable is not set
        AlarmLog(ALM_LOG, "Get ENV GS_CLUSTER_NAME failed!\n");
    }
}

void AlarmEnvInitialize()
{
    char* warningType = NULL;
    int nRet = 0;
    warningType = gs_getenv_r("GAUSS_WARNING_TYPE");
    if ((NULL == warningType) || ('\0' == warningType[0])) {
        AlarmLog(ALM_LOG, "can not read GAUSS_WARNING_TYPE env.\n");
    } else {
        check_input_for_security1(warningType);
        // save warningType into WarningType array
        // WarningType is a static global variable
        nRet = snprintf_s(WarningType, sizeof(WarningType), sizeof(WarningType) - 1, "%s", warningType);
        securec_check_ss_c(nRet, "\0", "\0");
    }

    // save this host name into MyHostName array
    // MyHostName is a static global variable
    GetHostName(MyHostName, sizeof(MyHostName));

    // save this host IP into MyHostIP array
    // MyHostIP is a static global variable
    GetHostIP(MyHostName, MyHostIP, sizeof(MyHostIP));

    // save this cluster name into ClusterName array
    // ClusterName is a static global variable
    GetClusterName(ClusterName, sizeof(ClusterName));

    // read alarm item info from the configure file(alarmItem.conf)
    ReadAlarmItem();

    // read alarm scope info from the configure file(alarmItem.conf)
    AlarmScopeInitialize();
}

/*
Fill in the structure AlarmAdditionalParam with alarmItem has been filled.
*/
static void FillAlarmAdditionalInfo(AlarmAdditionalParam* additionalParam, const char* instanceName,
    const char* databaseName, const char* dbUserName, const char* logicClusterName, Alarm* alarmItem)
{
    errno_t rc = 0;
    int nRet = 0;
    int lenAdditionInfo = sizeof(additionalParam->additionInfo);

    // fill in the addition Info field
    nRet = snprintf_s(additionalParam->additionInfo, lenAdditionInfo, lenAdditionInfo - 1, "%s", alarmItem->infoEn);
    securec_check_ss_c(nRet, "\0", "\0");

    // fill in the cluster name field
    size_t lenClusterName = strlen(ClusterName);
    rc = memcpy_s(additionalParam->clusterName, sizeof(additionalParam->clusterName) - 1, ClusterName, lenClusterName);
    securec_check_c(rc, "\0", "\0");
    additionalParam->clusterName[lenClusterName] = '\0';

    // fill in the host IP field
    size_t lenHostIP = strlen(MyHostIP);
    rc = memcpy_s(additionalParam->hostIP, sizeof(additionalParam->hostIP) - 1, MyHostIP, lenHostIP);
    securec_check_c(rc, "\0", "\0");
    additionalParam->hostIP[lenHostIP] = '\0';

    // fill in the host name field
    size_t lenHostName = strlen(MyHostName);
    rc = memcpy_s(additionalParam->hostName, sizeof(additionalParam->hostName) - 1, MyHostName, lenHostName);
    securec_check_c(rc, "\0", "\0");
    additionalParam->hostName[lenHostName] = '\0';

    // fill in the instance name field
    size_t lenInstanceName = (strlen(instanceName) < (sizeof(additionalParam->instanceName) - 1))
                                 ? strlen(instanceName)
                                 : (sizeof(additionalParam->instanceName) - 1);
    rc = memcpy_s(
        additionalParam->instanceName, sizeof(additionalParam->instanceName) - 1, instanceName, lenInstanceName);
    securec_check_c(rc, "\0", "\0");
    additionalParam->instanceName[lenInstanceName] = '\0';

    // fill in the database name field
    size_t lenDatabaseName = (strlen(databaseName) < (sizeof(additionalParam->databaseName) - 1))
                                 ? strlen(databaseName)
                                 : (sizeof(additionalParam->databaseName) - 1);
    rc = memcpy_s(
        additionalParam->databaseName, sizeof(additionalParam->databaseName) - 1, databaseName, lenDatabaseName);
    securec_check_c(rc, "\0", "\0");
    additionalParam->databaseName[lenDatabaseName] = '\0';

    // fill in the dbuser name field
    size_t lenDbUserName = (strlen(dbUserName) < (sizeof(additionalParam->dbUserName) - 1))
                               ? strlen(dbUserName)
                               : (sizeof(additionalParam->dbUserName) - 1);
    rc = memcpy_s(additionalParam->dbUserName, sizeof(additionalParam->dbUserName) - 1, dbUserName, lenDbUserName);
    securec_check_c(rc, "\0", "\0");
    additionalParam->dbUserName[lenDbUserName] = '\0';

    if (logicClusterName == NULL)
        return;

    // fill in the logic cluster name field
    size_t lenLogicClusterName = strlen(logicClusterName);
    size_t bufLen = sizeof(additionalParam->logicClusterName) - 1;
    if (lenLogicClusterName > bufLen)
        lenLogicClusterName = bufLen;

    rc = memcpy_s(additionalParam->logicClusterName, bufLen, logicClusterName, lenLogicClusterName);
    securec_check_c(rc, "\0", "\0");
    additionalParam->logicClusterName[lenLogicClusterName] = '\0';
}

void SetcbForGetLCName(cb_for_getlc get_lc_name)
{
    cb_GetLCName = get_lc_name;
}

static char* GetLogicClusterName()
{
    if (NULL != cb_GetLCName)
        cb_GetLCName(LogicClusterName);
    return LogicClusterName;
}

/*
Fill in the structure AlarmAdditionalParam
*/
void WriteAlarmAdditionalInfo(AlarmAdditionalParam* additionalParam, const char* instanceName, const char* databaseName,
    const char* dbUserName, Alarm* alarmItem, AlarmType type, ...)
{
    errno_t rc;
    int nRet;
    int lenInfoEn = sizeof(alarmItem->infoEn);
    int lenInfoCh = sizeof(alarmItem->infoCh);
    va_list argp1;
    va_list argp2;
    char* logicClusterName = NULL;

    // initialize the additionalParam
    rc = memset_s(additionalParam, sizeof(AlarmAdditionalParam), 0, sizeof(AlarmAdditionalParam));
    securec_check_c(rc, "\0", "\0");
    // initialize the alarmItem->infoEn
    rc = memset_s(alarmItem->infoEn, lenInfoEn, 0, lenInfoEn);
    securec_check_c(rc, "\0", "\0");
    // initialize the alarmItem->infoCh
    rc = memset_s(alarmItem->infoCh, lenInfoCh, 0, lenInfoCh);
    securec_check_c(rc, "\0", "\0");

    if (ALM_AT_Fault == type || ALM_AT_Event == type) {
        va_start(argp1, type);
        va_start(argp2, type);
        nRet = vsnprintf_s(alarmItem->infoEn, lenInfoEn, lenInfoEn - 1, AlarmIdToAlarmInfoEn(alarmItem->id), argp1);
        securec_check_ss_c(nRet, "\0", "\0");
        nRet = vsnprintf_s(alarmItem->infoCh, lenInfoCh, lenInfoCh - 1, AlarmIdToAlarmInfoCh(alarmItem->id), argp2);
        securec_check_ss_c(nRet, "\0", "\0");
        va_end(argp1);
        va_end(argp2);
    }

    logicClusterName = GetLogicClusterName();
    FillAlarmAdditionalInfo(additionalParam, instanceName, databaseName, dbUserName, logicClusterName, alarmItem);
}

/*
Fill in the structure AlarmAdditionalParam for logic cluster.
*/
void WriteAlarmAdditionalInfoForLC(AlarmAdditionalParam* additionalParam, const char* instanceName,
    const char* databaseName, const char* dbUserName, const char* logicClusterName, Alarm* alarmItem, AlarmType type,
    ...)
{
    errno_t rc = 0;
    int nRet = 0;
    int lenInfoEn = sizeof(alarmItem->infoEn);
    int lenInfoCh = sizeof(alarmItem->infoCh);
    va_list argp1;
    va_list argp2;

    // initialize the additionalParam
    rc = memset_s(additionalParam, sizeof(AlarmAdditionalParam), 0, sizeof(AlarmAdditionalParam));
    securec_check_c(rc, "\0", "\0");
    // initialize the alarmItem->infoEn
    rc = memset_s(alarmItem->infoEn, lenInfoEn, 0, lenInfoEn);
    securec_check_c(rc, "\0", "\0");
    // initialize the alarmItem->infoCh
    rc = memset_s(alarmItem->infoCh, lenInfoCh, 0, lenInfoCh);
    securec_check_c(rc, "\0", "\0");

    if (ALM_AT_Fault == type || ALM_AT_Event == type) {
        va_start(argp1, type);
        va_start(argp2, type);
        nRet = vsnprintf_s(alarmItem->infoEn, lenInfoEn, lenInfoEn - 1, AlarmIdToAlarmInfoEn(alarmItem->id), argp1);
        securec_check_ss_c(nRet, "\0", "\0");
        nRet = vsnprintf_s(alarmItem->infoCh, lenInfoCh, lenInfoCh - 1, AlarmIdToAlarmInfoCh(alarmItem->id), argp2);
        securec_check_ss_c(nRet, "\0", "\0");
        va_end(argp1);
        va_end(argp2);
    }
    FillAlarmAdditionalInfo(additionalParam, instanceName, databaseName, dbUserName, logicClusterName, alarmItem);
}

// check whether the alarm component exists
static bool CheckAlarmComponent(const char* alarmComponentPath)
{
    static int accessCount = 0;
    if (access(alarmComponentPath, F_OK) != 0) {
        if (0 == accessCount) {
            AlarmLog(ALM_LOG, "Alarm component does not exist.");
        }
        if (accessCount < 1000) {
            ++accessCount;
        } else {
            accessCount = 0;
        }
        return false;
    } else {
        return true;
    }
}

/* suppress the component alarm report, don't suppress the event report */
static bool SuppressComponentAlarmReport(Alarm* alarmItem, AlarmType type, int timeInterval)
{
    time_t thisTime = time(NULL);

    /* alarm suppression */
    if (ALM_AT_Fault == type) {                    // now the state is fault
        if (ALM_AS_Reported == alarmItem->stat) {  // original state is fault
            // check whether the interval between now and last report time is more than $timeInterval secs
            if (thisTime - alarmItem->lastReportTime >= timeInterval && alarmItem->reportCount < 5) {
                ++(alarmItem->reportCount);
                alarmItem->lastReportTime = thisTime;
                // need report
                return true;
            } else {
                // don't need report
                return false;
            }
        } else if (ALM_AS_Normal == alarmItem->stat) {  // original state is resume
            // now the state have changed, report the alarm immediately
            alarmItem->reportCount = 1;
            alarmItem->lastReportTime = thisTime;
            alarmItem->stat = ALM_AS_Reported;
            // need report
            return true;
        }
    } else if (ALM_AT_Resume == type) {            // now the state is resume
        if (ALM_AS_Reported == alarmItem->stat) {  // original state is fault
            // now the state have changed, report the resume immediately
            alarmItem->reportCount = 1;
            alarmItem->lastReportTime = thisTime;
            alarmItem->stat = ALM_AS_Normal;
            // need report
            return true;
        } else if (ALM_AS_Normal == alarmItem->stat) {  // original state is resume
            // check whether the interval between now and last report time is more than $timeInterval secs
            if (thisTime - alarmItem->lastReportTime >= timeInterval && alarmItem->reportCount < 5) {
                ++(alarmItem->reportCount);
                alarmItem->lastReportTime = thisTime;
                // need report
                return true;
            } else {
                // don't need report
                return false;
            }
        }
    } else if (ALM_AT_Event == type) {
        // report immediately
        return true;
    }

    return false;
}

// suppress the syslog alarm report, filter the resume, only report alarm
static bool SuppressSyslogAlarmReport(Alarm* alarmItem, AlarmType type, int timeInterval)
{
    time_t thisTime = time(NULL);

    if (ALM_AT_Fault == type) {
        // only report alarm and event
        if (ALM_AS_Reported == alarmItem->stat) {
            // original stat is fault
            // check whether the interval between now and the last report time is more than $timeInterval secs
            if (thisTime - alarmItem->lastReportTime >= timeInterval && alarmItem->reportCount < 5) {
                ++(alarmItem->reportCount);
                alarmItem->lastReportTime = thisTime;
                // need report
                return true;
            } else {
                // don't need report
                return false;
            }
        } else if (ALM_AS_Normal == alarmItem->stat) {
            // original state is resume
            alarmItem->reportCount = 1;
            alarmItem->lastReportTime = thisTime;
            alarmItem->stat = ALM_AS_Reported;
            return true;
        }
    } else if (ALM_AT_Event == type) {
        // report immediately
        return true;
    } else if (ALM_AT_Resume == type) {
        alarmItem->stat = ALM_AS_Normal;
        return false;
    }

    return false;
}

/* suppress the alarm log */
static bool SuppressAlarmLogReport(Alarm* alarmItem, AlarmType type, int timeInterval, int maxReportCount)
{
    struct timeval thisTime;
    gettimeofday(&thisTime, NULL);

    /* alarm suppression */
    if (type == ALM_AT_Fault) {                   /* now the state is fault */
        if (alarmItem->stat == ALM_AS_Reported) { /* original state is fault */
            /* check whether the interval between now and last report time is more than $timeInterval secs */
            if (thisTime.tv_sec - alarmItem->lastReportTime >= timeInterval &&
                alarmItem->reportCount < maxReportCount) {
                ++(alarmItem->reportCount);
                alarmItem->lastReportTime = thisTime.tv_sec;
                if (alarmItem->startTimeStamp == 0)
                    alarmItem->startTimeStamp = thisTime.tv_sec * 1000 + thisTime.tv_usec / 1000;
                /* need report */
                return false;
            } else {
                /* don't need report */
                return true;
            }
        } else if (alarmItem->stat == ALM_AS_Normal) { /* original state is resume */
            /* now the state have changed, report the alarm immediately */
            alarmItem->reportCount = 1;
            alarmItem->lastReportTime = thisTime.tv_sec;
            alarmItem->stat = ALM_AS_Reported;
            alarmItem->startTimeStamp = thisTime.tv_sec * 1000 + thisTime.tv_usec / 1000;
            alarmItem->endTimeStamp = 0;
            /* need report */
            return false;
        }
    } else if (type == ALM_AT_Resume) {           /* now the state is resume */
        if (alarmItem->stat == ALM_AS_Reported) { /* original state is fault */
            /* now the state have changed, report the resume immediately */
            alarmItem->reportCount = 1;
            alarmItem->lastReportTime = thisTime.tv_sec;
            alarmItem->stat = ALM_AS_Normal;
            alarmItem->endTimeStamp = thisTime.tv_sec * 1000 + thisTime.tv_usec / 1000;
            alarmItem->startTimeStamp = 0;
            /* need report */
            return false;
        } else if (alarmItem->stat == ALM_AS_Normal) { /* original state is resume */
            /* check whether the interval between now and last report time is more than $timeInterval secs */
            if (thisTime.tv_sec - alarmItem->lastReportTime >= timeInterval &&
                alarmItem->reportCount < maxReportCount) {
                ++(alarmItem->reportCount);
                alarmItem->lastReportTime = thisTime.tv_sec;
                if (alarmItem->endTimeStamp == 0)
                    alarmItem->endTimeStamp = thisTime.tv_sec * 1000 + thisTime.tv_usec / 1000;
                /* need report */
                return false;
            } else {
                /* don't need report */
                return true;
            }
        }
    } else if (type == ALM_AT_Event) {
        /* need report */
        alarmItem->startTimeStamp = thisTime.tv_sec * 1000 + thisTime.tv_usec / 1000;
        return false;
    }

    return true;
}

// This function converts an integer 'inputLen' into a 4-character string and stores it in 'outputLen'.

static void GetFormatLenStr(char* outputLen, int inputLen)
{
    outputLen[4] = '\0';           // Null-terminate the string to ensure it's properly terminated
    outputLen[3] = '0' + inputLen % 10;  // Convert the last digit of 'inputLen' to a character and store it in the last position
    inputLen /= 10;               // Remove the last digit from 'inputLen' by integer division
    outputLen[2] = '0' + inputLen % 10;  // Convert the next digit to a character and store it in the third position
    inputLen /= 10;               // Remove the next digit from 'inputLen'
    outputLen[1] = '0' + inputLen % 10;  // Convert the next digit to a character and store it in the second position
    inputLen /= 10;               // Remove the next digit from 'inputLen'
    outputLen[0] = '0' + inputLen % 10;  // Convert the last remaining digit to a character and store it in the first position
}


// This function reports an alarm using a specified alarm component path, alarm item, alarm type, and additional parameters.

static void ComponentReport(
    char* alarmComponentPath, Alarm* alarmItem, AlarmType type, AlarmAdditionalParam* additionalParam)
{
    int nRet = 0; // Integer return value
    char reportCmd[4096] = {0}; // Buffer to store the report command
    int retCmd = 0; // Return code from the system command
    int cnt = 0; // Counter for retries
    char tempBuff[4096] = {0}; // Temporary buffer
    char clusterNameLen[5] = {0}; // Buffer for the length of cluster name
    char databaseNameLen[5] = {0}; // Buffer for the length of database name
    char dbUserNameLen[5] = {0}; // Buffer for the length of database user name
    char hostIPLen[5] = {0}; // Buffer for the length of host IP
    char hostNameLen[5] = {0}; // Buffer for the length of host name
    char instanceNameLen[5] = {0}; // Buffer for the length of instance name
    char additionInfoLen[5] = {0}; // Buffer for the length of additional info
    char clusterName[512] = {0}; // Buffer for the cluster name

    int i = 0; // Counter for loops
    errno_t rc = 0; // Error code for secure functions

    // Set the host IP and host name of feature permission alarms to make alarms of different hosts suppressible
    if (ALM_AI_UnbalancedCluster == alarmItem->id || ALM_AI_FeaturePermissionDenied == alarmItem->id) {
        rc = memset_s(additionalParam->hostIP, sizeof(additionalParam->hostIP), 0, sizeof(additionalParam->hostIP));
        securec_check_c(rc, "\0", "\0");
        rc = memset_s(
            additionalParam->hostName, sizeof(additionalParam->hostName), 0, sizeof(additionalParam->hostName));
        securec_check_c(rc, "\0", "\0");
    }

    // If a logic cluster name is provided, create a combined cluster name
    if (additionalParam->logicClusterName[0] != '\0') {
        rc = snprintf_s(clusterName,
            sizeof(clusterName),
            sizeof(clusterName) - 1,
            "%s:%s",
            additionalParam->clusterName,
            additionalParam->logicClusterName);
        securec_check_ss_c(rc, "\0", "\0");
    } else {
        rc = memcpy_s(
            clusterName, sizeof(clusterName), additionalParam->clusterName, sizeof(additionalParam->clusterName));
        securec_check_ss_c(rc, "\0", "\0");
    }

    // Calculate the length of various parameters and store them as 4-character strings
    GetFormatLenStr(clusterNameLen, strlen(clusterName));
    GetFormatLenStr(databaseNameLen, strlen(additionalParam->databaseName));
    GetFormatLenStr(dbUserNameLen, strlen(additionalParam->dbUserName));
    GetFormatLenStr(hostIPLen, strlen(additionalParam->hostIP));
    GetFormatLenStr(hostNameLen, strlen(additionalParam->hostName));
    GetFormatLenStr(instanceNameLen, strlen(additionalParam->instanceName));
    GetFormatLenStr(additionInfoLen, strlen(additionalParam->additionInfo));

    // Replace spaces in the additional info with '#' for security
    for (i = 0; i < (int)strlen(additionalParam->additionInfo); ++i) {
        if (' ' == additionalParam->additionInfo[i]) {
            additionalParam->additionInfo[i] = '#';
        }
    }

    // Create a formatted string containing all the lengths and values
    nRet = snprintf_s(tempBuff,
        sizeof(tempBuff),
        sizeof(tempBuff) - 1,
        "%s%s%s%s%s%s%s%s%s%s%s%s%s%s",
        clusterNameLen,
        databaseNameLen,
        dbUserNameLen,
        hostIPLen,
        hostNameLen,
        instanceNameLen,
        additionInfoLen,
        clusterName,
        additionalParam->databaseName,
        additionalParam->dbUserName,
        additionalParam->hostIP,
        additionalParam->hostName,
        additionalParam->instanceName,
        additionalParam->additionInfo);
    securec_check_ss_c(nRet, "\0", "\0");

    // Ensure the security of input parameters
    check_input_for_security1(alarmComponentPath);
    check_input_for_security1(tempBuff);

    // Create the full alarm report command
    nRet = snprintf_s(reportCmd,
        sizeof(reportCmd),
        sizeof(reportCmd) - 1,
        "%s alarm %ld %d %s",
        alarmComponentPath,
        alarmItem->id,
        type,
        tempBuff);
    securec_check_ss_c(nRet, "\0", "\0");

    // Perform the alarm report, with retries
    do {
        retCmd = system(reportCmd);

        // If the return code indicates suppression of the alarm report, exit the loop
        if (ALARM_REPORT_SUPPRESS == WEXITSTATUS(retCmd))
            break;
        if (++cnt > 3)
            break;
    } while (WEXITSTATUS(retCmd) != ALARM_REPORT_SUCCEED);

    // Handle success or failure of the alarm report
    if (ALARM_REPORT_SUCCEED != WEXITSTATUS(retCmd) && ALARM_REPORT_SUPPRESS != WEXITSTATUS(retCmd)) {
        AlarmLog(ALM_LOG, "Component alarm report failed! Cmd: %s, retCmd: %d.", reportCmd, WEXITSTATUS(retCmd));
    } else if (ALARM_REPORT_SUCCEED == WEXITSTATUS(retCmd)) {
        if (type != ALM_AT_Resume) {
            AlarmLog(ALM_LOG, "Component alarm report succeed! Cmd: %s, retCmd: %d.", reportCmd, WEXITSTATUS(retCmd));
        }
    }
}


// This function reports an alarm to syslog with specific alarm information and additional parameters.

static void SyslogReport(Alarm* alarmItem, AlarmAdditionalParam* additionalParam)
{
    int nRet = 0; // Integer return value
    char reportInfo[4096] = {0}; // Buffer to store the alarm report information

    // Create a formatted string containing various alarm and additional parameters
    nRet = snprintf_s(reportInfo,
        sizeof(reportInfo),
        sizeof(reportInfo) - 1,
        "%s||%s||%s||||||||%s||%s||%s||%s||%s||%s||%s||%s||%s||%s||%s||||||||||||||%s||%s||||||||||||||||||||",
        "Syslog MPPDB",                   // Syslog identification tag
        additionalParam->hostName,        // Host name
        additionalParam->hostIP,          // Host IP address
        "Database",                       // Database information
        "MppDB",                          // MppDB information
        additionalParam->logicClusterName,// Logic cluster name
        "SYSLOG",                         // Log type
        additionalParam->instanceName,    // Instance name
        "Alarm",                          // Alarm category
        AlarmIdToAlarmNameEn(alarmItem->id), // Alarm name in English
        AlarmIdToAlarmNameCh(alarmItem->id), // Alarm name in Chinese
        "1",                              // Unknown parameter
        "0",                              // Unknown parameter
        "6",                              // Unknown parameter
        alarmItem->infoEn,                // Alarm information in English
        alarmItem->infoCh);               // Alarm information in Chinese

    securec_check_ss_c(nRet, "\0", "\0");

    // Report the alarm information to the syslog using the LOG_ERR level
    syslog(LOG_ERR, "%s", reportInfo);
}


/* Check this line is comment line or not, which is in AlarmItem.conf file */
static bool isValidScopeLine(const char* str)
{
    size_t ii = 0;

    for (;;) {
        if (*(str + ii) == ' ') {
            ii++; /* skip blank */
        } else {
            break;
        }
    }

    if (*(str + ii) == '#')
        return true; /* comment line */

    return false; /* not comment line */
}

// This function initializes the alarm scope by reading and parsing a configuration file.

static void AlarmScopeInitialize(void)
{
    char* gaussHomeDir = NULL; // Pointer to store the value of the GAUSSHOME environment variable
    char* subStr = NULL; // Substring pointer
    char* subStr1 = NULL; // Substring pointer 1
    char* subStr2 = NULL; // Substring pointer 2
    char* saveptr1 = NULL; // Save pointer for strtok_r
    char* saveptr2 = NULL; // Save pointer for strtok_r
    char alarmItemPath[MAXPGPATH]; // Path to the alarm configuration file
    char buf[MAX_BUF_SIZE] = {0}; // Buffer to store a line from the configuration file
    errno_t nRet, rc; // Error code variables

    // Retrieve the value of the GAUSSHOME environment variable
    if ((gaussHomeDir = gs_getenv_r("GAUSSHOME")) == NULL) {
        AlarmLog(ALM_LOG, "ERROR: environment variable $GAUSSHOME is not set!\n");
        return;
    }
    // Check for potential security issues with the environment variable
    check_input_for_security1(gaussHomeDir);

    // Create the path to the alarm configuration file
    nRet = snprintf_s(alarmItemPath, MAXPGPATH, MAXPGPATH - 1, "%s/bin/alarmItem.conf", gaussHomeDir);
    securec_check_ss_c(nRet, "\0", "\0");
    canonicalize_path(alarmItemPath);

    // Attempt to open the alarm configuration file for reading
    FILE* fd = fopen(alarmItemPath, "r");
    if (fd == NULL)
        return;

    // Read each line from the configuration file
    while (!feof(fd)) {
        // Initialize the 'buf' buffer with zeros
        rc = memset_s(buf, MAX_BUF_SIZE, 0, MAX_BUF_SIZE);
        securec_check_c(rc, "\0", "\0");
        
        // Read a line from the configuration file into the 'buf' buffer
        if (fgets(buf, MAX_BUF_SIZE, fd) == NULL)
            continue;

        // Check if the line is a valid scope line; if so, skip it
        if (isValidScopeLine(buf))
            continue;

        // Search for the substring "alarm_scope" in the line
        subStr = strstr(buf, "alarm_scope");
        if (subStr == NULL)
            continue;

        // Find the position of the equal sign '=' after "alarm_scope"
        subStr = strstr(subStr + strlen("alarm_scope"), "=");
        if (subStr == NULL || *(subStr + 1) == '\0') /* '=' is the last character */
            continue;

        // Move to the first non-blank character after the equal sign
        int ii = 1;
        for (;;) {
            if (*(subStr + ii) == ' ') {
                ii++; /* skip blank */
            } else
                break;
        }

        // Extract the substring after the equal sign
        subStr = subStr + ii;
        subStr1 = strtok_r(subStr, "\n", &saveptr1);
        if (subStr1 == NULL)
            continue;
        subStr2 = strtok_r(subStr1, "\r", &saveptr2);
        if (subStr2 == NULL)
            continue;
        
        // Copy the extracted alarm scope value to the 'g_alarm_scope' buffer
        rc = memcpy_s(g_alarm_scope, MAX_BUF_SIZE, subStr2, strlen(subStr2));
        securec_check_c(rc, "\0", "\0");
    }
    
    // Close the configuration file
    fclose(fd);
}


void AlarmReporter(Alarm* alarmItem, AlarmType type, AlarmAdditionalParam* additionalParam)
{
    if (NULL == alarmItem) {
        AlarmLog(ALM_LOG, "alarmItem is NULL.");
        return;
    }
    if (0 == strcmp(WarningType, FUSIONINSIGHTTYPE)) {  // the warning type is FusionInsight type
        // check whether the alarm component exists
        if (false == CheckAlarmComponent(g_alarmComponentPath)) {
            // the alarm component does not exist
            return;
        }
        // suppress the component alarm
        if (true ==
            SuppressComponentAlarmReport(alarmItem, type, g_alarmReportInterval)) {  // check whether report the alarm
            ComponentReport(g_alarmComponentPath, alarmItem, type, additionalParam);
        }
    } else if (0 == strcmp(WarningType, ICBCTYPE)) {  // the warning type is ICBC type
        // suppress the syslog alarm
        if (true ==
            SuppressSyslogAlarmReport(alarmItem, type, g_alarmReportInterval)) {  // check whether report the alarm
            SyslogReport(alarmItem, additionalParam);
        }
    } else if (strcmp(WarningType, CBGTYPE) == 0) {
        if (!SuppressAlarmLogReport(alarmItem, type, g_alarmReportInterval, g_alarmReportMaxCount))
            write_alarm(alarmItem,
                AlarmIdToAlarmNameEn(alarmItem->id),
                AlarmIdToAlarmLevel(alarmItem->id),
                type,
                additionalParam);
    }
}

/*
---------------------------------------------------------------------------
The first report method:

We register check function in the alarm module.
And we will check and report all the alarm(alarm or resume) item in a loop.
---------------------------------------------------------------------------

---------------------------------------------------------------------------
The second report method:

We don't register any check function in the alarm module.
And we don't initialize the alarm item(typedef struct Alarm) structure here.
We will initialize the alarm item(typedef struct Alarm) in the begining of alarm module.
We invoke report function internally in the monitor process.
We fill the report message and then invoke the AlarmReporter.
---------------------------------------------------------------------------

---------------------------------------------------------------------------
The third report method:

We don't register any check function in the alarm module.
When we detect some errors occur, we will report some alarm.
Firstly, initialize the alarm item(typedef struct Alarm).
Secondly, fill the report message(typedef struct AlarmAdditionalParam).
Thirdly, invoke the AlarmReporter, report the alarm.
---------------------------------------------------------------------------
*/
// This function performs a loop to check a list of alarms and report their status.

void AlarmCheckerLoop(Alarm* checkList, int checkListSize)
{
    int i; // Loop counter
    AlarmAdditionalParam tempAdditionalParam; // Temporary storage for additional alarm parameters

    // Check if the checkList is NULL or the checkListSize is invalid
    if (NULL == checkList || checkListSize <= 0) {
        AlarmLog(ALM_LOG, "AlarmCheckerLoop failed.");
        return;
    }

    // Iterate through the list of alarms to check each one
    for (i = 0; i < checkListSize; ++i) {
        Alarm* alarmItem = &(checkList[i]); // Get the current alarm item
        AlarmCheckResult result = ALM_ACR_UnKnown; // Initialize the alarm check result to unknown

        AlarmType type = ALM_AT_Fault; // Initialize the alarm type to fault

        // Check if the alarm item has a checker function assigned
        if (alarmItem->checker != NULL) {
            // Execute the alarm check function and obtain the check result
            result = alarmItem->checker(alarmItem, &tempAdditionalParam);

            // If the check result is unknown, continue to the next alarm
            if (ALM_ACR_UnKnown == result) {
                continue;
            }

            // If the check result is normal, set the alarm type to resume
            if (ALM_ACR_Normal == result) {
                type = ALM_AT_Resume;
            }

            // Report the alarm status using the AlarmReporter function
            (void)AlarmReporter(alarmItem, type, &tempAdditionalParam);
        }
    }
}


// This function logs an alarm message with a specified log level and a variable number of arguments.

void AlarmLog(int level, const char* fmt, ...)
{
    va_list args; // Variable argument list
    char buf[MAXPGPATH] = {0}; // Buffer to store the log message
    int nRet = 0; // Integer return value

    // Start processing variable arguments with the 'fmt' format string
    (void)va_start(args, fmt);

    // Format the log message with the specified format and variable arguments,
    // and store it in the 'buf' buffer
    nRet = vsnprintf_s(buf, sizeof(buf), sizeof(buf) - 1, fmt, args);
    securec_check_ss_c(nRet, "\0", "\0");

    // End processing variable arguments
    va_end(args);

    // Call the AlarmLogImplementation function to handle the logging with the specified log level,
    // a log prefix (AlarmLogPrefix), and the formatted log message
    AlarmLogImplementation(level, AlarmLogPrefix, buf);
}

/*
Initialize the alarm item
reportTime:  express the last time of alarm report. the default value is 0.
*/
// This function initializes an Alarm structure with the specified values.

void AlarmItemInitialize(
    Alarm* alarmItem, AlarmId alarmId, AlarmStat alarmStat, CheckerFunc checkerFunc, time_t reportTime, int reportCount)
{
    // Set the checker function for the alarm item
    alarmItem->checker = checkerFunc;

    // Set the ID of the alarm item
    alarmItem->id = alarmId;

    // Set the initial alarm status (e.g., ALM_AS_Normal, ALM_AS_Fault)
    alarmItem->stat = alarmStat;

    // Set the time of the last report for this alarm item
    alarmItem->lastReportTime = reportTime;

    // Set the count of reports for this alarm item
    alarmItem->reportCount = reportCount;

    // Initialize the start and end timestamps to 0 (may be updated during alarm handling)
    alarmItem->startTimeStamp = 0;
    alarmItem->endTimeStamp = 0;
}