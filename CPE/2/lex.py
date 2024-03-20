# 定义源语言的关键字
keywords = ["else", "if", "int", "while", "bool", "do", "read", "write", "then"]
# 定义源语言的常量值
constants = ["true", "false"]
# 定义需要过滤掉的字符（空白字符）
filter_chars = [" ", "\t", "\r", "\n"]
# 定义源语言的分隔符
delimiters = ["(", ")", "{", "}", ";", ","]
# 定义源语言的运算符（包括单字符运算符和双字符运算符）
operators = [
    "+",
    "-",
    "*",
    "/",
    "<",
    ">",
    "=",
    "!",
    "<=",
    ">=",
    "==",
    "!=",
    "&&",
    "||",
    ":=",
]
# 初始化一个字典来存储标识符及其对应的编号
tokens = {}
# 定义源语言的括号对
brackets = {"(": ")", "{": "}", "[": "]"}


# 定义一个函数用来计算字符在源代码中的行和列
def get_line_column(source, i):
    line = 1  # 初始化行号为1
    column = 1  # 初始化列号为1
    # 遍历源代码到指定位置
    for index, char in enumerate(source):
        if index == i:  # 如果到达指定位置，则结束循环
            break
        if char == "\n":  # 如果遇到换行符，则行号增加，列号重置为1
            line += 1
            column = 1
        else:  # 否则列号增加
            column += 1
    return line, column  # 返回行号和列号


# 定义一个函数用来分析源代码，并识别出所有合法的单词符号
def analyze(source):
    i = 0  # 初始化索引i，用来遍历源代码
    len_source = len(source)  # 计算源代码的长度
    output = []  # 初始化输出列表，用来存储识别出的单词符号
    stack = []  # 初始化栈，用来匹配括号
    error = []  # 初始化错误列表，用来存储无法识别的子串
    # 循环遍历源代码
    while i < len_source:
        # 如果当前字符是需要过滤的空白字符，则跳过
        if source[i] in filter_chars:
            i += 1
            continue
        # 如果当前字符是单行注释的开始，则跳过注释内容
        elif source[i] == "/" and i + 1 < len_source and source[i + 1] == "/":
            i += 2  # 跳过注释标志“//”
            while i < len_source and source[i] != "\n":  # 跳过注释内容直到行末
                i += 1
            continue
        # 如果当前字符是多行注释的开始，则跳过注释内容
        elif source[i] == "/" and i + 1 < len_source and source[i + 1] == "*":
            i += 2  # 跳过注释标志“/*”
            while i < len_source:
                if (
                    source[i] == "*" and i + 1 < len_source and source[i + 1] == "/"
                ):  # 遇到注释结束标志“*/”
                    i += 2
                    break
                i += 1
            continue
        # 如果当前字符是开括号，则将其压入栈中，并记录为分隔符
        elif source[i] in brackets.keys():
            stack.append(source[i])
            output.append((source[i], "delimiter"))
            i += 1
        # 如果当前字符是闭括号
        elif source[i] in brackets.values():
            if (
                not stack or brackets[stack.pop()] != source[i]
            ):  # 如果栈为空或不匹配，则记录为非法括号
                error.append(
                    (source[i], f"illegal bracket{get_line_column(source, i)}")
                )
            else:  # 否则记录为分隔符
                output.append((source[i], "delimiter"))
            i += 1
        # 如果当前字符是分隔符，则记录为分隔符
        elif source[i] in delimiters:
            output.append((source[i], "delimiter"))
            i += 1
        # 如果当前字符是字母或下划线，则可能是关键字、常量或标识符
        elif source[i].isalpha() or source[i] == "_":
            token = ""  # 初始化词元字符串
            # 循环读取字符直到非字母、非数字、非下划线
            while i < len_source and (
                source[i].isalpha() or source[i].isdigit() or source[i] == "_"
            ):
                token += source[i]
                i += 1
            token = token.lower()  # 将词元转换为小写，以便匹配关键字和常量
            # 如果词元长度超过8个字符，则记录为非法标识符
            if len(token) > 8:
                error.append((token, f"illegal identifier{get_line_column(source, i)}"))
            # 如果词元是关键字，则记录为关键字
            elif token in keywords:
                output.append((token, "keyword"))
            # 如果词元是常量，则记录为常量
            elif token in constants:
                output.append((token, "constant"))
            # 否则，词元被视为标识符
            else:
                tokens.setdefault(token, len(tokens) + 1)  # 为新标识符分配一个唯一编号
                output.append((token, f"identifier {tokens[token]}"))  # 记录为标识符
        # 如果当前字符是数字或负号且后面紧跟数字，则可能是常量
        elif source[i].isdigit() or (
            source[i] == "-" and i + 1 < len_source and source[i + 1].isdigit()
        ):
            token = source[i]  # 初始化词元字符串
            i += 1
            # 循环读取数字字符
            while i < len_source and source[i].isdigit():
                token += source[i]
                i += 1
            if token == "0":
                output.append((token, "constant"))
            # 如果词元长度超过8个字符或以0开头，则记录为非法常量
            elif len(token) > 8 or token[0] == "0":
                error.append((token, f"invalid constant{get_line_column(source, i)}"))
            else:  # 否则，记录为常量
                output.append((token, "constant"))
        # 如果当前字符是感叹号，可能是逻辑非运算符或不等于运算符
        elif source[i] == "!":
            if (
                i + 1 < len_source and source[i + 1] == "="
            ):  # 如果下一个字符是等号，则是不等于运算符
                output.append(("!=", "operator"))
                i += 2  # 跳过“!=”
            else:  # 否则，是逻辑非运算符
                output.append(("!", "operator"))
                i += 1
        # 如果当前字符和下一个字符组成的字符串是运算符，则记录为运算符
        elif source[i : i + 2] in operators:
            output.append((source[i : i + 2], "operator"))
            i += 2
        # 如果当前字符是单字符运算符，则记录为运算符
        elif source[i] in operators:
            output.append((source[i], "operator"))
            i += 1
        # 如果当前字符不属于以上任何一种情况，则记录为未知错误
        else:
            error.append((source[i], f"illegal unknown{get_line_column(source, i)}"))
            i += 1
    return output, error  # 返回识别出的单词符号和错误列表


# 定义主驱动函数
def Driver():
    # 读取源代码文件
    with open("input.txt", "r") as f:
        source = f.read()

    # 调用分析函数
    analyzed, error = analyze(source)

    # 将分析结果写入输出文件
    with open("output.txt", "w") as f:
        for item in analyzed:  # 写入识别出的单词符号
            f.write(f"<{item[0]}, {item[1]}>\n")
        if error:  # 如果有错误，则写入分隔符
            f.write(
                "----------------------------------error----------------------------------\n"
            )
            for item in error:  # 写入错误列表
                f.write(f"<{item[0]}, {item[1]}>\n")


# 如果这个脚本作为主程序执行，则运行主驱动函数
if __name__ == "__main__":
    Driver()
