# cm_stringinfo模块解析（2）

![cm_stringinfo(2)](D:\xmind\cm_stringinfo(2).png)

[TOC]



## 函数名

### `CM_appendStringInfo`

## 参数
- `CM_StringInfo str`：要追加数据的 `CM_StringInfo` 结构的指针。
- `const char* fmt`：一个 `sprintf` 风格的格式字符串，用于格式化数据。
- `...`：可变数量的参数，用于填充格式字符串中的占位符。

## 功能
该函数用于根据提供的格式字符串 `fmt` 和可变数量的参数，将格式化的文本数据追加到 `CM_StringInfo` 结构 `str` 中。如果需要，将分配更多的内存来容纳新数据。这类似于 `sprintf` 和 `strcat` 的组合操作。

## 注意事项
- 在调用该函数之前，确保传入的 `CM_StringInfo` 结构 `str` 是有效的。
- 函数会尝试多次格式化数据并追加，如果成功则返回，如果失败则会扩展缓冲区的大小并重试，直到成功为止。
- 注意谨慎处理格式字符串和可变参数，以避免不安全的操作。

## 示例
```c
#include <stdio.h>
#include <stdarg.h>

typedef struct CM_StringInfoData {
    char* data;
    int maxlen;
    int len;
    int cursor;
    // 数据结构的其他成员
    // ...
} CM_StringInfoData;

typedef CM_StringInfoData* CM_StringInfo;

bool CM_appendStringInfoVA(CM_StringInfo str, const char* fmt, va_list args) {
    // 格式化并追加数据的实现
    // ...
}

bool CM_enlargeStringInfo(CM_StringInfo str, int needed) {
    // 扩展缓冲区的实现
    // ...
}

void CM_appendStringInfo(CM_StringInfo str, const char* fmt, ...) {
    for (;;) {
        va_list args;
        bool success = false;

        /* Try to format the data. */
        va_start(args, fmt);
        success = CM_appendStringInfoVA(str, fmt, args);
        va_end(args);

        if (success) {
            break;
        }

        /* Double the buffer size and try again. */
        (void)CM_enlargeStringInfo(str, str->maxlen);
    }
}

int main() {
    CM_StringInfo str_info = CM_makeStringInfo();
    
    CM_appendStringInfo(str_info, "Hello, %s!", "world"); // 格式化追加数据

    // 使用str_info进行操作
    // ...

    // 在适当的时候释放str_info的内存
    // ...

    return 0;
}
```

在上述示例中，`CM_appendStringInfo` 函数用于根据格式字符串和可变参数将格式化的文本数据追加到 `CM_StringInfo` 结构中。如果需要，它会动态扩展缓冲区以容纳更多的数据。请注意谨慎处理格式字符串和可变参数，以确保安全性。

## 函数名
### `CM_appendStringInfoVA`

## 参数
- `CM_StringInfo str`：要追加数据的 `CM_StringInfo` 结构的指针。
- `const char* fmt`：一个 `sprintf` 风格的格式字符串，用于格式化数据。
- `va_list args`：一个 `va_list` 参数列表，包含要填充到格式字符串中的可变数量的参数。

## 返回值
- `bool`：如果成功追加数据返回 `true`，如果由于缓冲区空间不足而无法追加数据则返回 `false`。

## 功能
该函数尝试根据提供的格式字符串 `fmt` 和 `va_list` 参数列表 `args`，将格式化的文本数据追加到 `CM_StringInfo` 结构 `str` 中。如果成功，返回 `true`，如果由于缓冲区空间不足而无法追加数据则返回 `false`。通常，如果返回 `false`，调用者应该扩展缓冲区并重试。

## 注意事项
- 在调用该函数之前，确保传入的 `CM_StringInfo` 结构 `str` 是有效的。
- 函数会尝试格式化数据并追加到缓冲区，但如果缓冲区空间不足，它会返回 `false`。
- 请注意，某些版本的 `vsnprintf` 在失败时返回 -1，而不是实际写入的字符数，因此要保守地处理结果。

## 示例
```c
#include <stdio.h>
#include <stdarg.h>

typedef struct CM_StringInfoData {
    char* data;
    int maxlen;
    int len;
    int cursor;
    // 数据结构的其他成员
    // ...
} CM_StringInfoData;

typedef CM_StringInfoData* CM_StringInfo;

bool CM_appendStringInfoVA(CM_StringInfo str, const char* fmt, va_list args) {
    int avail, nprinted;

    /*
     * If there's hardly any space, don't bother trying, just fail to make the
     * caller enlarge the buffer first.
     */
    avail = str->maxlen - str->len - 1;
    if (avail < 16) {
        return false;
    }

#ifdef USE_ASSERT_CHECKING
    str->data[str->maxlen - 1] = '\0'; // 用于检测vsprintf是否越界的断言
#endif

    nprinted = vsnprintf_s(str->data + str->len, str->maxlen - str->len, avail, fmt, args);

    if (nprinted >= 0 && nprinted < avail - 1) {
        /* Success.  Note nprinted does not include trailing null. */
        str->len += nprinted;
        return true;
    }

    /* Restore the trailing null so that str is unmodified. */
    str->data[str->len] = '\0';
    return false;
}

int main() {
    CM_StringInfo str_info = CM_makeStringInfo();

    if (CM_appendStringInfoVA(str_info, "Hello, %s!", "world")) {
        // 追加成功
        // 使用str_info进行操作
        // ...
    } else {
        // 追加失败，需要扩展缓冲区
        // ...
    }

    // 在适当的时候释放str_info的内存
    // ...

    return 0;
}
```

在上述示例中，`CM_appendStringInfoVA` 函数用于尝试根据格式字符串和 `va_list` 参数列表将格式化的文本数据追加到 `CM_StringInfo` 结构中。如果成功追加数据，返回 `true`，否则返回 `false`，并要求调用者扩展缓冲区以重新尝试。

## 函数名
### `CM_appendStringInfoChar`

## 参数
- `CM_StringInfo str`：要追加数据的 `CM_StringInfo` 结构的指针。
- `char ch`：要追加的单个字节字符。

## 功能
该函数用于将单个字节字符 `ch` 追加到 `CM_StringInfo` 结构 `str` 中。如果需要，函数会自动扩展缓冲区以容纳新字符。这个函数的性能比使用 `appendStringInfo` 函数来追加字符要高。

## 注意事项
- 在调用该函数之前，确保传入的 `CM_StringInfo` 结构 `str` 是有效的。
- 函数会检查是否需要扩展缓冲区以容纳新字符，如果需要则会自动扩展。
- 追加字符后，`str` 结构的长度和终止符会相应地更新。

## 示例
```c
#include <stdio.h>

typedef struct CM_StringInfoData {
    char* data;
    int maxlen;
    int len;
    int cursor;
    // 数据结构的其他成员
    // ...
} CM_StringInfoData;

typedef CM_StringInfoData* CM_StringInfo;

void CM_appendStringInfoChar(CM_StringInfo str, char ch) {
    /* Make more room if needed */
    if (str->len + 1 >= str->maxlen) {
        (void)CM_enlargeStringInfo(str, 1);
    }

    /* OK, append the character */
    str->data[str->len] = ch;
    str->len++;
    str->data[str->len] = '\0';
}

int main() {
    CM_StringInfo str_info = CM_makeStringInfo();
    
    CM_appendStringInfoChar(str_info, 'H'); // 追加字符 'H'
    CM_appendStringInfoChar(str_info, 'i'); // 追加字符 'i'

    // 使用str_info进行操作
    // ...

    // 在适当的时候释放str_info的内存
    // ...

    return 0;
}
```

在上述示例中，`CM_appendStringInfoChar` 函数用于将单个字节字符追加到 `CM_StringInfo` 结构中，而不需要使用格式字符串。函数会自动扩展缓冲区以容纳新字符，并更新长度和终止符。

## 函数名
### `CM_appendBinaryStringInfo`

## 参数
- `CM_StringInfo str`：要追加数据的 `CM_StringInfo` 结构的指针。
- `const char* data`：指向要追加的二进制数据的指针。
- `int datalen`：要追加的二进制数据的长度（字节数）。

## 功能
该函数用于将任意二进制数据追加到 `CM_StringInfo` 结构 `str` 中，并在需要时分配更多的空间。函数会自动扩展缓冲区以容纳新数据，并将数据复制到缓冲区中。

## 注意事项
- 在调用该函数之前，确保传入的 `CM_StringInfo` 结构 `str` 是有效的。
- 函数会自动扩展缓冲区以容纳新数据，但请注意防止内存泄漏，适时释放结构中的内存。
- 函数使用 `memcpy_s` 来安全地复制二进制数据，确保不会发生缓冲区溢出。

## 示例
```c
#include <stdio.h>
#include <string.h>

typedef struct CM_StringInfoData {
    char* data;
    int maxlen;
    int len;
    int cursor;
    // 数据结构的其他成员
    // ...
} CM_StringInfoData;

typedef CM_StringInfoData* CM_StringInfo;

void CM_appendBinaryStringInfo(CM_StringInfo str, const char* data, int datalen) {
    errno_t rc;

    /* Make more room if needed */
    (void)CM_enlargeStringInfo(str, datalen);

    /* OK, append the data */
    rc = memcpy_s(str->data + str->len, str->maxlen - str->len, data, datalen);
    securec_check_c(rc, "\0", "\0");
    str->len += datalen;

    /*
     * Keep a trailing null in place, even though it's probably useless for
     * binary data...
     */
    str->data[str->len] = '\0';
}

int main() {
    CM_StringInfo str_info = CM_makeStringInfo();
    const char* binary_data = "\x01\x02\x03\x04\x05";
    
    CM_appendBinaryStringInfo(str_info, binary_data, 5); // 追加二进制数据

    // 使用str_info进行操作
    // ...

    // 在适当的时候释放str_info的内存
    // ...

    return 0;
}
```

在上述示例中，`CM_appendBinaryStringInfo` 函数用于将二进制数据追加到 `CM_StringInfo` 结构中，函数会自动扩展缓冲区以容纳新数据，并安全地复制数据到缓冲区中。

## 函数名
### `CM_enlargeStringInfo`

![CM_enlargeStringInfo](D:\xmind\CM_enlargeStringInfo.png)

## 参数
- `CM_StringInfo str`：要扩展的 `CM_StringInfo` 结构的指针。
- `int needed`：需要的额外字节数（不包括终止空字符）。

## 返回值
- `int`：如果成功扩展字符串缓冲区则返回0，如果失败则返回-1。

## 功能
该函数用于确保字符串缓冲区具有足够的空间来容纳指定数量的额外字节（不包括终止空字符）。如果缓冲区已经具有足够的空间，函数将立即返回。否则，它会自动扩展缓冲区的大小，以满足需要的空间。

## 注意事项
- 在调用该函数之前，确保传入的 `CM_StringInfo` 结构 `str` 是有效的。
- 函数会自动扩展缓冲区的大小，以满足所需的空间。它会根据需要多次扩展，每次扩展大小为当前大小的两倍，以提高效率。
- 如果扩展后的大小超过了最大可分配大小（`CM_MaxAllocSize`），函数会将大小限制为最大可分配大小，以防止溢出。
- 函数会在扩展时保留原始数据，如果内存分配失败，会释放原始数据。

## 示例
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct CM_StringInfoData {
    char* data;
    int maxlen;
    int len;
    int cursor;
    // 数据结构的其他成员
    // ...
} CM_StringInfoData;

typedef CM_StringInfoData* CM_StringInfo;

int CM_enlargeStringInfo(CM_StringInfo str, int needed) {
    int newlen;
    char* newdata = NULL;

    /*
     * Guard against out-of-range "needed" values.  Without this, we can get
     * an overflow or infinite loop in the following.
     */
    if (needed < 0) /* should not happen */
    {
        fprintf(stderr, "invalid string enlargement request size: %d\n", needed);
        return -1;
    }

    if (((size_t)needed) >= (CM_MaxAllocSize - (size_t)str->len)) {
        fprintf(stderr,
            "out of memory! Cannot enlarge string buffer containing %d bytes by %d more bytes.\n",
            str->len,
            needed);
        return -1;
    }

    needed += str->len + 1; /* total space required now */

    /* Because of the above test, we now have needed <= MaxAllocSize */

    if (needed <= str->maxlen) {
        return 0; /* got enough space already */
    }

    /*
     * We don't want to allocate just a little more space with each append;
     * for efficiency, double the buffer size each time it overflows.
     * Actually, we might need to more than double it if 'needed' is big...
     */
    newlen = 2 * str->maxlen;
    while (needed > newlen) {
        newlen = 2 * newlen;
    }

    /*
     * Clamp to MaxAllocSize in case we went past it.  Note we are assuming
     * here that MaxAllocSize <= INT_MAX/2, else the above loop could
     * overflow.  We will still have newlen >= needed.
     */
    if (newlen > (int)CM_MaxAllocSize) {
        newlen = (int)CM_MaxAllocSize;
    }

    newdata = (char*)malloc(newlen);
    if (newdata != NULL) {
        if (str->data != NULL) {
            memcpy(newdata, str->data, str->len);
            free(str->data);
        }
        str->data = newdata;
        str->maxlen = newlen;
    } else {
        if (str->data != NULL) {
            free(str->data);
            str->maxlen = 0;
        }
    }
    return 0;
}

int main() {
    CM_StringInfo str_info = (CM_StringInfo)malloc(sizeof(CM_StringInfoData));

    // 初始化str_info并设置初始数据
    str_info->data = (char*)malloc(64);
    strcpy(str_info->data, "Hello, World!");
    str_info->maxlen = 64;
    str_info->len = strlen(str_info->data);

    // 扩展缓冲区以容纳更多数据
    int additional_space = 20;
    if (CM_enlargeStringInfo(str_info, additional_space) == 0) {
        // 扩展成功，现在可以在str_info中追加更多数据
        // ...
    }

    // 在适当的时候释放str_info的内存
    free(str_info->data);
    free(str_info);

    return 0;
}
```

在上述示例中，`CM_enlargeStringInfo` 函数用于确保字符串缓冲区具有足够的空间来容纳所需的额外字节数。函数会自动扩展缓冲区的大小，如果扩展成功，返回0。然后，可以在扩展后的缓冲区中追加更多数据。最后，适时释放内存以避免内存泄漏。

## 函数名
### `CM_is_str_all_digit`

## 参数
- `const char* name`：要检查的字符串。

## 返回值
- `int`：如果字符串中的所有字符都是数字，则返回0；如果字符串为空或包含非数字字符，则返回-1。

## 功能
该函数用于检查给定的字符串 `name` 是否由数字字符组成。如果字符串中的所有字符都是数字（0到9），则返回0；否则返回-1。函数会检查字符串中的每个字符，如果发现任何一个字符不是数字，则立即返回-1。

## 注意事项
- 在调用该函数之前，确保传入的字符串 `name` 不为空（即非NULL）。
- 函数会遍历字符串中的每个字符，并检查其是否为数字字符。
- 返回值为0表示字符串中的所有字符都是数字，返回-1表示字符串为空或包含非数字字符。

## 示例
```c
#include <stdio.h>
#include <string.h>

int CM_is_str_all_digit(const char* name) {
    int size = 0;
    int i = 0;

    if (name == NULL) {
        fprintf(stderr, "CM_is_str_all_digit input null\n");
        return -1;
    }

    size = strlen(name);
    for (i = 0; i < size; i++) {
        if (name[i] < '0' || name[i] > '9') {
            return -1;
        }
    }
    return 0;
}

int main() {
    const char* str1 = "12345";
    const char* str2 = "abc123";
    const char* str3 = "";

    int result1 = CM_is_str_all_digit(str1); // 返回0，str1中的所有字符都是数字
    int result2 = CM_is_str_all_digit(str2); // 返回-1，str2中包含非数字字符
    int result3 = CM_is_str_all_digit(str3); // 返回-1，str3为空字符串

    printf("Result 1: %d\n", result1);
    printf("Result 2: %d\n", result2);
    printf("Result 3: %d\n", result3);

    return 0;
}
```

在上述示例中，`CM_is_str_all_digit` 函数用于检查字符串是否由数字字符组成。三个示例字符串分别用于测试，输出结果显示了函数的返回值。