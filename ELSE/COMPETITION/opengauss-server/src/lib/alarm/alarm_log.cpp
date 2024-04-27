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
 * alarm_log.c
 *    alarm logging and reporting
 *
 * IDENTIFICATION
 *    src/lib/alarm/alarm_log.cpp
 *
 * -------------------------------------------------------------------------
 */


#include <fcntl.h>
#include <signal.h>
#include <ctype.h>
#include <syslog.h>
#include <limits.h>
#include "cm/path.h"
#include "cm/cm_c.h"
#include "cm/stringinfo.h"
#include "alarm/alarm_log.h"
#include <sys/time.h>
#if !defined(WIN32)
#include <sys/syscall.h>
#define gettid() syscall(__NR_gettid)
#else
/* windows */
#endif
#include <sys/stat.h>

#undef _
#define _(x) x

/*
 * We really want line-buffered mode for logfile output, but Windows does
 * not have it, and interprets _IOLBF as _IOFBF (bozos).  So use _IONBF
 * instead on Windows.
 */
#ifdef WIN32
#define LBF_MODE _IONBF
#else
#define LBF_MODE _IOLBF
#endif

#define SYSTEM_ALARM_LOG "system_alarm"
#define MAX_SYSTEM_ALARM_LOG_SIZE (128 * 1024 * 1024) /* 128MB */
#define CURLOGFILEMARK "-current.log"

const int LOG_MAX_TIMELEN = 80;
const int COMMAND_SIZE = 4196;
const int REPORT_MSG_SIZE = 4096;

char g_alarm_scope[MAX_BUF_SIZE] = {0};
char system_alarm_log[MAXPGPATH] = {0};
static char system_alarm_log_name[MAXPGPATH];
pthread_rwlock_t alarm_log_write_lock;
FILE* alarmLogFile = NULL;
typedef int64 pg_time_t;
char sys_alarm_log_path[MAX_PATH_LEN] = {0};

/*
 * Open a new logfile with proper permissions and buffering options.
 *
 */
static FILE* logfile_open(const char* filename, const char* mode)
{
    FILE* fh = NULL;
    mode_t oumask;

    // Set the file permission mask to allow read, write, and execute permissions for the owner (user)
    // while preserving the permissions for the group and others.
    oumask = umask((mode_t)((~(mode_t)(S_IRUSR | S_IWUSR | S_IXUSR)) & (S_IRWXU | S_IRWXG | S_IRWXO)));

    // Open the file with the specified filename and mode.
    fh = fopen(filename, mode);

    // Restore the original file permission mask.
    (void)umask(oumask);

    // If the file was successfully opened, set the buffering mode to line-buffered.
    if (fh != NULL) {
        setvbuf(fh, NULL, LBF_MODE, 0);

#ifdef WIN32
        // On Windows, use CRLF line endings.
        _setmode(_fileno(fh), _O_TEXT);
#endif
    } else {
        // If the file could not be opened, log an error message.
        AlarmLog(ALM_LOG, "could not open log file \"%s\"\n", filename);
    }

    // Return the file handle.
    return fh;
}

static void create_new_alarm_log_file(const char* sys_log_path)
{
    pg_time_t current_time;
    struct tm systm;
    char log_create_time[LOG_MAX_TIMELEN] = {0};
    char log_temp_name[MAXPGPATH] = {0};
    errno_t rc;

    // Initialize the systm struct and log_create_time buffer
    rc = memset_s(&systm, sizeof(systm), 0, sizeof(systm));
    securec_check_c(rc, "\0", "\0");

    // Clear the system_alarm_log buffer
    rc = memset_s(system_alarm_log, MAXPGPATH, 0, MAXPGPATH);
    securec_check_c(rc, "\0", "\0");

    // Get the current time
    current_time = time(NULL);

    // Convert the current time to a formatted string
    if (localtime_r(&current_time, &systm) != NULL) {
        (void)strftime(log_create_time, LOG_MAX_TIMELEN, "-%Y-%m-%d_%H%M%S", &systm);
    } else {
        // Print an error message if getting the local time failed
        AlarmLog(ALM_LOG, "get localtime_r failed\n");
    }

    // Create the temporary log file name
    rc = snprintf_s(
        log_temp_name, MAXPGPATH, MAXPGPATH - 1, "%s%s%s", SYSTEM_ALARM_LOG, log_create_time, CURLOGFILEMARK);
    securec_check_ss_c(rc, "\0", "\0");

    // Create the full path of the new log file
    rc = snprintf_s(system_alarm_log, MAXPGPATH, MAXPGPATH - 1, "%s/%s", sys_log_path, log_temp_name);
    securec_check_ss_c(rc, "\0", "\0");

    // Clear the system_alarm_log_name buffer
    rc = memset_s(system_alarm_log_name, MAXPGPATH, 0, MAXPGPATH);
    securec_check_c(rc, "\0", "\0");

    // Copy the temporary log file name to system_alarm_log_name
    rc = strncpy_s(system_alarm_log_name, MAXPGPATH, log_temp_name, strlen(log_temp_name));
    securec_check_c(rc, "\0", "\0");

    // Open the new log file in "append" mode
    alarmLogFile = logfile_open(system_alarm_log, "a");
}

/**
 * Renames the current alarm log file without the "CURLOGFILEMARK" suffix.
 * 
 * @param sys_log_path The system log path.
 * @return True if the log file was successfully renamed, false otherwise.
 */
static bool rename_alarm_log_file(const char* sys_log_path)
{
    int len_log_old_name, len_suffix_name, len_log_new_name;
    char logFileBuff[MAXPGPATH] = {0};
    char log_new_name[MAXPGPATH] = {0};
    errno_t rc;
    int ret;

    /* Get the lengths of the old log file name, the suffix name, and the new log file name */
    len_log_old_name = strlen(system_alarm_log_name);
    len_suffix_name = strlen(CURLOGFILEMARK);
    len_log_new_name = len_log_old_name - len_suffix_name;

    /* Copy the old log file name to logFileBuff */
    rc = strncpy_s(logFileBuff, MAXPGPATH, system_alarm_log_name, len_log_new_name);
    securec_check_c(rc, "\0", "\0");

    /* Append the ".log" suffix to logFileBuff */
    rc = strncat_s(logFileBuff, MAXPGPATH, ".log", strlen(".log"));
    securec_check_c(rc, "\0", "\0");

    /* Create the full path of the new log file */
    rc = snprintf_s(log_new_name, MAXPGPATH, MAXPGPATH - 1, "%s/%s", sys_log_path, logFileBuff);
    securec_check_ss_c(rc, "\0", "\0");

    /* Close the current log file */
    if (alarmLogFile != NULL) {
        fclose(alarmLogFile);
        alarmLogFile = NULL;
    }

    /* Rename the current log file to the new log file name */
    ret = rename(system_alarm_log, log_new_name);
    if (ret != 0) {
        AlarmLog(ALM_LOG, "ERROR: %s: rename log file %s failed! \n", system_alarm_log, system_alarm_log);
        return false;
    }
    return true;
}


/**
 * Writes the given buffer to the alarm log file.
 * 
 * @param buffer The buffer containing the data to be written.
 */
static void write_log_file(const char* buffer)
{
    int rc;
    (void)pthread_rwlock_wrlock(&alarm_log_write_lock);

    // Check if the alarm log file is not open
    if (alarmLogFile == NULL) {
        // If the current log file is "/dev/null", create a new system alarm log
        if (strncmp(system_alarm_log, "/dev/null", strlen("/dev/null")) == 0) {
            create_system_alarm_log(sys_alarm_log_path);
        }
        // Open the alarm log file in "append" mode
        alarmLogFile = logfile_open(system_alarm_log, "a");
    }

    // Write the buffer to the alarm log file
    if (alarmLogFile != NULL) {
        int count = strlen(buffer);

        rc = fwrite(buffer, 1, count, alarmLogFile);
        if (rc != count) {
            AlarmLog(ALM_LOG, "could not write to log file: %s\n", system_alarm_log);
        }
        fflush(alarmLogFile);
        fclose(alarmLogFile);
        alarmLogFile = NULL;
    } else {
        AlarmLog(ALM_LOG, "write_log_file, log file is null now: %s\n", buffer);
    }

    (void)pthread_rwlock_unlock(&alarm_log_write_lock);
}

/* unify log style */
void create_system_alarm_log(const char* sys_log_path)
{
    DIR* dir = NULL;
    struct dirent* de = NULL;
    bool is_exist = false;

    /* check validity of current log file name */
    char* name_ptr = NULL;
    errno_t rc;

    // Check if the sys_alarm_log_path is empty
    if (strlen(sys_alarm_log_path) == 0) {
        // Copy the sys_log_path to sys_alarm_log_path
        rc = strncpy_s(sys_alarm_log_path, MAX_PATH_LEN, sys_log_path, strlen(sys_log_path));
        securec_check_c(rc, "\0", "\0");
    }

    // Open the directory specified by sys_log_path
    if ((dir = opendir(sys_log_path)) == NULL) {
        // Print an error message if opendir fails
        AlarmLog(ALM_LOG, "opendir %s failed! \n", sys_log_path);
        rc = strncpy_s(system_alarm_log, MAXPGPATH, "/dev/null", strlen("/dev/null"));
        securec_check_ss_c(rc, "\0", "\0");
        return;
    }

    // Iterate through the directory entries
    while ((de = readdir(dir)) != NULL) {
        // Check if the current log file exists
        if (strstr(de->d_name, SYSTEM_ALARM_LOG) != NULL) {
            name_ptr = strstr(de->d_name, CURLOGFILEMARK);
            if (name_ptr != NULL) {
                name_ptr += strlen(CURLOGFILEMARK);
                if ((*name_ptr) == '\0') {
                    is_exist = true;
                    break;
                }
            }
        }
    }

    // If the current log file exists
    if (is_exist) {
        // Clear the system_alarm_log_name and system_alarm_log buffers
        rc = memset_s(system_alarm_log_name, MAXPGPATH, 0, MAXPGPATH);
        securec_check_c(rc, "\0", "\0");
        rc = memset_s(system_alarm_log, MAXPGPATH, 0, MAXPGPATH);
        securec_check_c(rc, "\0", "\0");

        // Construct the new log file path
        rc = snprintf_s(system_alarm_log, MAXPGPATH, MAXPGPATH - 1, "%s/%s", sys_log_path, de->d_name);
        securec_check_ss_c(rc, "\0", "\0");

        // Copy the log file name to system_alarm_log_name
        rc = strncpy_s(system_alarm_log_name, MAXPGPATH, de->d_name, strlen(de->d_name));
        securec_check_c(rc, "\0", "\0");
    } else {
        /* create current log file name */
        create_new_alarm_log_file(sys_log_path);
    }
    (void)closedir(dir);
}

void clean_system_alarm_log(const char* file_name, const char* sys_log_path)
{
    // Assert that file_name is not NULL
    Assert(file_name != NULL);

    unsigned long filesize = 0;
    struct stat statbuff;
    int ret;

    // Initialize statbuff with zeros
    errno_t rc = memset_s(&statbuff, sizeof(statbuff), 0, sizeof(statbuff));
    securec_check_c(rc, "\0", "\0");

    // Get the file status using stat
    ret = stat(file_name, &statbuff);

    // Check if stat failed or if the file_name is "/dev/null"
    if (ret != 0 || (strncmp(file_name, "/dev/null", strlen("/dev/null")) == 0)) {
        // Print an error message and return if there is an error with stat or if the file_name is "/dev/null"
        AlarmLog(ALM_LOG, "ERROR: stat system alarm log %s error.ret=%d\n", file_name, ret);
        return;
    } else {
        // Get the file size from the statbuff
        filesize = statbuff.st_size;
    }

    // Check if the file size is greater than MAX_SYSTEM_ALARM_LOG_SIZE
    if (filesize > MAX_SYSTEM_ALARM_LOG_SIZE) {
        // Acquire a write lock on alarm_log_write_lock
        (void)pthread_rwlock_wrlock(&alarm_log_write_lock);

        // Rename the current file without the Mark
        if (rename_alarm_log_file(sys_log_path)) {
            // Create a new log file
            create_new_alarm_log_file(sys_log_path);
        }

        // Release the write lock on alarm_log_write_lock
        (void)pthread_rwlock_unlock(&alarm_log_write_lock);
    }

    return;
}

void write_alarm(Alarm* alarmItem, const char* alarmName, const char* alarmLevel, AlarmType type,
    AlarmAdditionalParam* additionalParam)
{
    // Declare variables
    char command[COMMAND_SIZE];
    char reportInfo[REPORT_MSG_SIZE];
    errno_t rcs = 0;

    // Check if system_alarm_log is empty, if so, return
    if (strlen(system_alarm_log) == 0)
        return;

    // Initialize command and reportInfo buffers with zeros
    errno_t rc = memset_s(command, COMMAND_SIZE, 0, COMMAND_SIZE);
    securec_check_c(rc, "\0", "\0");
    rc = memset_s(reportInfo, REPORT_MSG_SIZE, 0, REPORT_MSG_SIZE);
    securec_check_c(rc, "\0", "\0");

    // Check the type of the alarm
    if (type == ALM_AT_Fault || type == ALM_AT_Event) {
        // Construct the reportInfo string for fault or event alarms
        rcs = snprintf_s(reportInfo,
            REPORT_MSG_SIZE,
            REPORT_MSG_SIZE - 1,
            "{" SYSQUOTE "id" SYSQUOTE SYSCOLON SYSQUOTE "%016ld" SYSQUOTE SYSCOMMA SYSQUOTE
            "name" SYSQUOTE SYSCOLON SYSQUOTE "%s" SYSQUOTE SYSCOMMA SYSQUOTE "level" SYSQUOTE SYSCOLON SYSQUOTE
            "%s" SYSQUOTE SYSCOMMA SYSQUOTE "scope" SYSQUOTE SYSCOLON "%s" SYSCOMMA SYSQUOTE
            "source_tag" SYSQUOTE SYSCOLON SYSQUOTE "%s-%s" SYSQUOTE SYSCOMMA SYSQUOTE
            "op_type" SYSQUOTE SYSCOLON SYSQUOTE "%s" SYSQUOTE SYSCOMMA SYSQUOTE "details" SYSQUOTE SYSCOLON SYSQUOTE
            "%s" SYSQUOTE SYSCOMMA SYSQUOTE "clear_type" SYSQUOTE SYSCOLON SYSQUOTE "%s" SYSQUOTE SYSCOMMA SYSQUOTE
            "start_timestamp" SYSQUOTE SYSCOLON "%ld" SYSCOMMA SYSQUOTE "end_timestamp" SYSQUOTE SYSCOLON "%d"
            "}\n",
            alarmItem->id,
            alarmName,
            alarmLevel,
            g_alarm_scope,
            additionalParam->hostName,
            (strlen(additionalParam->instanceName) != 0) ? additionalParam->instanceName : additionalParam->cluster
                        "ame" SYSQUOTE SYSCOLON SYSQUOTE "%s" SYSQUOTE SYSCOMMA SYSQUOTE
            "op_type" SYSQUOTE SYSCOLON SYSQUOTE "%s" SYSQUOTE SYSCOMMA SYSQUOTE "start_timestamp" SYSQUOTE SYSCOLON
            "%d" SYSCOMMA SYSQUOTE "end_timestamp" SYSQUOTE SYSCOLON "%ld"
            "}\n",
            alarmItem->id,
            alarmName,
            alarmLevel,
            g_alarm_scope,
            additionalParam->hostName,
            (strlen(additionalParam->instanceName) != 0) ? additionalParam->instanceName : additionalParam->clusterName,
            "resolved",
            0,
            alarmItem->endTimeStamp);
    }

    // Check if the snprintf_s function succeeded
    securec_check_ss_c(rcs, "\0", "\0");

    // Write the reportInfo to the log file
    write_log_file(reportInfo);
}
