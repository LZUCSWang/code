

# cm_elog 分析（1）

​		这一部分通过分析`cm_elog`中的部分函数用来解释opengauss数据库对日志的相关操作

![cm_elog 分析(1)](D:\xmind\cm_elog 分析(1).png)

[TOC]



## `SetFdCloseExecFlag` 函数

### 参数

- `fp`（类型：`FILE*`）：一个指向 `FILE` 流的指针，用于获取其关联的文件描述符。

### 返回值

- `int`：返回值表示函数执行的结果，0 表示成功，-1 表示失败。

### 功能

`SetFdCloseExecFlag` 函数的主要功能是为与给定 `FILE` 流关联的文件描述符设置关闭执行标志。具体细节如下：

1. 通过调用 `fileno(fp)` 函数，获取与 `FILE` 流 `fp` 关联的文件描述符 `fd`。
2. 通过调用 `fcntl(fd, F_GETFD)` 函数，获取当前文件描述符 `fd` 的标志。
3. 如果获取标志失败（`flags < 0`），则打印错误消息，并返回失败。
4. 在标志中设置 `FD_CLOEXEC` 标志位，以确保在执行时关闭文件描述符。
5. 通过调用 `fcntl(fd, F_SETFD, flags)` 函数，将修改后的标志重新设置回文件描述符 `fd`。
6. 如果设置标志失败（`ret == -1`），则打印错误消息。

### 注意事项

- 如果函数返回值为 -1，表示设置标志失败，请检查错误消息以获取详细信息。
- 本函数执行后，关联的文件描述符将在执行时自动关闭，这对于确保文件描述符不被不必要的子进程继承非常有用。

### 示例

```c
// 示例用法
FILE* myFile = fopen("example.txt", "r");
if (myFile != NULL) {
    int result = SetFdCloseExecFlag(myFile);
    if (result == 0) {
        // 文件描述符标志已成功设置
        // 可以在这里进行文件操作
        // ...
    } else {
        // 文件描述符标志设置失败
        // 可以处理错误情况
        // ...
    }
    fclose(myFile);
}
```



## `AlarmLogImplementation` 函数

### 参数

- `level`（类型：`int`）：日志级别，表示日志的重要程度。
- `prefix`（类型：`const char*`）：日志前缀，用于标识日志来源。
- `logtext`（类型：`const char*`）：日志内容文本，包含要记录的日志信息。

### 返回值

无返回值（`void`）。

### 功能

`AlarmLogImplementation` 函数用于执行日志记录操作，根据日志级别 `level` 将指定的日志内容写入日志文件中。具体功能如下：

1. 根据传入的 `level` 参数，决定是否记录日志。只有 `ALM_DEBUG` 和 `ALM_LOG` 两个级别的日志会被记录，其他级别的日志将被忽略。
2. 如果 `level` 参数为 `ALM_DEBUG` 或 `ALM_LOG`，则将 `prefix` 和 `logtext` 拼接成一条完整的日志文本，然后使用 `write_runlog(LOG, ...)` 函数写入日志文件。
3. 日志文件中的格式为 `prefix + logtext`。
4. 如果 `level` 参数不是 `ALM_DEBUG` 或 `ALM_LOG`，则不执行任何操作。

### 注意事项

- 该函数用于根据日志级别记录日志，确保传入的 `level` 参数为 `ALM_DEBUG` 或 `ALM_LOG` 以启用日志记录。
- 日志级别的含义如下：
  - `ALM_DEBUG`：调试级别日志
  - `ALM_LOG`：普通日志级别
- 如果需要记录其他级别的日志，可能需要修改函数的实现。
- 请确保在使用该函数前初始化日志记录系统和文件。

### 示例

```c
// 示例用法
const char* prefix = "[INFO] ";
const char* logtext = "This is an informational message.";
int level = ALM_LOG;

// 调用 AlarmLogImplementation 记录日志
AlarmLogImplementation(level, prefix, logtext);
```



## `setup_formatted_log_time` 函数

### 功能

`setup_formatted_log_time` 函数用于设置 `formatted_log_time`，以保持CSV日志和常规日志之间的时间一致性。

### 参数

无参数。

### 返回值

无返回值（`void`）。

### 详细说明

该函数的主要功能如下：

1. 创建一个 `struct timeval` 结构体 `tv` 用于存储时间信息，并初始化为0。
2. 创建一个 `time_t` 类型的变量 `stamp_time`，用于存储时间戳。
3. 创建一个字符数组 `msbuf` 用于存储毫秒部分。
4. 创建一个 `struct tm` 结构体 `timeinfo` 用于存储时间相关信息，并初始化为0。
5. 使用 `gettimeofday(&tv, NULL)` 获取当前时间，并将其存储在 `tv` 结构体中。
6. 提取 `tv` 结构体的秒部分，并将其转换为 `time_t` 类型，存储在 `stamp_time` 变量中。
7. 使用 `localtime_r(&stamp_time, &timeinfo)` 将 `stamp_time` 转换为本地时间表示，并存储在 `timeinfo` 结构体中。
8. 使用 `strftime` 函数将时间信息格式化为字符串，并存储在 `formatted_log_time` 中，同时保留位置以添加毫秒部分。
9. 将毫秒部分从 `tv` 中提取并格式化为字符串，并将其粘贴到 `formatted_log_time` 中，以生成完整的时间字符串。

### 注意事项

- 该函数用于确保CSV日志和常规日志的时间戳格式一致。
- 函数中的时间格式为 "%Y-%m-%d %H:%M:%S     %Z"，可根据需要进行修改。
- 请确保在调用该函数之前已经初始化了 `formatted_log_time`、`MSBUF_LENGTH`、`sprintf_s`、`securec_check_ss_c`、`rc` 和 `rcs`。

### 示例

```c
// 示例用法
setup_formatted_log_time();

// 现在，formatted_log_time 包含了格式化后的时间字符串，包括毫秒部分。
```



## `is_log_level_output` 函数

### 功能

`is_log_level_output` 函数用于检查 `elevel` 是否在逻辑上大于或等于 `log_min_level`。

### 参数

- `elevel`（类型：`int`）：表示日志级别，用于判断日志消息的重要性。
- `log_min_level`（类型：`int`）：表示最低要求的日志级别，用于确定是否应记录日志消息。

### 返回值

返回值为布尔类型 `bool`，如果 `elevel` 大于或等于 `log_min_level`，则返回 `true`；否则返回 `false`。

### 详细说明

该函数的主要功能如下：

- 用于测试确定日志消息是否属于指定的日志级别或更高级别。
- 处理了日志级别为 `LOG` 时的特殊情况，使得 `LOG` 级别的消息可以排序在 `ERROR` 和 `FATAL` 级别之间。
- 通常用于确定消息是否应写入 postmaster 日志。对于判断消息是否应发送给客户端，通常只需要进行简单的比较（例如，>=）即可。

### 步骤说明

- 如果 `elevel` 等于 `LOG`，则执行以下检查：
  - 如果 `log_min_level` 也等于 `LOG` 或者小于等于 `ERROR`，则返回 `true`。
- 如果 `log_min_level` 等于 `LOG`，则执行以下检查：
  - 如果 `elevel` 不等于 `LOG` 且大于等于 `FATAL`，则返回 `true`。
- 如果 `elevel` 大于等于 `log_min_level`，则返回 `true`。
- 如果以上条件均不满足，则返回 `false`。

### 注意事项

- 该函数用于确定日志消息的记录级别是否满足最低要求。
- 如果需要判断消息是否应发送给客户端，通常只需要进行简单的比较，而不需要使用此函数。
- 请注意，`elevel` 和 `log_min_level` 都是整数，表示不同的日志级别。

### 示例

```c
// 示例用法
int logLevel = ALM_LOG;
int minLogLevel = ERROR;

bool result = is_log_level_output(logLevel, minLogLevel);

if (result) {
    // 记录日志消息，因为 logLevel >= minLogLevel
} else {
    // 不记录日志消息，因为 logLevel < minLogLevel
}
```



## `write_runlog` 函数

![write_runlog](D:\xmind\write_runlog.png)

### 功能

`write_runlog` 函数用于记录日志消息，支持不同级别的日志消息，将日志消息输出到服务器日志文件或标准输出。

### 参数

- `elevel`（类型：`int`）：表示日志级别，用于指示日志消息的重要性。
- `fmt`（类型：`const char*`）：表示日志消息的格式字符串，支持可变参数。

### 返回值

该函数没有返回值（`void`）。

### 详细说明

该函数的主要功能如下：

- 根据指定的日志级别（`elevel`）和消息格式（`fmt`），生成日志消息。
- 检查是否应将该日志消息记录到服务器日志文件，如果不需要，则提前返回。
- 如果需要记录日志消息，会进行以下操作：
  - 获取国际化文本，如果适用。
  - 对消息进行格式化处理，包括时间戳、线程信息等。
  - 将日志消息输出到标准输出，如果适用。
  - 将日志消息添加到服务器日志文件，如果适用。

### 步骤说明

1. 检查是否应将日志消息记录到服务器日志文件，如果 `elevel` 小于最低记录级别 `log_min_messages`，则不记录，提前返回。
2. 获取国际化文本，如果 `fmt` 需要进行国际化处理。
3. 如果 `prefix_name` 不为空且等于 "cm_ctl"，执行以下操作：
   - 如果 `fmt` 等于 "."，表示要记录一个特殊的消息，处理特殊逻辑并返回。
   - 如果 `elevel` 大于等于 `LOG` 或者服务器日志文件路径未初始化，执行以下操作：
     - 检查并输出 dot 计数消息，重置 dot 计数标志。
     - 格式化日志消息，包括添加前缀等，输出到标准输出。
4. 格式化日志消息，将格式化后的消息存储在 `errbuf` 中。
5. 根据 `log_destion_choice` 的值，执行相应的操作：
   - 如果 `log_destion_choice` 为 `LOG_DESTION_FILE`，执行以下操作：
     - 添加日志前缀（例如，时间戳）到日志消息中。
     - 将日志消息写入服务器日志文件。
   
### 注意事项

- 该函数支持不同的日志级别，允许记录不同重要性的日志消息。
- 可以通过调整 `log_min_messages` 设置最低记录级别，低于该级别的日志消息将不会被记录。
- 该函数支持国际化文本处理，通过 `_(fmt)` 进行处理。
- 在特殊情况下，函数会输出 dot 计数消息，用于某些特殊处理逻辑。
- 如果需要将日志消息记录到服务器日志文件，请设置 `log_destion_choice` 为 `LOG_DESTION_FILE`。
- 日志消息的格式可以通过 `fmt` 参数进行自定义，支持可变参数。

### 示例

```c
// 示例用法
int logLevel = ALM_LOG;
const char* logMessage = "This is a log message.";

write_runlog(logLevel, "%s", logMessage);
```

根据日志级别和配置，该日志消息可能会被记录到服务器日志文件或标准输出。



## `add_message_string` 函数

### 参数

- `errmsg_tmp`：用于存储错误消息组件的缓冲区指针。
- `errdetail_tmp`：用于存储错误详细信息组件的缓冲区指针。
- `errmodule_tmp`：用于存储错误模块组件的缓冲区指针。
- `errcode_tmp`：用于存储错误代码组件的缓冲区指针。
- `fmt`：包含消息组件的格式化错误消息。

### 返回值

- `int`：成功返回0，失败时返回错误代码。

### 功能

该函数从格式化的错误消息中提取不同的错误消息组件（ERRMSG、ERRDETAIL、ERRMODULE、ERRCODE）。
格式化的错误消息应包括标签如"[ERRMSG]:"、"[ERRDETAIL]:"、"[ERRMODULE]:"和"[ERRCODE]:"，
以指定每个组件的类型。函数根据这些标签提取并存储在相应的缓冲区中。

### 注意事项

- 该函数期望格式化的错误消息中包含特定标签，用于标识不同的消息组件。
- 错误消息组件的提取和存储依赖于标签的存在和格式。
- 函数在处理错误消息时应小心，以避免内存越界或数据损坏。

### 示例

```c
char errmsg[BUF_LEN] = {0};
char errdetail[BUF_LEN] = {0};
char errmodule[BUF_LEN] = {0};
char errcode[BUF_LEN] = {0};
const char* formatted_error = "[ERRMSG]:Something went wrong [ERRDETAIL]:This is a detailed error message [ERRMODULE]:ModuleX [ERRCODE]:12345";
add_message_string(errmsg, errdetail, errmodule, errcode, formatted_error);
// 现在 errmsg、errdetail、errmodule、errcode 分别包含相应的消息组件。
```

以上是 `add_message_string` 函数的用法示例。



## `add_log_prefix2 函数

该函数用于添加日志消息的前缀信息，包括时间戳、线程信息以及错误模块和错误代码。

### 参数

- `elevel`：日志级别。
- `errmodule_tmp`：错误模块字符串。
- `errcode_tmp`：错误代码字符串。
- `str`：原始日志消息字符串。

### 返回值

无返回值。

### 功能

1. 初始化一个用于构建日志消息的临时字符数组 `errbuf_tmp`，大小为 `BUF_LEN * 3`。
2. 定义一个用于字符串操作的错误码变量 `rc` 和一个整数变量 `rcs` 作为返回码。
3. 使用 `setup_formatted_log_time` 函数设置日志消息的时间戳和线程信息。
4. 统一日志样式，如果线程名称 `thread_name` 为 NULL，则将其设置为空字符串。
5. 如果错误模块 `errmodule_tmp` 和错误代码 `errcode_tmp` 不为空，则构建包含错误模块和错误代码的日志消息。
6. 如果错误模块和错误代码为空，则构建不包含错误模块和错误代码的日志消息。
7. 使用 `snprintf_s` 函数构建日志消息，并将结果存储在 `errbuf_tmp` 中。
8. 检查日志消息的长度是否超过最大长度限制（2048）。
9. 使用 `strncat_s` 函数将原始日志消息 `str` 追加到 `errbuf_tmp` 中。
10. 使用 `memcpy_s` 函数将构建的日志消息复制回原始的 `str` 中。
11. 添加字符串终止符，确保日志消息的字符串以 null 结束。

### 注意事项

- 该函数不处理日志消息的输出，只负责构建带有前缀信息的日志消息。

### 示例

```c
char log_message[BUF_LEN * 2] = {0};
const char* errmodule = "MODULE";
const char* errcode = "ERROR123";
int log_level = LOG;

add_log_prefix2(log_level, errmodule, errcode, log_message);
printf("Log Message: %s\n", log_message);
```

在上述示例中，函数 `add_log_prefix2` 用于构建带有前缀信息的日志消息，然后通过 `printf` 输出该日志消息。




##  `write_runlog3` 函数

### 参数

- `elevel`：日志级别（整数）。
- `errmodule_tmp`：错误模块名称（字符串）。可选。
- `errcode_tmp`：错误代码（字符串）。可选。
- `fmt`：格式化的日志消息字符串，支持可变参数（字符串）。

### 返回值
无。

### 功能
`write_runlog3` 函数用于将错误信息写入 stderr（标准错误流），或者使用等效方式，当标准错误不可用时。此函数接受日志级别和其他参数，并将格式化的日志消息输出到标准错误或其他适当的输出通道。

### 注意事项
- 在使用 `write_runlog3` 函数之前，请确保以下全局变量和函数已正确设置和初始化：
    - `log_min_messages`：最小允许的日志级别。
    - `formatted_log_time`：格式化的时间戳。
    - `is_log_level_output`：判断是否需要输出日志消息的函数。
- 日志消息的格式化字符串 `fmt` 可以包含国际化文本。函数内部使用 `_()` 进行本地化处理，所以 `fmt` 的内容可以适应不同的语言和地区。
- 函数会根据不同的条件选择是否将日志消息输出到标准错误或其他输出通道。这取决于给定的日志级别和其他条件。
- 如果日志消息中包含特殊字符，如百分号 `%`，请确保使用 `%` 转义来避免不正确的格式化。
- 请确保在使用本函数之前已初始化相关的全局变量，以确保正确的日志记录行为。

### 示例
```c
// 示例 1: 以 ERROR 级别记录一条日志消息
write_runlog3(ERROR, "模块A", "ERR001", "这是一条错误消息：%s", error_description);

// 示例 2: 以 INFO 级别记录一条国际化日志消息
write_runlog3(INFO, "模块B", "", _("这是一条信息消息：%s"), info_message);

// 示例 3: 记录一条特殊消息，跳过特定条件下的输出
write_runlog3(INFO, "模块C", "", ".");
```


