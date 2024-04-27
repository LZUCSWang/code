/*** 
 * @Author: 张鹏春
 * @Team: 兰心开源
 * @Date: 2023-09-11 20:25:05
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
 * build_query.cpp
 *      functions used by cm_ctl and gs_ctl to display build progress
 *
 * Portions Copyright (c) 2012-2015, Huawei Tech. Co., Ltd.
 * Portions Copyright (c) 2010-2012, Postgres-XC Development Group
 * Portions Copyright (c) 1996-2011, PostgreSQL Global Development Group
 *
 * IDENTIFICATION
 *        src/lib/build_query/build_query.cpp
 *
 * ---------------------------------------------------------------------------------------
 */

#include "common/build_query/build_query.h"
#include "securec.h"
#include "securec_check.h"

/*
 * strdup() replacements that prints an error and exits
 * if something goes wrong. Can never return NULL.
 */

/**

This function duplicates a given string and returns the duplicated string.

@param s The string to be duplicated.

@return char* The duplicated string.
*/
static char xstrdup(const char* s)
{
char* result = NULL;

// Duplicate the string 's' using the strdup function
result = strdup(s);

// Check if memory allocation failed
if (result == NULL) {
printf("out of memory\n");
exit(1);
}

// Return the duplicated string
return result;
}


/**
 * This function takes an estimated time in seconds as input and converts it
 * into a formatted time string in the "HH:MM:SS" format. If the estimated_time
 * is -1, it returns "--:--:--" to represent an unknown time.
 *
 * @param estimated_time The estimated time in seconds.
 *
 * @return char* A dynamically allocated string representing the formatted time.
 */
char* show_estimated_time(int estimated_time)
{
    // Create a character array to store the formatted time string, initialize to zero
    char time_string[MAXPGPATH] = {0};

    // Declare variables to store hours, minutes, seconds, and a return value
    int hour = 0;
    int min = 0;
    int sec = 0;
    int nRet = 0;

    // Check if estimated_time is -1, indicating an unknown time
    if (estimated_time == -1)
        return xstrdup("--:--:--"); // Return a string representing unknown time

    // Calculate hours, minutes, and seconds from the estimated_time
    hour = estimated_time / S_PER_H;
    min = (estimated_time % S_PER_H) / S_PER_MIN;
    sec = (estimated_time % S_PER_H) % S_PER_MIN;

    // Format the calculated values into a string and store it in time_string
    nRet = snprintf_s(time_string, MAXPGPATH, MAXPGPATH - 1, "%.2d:%.2d:%.2d", hour, min, sec);
    
    // Check for errors during string formatting using securec_check_ss_c
    securec_check_ss_c(nRet, "\0", "\0");

    // Return a dynamically allocated copy of the formatted time string
    return xstrdup(time_string);
}


/**
 * This function takes a data size in bytes as input and converts it
 * into a formatted string with appropriate units (e.g., KB, MB, GB, TB).
 *
 * @param size The data size in bytes.
 *
 * @return char* A dynamically allocated string representing the formatted data size.
 */
char* show_datasize(uint64 size)
{
    // Create a character array to store the formatted size string, initialize to zero
    char size_string[MAXPGPATH] = {0};

    // Declare variables to store the size in a human-readable format and the unit string
    float showsize = 0;
    const char* unit = NULL;
    int nRet = 0;

    // Check for the largest unit (TB, GB, MB, or KB) that is appropriate for the size
    if (size / KB_PER_TB != 0) {
        showsize = (float)size / KB_PER_TB;
        unit = "TB";
    } else if (size / KB_PER_GB != 0) {
        showsize = (float)size / KB_PER_GB;
        unit = "GB";
    } else if (size / KB_PER_MB != 0) {
        showsize = (float)size / KB_PER_MB;
        unit = "MB";
    } else {
        showsize = (float)size;
        unit = "kB";
    }

    // Format the calculated size and unit into a string and store it in size_string
    nRet = snprintf_s(size_string, MAXPGPATH, MAXPGPATH - 1, "%.2f%s", showsize, unit);
    
    // Check for errors during string formatting using securec_check_ss_c
    securec_check_ss_c(nRet, "\0", "\0");

    // Return a dynamically allocated copy of the formatted size string
    return xstrdup(size_string);
}


/**
 * This function updates a database state file located at the specified path with
 * the data provided in the GaussState structure.
 *
 * @param path The path to the database state file to be updated.
 * @param state A pointer to the GaussState structure containing the data to be written.
 */
void UpdateDBStateFile(char* path, GaussState* state)
{
    FILE* statef = NULL; // File pointer for the state file
    char temppath[MAXPGPATH] = {0}; // Temporary file path for writing

    int ret; // Return value from snprintf_s

    // Check for NULL pointers and return if either is NULL
    if (NULL == state || path == NULL) {
        return;
    }

    // Create the temporary file path by appending ".temp" to the original path
    ret = snprintf_s(temppath, MAXPGPATH, MAXPGPATH - 1, "%s.temp", path);
    securec_check_ss_c(ret, "\0", "\0");

    // Canonicalize the original path to ensure consistency
    canonicalize_path(path);

    // Open the temporary file for writing
    statef = fopen(temppath, "w");
    
    // Return if unable to open the temporary file
    if (statef == NULL) {
        return;
    }

    // Set the file permissions for the temporary file
    if (chmod(temppath, S_IRUSR | S_IWUSR) == -1) {
        /* Close file and Nullify the pointer for retry */
        fclose(statef);
        statef = NULL;
        return;
    }

    // Write the contents of the GaussState structure to the temporary file
    if (0 == (fwrite(state, 1, sizeof(GaussState), statef))) {
        fclose(statef);
        statef = NULL;
        return;
    }

    // Close the temporary file
    fclose(statef);

    // Rename the temporary file to replace the original state file
    (void)rename(temppath, path);
}

