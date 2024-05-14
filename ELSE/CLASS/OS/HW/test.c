#include <stdio.h>
#include <stdlib.h>

// (1) 全局未初始化变量
int g_uninitial;
// (2) 全局常量
const int g_constant = 42;
// (5) 全局字符串
char g_string[] = "Hello, World!";
int main() {
    // (3) 局部未初始化变量
    int l_uninitial;
    // (4) 局部常量
    const int l_constant = 123;
    // (5) 动态分配内存（malloc）
    int* dynamic_memory = (int*)malloc(sizeof(int));
    // (5) 数组类型
    int l_array[5] = {1, 2, 3, 4, 5};
    *dynamic_memory = 42;
    return 0;
}
