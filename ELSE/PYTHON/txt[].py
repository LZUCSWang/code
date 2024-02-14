'''
Author: 王贤义
FilePath: \code\PYTHON\txt[].py
Description: D:\毛概.txt
'''
import re

def remove_brackets(file_path):
    # 读取文本文件内容，使用UTF-8编码
    with open(file_path, 'r', encoding='utf-8') as file:
        content = file.read()
    # print(content)

    # 使用正则表达式删除方括号及其中的内容
    cleaned_content = re.sub(r'\[.*?\]', '', content)
    print(cleaned_content)
    # 将处理后的内容写回文件，使用UTF-8编码
    with open(file_path, 'w', encoding='utf-8') as file:
        file.write(cleaned_content)

if __name__ == '__main__':
    # 替换为你的文本文件路径
    file_path = 'D:\\毛概.txt'

    remove_brackets(file_path)

    print("括号内容已成功删除。")
