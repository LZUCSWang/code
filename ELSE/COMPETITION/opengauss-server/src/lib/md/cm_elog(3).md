# cm_elog 分析（3）

​		 这一部分通过分析`cm_elog`中的部分函数用来解释opengauss数据库对日志的相关操作![cm_elog 分析(3)](D:\xmind\cm_elog 分析(3).png)

[TOC]



## `GetStringFromConf` 函数

### 参数
- `configFile`：指向要读取的配置文件路径的指针。
- `itemValue`：指向提取的值将被存储的缓冲区的指针。
- `itemValueLength`：`itemValue` 缓冲区的最大长度。
- `itemName`：需要提取其值的配置项的名称。

### 返回值
无。

### 功能
该函数从指定的配置文件中读取并提取与提供的 `itemName` 相关联的值，并将该值存储在 `itemValue` 中。

### 注意事项
- 该函数初始化了各种用于解析和操作的变量。
- 如果输入的 `configFile` 为 NULL，则函数将不做任何更改而返回。
- 如果无法打开配置文件，则打印错误消息并以状态代码 1 退出，其中提到了 `itemName`。
- 该函数遍历配置文件的各行，搜索 `itemName`。
- 它提取与 `itemName` 相关联的值，移除周围的单引号，并将其存储在 `itemValue` 中。
- 从提取的值中还会修剪前导和尾随空白。
- 如果值为空或无效，将在运行日志中写入错误消息。

### 示例
```c
char databasePath[MAX_PATH];
GetStringFromConf("config.conf", databasePath, MAX_PATH, "database_path");
// 从配置文件 "config.conf" 中提取名为 "database_path" 的配置项的值，存储在 databasePath 中。
```



## `get_log_level` 函数

### 参数
- `config_file`: 指向要读取的配置文件路径的指针，字符串类型。

### 返回值
- 无返回值 (`void`)

### 功能
该函数用于从指定的配置文件中获取日志级别设置。日志级别确定了哪些消息会被记录在日志中。它适用于`cm_agent`和`cm_server`组件的日志级别设置。

### 注意事项
- 如果输入的 `config_file` 为 `NULL`，则函数会立即返回，不做任何修改。
- 如果无法打开配置文件，函数会打印错误消息并以状态码1退出。
- 该函数会迭代配置文件的各行，查找"log_min_messages"设置。
- 当找到匹配的日志级别时，它会相应地设置全局变量`log_min_messages`，并停止搜索。

### 示例
```c
// 示例配置文件内容
// config.txt
// ...
// log_min_messages = DEBUG1
// ...

#include <stdio.h>

int main() {
    const char* config_file = "config.txt";
    get_log_level(config_file);

    // 检查日志级别设置
    if (log_min_messages == DEBUG1) {
        printf("日志级别已设置为DEBUG1。\n");
    } else {
        printf("未找到匹配的日志级别设置。\n");
    }

    return 0;
}
```

在示例中，假设配置文件`config.txt`包含了日志级别设置，并且已使用`get_log_level`函数读取了该设置。然后，根据读取的日志级别，程序输出相应的消息，以示日志级别是否成功设置。



## `get_build_mode` 函数

### 参数
- `config_file`: 指向要读取的配置文件路径的指针，字符串类型。

### 返回值
- 无返回值 (`void`)

### 功能
该函数用于从指定的配置文件中获取构建模式设置。构建模式确定是否启用或禁用增量构建。

### 注意事项
- 如果输入的 `config_file` 为 `NULL`，则函数会立即返回，不做任何修改。
- 如果无法打开配置文件，函数会打印错误消息并以状态码1退出。
- 该函数会迭代配置文件的各行，查找"incremental_build"设置。
- 它检查配置文件中"incremental_build"参数的值是否为"on"或"off"，并相应地设置全局变量`incremental_build`。
- 如果遇到无效值的"incremental_build"参数，函数将其设置为`true`，并记录致命错误消息。

### 示例
```c
// 示例配置文件内容
// config.txt
// ...
// incremental_build = on
// ...

#include <stdio.h>

int main() {
    const char* config_file = "config.txt";
    get_build_mode(config_file);

    // 检查构建模式设置
    if (incremental_build) {
        printf("增量构建已启用。\n");
    } else {
        printf("增量构建已禁用。\n");
    }

    return 0;
}
```

在示例中，假设配置文件`config.txt`包含了构建模式设置，并且已使用`get_build_mode`函数读取了该设置。然后，根据读取的构建模式，程序输出相应的消息，以示增量构建是否成功设置。



## `get_log_file_size` 函数

### 参数
- `config_file`: 指向要读取的配置文件路径的指针，字符串类型。

### 返回值
- 无返回值 (`void`)

### 功能
该函数用于从指定的配置文件中获取日志文件大小设置。日志文件大小确定日志文件的最大大小，以字节为单位。

### 注意事项
- 如果输入的 `config_file` 为 `NULL`，则函数会立即返回，不做任何修改。
- 如果无法打开配置文件，函数会打印错误消息并以状态码1退出。
- 该函数会迭代配置文件的各行，查找"log_file_size"设置。
- 它只检查包含"log_file_size"的第一行，并解析"="符号后的值。
- 解析的值将被转换为整数，表示最大日志文件大小（以字节为单位）。
- 如果"log_file_size"参数的值无效，函数将记录错误消息并以状态码1退出。

### 示例
```c
// 示例配置文件内容
// config.txt
// ...
// log_file_size = 5242880
// ...

#include <stdio.h>

int main() {
    const char* config_file = "config.txt";
    get_log_file_size(config_file);

    // 检查日志文件大小设置
    printf("日志文件的最大大小为 %d 字节。\n", maxLogFileSize);

    return 0;
}
```

在示例中，假设配置文件`config.txt`包含了日志文件大小设置，并且已使用`get_log_file_size`函数读取了该设置。然后，程序输出最大日志文件大小，以显示设置是否已成功解析。



## `get_cm_thread_count` 函数

![get_cm_thread_count](D:\xmind\get_cm_thread_count.png)

### 参数
- `config_file`：指向要读取的配置文件路径的指针，字符串类型。

### 返回值
- 整数：表示线程数量。如果配置文件未找到或遇到无效值，则返回默认线程数量 5。

### 功能
该函数从指定的配置文件中获取线程数量设置。该设置用于配置 cm_agent 和 cm_server 组件的线程数量，决定了并发处理的线程数量。

### 注意事项
- 如果输入的 `config_file` 为 `NULL`，函数将打印错误消息并以状态码 1 退出。
- 如果无法打开配置文件，函数将打印错误消息并以状态码 1 退出。
- 该函数迭代配置文件的各行，查找 "thread_count" 设置。
- 仅检查包含 "thread_count" 的第一行，并解析 "=" 符号后的值。
- 解析的值将被转换为整数，表示所需的线程数量。
- 如果 "thread_count" 参数的值无效，函数将打印错误消息并以状态码 1 退出。
- 有效的线程数量范围在 2 到 1000 之间。

### 示例
```c
// 示例配置文件内容
// config.txt
// ...
// thread_count = 8
// ...

#include <stdio.h>

int main() {
    const char* config_file = "config.txt";
    int threadCount = get_cm_thread_count(config_file);

    // 检查线程数量设置
    printf("线程数量设置为：%d\n", threadCount);

    return 0;
}
```

在示例中，假设配置文件 `config.txt` 包含了线程数量设置，并使用 `get_cm_thread_count` 函数读取了该设置。然后，程序输出线程数量，以显示设置是否已成功解析。

## `get_int_value_from_config` 函数

### 参数
- `config_file`：指向要读取的配置文件路径的指针，字符串类型。
- `key`：要从配置文件中检索其值的参数名称，字符串类型。
- `defaultValue`：如果未找到 'key' 或值不是有效整数，则返回的默认值，整数类型。

### 返回值
- 整数：表示 'key' 参数的值，如果在配置文件中找到且为有效整数。如果未找到 'key' 或值不是有效整数，则返回 'defaultValue'。

### 功能
该函数从指定的配置文件中获取参数值。它读取指定的配置文件并检索与提供的 'key' 相关联的值。如果在配置文件中找到 'key'，则将其对应的值作为整数返回。如果未找到 'key' 或值不是有效整数，则返回 'defaultValue'。

### 注意事项
- 如果输入的 `config_file` 或 `key` 为 `NULL`，或者无法打开配置文件，此函数将返回 `defaultValue`。
- 该函数首先调用 `get_int64_value_from_config` 来检索值作为64位整数。如果该值在32位整数的有效范围内（INT_MIN 到 INT_MAX），则将其强制转换为整数并返回；否则，将返回 `defaultValue`。

### 示例
```c
// 示例用法
#include <stdio.h>

int main() {
    const char* config_file = "config.txt";
    const char* key = "max_connections";
    int defaultValue = 100;
    
    int maxConnections = get_int_value_from_config(config_file, key, defaultValue);
    
    if (maxConnections == defaultValue) {
        printf("未找到 'max_connections' 参数或值不是有效整数。使用默认值：%d\n", defaultValue);
    } else {
        printf("'max_connections' 参数的值为：%d\n", maxConnections);
    }
    
    return 0;
}
```

在上述示例中，我们使用 `get_int_value_from_config` 函数从配置文件中检索了 `max_connections` 参数的值。如果找到了有效值，则打印该值，否则使用默认值。



## `get_uint32_value_from_config` 函数

### 参数
- `config_file`：指向要读取的配置文件路径的指针，类型为字符串（string）。
- `key`：要从配置文件中检索其值的参数名称，类型为字符串（string）。
- `defaultValue`：如果未找到`key`或值不是有效的非负整数，则返回的默认值，类型为uint32。

### 返回值
- 返回一个32位无符号整数（uint32），表示从配置文件中获取的参数`key`的值，如果在配置文件中找到并且是有效的非负整数。如果未找到`key`或值不是有效的非负整数，则返回`defaultValue`。

### 功能
该函数用于读取指定的配置文件并检索与提供的`key`相关联的值。如果在配置文件中找到`key`，则返回其对应的值作为32位无符号整数（uint32）。如果未找到`key`或者值不是有效的非负整数，则返回`defaultValue`。

### 注意事项
- 如果输入的`config_file`或`key`为NULL，或者无法打开配置文件，该函数将返回`defaultValue`。
- 该函数首先调用`get_int64_value_from_config`函数以64位整数的形式检索值。如果值在32位非负整数的有效范围内（0到`UINT_MAX`），则将其强制转换为`uint32`并返回；否则，返回`defaultValue`。

### 示例
```c
#include <stdio.h>

int main() {
    const char* config_file = "config.ini";
    const char* key = "timeout";
    uint32 defaultValue = 30;

    uint32 value = get_uint32_value_from_config(config_file, key, defaultValue);
    printf("Timeout value: %u\n", value);

    return 0;
}
```
在上述示例中，`get_uint32_value_from_config`函数将尝试从名为`config.ini`的配置文件中检索名为`timeout`的参数的值。如果找到且为有效的非负整数，则将其打印出来，否则将返回默认值30。



## `get_int64_value_from_config` 函数

### 参数
- `config_file`：要读取的配置文件的路径，字符串指针。
- `key`：要从配置文件中检索其值的参数名称，字符串。
- `defaultValue`：如果未在配置文件中找到`key`或者值不是有效整数，则返回的默认值，int64类型。

### 返回值
- 返回一个64位有符号整数（int64），表示从配置文件中获取的参数`key`的值，如果在配置文件中找到且为有效整数。如果未找到`key`或值不是有效整数，则返回`defaultValue`。

### 功能
此函数用于读取指定的配置文件，并检索与提供的`key`相关联的值。如果在配置文件中找到`key`，则将其对应的值作为64位有符号整数（int64）返回。如果未找到`key`或者值不是有效整数，则返回`defaultValue`。

### 注意事项
- 如果输入的`config_file`或`key`为NULL，或者无法打开配置文件，此函数将返回`defaultValue`。
- 该函数从配置文件中读取行，并检查格式为`key=value`的`key`赋值。然后将值部分提取为整数。
- 如果值不是有效整数，则将其忽略，并返回`defaultValue`。
- 忽略以'#'开头的注释行。

### 示例
```c
#include <stdio.h>

int main() {
    const char* config_file = "config.ini";
    const char* key = "timeout";
    int64 defaultValue = 30;

    int64 value = get_int64_value_from_config(config_file, key, defaultValue);
    printf("Timeout value: %lld\n", value);

    return 0;
}
```
在上述示例中，`get_int64_value_from_config`函数将尝试从名为`config.ini`的配置文件中检索名为`timeout`的参数的值。如果找到且为有效整数，则将其打印出来，否则将返回默认值30。

