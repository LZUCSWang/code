/*** 
 * @Author: 王贤义
 * @Team: 兰心开源
 * @Date: 2023-09-12 20:25:05
 */



/**
 * @file cm_elog.cpp
 * @brief error logging and reporting
 * @author xxx
 * @version 1.0
 * @date 2020-08-06
 *
 * @copyright Copyright (c) Huawei Technologies Co., Ltd. 2011-2020. All rights reserved.
 *
 */
#include <fcntl.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <ctype.h>
#include <syslog.h>
#include <limits.h>
#include "cm/path.h"

#include "cm/cm_c.h"
#include "cm/stringinfo.h"
#include "cm/elog.h"
#include "alarm/alarm.h"
#include "cm/cm_misc.h"
#include "cm/be_module.h"

#include <sys/time.h>
#if !defined(WIN32)
#include <sys/syscall.h>
#define gettid() syscall(__NR_gettid)
#else
/* windows. */
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

int log_destion_choice = LOG_DESTION_FILE;

/* declare the global variable of alarm module. */
int g_alarmReportInterval;
char g_alarmComponentPath[MAXPGPATH];
int g_alarmReportMaxCount;

char sys_log_path[MAX_PATH_LEN] = {0};  /* defalut cmData/cm_server  or cmData/cm_agent. */
char cm_krb_server_keyfile[MAX_PATH_LEN] = {0};
int Log_RotationSize = 16 * 1024 * 1024L;
pthread_rwlock_t syslog_write_lock;
pthread_rwlock_t dotCount_lock;
static bool dotCountNotZero = false;

FILE* syslogFile = NULL;
const char* prefix_name = NULL;

char curLogFileName[MAXPGPATH] = {0};
volatile int log_min_messages = WARNING;
volatile bool incremental_build = true;
volatile bool security_mode = false;
volatile int maxLogFileSize = 16 * 1024 * 1024;
volatile bool logInitFlag = false;
/* undocumentedVersion:
 * It's for inplace upgrading. This variable means which version we are
 * upgrading from. Zero means we are not upgrading.
 */
volatile uint32 undocumentedVersion = 0;
bool log_file_set = false;
/* unify log style */
THR_LOCAL const char* thread_name = NULL;

FILE* logfile_open(const char* filename, const char* mode);
static void get_alarm_report_interval(const char* conf);
static void TrimPathDoubleEndQuotes(char* path);

#define BUF_LEN 1024
#define COUNTSTR_LEN 128
#define MSBUF_LENGTH 8
#define FORMATTED_TS_LEN 128

static THR_LOCAL char  errbuf_errdetail[EREPORT_BUF_LEN];
static THR_LOCAL char  errbuf_errcode[EREPORT_BUF_LEN];
static THR_LOCAL char  errbuf_errmodule[EREPORT_BUF_LEN];
static THR_LOCAL char  errbuf_errmsg[EREPORT_BUF_LEN];
static THR_LOCAL char  errbuf_errcause[EREPORT_BUF_LEN];
static THR_LOCAL char  errbuf_erraction[EREPORT_BUF_LEN];

static THR_LOCAL char formatted_log_time[FORMATTED_TS_LEN];

/**
 * @brief When a parent process opens a file, the child processes will inherit the
 * file handle of the parent process. If the file is deleted and the child processes
 * are still running, the file handle will not be freed and take up disk space.
 * We set the FD_CLOEXEC flag to the file, so that the child processes don't inherit
 * the file handle of the parent process, and do not cause handle leak.
 *
 * @param fp open file object
 * @return int 0 means successfully set the flag.
 */
/**
 * @brief Set the close-on-exec flag for a file descriptor associated with a FILE stream.
 *
 * @param fp Pointer to a FILE stream.
 * @return 0 on success, or -1 on failure.
 */
int SetFdCloseExecFlag(FILE* fp)
{
    // Get the file descriptor associated with the FILE stream
    int fd = fileno(fp);
    
    // Get the current file descriptor flags
    int flags = fcntl(fd, F_GETFD);

    // Check if getting the flags failed
    if (flags < 0) {
        (void)printf("fcntl get flags failed.\n");
        return flags;
    }
    
    // Set the FD_CLOEXEC flag to close the file descriptor on exec
    flags |= FD_CLOEXEC;
    
    // Set the modified flags back to the file descriptor
    int ret = fcntl(fd, F_SETFD, flags);

    // Check if setting the flags failed
    if (ret == -1) {
        (void)printf("fcntl set flags failed.\n");
    }

    return ret;
}


void AlarmLogImplementation(int level, const char* prefix, const char* logtext)
{
    // Logging levels are as follows:
    // ALM_DEBUG: Debug level logging
    // ALM_LOG: Log level logging
    // All other levels are ignored.
    switch (level) {
        case ALM_DEBUG:
            write_runlog(LOG, "%s%s\n", prefix, logtext);
            break;
        case ALM_LOG:
            write_runlog(LOG, "%s%s\n", prefix, logtext);
            break;
        default:
            break;
    }
}

/*
 * setup formatted_log_time, for consistent times between CSV and regular logs
 */
static void setup_formatted_log_time(void)
{
    struct timeval tv = {0};  // Initialize a timeval structure for storing time information.
    time_t stamp_time;        // Define a variable to store the timestamp in seconds.
    char msbuf[MSBUF_LENGTH]; // Create a character array for storing milliseconds.
    struct tm timeinfo = {0}; // Initialize a tm structure for time-related information.
    int rc;                   // Define an integer variable for return code.
    errno_t rcs;              // Define an error code variable for string operations.

    // Get the current time of day and store it in the timeval structure 'tv'.
    (void)gettimeofday(&tv, NULL);
    stamp_time = (time_t)tv.tv_sec; // Extract the seconds part of the timeval and store it in 'stamp_time'.
    (void)localtime_r(&stamp_time, &timeinfo); // Convert 'stamp_time' into a local time representation.

    // Format the time into 'formatted_log_time' with placeholders for milliseconds.
    (void)strftime(formatted_log_time,
        FORMATTED_TS_LEN,
        /* leave room for milliseconds... */
        "%Y-%m-%d %H:%M:%S     %Z",
        &timeinfo);

    /* 'paste' milliseconds into place... */
    // Extract milliseconds from 'tv' and format them into 'msbuf'.
    rc = sprintf_s(msbuf, MSBUF_LENGTH, ".%03d", (int)(tv.tv_usec / 1000));
    securec_check_ss_c(rc, "\0", "\0");
    // Copy the formatted milliseconds from 'msbuf' into the 'formatted_log_time' string.
    rcs = strncpy_s(formatted_log_time + 19, FORMATTED_TS_LEN - 19, msbuf, 4);
    securec_check_c(rcs, "\0", "\0");
}


void add_log_prefix(int elevel, char* str)
{
    char errbuf_tmp[BUF_LEN * 3] = {0}; // Initialize a temporary character array for constructing the log message.
    errno_t rc; // Define an error code variable for string operations.
    int rcs; // Define an integer variable for return code.

    // Set up the log message with a timestamp and thread information.
    setup_formatted_log_time();

    /* unify log style */
    if (thread_name == NULL) {
        thread_name = ""; // If thread_name is NULL, set it to an empty string.
    }
    rcs = snprintf_s(errbuf_tmp,
        sizeof(errbuf_tmp),
        sizeof(errbuf_tmp) - 1,
        "%s tid=%ld %s %s: ", // Format the log message with timestamp, thread ID, thread name, and log level.
        formatted_log_time,
        gettid(),
        thread_name,
        log_level_int_to_string(elevel));
    securec_check_intval(rcs, );

    /* max message length less than 2048. */
    rc = strncat_s(errbuf_tmp, BUF_LEN * 3, str, BUF_LEN * 3 - strlen(errbuf_tmp)); // Concatenate the original message to the log message.

    securec_check_c(rc, "\0", "\0");

    // Copy the constructed log message back to the original 'str'.
    rc = memcpy_s(str, BUF_LEN * 2, errbuf_tmp, BUF_LEN * 2 - 1);
    securec_check_c(rc, "\0", "\0");

    str[BUF_LEN * 2 - 1] = '\0'; // Null-terminate the final log message.
}


/*
 * is_log_level_output -- Checks if 'elevel' is logically greater than or equal to 'log_min_level'.
 *
 * This function is used for tests that need to determine if a log message belongs to
 * the specified log level or higher. It handles cases where LOG level messages should be
 * sorted between ERROR and FATAL levels. Typically, this is useful for testing whether
 * a message should be written to the postmaster log. A simple comparison (e.g., >=) is
 * generally sufficient for testing whether the message should go to the client.
 */
static bool is_log_level_output(int elevel, int log_min_level)
{
    if (elevel == LOG) {
        if (log_min_level == LOG || log_min_level <= ERROR) {
            // If 'elevel' is LOG and 'log_min_level' is also LOG or less than ERROR, return true.
            return true;
        }
    } else if (log_min_level == LOG) {
        /* 'elevel' is not equal to LOG */
        if (elevel >= FATAL) {
            // If 'log_min_level' is LOG and 'elevel' is FATAL or higher, return true.
            return true;
        }
    } else if (elevel >= log_min_level) {
        /* Neither 'elevel' nor 'log_min_level' is LOG */
        // If 'elevel' is greater than or equal to 'log_min_level', return true.
        return true;
    }

    // Return false if none of the above conditions are met.
    return false;
}


/*
 * Write errors to stderr (or by equal means when stderr is
 * not available).
 */
void write_runlog(int elevel, const char* fmt, ...)
{
    va_list ap;         // Declare a va_list for variable argument processing.
    va_list bp;         // Another va_list for potential duplicate use.
    char errbuf[2048] = {0};    // Initialize an error buffer for log messages.
    char fmtBuffer[2048] = {0}; // Initialize a format buffer for log message formatting.
    int count = 0;      // Initialize a count variable to store the length of formatted messages.
    int ret = 0;        // Initialize a return code variable.
    bool output_to_server = false;  // Initialize a flag to determine whether to output to the server log.

    /* Get whether the record will be logged into the file. */
    output_to_server = is_log_level_output(elevel, log_min_messages);
    if (!output_to_server) {
        return;         // Return early if the log message shouldn't be written.
    }   

    /* Obtaining international texts. */
    fmt = _(fmt);       // Obtain internationalized text for the log message format.

    va_start(ap, fmt);  // Start variable argument processing with 'ap'.

    if (prefix_name != NULL && strcmp(prefix_name, "cm_ctl") == 0) {
        /* Skip the wait dot log and the line break log. */
        if (strcmp(fmt, ".") == 0) {
            (void)pthread_rwlock_wrlock(&dotCount_lock);
            dotCountNotZero = true; // Set a flag for dot count.
            (void)pthread_rwlock_unlock(&dotCount_lock);
            (void)vfprintf(stdout, fmt, ap); // Print a dot message to stdout.
            (void)fflush(stdout);    // Flush stdout.
            va_end(ap); // End variable argument processing.
            return;     // Return after printing the dot message.
        }

        /**
         * Log the record to std error.
         * 1. The log level is greater than the level "LOG", and the process name is "cm_ctl".
         * 2. The log file path was not initialized.
         */
        if (elevel >= LOG || sys_log_path[0] == '\0') {
            if (dotCountNotZero == true) {
                fprintf(stdout, "\n"); // Print a newline to stdout.
                (void)pthread_rwlock_wrlock(&dotCount_lock);
                dotCountNotZero = false; // Clear the dot count flag.
                (void)pthread_rwlock_unlock(&dotCount_lock);
            }

            /* Get the print out format. */
            ret = snprintf_s(fmtBuffer, sizeof(fmtBuffer), sizeof(fmtBuffer) - 1, "%s: %s", prefix_name, fmt);
            securec_check_ss_c(ret, "\0", "\0"); // Check for secure snprintf.
            va_copy(bp, ap); // Copy va_list to bp for reuse.
            (void)vfprintf(stdout, fmtBuffer, bp); // Print the formatted message to stdout.
            (void)fflush(stdout);    // Flush stdout.
            va_end(bp); // End variable argument processing for bp.
        }
    }

    /* Format the log record. */
    count = vsnprintf_s(errbuf, sizeof(errbuf), sizeof(errbuf) - 1, fmt, ap); // Format the log message.
    va_end(ap); // End variable argument processing.

    switch (log_destion_choice) {
        case LOG_DESTION_FILE:
            add_log_prefix(elevel, errbuf); // Add log prefix (timestamp, etc.) to the log message.
            write_log_file(errbuf, count); // Write the log message to a log file.
            break;

        default:
            break;
    }
}

/**
 * @brief This function extracts message components from a formatted error message and stores them in separate variables.
 *
 * @param errmsg_tmp - Pointer to a buffer to store the error message component.
 * @param errdetail_tmp - Pointer to a buffer to store the error detail component.
 * @param errmodule_tmp - Pointer to a buffer to store the error module component.
 * @param errcode_tmp - Pointer to a buffer to store the error code component.
 * @param fmt - The formatted error message containing message components.
 *
 * @return 0 on success, or an error code on failure.
 *
 * This function extracts different error message components (ERRMSG, ERRDETAIL, ERRMODULE, ERRCODE) from a formatted error message.
 * The formatted error message should include tags like "[ERRMSG]:", "[ERRDETAIL]:", "[ERRMODULE]:", and "[ERRCODE]:"
 * to specify the type of each component. It extracts the components based on these tags and stores them in the respective buffers.
 */
int add_message_string(char* errmsg_tmp, char* errdetail_tmp, char* errmodule_tmp, char* errcode_tmp, const char* fmt)
{
    int rcs = 0;
    char *p = NULL;
    char errbuf_tmp[BUF_LEN] = {0};

    // Copy the formatted error message to a temporary buffer.
    rcs = snprintf_s(errbuf_tmp, sizeof(errbuf_tmp), sizeof(errbuf_tmp) - 1, "%s", fmt);
    securec_check_intval(rcs, );

    // Check if "[ERRMSG]:" tag is present in the error message.
    if ((p = strstr(errbuf_tmp, "[ERRMSG]:")) != NULL) {
        // Extract and store the ERRMSG component.
        rcs = snprintf_s(errmsg_tmp, BUF_LEN, BUF_LEN - 1, "%s", fmt + strlen("[ERRMSG]:"));
    } else if ((p = strstr(errbuf_tmp, "[ERRDETAIL]:")) != NULL) {
        // Extract and store the ERRDETAIL component.
        rcs = snprintf_s(errdetail_tmp, BUF_LEN, BUF_LEN - 1, "%s", fmt);
    } else if ((p = strstr(errbuf_tmp, "[ERRMODULE]:")) != NULL) {
        // Extract and store the ERRMODULE component.
        rcs = snprintf_s(errmodule_tmp, BUF_LEN, BUF_LEN - 1, "%s", fmt + strlen("[ERRMODULE]:"));
    } else if ((p = strstr(errbuf_tmp, "[ERRCODE]:")) != NULL) {
        // Extract and store the ERRCODE component.
        rcs = snprintf_s(errcode_tmp, BUF_LEN, BUF_LEN - 1, "%s", fmt + strlen("[ERRCODE]:"));
    }
    securec_check_intval(rcs, );

    // Return success code.
    return 0;
}


int add_message_string(char* errmsg_tmp, char* errdetail_tmp, char* errmodule_tmp, char* errcode_tmp,
    char* errcause_tmp, char* erraction_tmp, const char* fmt)
{
    int rcs = 0;
    char *p = NULL;
    char errbuf_tmp[BUF_LEN] = {0};

    rcs = snprintf_s(errbuf_tmp, sizeof(errbuf_tmp), sizeof(errbuf_tmp) - 1, "%s", fmt);
    securec_check_intval(rcs, );
    if ((p = strstr(errbuf_tmp, "[ERRMSG]:")) != NULL) {
        rcs = snprintf_s(errmsg_tmp, BUF_LEN, BUF_LEN - 1, "%s", fmt + strlen("[ERRMSG]:"));
    } else if ((p = strstr(errbuf_tmp, "[ERRDETAIL]:")) != NULL) {
        rcs = snprintf_s(errdetail_tmp, BUF_LEN, BUF_LEN - 1, "%s", fmt);
    } else if ((p = strstr(errbuf_tmp, "[ERRMODULE]:")) != NULL) {
        rcs = snprintf_s(errmodule_tmp, BUF_LEN, BUF_LEN - 1, "%s", fmt + strlen("[ERRMODULE]:"));
    } else if ((p = strstr(errbuf_tmp, "[ERRCODE]:")) != NULL) {
        rcs = snprintf_s(errcode_tmp, BUF_LEN, BUF_LEN - 1, "%s", fmt + strlen("[ERRCODE]:"));
    } else if ((p = strstr(errbuf_tmp, "[ERRCAUSE]:")) != NULL) {
        rcs = snprintf_s(errcause_tmp, BUF_LEN, BUF_LEN - 1, "%s", fmt);
    } else if ((p = strstr(errbuf_tmp, "[ERRACTION]:")) != NULL) {
        rcs = snprintf_s(erraction_tmp, BUF_LEN, BUF_LEN - 1, "%s", fmt);
    }
    securec_check_intval(rcs, );
    return 0;
}


void add_log_prefix2(int elevel, const char* errmodule_tmp, const char* errcode_tmp, char* str)
{
    char errbuf_tmp[BUF_LEN * 3] = {0}; // Initialize a temporary character array for constructing the log message.
    errno_t rc; // Define an error code variable for string operations.
    int rcs; // Define an integer variable for return code.

    // Set up the log message with a timestamp and thread information.
    setup_formatted_log_time();

    /* unify log style */
    if (thread_name == NULL) {
        thread_name = ""; // If thread_name is NULL, set it to an empty string.
    }
    if (errmodule_tmp[0] && errcode_tmp[0]) {
        // Construct the log message with error module and error code if available.
        rcs = snprintf_s(errbuf_tmp,
            sizeof(errbuf_tmp),
            sizeof(errbuf_tmp) - 1,
            "%s tid=%ld %s [%s] %s %s: ",
            formatted_log_time,
            gettid(),
            thread_name,
            errmodule_tmp,
            errcode_tmp,
            log_level_int_to_string(elevel));
    } else {
        // Construct the log message without error module and error code.
        rcs = snprintf_s(errbuf_tmp,
            sizeof(errbuf_tmp),
            sizeof(errbuf_tmp) - 1,
            "%s tid=%ld %s %s: ",
            formatted_log_time,
            gettid(),
            thread_name,
            log_level_int_to_string(elevel));
    }
    securec_check_intval(rcs, );
    /* max message length less than 2048. */
    rc = strncat_s(errbuf_tmp, BUF_LEN * 3, str, BUF_LEN * 3 - strlen(errbuf_tmp));

    securec_check_c(rc, "\0", "\0");

    // Copy the constructed log message back to the original 'str'.
    rc = memcpy_s(str, BUF_LEN * 2, errbuf_tmp, BUF_LEN * 2 - 1);
    securec_check_c(rc, "\0", "\0");

    str[BUF_LEN * 2 - 1] = '\0'; // Null-terminate the final log message.
}


/*
 * Write errors to stderr (or by equal means when stderr is
 * not available).
 */
void write_runlog3(int elevel, const char* errmodule_tmp, const char* errcode_tmp, const char* fmt, ...) {
    va_list ap;          // Argument pointer for variadic arguments.
    va_list bp;          // Argument pointer for backup of variadic arguments.
    char errbuf[2048] = {0};     // Buffer to store the formatted error message.
    char fmtBuffer[2048] = {0}; // Buffer to store the formatted message format.
    int count = 0;        // Count of characters in the formatted log record.
    int ret = 0;          // Return code from snprintf_s.
    bool output_to server = false; // Flag to determine if the log record should be output to the server.

    /* Get whether the record will be logged into the file. */
    output_to_server = is_log_level_output(elevel, log_min_messages);

    if (!output_to_server) {
        return; // If log level doesn't meet the criteria, return without logging.
    }

    /* Obtaining international texts. */
    fmt = _(fmt); // Apply internationalization to the log message.

    va_start(ap, fmt); // Initialize the argument list.

    if (prefix_name != NULL && strcmp(prefix_name, "cm_ctl") == 0) {
        /* Skip the wait dot log and the line break log. */
        if (strcmp(fmt, ".") == 0) {
            (void)pthread_rwlock_wrlock(&dotCount_lock); // Acquire a write lock.
            dotCountNotZero = true; // Set a flag indicating dot count is not zero.
            (void)pthread_rwlock_unlock(&dotCount_lock); // Release the write lock.
            (void)vfprintf(stdout, fmt, ap); // Print the dot character to stdout.
            (void)fflush(stdout); // Flush stdout to ensure immediate display.
            va_end(ap); // Clean up the argument list.
            return; // Return after logging the dot character.
        }

        /**
         * Log the record to std error.
         * 1. The log level is greater than or equal to "LOG", and the process name is "cm_ctl".
         * 2. The log file path was not initialized.
         */
        if (elevel >= LOG || sys_log_path[0] == '\0') {
            if (dotCountNotZero == true) {
                fprintf(stdout, "\n"); // Print a newline character to stdout.
                (void)pthread_rwlock_wrlock(&dotCount_lock); // Acquire a write lock.
                dotCountNotZero = false; // Set a flag indicating dot count is zero.
                (void)pthread_rwlock_unlock(&dotCount_lock); // Release the write lock.
            }

            /* Get the print out format. */
            ret = snprintf_s(fmtBuffer, sizeof(fmtBuffer), sizeof(fmtBuffer) - 1, "%s: %s", prefix_name, fmt);
            securec_check_intval(ret, ); // Check for errors in snprintf_s.
            va_copy(bp, ap); // Create a backup of the argument list.
            (void)vfprintf(stdout, fmtBuffer, bp); // Print the formatted message to stdout.
            (void)fflush(stdout); // Flush stdout to ensure immediate display.
            va_end(bp); // Clean up the backup argument list.
        }
    }

    /* Format the log record. */
    count = vsnprintf_s(errbuf, sizeof(errbuf), sizeof(errbuf) - 1, fmt, ap); // Format the error message.
    securec_check_intval(count, ); // Check for errors in vsnprintf_s.
    va_end(ap); // Clean up the argument list.

    switch (log_destion_choice) {
        case LOG_DESTION_FILE:
            add_log_prefix2(elevel, errmodule_tmp, errcode_tmp, errbuf); // Add a log prefix to the error message.
            write_log_file(errbuf, count); // Write the error message to the log file.
            break;

        default:
            break;
    }
}


/*
 * Open a new logfile with proper permissions and buffering options.
 *
 * If allow_errors is true, we just log any open failure and return NULL
 * (with errno still correct for the fopen failure).
 * Otherwise, errors are treated as fatal.
 */
FILE* logfile_open(const char* log_path, const char* mode) {
    FILE* fh = NULL; // File handle for the opened logfile.
    mode_t oumask; // Original umask value.
    char log_file_name[MAXPGPATH] = {0}; // Buffer to store the logfile name.
    char log_temp_name[MAXPGPATH] = {0}; // Buffer to store temporary logfile name.
    char log_create_time[LOG_MAX_TIMELEN] = {0}; // Buffer to store the creation time of the logfile.
    DIR* dir = NULL; // Directory handle for log_path.
    struct dirent* de = NULL; // Directory entry structure.
    bool is_exist = false; // Flag indicating if a current log file exists.
    pg_time_t current_time; // Current system time.
    struct tm* systm = NULL; // Pointer to a time structure.
    char* name_ptr = NULL; // Pointer to the log file name in directory entry.
    errno_t rc = 0; // Error code for memset_s and snprintf_s.
    int ret = 0; // Return code for snprintf_s.

    if (log_path == NULL) {
        (void)printf("logfile_open, log file path is null.\n");
        return NULL; // If log_path is NULL, return NULL indicating an error.
    }

    /*
     * Note we do not let Log_file_mode disable IWUSR,
     * since we certainly want to be able to write the files ourselves.
     */
    oumask = umask((mode_t)((~(mode_t)(S_IRUSR | S_IWUSR | S_IXUSR)) & (S_IRWXU | S_IRWXG | S_IRWXO)));

    /* Find the current log file. */
    if ((dir = opendir(log_path)) == NULL) {
        printf(_("%s: opendir %s failed! \n"), prefix_name, log_path);
        return NULL; // Return NULL on opendir failure.
    }

    while ((de = readdir(dir)) != NULL) {
        /* Check if a current log file exists. */
        if (strstr(de->d_name, prefix_name) != NULL) {
            name_ptr = strstr(de->d_name, "-current.log");
            if (name_ptr != NULL) {
                name_ptr += strlen("-current.log");
                if ((*name_ptr) == '\0') {
                    is_exist = true;
                    break;
                }
            }
        }
    }

    rc = memset_s(log_file_name, MAXPGPATH, 0, MAXPGPATH); // Clear log_file_name buffer.
    securec_check_errno(rc, );

    if (!is_exist) {
        /* Create a new current log file name. */
        current_time = time(NULL);
        systm = localtime(&current_time);
        if (systm != NULL) {
            (void)strftime(log_create_time, LOG_MAX_TIMELEN, "-%Y-%m-%d_%H%M%S", systm);
        }
        ret = snprintf_s(log_temp_name, MAXPGPATH, MAXPGPATH - 1, "%s%s%s", prefix_name, log_create_time, curLogFileMark);
        securec_check_intval(ret, );
        ret = snprintf_s(log_file_name, MAXPGPATH, MAXPGPATH - 1, "%s/%s", log_path, log_temp_name);
        securec_check_intval(ret, );
    } else {
        /* If a log file exists, get its file name. */
        ret = snprintf_s(log_file_name, MAXPGPATH, MAXPGPATH - 1, "%s/%s", log_path, de->d_name);
        securec_check_intval(ret, );
    }

    (void)closedir(dir); // Close the directory.

    fh = fopen(log_file_name, mode); // Open the log file.

    (void)umask(oumask); // Restore the original umask.

    if (fh != NULL) {
        (void)setvbuf(fh, NULL, LBF_MODE, 0); // Set buffering options.

#ifdef WIN32
        /* Use CRLF line endings on Windows. */
        _setmode(_fileno(fh), _O_TEXT);
#endif
        /*
         * When the parent process (cm_agent) opens the cm_agent_xxx.log,
         * the child processes (cn\dn\gtm\cm_server) inherit the file handle
         * of the parent process. If the file is deleted and the child processes
         * are still running, the file handle will not be freed, taking up disk space.
         * To prevent this, we set the FD_CLOEXEC flag to the file, so that the child processes
         * don't inherit the file handle of the parent process.
         */
        if (SetFdCloseExecFlag(fh) == -1) {
            (void)printf("set file flag failed, filename:%s, errmsg: %s.\n", log_file_name, strerror(errno));
        }
    } else {
        int save_errno = errno;

        (void)printf("logfile_open could not open log file:%s %s.\n", log_file_name, strerror(errno));
        errno = save_errno;
    }

    /* Store the current log file name. */
    rc = memset_s(curLogFileName, MAXPGPATH, 0, MAXPGPATH);
    securec_check_errno(rc, );
    rc = strncpy_s(curLogFileName, MAXPGPATH, log_file_name, strlen(log_file_name));
    securec_check_errno(rc, );

    return fh; // Return the opened file handle.
}

/*
 * Initialize the log file system.
 *
 * This function initializes the necessary data structures and locks for the
 * log file system. It is typically called at the beginning of the program.
 *
 * Returns:
 * - 0 on success.
 *
 * Note:
 * - If initialization fails, the function will print an error message to
 *   stderr and exit the program with a non-zero status code.
 */

int logfile_init() {
    int rc;            // Return code for pthread_rwlock_init.
    errno_t rcs;       // Error code for memset_s.

    // Initialize the syslog_write_lock for thread-safe log writes.
    rc = pthread_rwlock_init(&syslog_write_lock, NULL);
    if (rc != 0) {
        fprintf(stderr, "logfile_init: Failed to initialize syslog_write_lock. Exiting.\n");
        exit(1);
    }

    // Initialize the dotCount_lock for controlling dot log output.
    rc = pthread_rwlock_init(&dotCount_lock, NULL);
    if (rc != 0) {
        fprintf(stderr, "logfile_init: Failed to initialize dotCount_lock. Exiting.\n");
        exit(1);
    }

    // Initialize sys_log_path to an empty string.
    rcs = memset_s(sys_log_path, MAX_PATH_LEN, 0, MAX_PATH_LEN);
    securec_check_c(rcs, "\0", "\0");

    return 0;
}


/*
 * Check if a given string represents a comment line.
 *
 * This function examines a string to determine if it represents a comment line
 * in a configuration file. Comment lines are lines that start with the '#' character.
 *
 * Parameters:
 * - str: A pointer to the input string to be checked.
 *
 * Returns:
 * - 1 if the input string is a comment line.
 * - 0 if the input string is not a comment line.
 *
 * Note:
 * - If the input string is NULL, the function prints an error message and exits with
 *   a status code of 1.
 */

int is_comment_line(const char* str) {
    size_t ii = 0; // Index for iterating through the input string.

    if (str == NULL) {
        printf("bad config file line\n");
        exit(1); // Print an error message and exit if the input string is NULL.
    }

    /* Skip leading spaces. */
    for (;;) {
        if (*(str + ii) == ' ') {
            ii++;  /* Skip blank spaces */
        } else {
            break; // Exit the loop when a non-space character is encountered.
        }
    }

    if (*(str + ii) == '#') {
        return 1;  // The input string is a comment line.
    }

    return 0;  // The input string is not a comment line.
}

/* 
 * Get the authentication type from a configuration file.
 *
 * This function reads the specified configuration file and retrieves the authentication type
 * setting from it. The authentication type determines how authentication is handled.
 *
 * Parameters:
 * - config_file: A pointer to the path of the configuration file to be read.
 *
 * Returns:
 * - The authentication type:
 *   - CM_AUTH_TRUST: If no authentication method is specified in the file or if the file is NULL.
 *   - CM_AUTH_GSS: If "gss" authentication method is specified in the file.
 *
 * Notes:
 * - If the specified configuration file cannot be opened, the function prints an error message
 *   and exits with a status code of 1.
 * - The function also calls the is_comment_line function to skip comment lines in the file.
 * - The authentication type is determined by searching for the "cm_auth_method" setting in the file.
 *   If "trust" is found, CM_AUTH_TRUST is returned; if "gss" is found, CM_AUTH_GSS is returned.
 *   If neither is found, CM_AUTH_TRUST is the default.
 */

int get_authentication_type(const char* config_file)
{
    char buf[BUF_LEN]; // Buffer for reading lines from the configuration file.
    FILE* fd = NULL; // File descriptor for the configuration file.
    int type = CM_AUTH_TRUST; // Default authentication type is trust.

    if (config_file == NULL) {
        return CM_AUTH_TRUST;  /* Default level: CM_AUTH_TRUST */
    }

    // Attempt to open the configuration file for reading.
    fd = fopen(config_file, "r");
    if (fd == NULL) {
        char errBuffer[ERROR_LIMIT_LEN];
        printf("Can not open config file: %s %s\n", config_file, pqStrerror(errno, errBuffer, ERROR_LIMIT_LEN));
        exit(1);
    }

    // Read each line from the configuration file.
    while (!feof(fd)) {
        errno_t rc;
        rc = memset_s(buf, BUF_LEN, 0, BUF_LEN); // Initialize the buffer to all zeros.
        securec_check_c(rc, "\0", "\0");
        (void)fgets(buf, BUF_LEN, fd); // Read a line from the file into the buffer.

        // Skip comment lines in the file using the is_comment_line function.
        if (is_comment_line(buf) == 1) {
            continue;  /* Skip lines that start with '#' (comments) */
        }

        // Check for the "cm_auth_method" setting in the file and update the authentication type accordingly.
        if (strstr(buf, "cm_auth_method") != NULL) {
            /* Check all lines */
            if (strstr(buf, "trust") != NULL) {
                type = CM_AUTH_TRUST; // Authentication method is trust.
            }

            if (strstr(buf, "gss") != NULL) {
                type = CM_AUTH_GSS; // Authentication method is gss.
            }
        }
    }

    fclose(fd); // Close the configuration file.
    return type; // Return the determined authentication type.
}


/*
 * Trim successive characters on both ends of a string.
 *
 * This function trims leading and trailing occurrences of a specified delimiter character from a string.
 *
 * Parameters:
 * - src: A pointer to the source string to be trimmed.
 * - delim: The delimiter character to be trimmed from the ends of the string.
 *
 * Returns:
 * - A pointer to the trimmed string, which is the same as the input string with leading and trailing delimiters removed.
 *
 * Notes:
 * - The function initializes pointers 's' and 'e' to NULL to keep track of the start and end of the trimmed part.
 * - It iterates through the source string and looks for delimiter characters at both ends.
 * - Leading delimiters are skipped until a non-delimiter character is encountered (pointed to by 's').
 * - Trailing delimiters are marked by 'e', and if found, the function replaces the first trailing delimiter with a null terminator.
 * - If there are no leading delimiters, 's' is set to the beginning of the source string.
 * - If there are no trailing delimiters, 'e' remains NULL.
 */

static char* TrimToken(char* src, const char& delim)
{
    char* s = NULL; // Pointer to the start of the trimmed string.
    char* e = NULL; // Pointer to the end of the trimmed string.
    char* c = NULL; // Pointer for iterating through the source string.

    for (c = src; (c != NULL) && *c; ++c) {
        if (*c == delim) {
            if (e == NULL) {
                e = c;
            }
        } else {
            if (s == NULL) {
                s = c;
            }
            e = NULL;
        }
    }

    if (s == NULL) {
        s = src;
    }

    if (e != NULL) {
        *e = 0; // Replace the first trailing delimiter with a null terminator.
    }

    return s; // Return a pointer to the trimmed string.
}


/*
 * Trim double-end quotes from a path string.
 *
 * This function removes leading and trailing single quotes (' ') and double quotes (" ") from a path string.
 *
 * Parameters:
 * - path: A pointer to the path string to be trimmed.
 *
 * Notes:
 * - The function first calculates the length of the input path string.
 * - If the length of the path exceeds MAXPGPATH - 1 (a defined limit), the function returns without modification.
 * - The function calls the TrimToken function twice to remove both single quotes and double quotes from the path.
 * - After trimming, the resulting path is stored in a temporary buffer 'buf' and then copied back to the original 'path'.
 *
 * Important:
 * - The caller must ensure that 'path' points to a valid null-terminated string.
 */

static void TrimPathDoubleEndQuotes(char* path)
{
    int pathLen = strlen(path); // Calculate the length of the input path.

    /* Make sure buf[MAXPGPATH] can copy the whole path, last '\0' included. */
    if (pathLen > MAXPGPATH - 1) {
        return; // If the path length exceeds the defined limit, return without modification.
    }

    char* pathTrimmed = NULL;
    
    // Trim single quotes (') and store the trimmed path in 'pathTrimmed'.
    pathTrimmed = TrimToken(path, '\'');
    
    // Trim double quotes (") from 'pathTrimmed' and store the final result back in 'pathTrimmed'.
    pathTrimmed = TrimToken(pathTrimmed, '\"');

    char buf[MAXPGPATH] = {0}; // Temporary buffer to store the trimmed path.
    errno_t rc = 0;

    // Copy the trimmed path from 'pathTrimmed' to 'buf'.
    rc = strncpy_s(buf, MAXPGPATH, pathTrimmed, strlen(pathTrimmed));
    securec_check_errno(rc, );

    // Copy the trimmed path from 'buf' back to the original 'path'.
    rc = strncpy_s(path, pathLen + 1, buf, strlen(buf));
    securec_check_errno(rc, );
}


/*
 * Get the Kerberos server keyfile path from a configuration file.
 *
 * This function reads the specified configuration file and retrieves the Kerberos server keyfile path
 * setting from it.
 *
 * Parameters:
 * - config_file: A pointer to the path of the configuration file to be read.
 *
 * Notes:
 * - The function initializes various variables for parsing and manipulation.
 * - If the input 'config_file' is NULL, the function returns without making any changes.
 * - If the configuration file cannot be opened, it prints an error message and exits with a status code of 1.
 * - The function iterates through the lines of the configuration file, looking for the "cm_krb_server_keyfile"
 *   setting.
 * - It extracts the keyfile path value, removes surrounding single quotes, and stores it in 'cm_krb_server_keyfile'.
 * - Leading and trailing whitespace is also trimmed from the keyfile path.
 * - After successfully extracting and processing the keyfile path, the function returns.
 */

void get_krb_server_keyfile(const char* config_file)
{
    char buf[MAXPGPATH]; // Buffer for reading lines from the configuration file.
    FILE* fd = NULL; // File descriptor for the configuration file.
    int ii = 0; // Index for iterating through characters in a string.

    char* subStr = NULL;
    char* subStr1 = NULL;
    char* subStr2 = NULL;
    char* subStr3 = NULL;

    char* saveptr1 = NULL;
    char* saveptr2 = NULL;
    char* saveptr3 = NULL;
    errno_t rc = 0;

    if (config_file == NULL) {
        return; // If 'config_file' is NULL, return without modification.
    } else {
        logInitFlag = true;
    }

    // Attempt to open the configuration file for reading.
    fd = fopen(config_file, "r");
    if (fd == NULL) {
        printf("get_krb_server_keyfile confDir error\n");
        exit(1); // Print an error message and exit with a status code of 1 if the file cannot be opened.
    }

    while (!feof(fd)) {
        rc = memset_s(buf, MAXPGPATH, 0, MAXPGPATH);
        securec_check_errno(rc, );

        (void)fgets(buf, MAXPGPATH, fd);
        buf[MAXPGPATH - 1] = 0;

        if (is_comment_line(buf) == 1) {
            continue;  /* Skip lines that start with '#' (comments) */
        }

        subStr = strstr(buf, "cm_krb_server_keyfile");
        if (subStr == NULL) {
            continue; // Continue to the next line if "cm_krb_server_keyfile" is not found.
        }

        subStr = strstr(subStr + 7, "=");
        if (subStr == NULL) {
            continue; // Continue to the next line if '=' is not found.
        }

        /* Check if '=' is the last character */
        if (subStr + 1 == 0) {
            continue; // Continue to the next line if '=' is the last character.
        }

        /* Skip leading blanks */
        ii = 1;
        for (;;) {
            if (*(subStr + ii) == ' ') {
                ii++;  /* Skip blank spaces */
            } else {
                break;
            }
        }
        subStr = subStr + ii;

        /* Begin checking for trailing blanks and extract the keyfile path */
        subStr1 = strtok_r(subStr, " ", &saveptr1);
        if (subStr1 == NULL) {
            continue; // Continue to the next line if no path value is found.
        }

        subStr2 = strtok_r(subStr1, "\n", &saveptr2);
        if (subStr2 == NULL) {
            continue; // Continue to the next line if no path value is found.
        }

        subStr3 = strtok_r(subStr2, "\r", &saveptr3);
        if (subStr3 == NULL) {
            continue; // Continue to the next line if no path value is found.
        }

        if (subStr3[0] == '\'') {
            subStr3 = subStr3 + 1; // Remove leading single quote.
        }
        if (subStr3[strlen(subStr3) - 1] == '\'') {
            subStr3[strlen(subStr3) - 1] = '\0'; // Remove trailing single quote.
        }
        if (strlen(subStr3) > 0) {
            rc = memcpy_s(cm_krb_server_keyfile, sizeof(sys_log_path), subStr3, strlen(subStr3) + 1);
            securec_check_errno(rc, );
        }
    }

    fclose(fd); // Close the configuration file.

    TrimPathDoubleEndQuotes(cm_krb_server_keyfile);

    return;  /* Default value warning */
}

/*
 * Get a string value associated with a specific configuration item from a configuration file.
 *
 * This function reads the specified configuration file and extracts the value associated with the
 * provided 'itemName' from it. The value is stored in 'itemValue'.
 *
 * Parameters:
 * - configFile: A pointer to the path of the configuration file to be read.
 * - itemValue: A pointer to the buffer where the extracted value will be stored.
 * - itemValueLength: The maximum length of the 'itemValue' buffer.
 * - itemName: The name of the configuration item whose value needs to be extracted.
 *
 * Notes:
 * - The function initializes various variables for parsing and manipulation.
 * - If the input 'configFile' is NULL, the function returns without making any changes.
 * - If the configuration file cannot be opened, it prints an error message mentioning the 'itemName' and exits with a status code of 1.
 * - The function iterates through the lines of the configuration file, searching for the 'itemName'.
 * - It extracts the value associated with 'itemName', removes surrounding single quotes, and stores it in 'itemValue'.
 * - Leading and trailing whitespace is also trimmed from the extracted value.
 * - If the value is empty or invalid, an error message is written to the runlog.
 */

void GetStringFromConf(const char* configFile, char* itemValue, size_t itemValueLength, const char* itemName)
{
    char buf[MAXPGPATH]; // Buffer for reading lines from the configuration file.
    FILE* fd = NULL; // File descriptor for the configuration file.
    int ii = 0; // Index for iterating through characters in a string.

    char* subStr = NULL;
    char* subStr1 = NULL;
    char* subStr2 = NULL;
    char* subStr3 = NULL;

    char* saveptr1 = NULL;
    char* saveptr2 = NULL;
    char* saveptr3 = NULL;
    errno_t rc = 0;

    if (configFile == NULL) {
        return; // If 'configFile' is NULL, return without modification.
    } else {
        logInitFlag = true;
    }

    // Attempt to open the configuration file for reading.
    fd = fopen(configFile, "r");
    if (fd == NULL) {
        printf("%s confDir error\n", itemName);
        exit(1); // Print an error message mentioning 'itemName' and exit with a status code of 1 if the file cannot be opened.
    }

    while (!feof(fd)) {
        rc = memset_s(buf, MAXPGPATH, 0, MAXPGPATH);
        securec_check_errno(rc, );

        (void)fgets(buf, MAXPGPATH, fd);
        buf[MAXPGPATH - 1] = 0;

        if (is_comment_line(buf) == 1) {
            continue;  /* Skip lines that start with '#' (comments) */
        }

        subStr = strstr(buf, itemName);
        if (subStr == NULL) {
            continue; // Continue to the next line if 'itemName' is not found.
        }

        subStr = strstr(subStr + strlen(itemName), "=");
        if (subStr == NULL) {
            continue; // Continue to the next line if '=' is not found.
        }

        if (subStr + 1 == 0) {
            continue;  /* '=' is the last character */
        }

        /* Skip leading blanks */
        ii = 1;
        for (;;) {
            if (*(subStr + ii) == ' ') {
                ii++;  /* Skip blank spaces */
            } else {
                break;
            }
        }
        subStr = subStr + ii;

        /* Begin checking for trailing blanks and extract the value */
        subStr1 = strtok_r(subStr, " ", &saveptr1);
        if (subStr1 == NULL) {
            continue; // Continue to the next line if no value is found.
        }

        subStr2 = strtok_r(subStr1, "\n", &saveptr2);
        if (subStr2 == NULL) {
            continue; // Continue to the next line if no value is found.
        }

        subStr3 = strtok_r(subStr2, "\r", &saveptr3);
        if (subStr3 == NULL) {
            continue; // Continue to the next line if no value is found.
        }
        if (subStr3[0] == '\'') {
            subStr3 = subStr3 + 1; // Remove leading single quote.
        }
        if (subStr3[strlen(subStr3) - 1] == '\'') {
            subStr3[strlen(subStr3) - 1] = '\0'; // Remove trailing single quote.
        }
        if (strlen(subStr3) > 0) {
            rc = memcpy_s(itemValue, itemValueLength, subStr3, strlen(subStr3) + 1);
            securec_check_errno(rc, );
        } else {
            write_runlog(ERROR, "invalid value for parameter \" %s \" in %s.\n", itemName, configFile);
        }
    }

    fclose(fd); // Close the configuration file.

    return;  /* Default value warning */
}


/*
 * Get the logging level from a configuration file.
 *
 * This function reads the specified configuration file and retrieves the logging level
 * setting from it. The logging level determines which messages are recorded in the logs.
 * It is used for both the cm_agent and cm_server components.
 *
 * Parameters:
 * - config_file: A pointer to the path of the configuration file to be read.
 *
 * Notes:
 * - If the input 'config_file' is NULL, the function returns without making any changes.
 * - If the configuration file cannot be opened, it prints an error message and exits with a status code of 1.
 * - The function iterates through the lines of the configuration file, looking for the "log_min_messages" setting.
 * - It checks various log levels (DEBUG5, DEBUG1, WARNING, ERROR, FATAL, LOG) in the configuration file,
 *   and sets the 'log_min_messages' global variable accordingly when a matching level is found.
 * - The search stops as soon as a valid log level is found.
 */

void get_log_level(const char* config_file)
{
    char buf[BUF_LEN]; // Buffer for reading lines from the configuration file.
    FILE* fd = NULL; // File descriptor for the configuration file.

    if (config_file == NULL) {
        return; // If 'config_file' is NULL, return without modification.
    } else {
        logInitFlag = true;
    }

    // Attempt to open the configuration file for reading.
    fd = fopen(config_file, "r");
    if (fd == NULL) {
        char errBuffer[ERROR_LIMIT_LEN];
        printf("Can not open config file: %s %s\n", config_file, pqStrerror(errno, errBuffer, ERROR_LIMIT_LEN));
        exit(1); // Print an error message and exit with a status code of 1 if the file cannot be opened.
    }

    while (!feof(fd)) {
        errno_t rc;
        rc = memset_s(buf, BUF_LEN, 0, BUF_LEN); // Initialize the buffer to all zeros.
        securec_check_c(rc, "\0", "\0");
        (void)fgets(buf, BUF_LEN, fd); // Read a line from the file into the buffer.

        if (is_comment_line(buf) == 1) {
            continue;  /* Skip lines that start with '#' (comments) */
        }

        if (strstr(buf, "log_min_messages") != NULL) {
            /* Check all lines */
            if (strcasestr(buf, "DEBUG5") != NULL) {
                log_min_messages = DEBUG5;
                break; // Stop searching when DEBUG5 level is found.
            }

            if (strcasestr(buf, "DEBUG1") != NULL) {
                log_min_messages = DEBUG1;
                break; // Stop searching when DEBUG1 level is found.
            }

            if (strcasestr(buf, "WARNING") != NULL) {
                log_min_messages = WARNING;
                break; // Stop searching when WARNING level is found.
            }

            if (strcasestr(buf, "ERROR") != NULL) {
                log_min_messages = ERROR;
                break; // Stop searching when ERROR level is found.
            }

            if (strcasestr(buf, "FATAL") != NULL) {
                log_min_messages = FATAL;
                break; // Stop searching when FATAL level is found.
            }

            if (strcasestr(buf, "LOG") != NULL) {
                log_min_messages = LOG;
                break; // Stop searching when LOG level is found.
            }
        }
    }

    fclose(fd); // Close the configuration file.
    return;  /* Default value warning */
}


/* 
 * Get the build mode from a configuration file.
 *
 * This function is used for the cm_agent component. It reads the specified configuration file
 * and retrieves the build mode setting from it. The build mode determines whether incremental
 * builds are enabled or disabled.
 *
 * Parameters:
 * - config_file: A pointer to the path of the configuration file to be read.
 *
 * Notes:
 * - If the input 'config_file' is NULL, the function returns without making any changes.
 * - If the configuration file cannot be opened, it prints an error message and exits with a
 *   status code of 1.
 * - The function iterates through the lines of the configuration file, looking for the
 *   "incremental_build" setting.
 * - It checks for "on" and "off" values for the "incremental_build" parameter in the configuration
 *   file and sets the 'incremental_build' global variable accordingly.
 * - If an invalid value is encountered for the "incremental_build" parameter, it sets the value
 *   to 'true' and logs a fatal error message.
 */

void get_build_mode(const char* config_file)
{
    char buf[BUF_LEN]; // Buffer for reading lines from the configuration file.
    FILE* fd = NULL;   // File descriptor for the configuration file.

    if (config_file == NULL) {
        return; // If 'config_file' is NULL, return without modification.
    }

    // Attempt to open the configuration file for reading.
    fd = fopen(config_file, "r");
    if (fd == NULL) {
        char errBuffer[ERROR_LIMIT_LEN];
        printf("can not open config file: %s %s\n", config_file, pqStrerror(errno, errBuffer, ERROR_LIMIT_LEN));
        exit(1); // Print an error message and exit with a status code of 1 if the file cannot be opened.
    }

    while (!feof(fd)) {
        errno_t rc;
        rc = memset_s(buf, BUF_LEN, 0, BUF_LEN); // Initialize the buffer to all zeros.
        securec_check_c(rc, "\0", "\0");
        (void)fgets(buf, BUF_LEN, fd); // Read a line from the file into the buffer.

        // Skip lines that start with '#' (comments).
        if (is_comment_line(buf) == 1) {
            continue;
        }

        // Check for the "incremental_build" setting.
        if (strstr(buf, "incremental_build") != NULL) {
            if (strstr(buf, "on") != NULL) {
                incremental_build = true; // Enable incremental builds.
            } else if (strstr(buf, "off") != NULL) {
                incremental_build = false; // Disable incremental builds.
            } else {
                incremental_build = true; // Default to enabling incremental builds.
                write_runlog(FATAL, "invalid value for parameter \"incremental_build\" in %s.\n", config_file);
            }
        }
    }

    fclose(fd); // Close the configuration file.
    return;
}


/* 
 * Get the log file size setting from a configuration file.
 *
 * This function is used for both the cm_agent and cm_server components. It reads the specified
 * configuration file and retrieves the log file size setting from it. The log file size determines
 * the maximum size, in bytes, of the log files.
 *
 * Parameters:
 * - config_file: A pointer to the path of the configuration file to be read.
 *
 * Notes:
 * - If the input 'config_file' is NULL, the function returns with the default log file size.
 * - If the configuration file cannot be opened, it prints an error message and exits with a
 *   status code of 1.
 * - The function iterates through the lines of the configuration file, looking for the
 *   "log_file_size" setting.
 * - It checks the first line that contains "log_file_size" and parses the value following the "="
 *   sign.
 * - The parsed value is converted to an integer and represents the maximum log file size in bytes.
 * - If an invalid value is encountered for the "log_file_size" parameter, it logs an error message
 *   and exits with a status code of 1.
 */

void get_log_file_size(const char* config_file)
{
    char buf[BUF_LEN]; // Buffer for reading lines from the configuration file.
    FILE* fd = NULL;   // File descriptor for the configuration file.

    if (config_file == NULL) {
        return;  // Default value warning.
    } else {
        logInitFlag = true;
    }

    // Attempt to open the configuration file for reading.
    fd = fopen(config_file, "r");
    if (fd == NULL) {
        printf("get_log_file_size error\n");
        exit(1);  // Print an error message and exit with a status code of 1 if the file cannot be opened.
    }

    while (!feof(fd)) {
        errno_t rc;
        rc = memset_s(buf, BUF_LEN, 0, BUF_LEN); // Initialize the buffer to all zeros.
        securec_check_c(rc, "\0", "\0");
        (void)fgets(buf, BUF_LEN, fd); // Read a line from the file into the buffer.

        if (is_comment_line(buf) == 1) {
            continue;  // Skip lines that start with '#' (comments).
        }

        if (strstr(buf, "log_file_size") != NULL) {
            // Only check the first line.
            char* subStr = NULL;
            char countStr[COUNTSTR_LEN] = {0};
            int ii = 0;
            int jj = 0;

            subStr = strchr(buf, '=');
            if (subStr != NULL) {
                // Find '='.
                ii = 1;  // 1 is '='.

                // Skip blank.
                for (;;) {
                    if (*(subStr + ii) == ' ') {
                        ii++;  // Skip blank.
                    } else if (*(subStr + ii) >= '0' && *(subStr + ii) <= '9') {
                        break;  // Number found, break.
                    } else {
                        // Invalid character.
                        goto out;
                    }
                }

                while (*(subStr + ii) >= '0' && *(subStr + ii) <= '9') {
                    // End when no more numbers.
                    if (jj > (int)sizeof(countStr) - 2) {
                        printf("too large log file size.\n");
                        exit(1);
                    } else {
                        countStr[jj] = *(subStr + ii);
                    }

                    ii++;
                    jj++;
                }
                countStr[jj] = 0;  // jj may have added itself, terminate the string.

                if (countStr[0] != 0) {
                    maxLogFileSize = atoi(countStr) * 1024 * 1024;  // Convert to bytes.
                } else {
                    write_runlog(ERROR, "invalid value for parameter \"log_file_size\" in %s.\n", config_file);
                }
            }
        }
    }

out:
    fclose(fd);  // Close the configuration file.
    return;  // Default value is warning.
}

/* 
 * Get the thread count setting from a configuration file.
 *
 * This function retrieves the thread count setting from the specified configuration file,
 * which is used for configuring the number of threads for the cm_agent and cm_server components.
 * The thread count determines how many threads are used for concurrent processing.
 *
 * Parameters:
 * - config_file: A pointer to the path of the configuration file to be read.
 *
 * Returns:
 * An integer representing the thread count. If the configuration file is not found or an
 * invalid value is encountered, the default thread count of 5 is returned.
 *
 * Notes:
 * - If the input 'config_file' is NULL, the function prints an error message and exits with a
 *   status code of 1.
 * - If the configuration file cannot be opened, the function prints an error message and exits
 *   with a status code of 1.
 * - The function iterates through the lines of the configuration file, looking for the
 *   "thread_count" setting.
 * - It checks the first line that contains "thread_count" and parses the value following the "="
 *   sign.
 * - The parsed value is converted to an integer and represents the desired thread count.
 * - If an invalid value is encountered for the "thread_count" parameter, the function prints an
 *   error message and exits with a status code of 1.
 * - The valid thread count range is between 2 and 1000.
 */

int get_cm_thread_count(const char* config_file)
{
    #define DEFAULT_THREAD_NUM 5

    char buf[BUF_LEN]; // Buffer for reading lines from the configuration file.
    FILE* fd = NULL;   // File descriptor for the configuration file.
    int thread_count = DEFAULT_THREAD_NUM; // Default thread count.
    errno_t rc = 0; // Error code for secure functions.

    if (config_file == NULL) {
        printf("no cmserver config file! exit.\n");
        exit(1); // Print an error message and exit with a status code of 1 if 'config_file' is NULL.
    }

    // Attempt to open the configuration file for reading.
    fd = fopen(config_file, "r");
    if (fd == NULL) {
        printf("open cmserver config file: %s, error: %m\n", config_file);
        exit(1); // Print an error message and exit with a status code of 1 if the file cannot be opened.
    }

    while (!feof(fd)) {
        rc = memset_s(buf, sizeof(buf), 0, sizeof(buf)); // Initialize the buffer to all zeros.
        securec_check_errno(rc, ); // Check for errors in memset_s.
        (void)fgets(buf, BUF_LEN, fd); // Read a line from the file into the buffer.

        if (is_comment_line(buf) == 1) {
            continue; // Skip lines that start with '#' (comments).
        }

        if (strstr(buf, "thread_count") != NULL) {
            // Only check the first line.
            char* subStr = NULL;
            char countStr[COUNTSTR_LEN] = {0};
            int ii = 0;
            int jj = 0;

            subStr = strchr(buf, '='); // Find '='.
            if (subStr != NULL) {
                ii = 1; // 1 is '='.

                // Skip blank.
                for (;;) {
                    if (*(subStr + ii) == ' ') {
                        ii++; // Skip blank.
                    } else if (*(subStr + ii) >= '0' && *(subStr + ii) <= '9') {
                        break; // Number found, break.
                    } else {
                        // Invalid character.
                        goto out;
                    }
                }

                // End when no number.
                while (*(subStr + ii) >= '0' && *(subStr + ii) <= '9') {
                    if (jj > (int)sizeof(countStr) - 2) {
                        printf("too large thread count.\n");
                        exit(1);
                    } else {
                        countStr[jj] = *(subStr + ii);
                    }

                    ii++;
                    jj++;
                }
                countStr[jj] = 0; // jj may have added itself, terminate the string.

                if (countStr[0] != 0) {
                    thread_count = atoi(countStr);

                    if (thread_count < 2 || thread_count > 1000) {
                        printf("invalid thread count %d, range [2 - 1000].\n", thread_count);
                        exit(1);
                    }
                } else {
                    thread_count = DEFAULT_THREAD_NUM;
                }
            }
        }
    }

out:
    fclose(fd); // Close the configuration file.
    return thread_count; // Return the thread count.
}

/*
 * @Description: Get the value of a parameter from a configuration file.
 *
 * This function reads the specified configuration file and retrieves the value associated with
 * the provided 'key'. If the 'key' is found in the configuration file, its corresponding value
 * is returned as an integer. If the 'key' is not found or if the value is not a valid integer,
 * the 'defaultValue' is returned.
 *
 * Parameters:
 * - config_file: A pointer to the path of the configuration file to be read.
 * - key: The name of the parameter whose value is to be retrieved from the configuration file.
 * - defaultValue: The default value to be returned if the 'key' is not found or if the value
 *   is not a valid integer.
 *
 * Returns:
 * An integer representing the value of the parameter 'key' if it is found in the configuration
 * file and is a valid integer. If the 'key' is not found or the value is not a valid integer,
 * the 'defaultValue' is returned.
 *
 * Note:
 * - If the input 'config_file' or 'key' is NULL, or if the configuration file cannot be opened,
 *   this function returns the 'defaultValue'.
 * - This function first calls 'get_int64_value_from_config' to retrieve the value as a 64-bit
 *   integer. If the value is within the valid range for 32-bit integers (INT_MIN to INT_MAX),
 *   it is cast to an integer and returned; otherwise, the 'defaultValue' is returned.
 */

int get_int_value_from_config(const char* config_file, const char* key, int defaultValue)
{
    int64 i64 = get_int64_value_from_config(config_file, key, defaultValue);
    if (i64 > INT_MAX) {
        return defaultValue; // Return the 'defaultValue' if the value is too large for an integer.
    } else if (i64 < INT_MIN) {
        return defaultValue; // Return the 'defaultValue' if the value is too small for an integer.
    }

    return (int)i64; // Cast and return the value as an integer.
}


/*
 * @Description: Get the value of a parameter from a configuration file.
 *
 * This function reads the specified configuration file and retrieves the value associated with
 * the provided 'key'. If the 'key' is found in the configuration file, its corresponding value
 * is returned as a 32-bit unsigned integer (uint32). If the 'key' is not found or if the value
 * is not a valid non-negative integer, the 'defaultValue' is returned.
 *
 * Parameters:
 * - config_file: A pointer to the path of the configuration file to be read, a string.
 * - key: The name of the parameter whose value is to be retrieved from the configuration file, a string.
 * - defaultValue: The default value to be returned if the 'key' is not found or if the value
 *   is not a valid non-negative integer, a uint32 value.
 *
 * Returns:
 * A 32-bit unsigned integer (uint32) representing the value of the parameter 'key' if it is found
 * in the configuration file and is a valid non-negative integer. If the 'key' is not found or the
 * value is not a valid non-negative integer, the 'defaultValue' is returned.
 *
 * Note:
 * - If the input 'config_file' or 'key' is NULL, or if the configuration file cannot be opened,
 *   this function returns the 'defaultValue'.
 * - This function first calls 'get_int64_value_from_config' to retrieve the value as a 64-bit integer.
 *   If the value is within the valid range for a 32-bit non-negative integer (0 to UINT_MAX), it is
 *   cast to a uint32 and returned; otherwise, the 'defaultValue' is returned.
 */

uint32 get_uint32_value_from_config(const char* config_file, const char* key, uint32 defaultValue)
{
    int64 i64 = get_int64_value_from_config(config_file, key, defaultValue);
    if (i64 > UINT_MAX) {
        return defaultValue; // Return the 'defaultValue' if the value is too large for a uint32.
    } else if (i64 < 0) {
        return defaultValue; // Return the 'defaultValue' if the value is negative.
    }

    return (uint32)i64; // Cast and return the value as a uint32.
}

/*
 * @Description: Get the value of a parameter from a configuration file.
 *
 * This function reads the specified configuration file and retrieves the value associated with
 * the provided 'key'. If the 'key' is found in the configuration file, its corresponding value
 * is returned as a 64-bit signed integer (int64). If the 'key' is not found or if the value is
 * not a valid integer, the 'defaultValue' is returned.
 *
 * Parameters:
 * - config_file: A pointer to the path of the configuration file to be read, a string.
 * - key: The name of the parameter whose value is to be retrieved from the configuration file, a string.
 * - defaultValue: The default value to be returned if the 'key' is not found or if the value
 *   is not a valid integer, an int64 value.
 *
 * Returns:
 * A 64-bit signed integer (int64) representing the value of the parameter 'key' if it is found
 * in the configuration file and is a valid integer. If the 'key' is not found or the value is
 * not a valid integer, the 'defaultValue' is returned.
 *
 * Note:
 * - If the input 'config_file' or 'key' is NULL, or if the configuration file cannot be opened,
 *   this function returns the 'defaultValue'.
 * - The function reads lines from the configuration file and checks for 'key' assignments in the
 *   format 'key=value'. It extracts the value portion as an integer.
 * - If the value is not a valid integer, it is ignored, and the 'defaultValue' is returned.
 * - Comment lines starting with '#' are skipped.
 */

int64 get_int64_value_from_config(const char* config_file, const char* key, int64 defaultValue)
{
    char buf[BUF_LEN];
    FILE* fd = NULL;
    int64 int64Value = defaultValue;
    errno_t rc = 0;

    Assert(key);
    if (config_file == NULL) {
        printf("no config file! exit.\n");
        exit(1);
    }

    fd = fopen(config_file, "r");
    if (fd == NULL) {
        char errBuffer[ERROR_LIMIT_LEN];
        printf("open config file failed:%s ,error:%s\n", config_file, pqStrerror(errno, errBuffer, ERROR_LIMIT_LEN));
        exit(1);
    }

    while (!feof(fd)) {
        rc = memset_s(buf, sizeof(buf), 0, sizeof(buf));
        securec_check_errno(rc, );
        (void)fgets(buf, BUF_LEN, fd);

        if (is_comment_line(buf) == 1) {
            continue;  /* Skip # comment lines */
        }

        if (strstr(buf, key) != NULL) {
            /* Check only the first line */
            char* subStr = NULL;
            char countStr[COUNTSTR_LEN] = {0};
            int ii = 0;
            int jj = 0;

            subStr = strchr(buf, '=');
            if (subStr != NULL) {
                /* Find '=' */
                ii = 1;

                /* Skip blanks */
                while (1) {
                    if (*(subStr + ii) == ' ') {
                        ii++;  /* Skip blanks */
                    } else if (isdigit(*(subStr + ii))) {
                        /* Number found, break */
                        break;
                    } else {
                        /* Invalid character, exit */
                        goto out;
                    }
                }

                while (isdigit(*(subStr + ii))) {
                    /* End when no more numbers */
                    if (jj >= COUNTSTR_LEN - 1) {
                        write_runlog(ERROR, "Length is not enough for constr\n");
                        goto out;
                    }
                    countStr[jj] = *(subStr + ii);

                    ii++;
                    jj++;
                }
                countStr[jj] = 0; /* Null-terminate the string */

                if (countStr[0] != 0) {
                    int64Value = strtoll(countStr, NULL, 10);
                }
                break;
            }
        }
    }

out:
    fclose(fd);
    return int64Value;
}


#define ALARM_REPORT_INTERVAL "alarm_report_interval"
#define ALARM_REPORT_INTERVAL_DEFAULT 10

#define ALARM_REPORT_MAX_COUNT "alarm_report_max_count"
#define ALARM_REPORT_MAX_COUNT_DEFAULT 5

/*
 * @Description: Trim blank characters from the beginning and end of a string.
 *
 * This function takes a string as input and removes any leading and trailing whitespace characters.
 *
 * Parameters:
 * - src: The input string to be trimmed.
 *
 * Returns:
 * A pointer to the first non-whitespace character within the input string 'src'.
 *
 * Note:
 * - The input string 'src' is modified in place to remove leading and trailing whitespace.
 * - The function returns a pointer to the modified string.
 */

char* trim(char* src)
{
    char* s = 0;  // Pointer to the start of non-whitespace characters.
    char* e = 0;  // Pointer to the end of whitespace characters.
    char* c = 0;  // Pointer used for iteration through the string.

    for (c = src; (c != NULL) && *c; ++c) {
        if (isspace(*c)) {
            if (e == NULL) {
                e = c;  // Mark the end of whitespace.
            }
        } else {
            if (s == NULL) {
                s = c;  // Mark the start of non-whitespace.
            }
            e = 0;  // Reset end pointer.
        }
    }
    
    if (s == NULL) {
        s = src;  // If there were no non-whitespace characters, start pointer remains at the beginning.
    }
    if (e != NULL) {
        *e = 0;  // Null-terminate the string at the end of whitespace.
    }

    return s;  // Return a pointer to the modified string.
}


/*
 * @Description: Check if a given line is a comment line in the context of cm_server.conf file.
 *
 * This function checks whether a provided string line is a comment line within the context
 * of the cm_server.conf configuration file. Comment lines are typically lines that start with
 * a '#' character and are used to add comments or notes in configuration files.
 *
 * Parameters:
 * - str_line: The input string line to be checked for being a comment line, a character array.
 *
 * Returns:
 * A boolean value indicating whether the input line is a comment line (true) or not (false).
 *
 * Note:
 * - Comment lines in configuration files are used for documentation and are usually ignored
 *   by the configuration parser.
 * - The function first checks if the input line is empty or NULL and considers it not a comment.
 * - It then trims any leading and trailing whitespace from the line to ensure accurate detection.
 * - If the trimmed line starts with a '#' character, it is considered a comment line and returns true.
 * - Otherwise, it returns false, indicating that the line is not a comment.
 */

static bool is_comment_entity(char* str_line)
{
    char* src = NULL;

    if (str_line == NULL || strlen(str_line) < 1) {
        return false;  // Empty or NULL lines are not considered comment lines.
    }

    src = str_line;
    src = trim(src);

    if (src == NULL || strlen(src) < 1) {
        return true;  // After trimming, if the line is empty, it is considered a comment line.
    }

    if (*src == '#') {
        return true;  // Lines starting with '#' character are considered comment lines.
    }

    return false;  // If none of the above conditions are met, it's not a comment line.
}

/*
 * @Description: Check if a given string consists of only numeric digits.
 *
 * This function determines whether a provided string contains only numeric digits (0-9).
 *
 * Parameters:
 * - str: The input string to be checked for being a numeric digit string, a character array.
 *
 * Returns:
 * 1 if the input string consists of only numeric digits, 0 otherwise.
 *
 * Note:
 * - The function checks each character in the input string and verifies if it is a numeric digit.
 * - It returns 1 if all characters in the string are numeric digits.
 * - If the input string is NULL or empty, or if any character is not a digit, it returns 0.
 */

int is_digit_string(char* str)
{
#define isDigital(_ch) (((_ch) >= '0') && ((_ch) <= '9'))

    int i = 0;
    int len = -1;
    char* p = NULL;
    if (str == NULL) {
        return 0;  // Return 0 if the input string is NULL.
    }
    if ((len = strlen(str)) <= 0) {
        return 0;  // Return 0 if the input string is empty.
    }
    p = str;
    for (i = 0; i < len; i++) {
        if (!isDigital(p[i])) {
            return 0;  // Return 0 if a non-digit character is found in the string.
        }
    }
    return 1;  // Return 1 if the input string consists of only numeric digits.
}

/*
 * @Description: Read and retrieve alarm parameters from a configuration file.
 *
 * This function reads the specified configuration file ('config_file') and extracts alarm-related
 * parameters, such as the alarm report interval, from it. The extracted values are then used
 * to configure the alarm system.
 *
 * Parameters:
 * - config_file: A pointer to the path of the configuration file to be read, a string.
 *
 * Note:
 * - The function opens and reads the configuration file line by line, searching for relevant
 *   parameters and their values.
 * - Comment lines (lines starting with '#') are ignored during processing.
 * - The function trims leading and trailing whitespace from parameter names and values.
 * - When it finds the 'ALARM_REPORT_INTERVAL' parameter, it checks if the associated value is a
 *   valid numeric string and assigns it to 'g_alarmReportInterval'. If the value is not a valid
 *   numeric string or is -1, the 'ALARM_REPORT_INTERVAL_DEFAULT' is used.
 * - The function stops reading the file once the 'ALARM_REPORT_INTERVAL' parameter is found.
 */

static void get_alarm_parameters(const char* config_file)
{
    char buf[BUF_LEN] = {0};     // Buffer for reading lines from the configuration file.
    FILE* fd = NULL;             // File descriptor for the configuration file.
    char* index1 = NULL;         // Pointer to the '#' character in the line.
    char* index2 = NULL;         // Pointer to the '=' character in the line.
    char* src = NULL;            // Pointer to the current line being processed.
    char* key = NULL;            // Pointer to the extracted parameter name.
    char* value = NULL;          // Pointer to the extracted parameter value.
    errno_t rc = 0;             // Error code variable for safe C library functions.

    if (config_file == NULL) {
        return;  // If 'config_file' is NULL, return without further processing.
    }

    fd = fopen(config_file, "r");
    if (fd == NULL) {
        return;  // If the file cannot be opened, return without further processing.
    }

    while (!feof(fd)) {
        rc = memset_s(buf, BUF_LEN, 0, BUF_LEN);  // Clear the buffer before reading a new line.
        securec_check_c(rc, "\0", "\0");
        (void)fgets(buf, BUF_LEN, fd);  // Read a line from the configuration file.

        if (is_comment_entity(buf) == true) {
            continue;  // Skip comment lines.
        }
        index1 = strchr(buf, '#');  // Find the '#' character to mark the start of comments.
        if (index1 != NULL) {
            *index1 = '\0';  // Null-terminate the line at the '#' character to remove comments.
        }
        index2 = strchr(buf, '=');  // Find the '=' character to separate parameter and value.
        if (index2 == NULL) {
            continue;  // If no '=' character is found, skip this line.
        }
        src = buf;         // Initialize 'src' pointer to the beginning of the line.
        src = trim(src);   // Trim leading and trailing whitespace from the line.
        index2 = strchr(src, '=');  // Find '=' character in trimmed line.
        key = src;          // Set 'key' pointer to the trimmed line as the parameter name.
        value = index2 + 1;  // Set 'value' pointer to the part of the line after '='.

        key = trim(key);    // Trim leading and trailing whitespace from parameter name.
        value = trim(value);  // Trim leading and trailing whitespace from parameter value.

        if (strncmp(key, ALARM_REPORT_INTERVAL, strlen(ALARM_REPORT_INTERVAL)) == 0) {
            if (is_digit_string(value)) {
                g_alarmReportInterval = atoi(value);  // Convert value to integer.
                if (g_alarmReportInterval == -1) {
                    g_alarmReportInterval = ALARM_REPORT_INTERVAL_DEFAULT;
                }
            }
            break;  // Stop reading the file once 'ALARM_REPORT_INTERVAL' is found.
        }
    }
    fclose(fd);  // Close the configuration file.
}


/*
 * @Description: Read and retrieve the maximum alarm report count from a configuration file.
 *
 * This function reads the specified configuration file ('config_file') and extracts the maximum
 * alarm report count parameter from it. The extracted value is then used to configure the alarm system.
 *
 * Parameters:
 * - config_file: A pointer to the path of the configuration file to be read, a string.
 *
 * Note:
 * - The function opens and reads the configuration file line by line, searching for the 'ALARM_REPORT_MAX_COUNT'
 *   parameter and its value.
 * - Comment lines (lines starting with '#') are ignored during processing.
 * - The function trims leading and trailing whitespace from parameter names and values.
 * - When it finds the 'ALARM_REPORT_MAX_COUNT' parameter, it checks if the associated value is a
 *   valid numeric string and assigns it to 'g_alarmReportMaxCount'. If the value is not a valid
 *   numeric string or is -1, the 'ALARM_REPORT_MAX_COUNT_DEFAULT' is used.
 * - The function stops reading the file once the 'ALARM_REPORT_MAX_COUNT' parameter is found.
 */

static void get_alarm_report_max_count(const char* config_file)
{
    char buf[BUF_LEN] = {0};     // Buffer for reading lines from the configuration file.
    FILE* fd = NULL;             // File descriptor for the configuration file.
    char* index1 = NULL;         // Pointer to the '#' character in the line.
    char* index2 = NULL;         // Pointer to the '=' character in the line.
    char* src = NULL;            // Pointer to the current line being processed.
    char* key = NULL;            // Pointer to the extracted parameter name.
    char* value = NULL;          // Pointer to the extracted parameter value.
    errno_t rc = 0;             // Error code variable for safe C library functions.

    if (config_file == NULL) {
        return;  // If 'config_file' is NULL, return without further processing.
    }

    fd = fopen(config_file, "r");
    if (fd == NULL) {
        return;  // If the file cannot be opened, return without further processing.
    }

    while (!feof(fd)) {
        rc = memset_s(buf, BUF_LEN, 0, BUF_LEN);  // Clear the buffer before reading a new line.
        securec_check_c(rc, "\0", "\0");
        (void)fgets(buf, BUF_LEN, fd);  // Read a line from the configuration file.

        if (is_comment_entity(buf) == true) {
            continue;  // Skip comment lines.
        }
        index1 = strchr(buf, '#');  // Find the '#' character to mark the start of comments.
        if (index1 != NULL) {
            *index1 = '\0';  // Null-terminate the line at the '#' character to remove comments.
        }
        index2 = strchr(buf, '=');  // Find the '=' character to separate parameter and value.
        if (index2 == NULL) {
            continue;  // If no '=' character is found, skip this line.
        }
        src = buf;         // Initialize 'src' pointer to the beginning of the line.
        src = trim(src);   // Trim leading and trailing whitespace from the line.
        index2 = strchr(src, '=');  // Find '=' character in trimmed line.
        key = src;          // Set 'key' pointer to the trimmed line as the parameter name.
        value = index2 + 1;  // Set 'value' pointer to the part of the line after '='.

        key = trim(key);    // Trim leading and trailing whitespace from parameter name.
        value = trim(value);  // Trim leading and trailing whitespace from parameter value.

        if (strncmp(key, ALARM_REPORT_MAX_COUNT, strlen(ALARM_REPORT_MAX_COUNT)) == 0) {
            if (is_digit_string(value)) {
                g_alarmReportMaxCount = atoi(value);  // Convert value to integer.
                if (g_alarmReportMaxCount == -1) {
                    g_alarmReportMaxCount = ALARM_REPORT_MAX_COUNT_DEFAULT;
                }
            }
            break;  // Stop reading the file once 'ALARM_REPORT_MAX_COUNT' is found.
        }
    }
    fclose(fd);  // Close the configuration file.
}

/*
 * This function is responsible for reading parameters from the 'cm_server.conf' configuration file
 * that have been applied on the server side.
 *
 * In the current implementation within 'cm_server', this function is considered suboptimal and
 * should be rewritten in the next version for improved efficiency and clarity.
 *
 * Parameters:
 * - conf: A pointer to the path of the 'cm_server.conf' configuration file to be read, represented as a string.
 */
static void get_alarm_report_interval(const char* conf)
{
    // Calls a function (get_alarm_parameters) to retrieve alarm parameters from the configuration file.
    get_alarm_parameters(conf);
}

/*
 * This function is responsible for retrieving various log-related parameters from a configuration directory.
 *
 * It obtains and sets the log level, log file size, system log path, alarm component path, alarm report
 * interval, and alarm report maximum count from the provided 'confDir'.
 *
 * Parameters:
 * - confDir: A pointer to the path of the configuration directory containing log-related settings, as a string.
 */
void get_log_paramter(const char* confDir)
{
    // Retrieves and sets the log level from the configuration directory.
    get_log_level(confDir);

    // Retrieves and sets the log file size from the configuration directory.
    get_log_file_size(confDir);

    // Retrieves and sets the system log path from the configuration directory.
    GetStringFromConf(confDir, sys_log_path, sizeof(sys_log_path), "log_dir");

    // Retrieves and sets the alarm component path from the configuration directory.
    GetStringFromConf(confDir, g_alarmComponentPath, sizeof(g_alarmComponentPath), "alarm_component");

    // Calls the function to retrieve and set the alarm report interval from the configuration directory.
    get_alarm_report_interval(confDir);

    // Calls the function to retrieve and set the alarm report maximum count from the configuration directory.
    get_alarm_report_max_count(confDir);
}

/*
 * @GaussDB@
 * Brief: Close the current file and open the next file.
 * Description: This function is responsible for closing the current log file and opening a new one.
 *              It renames the current log file without any special marks, appends a timestamp
 *              to the filename, and then opens the new log file for writing. It also handles setting
 *              file permissions and error reporting.
 * Notes: None
 */

void switchLogFile(void)
{
    char log_new_name[MAXPGPATH] = {0};            // Buffer for the new log file name.
    mode_t oumask;                                 // Original umask value.
    char current_localtime[LOG_MAX_TIMELEN] = {0}; // Buffer for the current timestamp in the filename.
    pg_time_t current_time;                        // Current time.
    struct tm* systm;                             

    int len_log_cur_name = 0; // Length of the current log file name.
    int len_suffix_name = 0;  // Length of the log file mark (suffix).
    int len_log_new_name = 0; // Length of the new log file name.
    int ret = 0;             // Return code.
    errno_t rc = 0;          // Error code variable for safe C library functions.

    current_time = time(NULL); // Get the current time.

    systm = localtime(&current_time); // Convert current time to a local time structure.

    // Generate a timestamp in the format "-%Y-%m-%d_%H%M%S" and store it in current_localtime.
    if (systm != nullptr) {
        (void)strftime(current_localtime, LOG_MAX_TIMELEN, "-%Y-%m-%d_%H%M%S", systm);
    }

    /* Close the current file */
    if (syslogFile != NULL) {
        fclose(syslogFile);
        syslogFile = NULL;
    }

    /* Rename the current file without the log file mark */
    len_log_cur_name = strlen(curLogFileName);
    len_suffix_name = strlen(curLogFileMark);
    len_log_new_name = len_log_cur_name - len_suffix_name;

    // Copy the portion of the current file name without the mark to log_new_name.
    rc = strncpy_s(log_new_name, MAXPGPATH, curLogFileName, len_log_new_name);
    securec_check_errno(rc, );

    // Append ".log" to the new log file name.
    rc = strncat_s(log_new_name, MAXPGPATH, ".log", strlen(".log"));
    securec_check_errno(rc, );

    // Rename the current log file to the new log file name.
    ret = rename(curLogFileName, log_new_name);
    if (ret != 0) {
        printf(_("%s: Rename log file %s failed!\n"), prefix_name, curLogFileName);
        return;
    }

    /* Generate the new current file name */
    rc = memset_s(curLogFileName, MAXPGPATH, 0, MAXPGPATH);
    securec_check_errno(rc, );

    // Construct the new log file name with the current timestamp and log file mark.
    ret = snprintf_s(curLogFileName,
        MAXPGPATH,
        MAXPGPATH - 1,
        "%s/%s%s%s",
        sys_log_path,
        prefix_name,
        current_localtime,
        curLogFileMark);
    securec_check_intval(ret, );

    oumask = umask((mode_t)((~(mode_t)(S_IRUSR | S_IWUSR | S_IXUSR)) & (S_IRWXU | S_IRWXG | S_IRWXO)));

    // Open the new log file for appending.
    syslogFile = fopen(curLogFileName, "a");

    (void)umask(oumask);

    // Check if opening the new log file was successful and set close-on-exec flag if needed.
    if (syslogFile == NULL) {
        (void)printf("switchLogFile, switch new log file failed: %s\n", strerror(errno));
    } else {
        if (SetFdCloseExecFlag(syslogFile) == -1) {
            (void)printf("set file flag failed, filename: %s, errmsg: %s.\n", curLogFileName, strerror(errno));
        }
    }
}

/*
 * @GaussDB@
 * Brief: Write information to log files.
 * Description: This function is responsible for writing log information to log files. It checks if the current
 *              log file size is full and switches to the next log file when necessary. It also handles
 *              log file initialization and error reporting.
 * Notes: If the current log file size is full, the function switches to the next log file.
 */
void write_log_file(const char* buffer, int count)
{
    int rc = 0; // Return code for fwrite.

    // Obtain a write lock to ensure thread safety during log writing.
    (void)pthread_rwlock_wrlock(&syslog_write_lock);

    // Check if the syslogFile is uninitialized, and if so, open it.
    if (syslogFile == NULL) {
        syslogFile = logfile_open(sys_log_path, "a");
    }

    if (syslogFile != NULL) {
        count = strlen(buffer); // Calculate the length of the buffer.

        // Check if writing the buffer would exceed the maximum log file size, and switch to the next file if needed.
        if ((ftell(syslogFile) + count) > (maxLogFileSize)) {
            switchLogFile();
        }

        if (syslogFile != NULL) {
            // Write the buffer to the log file.
            rc = fwrite(buffer, 1, count, syslogFile);

            // Check if the write operation was successful.
            if (rc != count) {
                printf("Could not write to log file: %s %m\n", curLogFileName);
            }
        } else {
            printf("write_log_file could not open log file %s : %m\n", curLogFileName);
        }
    } else {
        printf("write_log_file, log file is null now: %s\n", buffer);
    }

    // Release the write lock after completing log writing.
    (void)pthread_rwlock_unlock(&syslog_write_lock);
}

/*
 * This function returns an error message formatted using the provided format string and arguments.
 *
 * Parameters:
 * - fmt: A format string specifying the error message format.
 * - ...: Variable arguments corresponding to the format placeholders in the format string.
 *
 * Returns:
 * - A pointer to a character array containing the formatted error message.
 *
 * Description:
 * - The function takes a format string 'fmt' and a variable number of arguments, similar to the 'printf' function.
 * - It formats the error message according to the 'fmt' string and the provided arguments.
 * - The formatted error message is stored in a character array 'errbuf' with a maximum length of 'BUF_LEN'.
 * - The function ensures that the 'errbuf' is null-terminated.
 * - The formatted error message is prefixed with "[ERRMSG]:" and then concatenated with any additional text.
 * - The resulting error message is stored in 'errbuf_errmsg' and returned.
 * - The caller should be aware that the returned error message is stored in a local array, and its memory may become
 *   invalid once the function exits.
 *
 * Notes:
 * - It's the caller's responsibility to handle and manage the memory of the returned error message.
 */

char* errmsg(const char* fmt, ...)
{
    va_list ap;         // Variable argument list.
    int count = 0;      // Count of characters written.
    int rcs;            // Return code of snprintf.
    errno_t rc;         // Error code variable for safe C library functions.
    char errbuf[BUF_LEN] = {0};  // Buffer for formatting the error message.

    // Make sure the format string is translated if required.
    fmt = _(fmt);

    va_start(ap, fmt);  // Initialize the variable argument list.
    rc = memset_s(errbuf_errmsg, EREPORT_BUF_LEN, 0, EREPORT_BUF_LEN);  // Clear the error message buffer.
    securec_check_c(rc, "\0", "\0");

    // Format the error message using vsnprintf_s.
    count = vsnprintf_s(errbuf, sizeof(errbuf), sizeof(errbuf) - 1, fmt, ap);
    securec_check_intval(count, );

    va_end(ap);  // End the variable argument list.

    // Prefix the formatted error message with "[ERRMSG]:" and concatenate it with any additional text.
    rcs = snprintf_s(errbuf_errmsg, EREPORT_BUF_LEN, EREPORT_BUF_LEN - 1, "%s", "[ERRMSG]:");
    securec_check_intval(rcs, );
    rc = memcpy_s(errbuf_errmsg + strlen(errbuf_errmsg), BUF_LEN - strlen(errbuf_errmsg),
        errbuf, BUF_LEN - strlen(errbuf_errmsg) - 1);
    securec_check_errno(rc, (void)rc);

    return errbuf_errmsg;  // Return the formatted error message.
}


/*
 * This function returns a detailed error message formatted using the provided format string and arguments.
 *
 * Parameters:
 * - fmt: A format string specifying the detailed error message format.
 * - ...: Variable arguments corresponding to the format placeholders in the format string.
 *
 * Returns:
 * - A pointer to a character array containing the formatted detailed error message.
 *
 * Description:
 * - The function takes a format string 'fmt' and a variable number of arguments, similar to the 'printf' function.
 * - It formats the detailed error message according to the 'fmt' string and the provided arguments.
 * - The formatted detailed error message is stored in a character array 'errbuf' with a maximum length of 'BUF_LEN'.
 * - The function ensures that 'errbuf' is null-terminated.
 * - The formatted detailed error message is prefixed with "[ERRDETAIL]:" and then concatenated with any additional text.
 * - The resulting detailed error message is stored in 'errbuf_errdetail' and returned.
 * - The caller should be aware that the returned detailed error message is stored in a local array, and its memory may become
 *   invalid once the function exits.
 *
 * Notes:
 * - It's the caller's responsibility to handle and manage the memory of the returned detailed error message.
 */

char* errdetail(const char* fmt, ...)
{
    va_list ap;         // Variable argument list.
    int count = 0;      // Count of characters written.
    int rcs;            // Return code of snprintf.
    errno_t rc;         // Error code variable for safe C library functions.
    char errbuf[BUF_LEN] = {0};  // Buffer for formatting the detailed error message.

    // Make sure the format string is translated if required.
    fmt = _(fmt);

    va_start(ap, fmt);  // Initialize the variable argument list.
    rc = memset_s(errbuf_errdetail, EREPORT_BUF_LEN, 0, EREPORT_BUF_LEN);  // Clear the detailed error message buffer.
    securec_check_c(rc, "\0", "\0");

    // Format the detailed error message using vsnprintf_s.
    count = vsnprintf_s(errbuf, sizeof(errbuf), sizeof(errbuf) - 1, fmt, ap);
    securec_check_intval(count, );

    va_end(ap);  // End the variable argument list.

    // Prefix the formatted detailed error message with "[ERRDETAIL]:" and concatenate it with any additional text.
    rcs = snprintf_s(errbuf_errdetail, EREPORT_BUF_LEN, EREPORT_BUF_LEN - 1, "%s", "[ERRDETAIL]:");
    securec_check_intval(rcs, );
    rc = memcpy_s(errbuf_errdetail + strlen(errbuf_errdetail), BUF_LEN - strlen(errbuf_errdetail),
        errbuf, BUF_LEN - strlen(errbuf_errdetail) - 1);
    securec_check_errno(rc, (void)rc);

    return errbuf_errdetail;  // Return the formatted detailed error message.
}

/*
 * This function generates an error code string based on the provided SQL state.
 *
 * Parameters:
 * - sql_state: An integer representing the SQL state code.
 *
 * Returns:
 * - A pointer to a character array containing the formatted error code.
 *
 * Description:
 * - The function takes an integer 'sql_state' representing an SQL state code and converts it into a string format.
 * - The SQL state code is a five-character code where each character represents a six-bit value.
 * - The function iterates through the SQL state code, extracting each six-bit value and converting it into a character.
 * - The resulting error code is prefixed with "[ERRCODE]:" and stored in 'errbuf_errcode'.
 * - The function ensures that 'errbuf_errcode' is null-terminated.
 * - The caller should be aware that the returned error code is stored in a local array, and its memory may become
 *   invalid once the function exits.
 *
 * Notes:
 * - It's the caller's responsibility to handle and manage the memory of the returned error code.
 */

char* errcode(int sql_state)
{
    int i;
    int rcs;
    errno_t rc;
    char buf[6] = {0};
    rc = memset_s(errbuf_errcode, EREPORT_BUF_LEN, 0, EREPORT_BUF_LEN);  // Clear the error code buffer.
    securec_check_c(rc, "\0", "\0");

    // Extract each six-bit value from the SQL state code and convert it into a character.
    for (i = 0; i < 5; i++) {
        buf[i] = PGUNSIXBIT(sql_state);
        sql_state >>= 6;
    }
    buf[i] = '\0';

    // Prefix the formatted error code with "[ERRCODE]:" and store it in 'errbuf_errcode'.
    rcs = snprintf_s(errbuf_errcode, EREPORT_BUF_LEN, EREPORT_BUF_LEN - 1, "%s%s", "[ERRCODE]:", buf);
    securec_check_intval(rcs, );

    return errbuf_errcode;  // Return the formatted error code.
}


/*
 * This function generates an error cause message formatted using the provided format string and arguments.
 *
 * Parameters:
 * - fmt: A format string specifying the error cause message format.
 * - ...: Variable arguments corresponding to the format placeholders in the format string.
 *
 * Returns:
 * - A pointer to a character array containing the formatted error cause message.
 *
 * Description:
 * - The function takes a format string 'fmt' and a variable number of arguments, similar to the 'printf' function.
 * - It formats the error cause message according to the 'fmt' string and the provided arguments.
 * - The formatted error cause message is stored in a character array 'errbuf' with a maximum length of 'BUF_LEN'.
 * - The function ensures that 'errbuf' is null-terminated.
 * - The formatted error cause message is prefixed with "[ERRCAUSE]:" and then concatenated with any additional text.
 * - The resulting error cause message is stored in 'errbuf_errcause' and returned.
 * - The caller should be aware that the returned error cause message is stored in a local array, and its memory may become
 *   invalid once the function exits.
 *
 * Notes:
 * - It's the caller's responsibility to handle and manage the memory of the returned error cause message.
 */

char* errcause(const char* fmt, ...)
{
    va_list ap;         // Variable argument list.
    int count = 0;      // Count of characters written.
    int rcs;            // Return code of snprintf.
    errno_t rc;         // Error code variable for safe C library functions.
    char errbuf[BUF_LEN] = {0};  // Buffer for formatting the error cause message.

    // Make sure the format string is translated if required.
    fmt = _(fmt);

    va_start(ap, fmt);  // Initialize the variable argument list.
    rc = memset_s(errbuf_errcause, EREPORT_BUF_LEN, 0, EREPORT_BUF_LEN);  // Clear the error cause message buffer.
    securec_check_c(rc, "\0", "\0");

    // Format the error cause message using vsnprintf_s.
    count = vsnprintf_s(errbuf, sizeof(errbuf), sizeof(errbuf) - 1, fmt, ap);
    securec_check_intval(count, );

    va_end(ap);  // End the variable argument list.

    // Prefix the formatted error cause message with "[ERRCAUSE]:" and concatenate it with any additional text.
    rcs = snprintf_s(errbuf_errcause, EREPORT_BUF_LEN, EREPORT_BUF_LEN - 1, "%s", "[ERRCAUSE]:");
    securec_check_intval(rcs, );
    rc = memcpy_s(errbuf_errcause + strlen(errbuf_errcause), BUF_LEN - strlen(errbuf_errcause),
        errbuf, BUF_LEN - strlen(errbuf_errcause) - 1);
    securec_check_errno(rc, (void)rc);

    return errbuf_errcause;  // Return the formatted error cause message.
}


/*
 * This function generates an error action message formatted using the provided format string and arguments.
 *
 * Parameters:
 * - fmt: A format string specifying the error action message format.
 * - ...: Variable arguments corresponding to the format placeholders in the format string.
 *
 * Returns:
 * - A pointer to a character array containing the formatted error action message.
 *
 * Description:
 * - The function takes a format string 'fmt' and a variable number of arguments, similar to the 'printf' function.
 * - It formats the error action message according to the 'fmt' string and the provided arguments.
 * - The formatted error action message is stored in a character array 'errbuf' with a maximum length of 'BUF_LEN'.
 * - The function ensures that 'errbuf' is null-terminated.
 * - The formatted error action message is prefixed with "[ERRACTION]:" and then concatenated with any additional text.
 * - The resulting error action message is stored in 'errbuf_erraction' and returned.
 * - The caller should be aware that the returned error action message is stored in a local array, and its memory may become
 *   invalid once the function exits.
 *
 * Notes:
 * - It's the caller's responsibility to handle and manage the memory of the returned error action message.
 */

char* erraction(const char* fmt, ...)
{
    va_list ap;         // Variable argument list.
    int count = 0;      // Count of characters written.
    int rcs;            // Return code of snprintf.
    errno_t rc;         // Error code variable for safe C library functions.
    char errbuf[BUF_LEN] = {0};  // Buffer for formatting the error action message.

    // Make sure the format string is translated if required.
    fmt = _(fmt);

    va_start(ap, fmt);  // Initialize the variable argument list.
    rc = memset_s(errbuf_erraction, EREPORT_BUF_LEN, 0, EREPORT_BUF_LEN);  // Clear the error action message buffer.
    securec_check_c(rc, "\0", "\0");

    // Format the error action message using vsnprintf_s.
    count = vsnprintf_s(errbuf, sizeof(errbuf), sizeof(errbuf) - 1, fmt, ap);
    securec_check_intval(count, );

    va_end(ap);  // End the variable argument list.

    // Prefix the formatted error action message with "[ERRACTION]:" and concatenate it with any additional text.
    rcs = snprintf_s(errbuf_erraction, EREPORT_BUF_LEN, EREPORT_BUF_LEN - 1, "%s", "[ERRACTION]:");
    securec_check_intval(rcs, );
    rc = memcpy_s(errbuf_erraction + strlen(errbuf_erraction), BUF_LEN - strlen(errbuf_erraction),
        errbuf, BUF_LEN - strlen(errbuf_erraction) - 1);
    securec_check_errno(rc, (void)rc);

    return errbuf_erraction;  // Return the formatted error action message.
}


/*
 * This function generates an error module message based on the provided ModuleId.
 *
 * Parameters:
 * - id: A ModuleId representing the error module.
 *
 * Returns:
 * - A pointer to a character array containing the formatted error module message.
 *
 * Description:
 * - The function takes a ModuleId 'id' and generates an error module message.
 * - The error module message is prefixed with "[ERRMODULE]:".
 * - The actual module name corresponding to 'id' is obtained using 'get_valid_module_name'.
 * - The obtained module name is concatenated with the prefix and stored in 'errbuf_errmodule'.
 * - The function ensures that 'errbuf_errmodule' is null-terminated.
 * - The caller should be aware that the returned error module message is stored in a local array, and its memory may become
 *   invalid once the function exits.
 *
 * Notes:
 * - It's the caller's responsibility to handle and manage the memory of the returned error module message.
 */

char* errmodule(ModuleId id)
{
    errno_t rc = memset_s(errbuf_errmodule, EREPORT_BUF_LEN, 0, EREPORT_BUF_LEN);  // Clear the error module message buffer.
    securec_check_c(rc, "\0", "\0");

    int rcs = snprintf_s(errbuf_errmodule, EREPORT_BUF_LEN - 1, EREPORT_BUF_LEN - 1, "%s", "[ERRMODULE]:");  // Prefix with "[ERRMODULE]:".
    securec_check_intval(rcs, (void)rcs);

    // Get the valid module name corresponding to the provided ModuleId and concatenate it with the prefix.
    rcs = snprintf_s(errbuf_errmodule + strlen(errbuf_errmodule), EREPORT_BUF_LEN - strlen(errbuf_errmodule),
        EREPORT_BUF_LEN - strlen(errbuf_errmodule) - 1, "%s", get_valid_module_name(id));
    securec_check_intval(rcs, (void)rcs);

    return errbuf_errmodule;  // Return the formatted error module message.
}
