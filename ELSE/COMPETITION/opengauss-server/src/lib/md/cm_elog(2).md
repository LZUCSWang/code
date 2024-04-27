# cm_elog 分析（2）

​		这一部分通过分析`cm_elog`中的部分函数用来解释opengauss数据库对日志的相关操作

![cm_elog 分析(2)](D:\xmind\cm_elog 分析(2).png)

[TOC]



## `errmodule` 函数

### 参数

- `id`: 表示错误模块的 ModuleId。

### 返回值

- 返回一个指向包含格式化错误模块消息的字符数组的指针。

### 功能

该函数基于提供的 `ModuleId` 生成一个错误模块消息，具体功能如下：

1. 接受一个 `ModuleId` 参数 `id`，并生成一个错误模块消息。
2. 错误模块消息以"[ERRMODULE]:"为前缀。
3. 使用 `get_valid_module_name(id)` 获取与提供的 `ModuleId` 对应的实际模块名称。
4. 将获得的模块名称与前缀连接，并存储在 `errbuf_errmodule` 中。
5. 确保 `errbuf_errmodule` 以空字符结尾。
6. 调用者应该注意返回的错误模块消息存储在一个本地数组中，一旦函数退出，它的内存可能会失效。

### 注意事项

- 调用者需要处理和管理返回的错误模块消息的内存。
- 请确保在使用 `get_valid_module_name(id)` 之前，已经合适地本地化或翻译模块名称，以适应不同的语言环境。
- 函数使用安全的 C 库函数来处理字符串和内存操作，以减少潜在的安全漏洞。

### 示例

```c
#include <stdio.h>

int main() {
    ModuleId moduleId = get_module_id(); // Get the current module ID.
    const char* moduleMessage = errmodule(moduleId);
    printf("%s\n", moduleMessage);

    return 0;
}
```

在这个示例中，`errmodule` 函数用于生成一个错误模块消息，然后将其打印出来。调用者需要注意处理返回的错误模块消息的内存。



## `logfile_open` 函数

![logfile_open](D:\xmind\logfile_open.png)

### 参数
- `log_path`：指向包含日志文件的目录路径的字符串指针。
- `mode`：以字符串形式表示的文件打开模式，例如 "w"（写入）或 "a"（追加）等。

### 返回值
- 返回类型：`FILE*`，指向已打开日志文件的文件指针。
- 如果打开失败，返回值为 `NULL`，并且 `errno` 将设置为对应的错误代码。

### 功能
`logfile_open` 函数用于以适当的权限和缓冲选项打开一个新的日志文件。它还支持处理打开失败的情况，根据 `allow_errors` 参数的值来决定是否视为致命错误。

### 注意事项
- 如果传递给 `log_path` 的指针为 `NULL`，函数将输出一条错误消息并返回 `NULL`，同时保持 `errno` 为表示打开失败的错误代码。
- 函数内部会设置文件权限掩码（`umask`）以确保适当的文件权限。
- 它会在指定的 `log_path` 目录下查找当前的日志文件，以检查是否存在一个当前日志文件。
- 如果找到当前日志文件，函数会返回该文件的文件指针。否则，函数会生成一个新的当前日志文件名，其中包含当前系统时间和其他信息，并使用该名称创建新的当前日志文件。
- 函数会设置文件的缓冲选项，并在Windows系统上使用CRLF换行符。
- 它还会设置 `FD_CLOEXEC` 标志，以确保子进程不会继承父进程的文件句柄。
- 如果 `allow_errors` 参数为 `true`，函数将只记录打开失败的情况，并返回 `NULL`，而不视为致命错误。如果为 `false`，则打开失败将被视为致命错误，函数将输出错误消息并终止程序。
- 如果打开日志文件失败，函数将输出一条错误消息并返回 `NULL`，同时保持 `errno` 为表示打开失败的错误代码。
- 函数还会记录当前打开的日志文件名，以备将来使用。

### 示例
```c
// 示例代码
int main() {
    const char* logPath = "/var/log/myapp"; // 日志文件存放路径
    const char* mode = "a"; // 打开模式为追加

    FILE* logFile = logfile_open(logPath, mode);

    if (logFile != NULL) {
        fprintf(logFile, "日志条目 1\n");
        fprintf(logFile, "日志条目 2\n");
        fclose(logFile);
    } else {
        printf("无法打开日志文件。\n");
    }

    return 0;
}
```

上述示例演示了如何使用 `logfile_open` 函数打开一个日志文件，并向其中写入日志条目。如果打开失败，程序将输出错误消息。



## `logfile_init` 函数

### 参数
无

### 返回值
- 返回类型：`int`
- 返回值为 `0` 表示初始化成功。

### 功能
`logfile_init` 函数用于初始化日志文件系统，它会创建并初始化必要的数据结构和锁。通常在程序的启动阶段调用此函数以准备日志系统的使用。

### 注意事项
- 如果初始化过程中出现错误，该函数会将错误消息打印到 stderr 并以非零状态码退出程序。

### 示例
```c
// 在程序的启动阶段调用logfile_init函数以初始化日志系统。
int main() {
    if (logfile_init() != 0) {
        fprintf(stderr, "日志系统初始化失败。\n");
        return 1;
    }

    // 继续执行程序的其他部分...

    return 0;
}
```

上述示例演示了如何在程序的启动阶段调用 `logfile_init` 函数来初始化日志系统。如果初始化失败，程序会打印错误消息并返回非零状态码。



## `is_comment_line` 函数

### 参数
- `str`: 一个指向要检查的输入字符串的指针。

### 返回值
- 如果输入字符串是注释行，则返回1。
- 如果输入字符串不是注释行，则返回0。

### 功能
这个函数用于检查一个给定的字符串是否表示配置文件中的注释行。注释行是以 '#' 字符开头的行。

### 注意事项
- 如果输入字符串为NULL，函数将打印错误消息并以状态码1退出。

### 示例
```c
#include <stdio.h>
#include <stdlib.h>

int is_comment_line(const char* str) {
    size_t ii = 0; // 用于遍历输入字符串的索引。

    if (str == NULL) {
        printf("bad config file line\n");
        exit(1); // 如果输入字符串为NULL，则打印错误消息并退出。
    }

    /* 跳过前导空格。 */
    for (;;) {
        if (*(str + ii) == ' ') {
            ii++;  /* 跳过空格字符 */
        } else {
            break; // 当遇到非空格字符时退出循环。
        }
    }

    if (*(str + ii) == '#') {
        return 1;  // 输入字符串是注释行。
    }

    return 0;  // 输入字符串不是注释行。
}

int main() {
    const char* line1 = "# This is a comment line";
    const char* line2 = "Not a comment line";

    int result1 = is_comment_line(line1);
    int result2 = is_comment_line(line2);

    printf("Result 1: %d\n", result1); // 应打印 "Result 1: 1"
    printf("Result 2: %d\n", result2); // 应打印 "Result 2: 0"

    return 0;
}
```

上述示例演示了如何使用`is_comment_line`函数来检查输入字符串是否为注释行。



## `get_authentication_type` 函数

### 参数
- `config_file`: 指向要读取的配置文件路径的指针。

### 返回值
- 鉴权类型：
  - `CM_AUTH_TRUST`：如果文件中未指定鉴权方法或文件为NULL。
  - `CM_AUTH_GSS`：如果文件中指定了鉴权方法为"gss"。

### 功能
该函数用于从指定的配置文件中读取并获取鉴权类型设置。鉴权类型决定了如何处理身份验证。

### 注意事项
- 如果无法打开指定的配置文件，该函数将打印错误消息并以状态码1退出。
- 该函数还调用了is_comment_line函数，以跳过文件中的注释行。
- 鉴权类型是通过在文件中搜索"cm_auth_method"设置来确定的。如果找到"trust"，则返回`CM_AUTH_TRUST`；如果找到"gss"，则返回`CM_AUTH_GSS`。如果两者都未找到，默认情况下返回`CM_AUTH_TRUST`。

### 示例
```c
#include <stdio.h>
#include <stdlib.h>

/* 此处省略is_comment_line函数的定义 */

#define BUF_LEN 256
#define ERROR_LIMIT_LEN 256
#define CM_AUTH_TRUST 0
#define CM_AUTH_GSS 1

int get_authentication_type(const char* config_file)
{
    char buf[BUF_LEN]; // 用于从配置文件中读取行的缓冲区。
    FILE* fd = NULL; // 配置文件的文件描述符。
    int type = CM_AUTH_TRUST; // 默认鉴权类型为trust。

    if (config_file == NULL) {
        return CM_AUTH_TRUST;  /* 默认级别: CM_AUTH_TRUST */
    }

    // 尝试以只读模式打开配置文件。
    fd = fopen(config_file, "r");
    if (fd == NULL) {
        char errBuffer[ERROR_LIMIT_LEN];
        printf("无法打开配置文件：%s %s\n", config_file, pqStrerror(errno, errBuffer, ERROR_LIMIT_LEN));
        exit(1);
    }

    // 从配置文件中读取每一行。
    while (!feof(fd)) {
        errno_t rc;
        rc = memset_s(buf, BUF_LEN, 0, BUF_LEN); // 将缓冲区初始化为全零。
        securec_check_c(rc, "\0", "\0");
        (void)fgets(buf, BUF_LEN, fd); // 从文件中读取一行到缓冲区。

        // 使用is_comment_line函数跳过文件中的注释行。
        if (is_comment_line(buf) == 1) {
            continue;  /* 跳过以 '#' 开头的行（注释） */
        }

        // 在文件中查找"cm_auth_method"设置，并相应地更新鉴权类型。
        if (strstr(buf, "cm_auth_method") != NULL) {
            /* 检查所有行 */
            if (strstr(buf, "trust") != NULL) {
                type = CM_AUTH_TRUST; // 鉴权方法是trust。
            }

            if (strstr(buf, "gss") != NULL) {
                type = CM_AUTH_GSS; // 鉴权方法是gss。
            }
        }
    }

    fclose(fd); // 关闭配置文件。
    return type; // 返回确定的鉴权类型。
}
```

上述示例代码演示了如何使用`get_authentication_type`函数来从配置文件中获取鉴权类型。注意，示例中省略了`is_comment_line`函数的定义。



## `TrimToken` 函数

### 参数
- `src`：指向要修剪的源字符串的指针。
- `delim`：要从字符串两端修剪的定界符字符。

### 返回值
- 返回指向修剪后的字符串的指针，该字符串与输入字符串相同，但已删除前导和尾随的定界符。

### 功能
该函数用于修剪字符串的前导和尾随指定定界符字符。

### 注意事项
- 函数初始化指针's'和'e'为NULL，以跟踪修剪部分的起始和结束位置。
- 它遍历源字符串并查找字符串两端的定界符字符。
- 前导定界符被跳过，直到遇到非定界符字符（由's'指向）。
- 尾随定界符由'e'标记，如果找到，则函数将第一个尾随定界符替换为空终止符。
- 如果没有前导定界符，则's'被设置为源字符串的开头。
- 如果没有尾随定界符，则'e'仍然为NULL。

### 示例
```c
/* 示例用法：
   假设有一个字符串 "   hello world!   " 和定界符为空格 ' '。
   调用 TrimToken 后，将返回指向修剪后的字符串 "hello world!" 的指针。
*/
char str[] = "   hello world!   ";
char delim = ' ';
char* trimmed = TrimToken(str, delim);
printf("修剪后的字符串: \"%s\"\n", trimmed); // 应该打印 "修剪后的字符串: \"hello world!\""
```

上述示例演示了如何使用`TrimToken`函数来修剪字符串的前导和尾随定界符。



## `TrimPathDoubleEndQuotes` 函数

### 参数
- `path`：指向要修剪的路径字符串的指针。

### 返回值
- 无返回值（void）。

### 功能
该函数用于从路径字符串中移除前导和尾随的单引号（'）和双引号（"）。

### 注意事项
- 函数首先计算输入路径字符串的长度。
- 如果路径长度超过MAXPGPATH - 1（一个定义的限制），则函数不会进行修改，直接返回。
- 函数两次调用TrimToken函数，分别移除单引号（'）和双引号（"）。
- 在修剪后，结果路径被存储在临时缓冲区'buf'中，然后再复制回原始的'path'中。

### 示例
```c
/* 示例用法：
   假设有一个路径字符串 "   'example'  "。
   调用 TrimPathDoubleEndQuotes 后，将移除前导和尾随的单引号，
   最终'path'将包含修剪后的字符串 "example"。
*/
char path[] = "   'example'  ";
TrimPathDoubleEndQuotes(path);
printf("修剪后的路径: \"%s\"\n", path); // 应该打印 "修剪后的路径: \"example\""
```

上述示例演示了如何使用`TrimPathDoubleEndQuotes`函数从路径字符串中移除前导和尾随的引号。请注意，示例中省略了`TrimToken`函数的定义。



## `get_krb_server_keyfile` 函数

### 参数
- `config_file`：要读取的配置文件的路径指针。

### 返回值
- 无返回值（void）。

### 功能
该函数用于从配置文件中读取并提取Kerberos服务器密钥文件路径设置。

### 注意事项
- 该函数初始化用于解析和处理的各种变量。
- 如果输入的 `config_file` 为NULL，则函数将不进行任何更改并直接返回。
- 如果无法打开配置文件，则打印错误消息并以状态码1退出。
- 该函数遍历配置文件的各行，查找 "cm_krb_server_keyfile" 设置。
- 提取密钥文件路径值，移除前导和尾随的单引号，并将其存储在 'cm_krb_server_keyfile' 中。
- 同时还会移除密钥文件路径的前导和尾随空白字符。
- 成功提取和处理密钥文件路径后，函数返回。

### 示例
```c
/* 示例用法：
   假设有一个配置文件包含以下内容：
   cm_krb_server_keyfile = '/path/to/keyfile'
   其中 "/path/to/keyfile" 是Kerberos服务器密钥文件的路径。
   调用 get_krb_server_keyfile 后，将提取并存储密钥文件路径到 'cm_krb_server_keyfile' 中。

   注意：示例中省略了 'TrimPathDoubleEndQuotes' 函数的定义。
*/
const char* config_file = "config.conf";
get_krb_server_keyfile(config_file);

printf("Kerberos服务器密钥文件路径: \"%s\"\n", cm_krb_server_keyfile);
// 应该打印 "Kerberos服务器密钥文件路径: \"/path/to/keyfile\""
```

上述示例演示了如何使用 `get_krb_server_keyfile` 函数从配置文件中提取Kerberos服务器密钥文件路径设置，并将其存储在 'cm_krb_server_keyfile' 中。请注意，示例中省略了 'TrimPathDoubleEndQuotes' 函数的定义。

