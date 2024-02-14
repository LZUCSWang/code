
/*
@Author: 王贤义
 * @FilePath: \code\C+++C\c++\9\Combine\Combine.cpp
@Description: 文件合并程序
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        cout << "Usage: combine.exe file1 file2 file3" << endl; // 使用说明: combine.exe是程序名，file1 file2 file3是参数
        return 1;
    }
    string file1_name = argv[1]; // 获取文件1的名称
    string file2_name = argv[2]; // 获取文件2的名称
    string file3_name = argv[3]; // 获取文件3的名称

    ifstream file1(file1_name); // 打开文件1进行读取
    ifstream file2(file2_name); // 打开文件2进行读取
    ofstream file3(file3_name); // 打开文件3进行写入

    if (!file1 || !file2 || !file3)
    {
        cout << "Error: Cannot open files" << endl; // 打开文件失败，输出错误信息
        return 1;
    }

    vector<string> lines; // 创建一个字符串向量，用于存储读取的文件内容
    string line;

    // 从文件1逐行读取内容，并存储到字符串向量中
    while (getline(file1, line))
    {
        lines.push_back(line);
    }

    // 从文件2逐行读取内容，并存储到字符串向量中
    while (getline(file2, line))
    {
        lines.push_back(line);
    }

    // 将字符串向量中的内容逐行写入文件3
    for (int i = 0; i < lines.size(); i++)
    {
        file3 << lines[i] << endl;
    }

    cout << "Files combined successfully." << endl; // 文件合并成功

    return 0;
}
