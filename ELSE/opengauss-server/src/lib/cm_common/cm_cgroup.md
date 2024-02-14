# `cm_cgroup`模块
[TOC]
## 引言
`cm_cgroup`模块包含了一些用于控制组（cgroup）管理的函数。这些函数可以用于初始化 cgroup 环境，或者将进程附加到指定的 cgroup 中,或者获取 cgroup 的相关信息等等。

![cm_cgroup](D:\xmind\cm_cgroup.png)
---

## `gscgroup_cm_init` 函数

### 描述

`gscgroup_cm_init` 函数是用于初始化 GSC（Gauss State Coordinator）的 cgroup 相关配置的重要函数。在数据库集群管理中，cgroup 是一种用于资源管理和隔离的重要机制。此函数的主要任务是获取适当的 cgroup 路径以便于将 GSC 进程隔离和管理。

### 参数

此函数无需任何参数。

### 返回值

- `char*`: 表示 GSC cgroup 路径的字符串。如果初始化失败，则返回 `NULL`。

### 使用示例

```c
char* cgroupPath = gscgroup_cm_init();
if (cgroupPath != NULL) {
    printf("GSC cgroup path: %s\n", cgroupPath);
    // ... 进一步处理 cgroupPath
    free(cgroupPath); // 记得释放内存
} else {
    // 处理初始化失败
}
```

### 实现细节

1. 初始化 cgroup 库：函数首先尝试初始化 cgroup 库。如果初始化失败，它会记录错误信息并返回 `NULL`。

2. 打开 `/proc/mounts` 文件：函数尝试打开 `/proc/mounts` 文件，以获取系统中挂载的文件系统信息。这是获取 cgroup 挂载点信息的重要步骤。

3. 遍历挂载点：函数通过遍历挂载点信息来查找适当的 cgroup 挂载点。它寻找类型为 "cgroup" 且包含 "cpu" 选项的挂载点。一旦找到匹配的挂载点，就会获取 GSC cgroup 的绝对路径。

4. 检查路径有效性：函数使用 `stat` 函数来验证获取到的 cgroup 路径是否有效。如果路径无效，它将记录警告并返回 `NULL`。

5. 提取相对路径：函数从绝对路径中提取相对路径，以便在 GSC 进程管理中使用。相对路径将是 GSC 进程在 cgroup 中的位置。

6. 清理资源：在函数成功获取 cgroup 相关信息后，它会关闭打开的文件并释放分配的内存，以防止资源泄漏。

### 注意事项

- 调用者有责任在不再需要返回的字符串时释放内存，以防止内存泄漏。
- 请确保文件路径 `/proc/mounts` 存在且可读。
- 初始化失败时，函数返回 `NULL`，需要进行适当的错误处理。

### 示例

```c
char* cgroupPath = gscgroup_cm_init();
if (cgroupPath != NULL) {
    printf("GSC cgroup path: %s\n", cgroupPath);
    // ... 进一步处理 cgroupPath
    free(cgroupPath); // 记得释放内存
} else {
    write_runlog(ERROR, "GSC cgroup initialization failed.\n");
    // 处理初始化失败
}
```

---

## `gscgroup_cm_attach_task` 函数

在数据库管理中，控制组（cgroup）是一种用于限制、隔离和管理进程的重要机制。`gscgroup_cm_attach_task` 函数是用于将当前线程附加到指定 cgroup 的关键函数。这个函数的目标是确保当前线程受到指定 cgroup 的资源管理。

### 函数签名

```c
void gscgroup_cm_attach_task(const char* relpath);
```

### 参数

- `relpath` (const char*): 一个字符串，表示要将当前线程附加到的 cgroup 的相对路径。

### 使用示例

```c
const char* cgroupPath = "/example/cgroup/path";
gscgroup_cm_attach_task(cgroupPath);
```

### 实现细节

1. 获取 cgroup 结构：函数首先尝试通过调用 `gscgroup_get_cgroup` 函数来获取指定相对路径 `relpath` 的 cgroup 结构。

2. 检查获取结果：如果无法获取 cgroup 结构，函数将记录警告消息，并返回。这可能表示指定的相对路径 `relpath` 无效。

3. 将当前线程附加到 cgroup：一旦获取到有效的 cgroup 结构，函数将调用 `cgroup_attach_task` 函数来将当前线程附加到该 cgroup 中。

4. 处理错误情况：如果附加操作失败，函数将记录警告消息，包括失败的原因。

5. 释放资源：最后，函数将释放 cgroup 结构以防止资源泄漏。

### 注意事项

- 调用者负责确保提供的 `relpath` 参数是有效的 cgroup 相对路径。
- 如果附加操作失败，函数将记录警告消息，但不会中止程序执行。

### 示例

```c
const char* cgroupPath = "/example/cgroup/path";
gscgroup_cm_attach_task(cgroupPath);
```

​		这个函数是数据库管理中的一个关键组件，用于确保数据库进程受到适当的资源管理和隔离。它在管理数据库资源和性能方面发挥了重要作用，特别是在多租户或多工作负载环境中。通过附加线程到正确的 cgroup，它有助于确保数据库进程的稳定性和可预测性。

---

## `gscgroup_cm_attach_task_pid` 函数

在数据库管理中，控制组（cgroup）是一种用于限制、隔离和管理进程的重要机制。`gscgroup_cm_attach_task_pid` 函数是用于将指定线程（任务）附加到指定 cgroup 的关键函数。这个函数的目标是确保指定线程受到指定 cgroup 的资源管理。

### 函数签名

```c
void gscgroup_cm_attach_task_pid(const char* relpath, pid_t tid);
```

### 参数

- `relpath` (const char*): 一个字符串，表示要将指定线程附加到的 cgroup 的相对路径。
- `tid` (pid_t): 要附加的线程（任务）的进程 ID。

### 使用示例

```c
const char* cgroupPath = "/example/cgroup/path";
pid_t threadId = 12345;
gscgroup_cm_attach_task_pid(cgroupPath, threadId);
```

### 实现细节

1. 获取 cgroup 结构：函数首先尝试通过调用 `gscgroup_get_cgroup` 函数来获取指定相对路径 `relpath` 的 cgroup 结构。

2. 检查获取结果：如果无法获取 cgroup 结构，函数将记录警告消息，并返回。这可能表示指定的相对路径 `relpath` 无效。

3. 将指定线程附加到 cgroup：一旦获取到有效的 cgroup 结构，函数将调用 `cgroup_attach_task_pid` 函数来将指定线程附加到该 cgroup 中。

4. 处理错误情况：如果附加操作失败，函数将记录警告消息，包括失败的原因。

5. 释放资源：最后，函数将释放 cgroup 结构以防止资源泄漏。

### 注意事项

- 调用者负责确保提供的 `relpath` 参数是有效的 cgroup 相对路径。
- 如果附加操作失败，函数将记录警告消息，但不会中止程序执行。

### 示例

```c
const char* cgroupPath = "/example/cgroup/path";
pid_t threadId = 12345;
gscgroup_cm_attach_task_pid(cgroupPath, threadId);
```

这个函数在多线程应用程序中具有重要作用，因为它允许将指定线程（任务）附加到适当的 cgroup，以确保线程的资源管理和隔离。这对于数据库管理等多租户或多工作负载环境非常关键，可以确保各个线程不会相互干扰，从而提高了系统的可靠性和性能。

---

## `gscroup_get_cgroup` 函数

`gscgroup_get_cgroup` 函数用于获取指定 cgroup 的相关信息并返回一个 `struct cgroup` 结构，以便后续的 cgroup 操作。这个函数是 cgroup 管理中的重要组件，用于建立与指定 cgroup 的连接。

### 函数签名

```c
static struct cgroup* gscgroup_get_cgroup(const char* relpath);
```

### 参数

- `relpath` (const char*): 一个字符串，表示要获取信息的 cgroup 的相对路径。

### 返回值

- `struct cgroup*`: 一个指向 `struct cgroup` 结构的指针，表示获取的 cgroup 信息。如果操作失败，则返回 `NULL`。

### 使用示例

```c
const char* cgroupPath = "/example/cgroup/path";
struct cgroup* cg = gscgroup_get_cgroup(cgroupPath);
if (cg != NULL) {
    // ... 进一步操作 cgroup 信息
    cgroup_free(&cg); // 记得释放资源
} else {
    // 处理获取 cgroup 信息失败
}
```

### 实现细节

1. 分配新的 cgroup 结构：函数首先尝试分配一个新的 `struct cgroup` 结构，以表示指定 cgroup 的相关信息。

2. 检查分配结果：如果无法成功分配 cgroup 结构，函数将记录警告消息，并返回 `NULL`。这可能是由于内存不足或其他分配失败的原因。

3. 获取 cgroup 信息：一旦成功分配了 cgroup 结构，函数将调用 `cgroup_get_cgroup` 函数来获取指定 cgroup 的信息，包括资源限制、控制选项等。

4. 检查获取结果：如果获取操作失败，函数将记录警告消息，包括失败的原因。然后，它将释放之前分配的 cgroup 结构，以防止资源泄漏。

### 注意事项

- 调用者有责任在不再需要 cgroup 信息时释放相关资源，以防止内存泄漏。
- 如果获取操作失败，函数将记录警告消息，但不会中止程序执行。

### 示例

```c
const char* cgroupPath = "/example/cgroup/path";
struct cgroup* cg = gscgroup_get_cgroup(cgroupPath);
if (cg != NULL) {
    // ... 进一步操作 cgroup 信息
    cgroup_free(&cg); // 记得释放资源
} else {
    write_runlog(ERROR, "Failed to get cgroup information for path %s.\n", cgroupPath);
    // 处理获取 cgroup 信息失败
}
```

这个函数是 cgroup 管理中的一个关键组件，它用于建立与指定 cgroup 的连接，并提供获取 cgroup 信息的接口，以便进行后续的 cgroup 操作。这对于数据库管理等多租户或多工作负载环境非常关键，可以确保各个 cgroup 的资源隔离和管理。

## 总结

`cm_cgroup`模块提供了一组用于控制组（cgroup）管理的关键函数，用于资源管理、隔离和进程管理。其中，`gscgroup_cm_init`函数用于初始化数据库集群中的cgroup配置，`gscgroup_cm_attach_task`函数将当前线程附加到指定cgroup中，`gscgroup_cm_attach_task_pid`函数将指定线程附加到指定cgroup中，`gscgroup_get_cgroup`函数用于获取指定cgroup的信息。这些函数在多租户或多工作负载环境中发挥重要作用，确保了资源管理、隔离和进程稳定性。在使用这些函数时，调用者需要注意释放资源以避免内存泄漏，并处理可能的错误情况。这些函数的细节实现确保了cgroup管理在数据库管理中的有效应用，提高了系统的可靠性和性能。