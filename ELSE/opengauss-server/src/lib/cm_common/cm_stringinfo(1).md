# cm_stringinfo函数解析（1）

![cm_stringinfo(1)](D:\xmind\cm_stringinfo(1).png)

[TOC]



##  函数名

### `CM_makeStringInfo`
## 返回值
- `CM_StringInfo`：返回一个指向 `CM_StringInfo` 结构的指针。
## 功能
该函数用于创建并初始化一个 `CM_StringInfo` 结构。
## 注意事项
- 如果内存分配失败，函数将打印错误消息并终止程序运行。
## 示例
```c
#include <stdio.h>
#include <stdlib.h>

typedef struct CM_StringInfoData {
    // 数据结构的成员
    // ...
} CM_StringInfoData;

typedef CM_StringInfoData* CM_StringInfo;

void write_runlog(int level, const char* message) {
    // 写日志的实现
    // ...
}

void CM_initStringInfo(CM_StringInfo str_info) {
    // 初始化CM_StringInfo结构的实现
    // ...
}

CM_StringInfo CM_makeStringInfo(void) {
    CM_StringInfo res;

    // 分配内存以存储CM_StringInfo结构
    res = (CM_StringInfo)malloc(sizeof(CM_StringInfoData));
    if (res == NULL) {
        // 如果内存分配失败，记录错误消息并终止程序运行
        write_runlog(ERROR, "malloc CM_StringInfo failed, out of memory.\n");
        exit(1);
    }

    // 初始化CM_StringInfo结构
    CM_initStringInfo(res);

    return res;
}

int main() {
    CM_StringInfo str_info = CM_makeStringInfo();
    // 使用str_info进行操作
    // ...

    free(str_info); // 释放内存
    return 0;
}
```

在上述示例中，`CM_makeStringInfo` 函数用于创建一个 `CM_StringInfo` 结构，并返回指向该结构的指针。如果内存分配失败，将记录错误消息并终止程序运行。该函数在示例程序的 `main` 函数中被调用，可以用于操作 `str_info` 结构。最后，别忘了在程序结束时释放内存。


##  函数名
### `CM_destroyStringInfo`
## 参数
- `CM_StringInfo str`：要销毁的 `CM_StringInfo` 结构的指针。
## 功能
该函数用于销毁并释放一个 `CM_StringInfo` 结构及其相关的资源。具体操作包括：
- 检查传入的 `str` 指针是否为非空，如果为空则不执行销毁操作。
- 检查 `str` 结构中的 `maxlen` 成员是否大于0，如果大于0，则释放 `data` 成员所指向的内存。
- 最后，释放 `str` 指向的内存空间。
## 注意事项
- 在调用该函数之前，确保传入的 `CM_StringInfo` 结构是通过 `CM_makeStringInfo` 函数创建的，否则可能会导致未定义的行为。
## 示例
```c
#include <stdio.h>
#include <stdlib.h>

typedef struct CM_StringInfoData {
    char* data;
    int maxlen;
    // 数据结构的其他成员
    // ...
} CM_StringInfoData;

typedef CM_StringInfoData* CM_StringInfo;

void FREE_AND_RESET(char* ptr) {
    // 释放内存并将指针置为NULL的实现
    // ...
}

void CM_destroyStringInfo(CM_StringInfo str) {
    if (str != NULL) {
        if (str->maxlen > 0) {
            FREE_AND_RESET(str->data); // 释放data指向的内存
        }
        free(str); // 释放CM_StringInfo结构的内存
    }
    return;
}

int main() {
    CM_StringInfo str_info = CM_makeStringInfo();
    // 使用str_info进行操作
    // ...

    CM_destroyStringInfo(str_info); // 销毁str_info及其资源
    return 0;
}
```

在上述示例中，`CM_destroyStringInfo` 函数用于销毁一个 `CM_StringInfo` 结构及其相关的资源，包括释放 `data` 指向的内存和销毁 `str` 结构本身。确保在调用该函数之前，传入的 `CM_StringInfo` 结构是通过 `CM_makeStringInfo` 函数创建的。

##  函数名
### `CM_freeStringInfo`
## 参数
- `CM_StringInfo str`：要释放的 `CM_StringInfo` 结构的指针。
## 功能
该函数用于释放一个 `CM_StringInfo` 结构的相关资源，具体操作包括：
- 检查传入的 `str` 结构中的 `maxlen` 成员是否大于0，如果大于0，则释放 `data` 成员所指向的内存。
## 注意事项
- 在调用该函数之前，确保传入的 `CM_StringInfo` 结构是通过合适的方式创建的，以防止未定义的行为。
- 该函数只负责释放相关资源，不会销毁 `str` 结构本身。如果需要销毁整个 `CM_StringInfo` 结构，应使用 `CM_destroyStringInfo` 函数。
## 示例
```c
#include <stdio.h>
#include <stdlib.h>

typedef struct CM_StringInfoData {
    char* data;
    int maxlen;
    // 数据结构的其他成员
    // ...
} CM_StringInfoData;

typedef CM_StringInfoData* CM_StringInfo;

void FREE_AND_RESET(char* ptr) {
    // 释放内存并将指针置为NULL的实现
    // ...
}

void CM_freeStringInfo(CM_StringInfo str) {
    if (str->maxlen > 0) {
        FREE_AND_RESET(str->data); // 释放data指向的内存
    }
    return;
}

int main() {
    CM_StringInfo str_info = CM_makeStringInfo();
    // 使用str_info进行操作
    // ...

    CM_freeStringInfo(str_info); // 释放str_info相关资源
    // str_info指针仍然有效，但数据资源已释放
    return 0;
}
```

在上述示例中，`CM_freeStringInfo` 函数用于释放一个 `CM_StringInfo` 结构的相关资源，包括释放 `data` 指向的内存。请注意，该函数不会销毁 `str` 结构本身，如果需要销毁整个 `CM_StringInfo` 结构，应使用 `CM_destroyStringInfo` 函数。

## 函数名
### `CM_dupStringInfo`

## 参数
- `CM_StringInfo orig`：要复制的 `CM_StringInfo` 结构的指针。

## 返回值
- `CM_StringInfo`：返回一个指向新创建的 `CM_StringInfo` 结构的指针，其中包含复制的内容。

## 功能
该函数用于创建一个新的 `CM_StringInfo` 结构，并将原始结构的内容复制到新结构中。具体操作包括：
- 创建一个新的 `CM_StringInfo` 结构并初始化。
- 如果原始结构中的 `len` 成员大于0，则将原始结构中的数据复制到新结构中，并将新结构的 `cursor` 成员设置为原始结构的 `cursor` 值。

## 注意事项
- 在调用该函数之前，确保传入的 `CM_StringInfo` 结构 `orig` 是有效的。
- 函数返回的新结构需要在适当的时候进行释放，以避免内存泄漏。

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

void CM_appendBinaryStringInfo(CM_StringInfo str, const char* data, int len) {
    // 在str中追加二进制数据的实现
    // ...
}

CM_StringInfo CM_makeStringInfo(void) {
    // 创建并初始化CM_StringInfo结构的实现
    // ...
}

CM_StringInfo CM_dupStringInfo(CM_StringInfo orig) {
    CM_StringInfo newvar;

    newvar = CM_makeStringInfo();
    if (newvar == NULL) {
        return (newvar);
    }

    if (orig->len > 0) {
        CM_appendBinaryStringInfo(newvar, orig->data, orig->len);
        newvar->cursor = orig->cursor;
    }
    return (newvar);
}

int main() {
    CM_StringInfo str_info = CM_makeStringInfo();
    // 使用str_info进行操作
    // ...

    CM_StringInfo dup_info = CM_dupStringInfo(str_info); // 复制str_info
    // 使用dup_info进行操作
    // ...

    // 在适当的时候释放str_info和dup_info的内存
    // ...

    return 0;
}
```

在上述示例中，`CM_dupStringInfo` 函数用于创建一个新的 `CM_StringInfo` 结构，并将原始结构的内容复制到新结构中。需要注意的是，返回的新结构需要在适当的时候进行释放，以避免内存泄漏。

## 函数名
### `CM_initStringInfo`

## 参数
- `CM_StringInfo str`：要初始化的 `CM_StringInfo` 结构的指针。

## 功能
该函数用于初始化一个 `CM_StringInfo` 结构，使其描述一个空字符串。具体操作包括：
- 分配一个初始默认大小为1024字节的内存缓冲区，并将指针存储在 `str->data` 中。
- 如果内存分配失败，函数将打印错误消息并终止程序运行。
- 设置 `str->maxlen` 成员为分配的缓冲区大小。
- 调用 `CM_resetStringInfo` 函数，将 `str` 结构重置为空字符串。

## 注意事项
- 在调用该函数之前，确保传入的 `CM_StringInfo` 结构 `str` 是有效的。
- 函数分配的内存需要在适当的时候进行释放，以防止内存泄漏。

## 示例
```c
#include <stdio.h>
#include <stdlib.h>

typedef struct CM_StringInfoData {
    char* data;
    int maxlen;
    int len;
    int cursor;
    // 数据结构的其他成员
    // ...
} CM_StringInfoData;

typedef CM_StringInfoData* CM_StringInfo;

void write_runlog(int level, const char* message) {
    // 写日志的实现
    // ...
}

void CM_resetStringInfo(CM_StringInfo str) {
    // 重置CM_StringInfo结构的实现，将其初始化为空字符串
    // ...
}

void CM_initStringInfo(CM_StringInfo str) {
    int size = 1024; /* initial default buffer size */

    str->data = (char*)malloc(size);
    if (str->data == NULL) {
        write_runlog(ERROR, "malloc CM_StringInfo->data failed, out of memory.\n");
        exit(1);
    }
    str->maxlen = size;
    CM_resetStringInfo(str);
}

int main() {
    CM_StringInfo str_info = CM_makeStringInfo();
    // 使用str_info进行操作
    // ...

    // 在适当的时候释放str_info的内存
    // ...

    return 0;
}
```

在上述示例中，`CM_initStringInfo` 函数用于初始化一个 `CM_StringInfo` 结构，使其描述一个空字符串。它会分配一个初始默认大小的内存缓冲区，并将其相关信息存储在 `str` 结构中。确保在调用函数后，释放分配的内存以避免内存泄漏。

## 函数名
### `CM_resetStringInfo`

## 参数
- `CM_StringInfo str`：要重置的 `CM_StringInfo` 结构的指针。

## 功能
该函数用于重置一个 `CM_StringInfo` 结构，使其保持有效的数据缓冲区，但清除之前的内容。具体操作包括：
- 检查传入的 `str` 是否为NULL，如果为NULL则不执行任何操作。
- 将数据缓冲区的第一个字符设置为终止符 '\0'，表示空字符串。
- 将 `len` 成员设置为0，表示字符串长度为0。
- 将 `cursor`、`qtype` 和 `msglen` 成员都设置为0。

## 注意事项
- 在调用该函数之前，确保传入的 `CM_StringInfo` 结构 `str` 是有效的。
- 该函数只清除数据内容，不会释放相关的内存。如果需要释放内存并重置结构，请使用其他适当的函数。

## 示例
```c
#include <stdio.h>
#include <stdlib.h>

typedef struct CM_StringInfoData {
    char* data;
    int maxlen;
    int len;
    int cursor;
    int qtype;
    int msglen;
    // 数据结构的其他成员
    // ...
} CM_StringInfoData;

typedef CM_StringInfoData* CM_StringInfo;

void CM_resetStringInfo(CM_StringInfo str) {
    if (str == NULL) {
        return;
    }

    str->data[0] = '\0'; // 清除数据内容
    str->len = 0; // 重置长度为0
    str->cursor = 0; // 重置游标为0
    str->qtype = 0; // 重置qtype为0
    str->msglen = 0; // 重置msglen为0
}

int main() {
    CM_StringInfo str_info = CM_makeStringInfo();
    // 使用str_info进行操作
    // ...

    CM_resetStringInfo(str_info); // 重置str_info的内容

    // 继续使用str_info进行操作，它现在是一个空字符串
    // ...

    // 在适当的时候释放str_info的内存
    // ...

    return 0;
}
```

在上述示例中，`CM_resetStringInfo` 函数用于重置一个 `CM_StringInfo` 结构，保持其有效的数据缓冲区，但清除之前的内容。在示例中，我们首先创建一个 `str_info` 结构，使用它进行操作，然后通过调用 `CM_resetStringInfo` 函数将其内容重置为空字符串，以便继续使用。


