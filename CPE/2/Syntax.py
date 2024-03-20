class Node:
    def __init__(self, val, type):
        self.val = val  # 节点的值
        self.type = type  # 节点的类型
        self.l = None  # 左子节点
        self.r = None  # 右子节点

op = []  # 符号栈
pfix = []  # 后缀表达式
prio = {}  # 运算符优先级

def ini():
    # 初始化运算符优先级
    prio["{"] = 101
    prio["-"] = 4
    prio["+"] = 4
    prio["*"] = 3
    prio["/"] = 3
    prio["("] = 99
    prio["="] = 5
    prio[">"] = prio["<"] = prio[">="] = prio["<="] = prio["=="] = 6
    prio[":="] = 7
    prio["||"] = 11
    prio["&&"] = 12
    prio["!"] = 2
    prio["}"] = 100
    # op.append(Node("{", "op"))  # 初始操作符栈顶放置 $

def print_tree(root, wid):
    # 打印表达式树
    if root is None:
        return
    print("{0:3}".format(root.val), end='')  # 输出节点值
    if root.r is None:
        return
    print(".")  # 输出省略号表示右子节点
    if root.val == "!":
        print("{0:<{1}}|".format("", wid + 3))  # 输出垂直线
    else:
        print("{0:<{1}}|{2:3}|".format("", wid, ""))  # 输出水平线
    if root.l is not None:
        print("{0:<{1}}".format(root.l.val, wid), end='')  # 输出左子节点值
    else:
        print("{0:<{1}}".format("", wid), end='')  # 如果左子节点为空，输出空格
    print_tree(root.r, wid + 3)  # 递归打印右子树

def add(val, type):
    t = Node(val, type)
    if type == "op" or type == "delimiter":  # 如果类型为操作符或分隔符
        if val == ";":
            return
        elif val == ")":  # 如果是右括号
            while op[-1].val != "(":  # 弹出操作符栈中直到遇到左括号的所有操作符
                temp3 = op.pop()
                pfix.append(temp3) 
            op.pop()  # 弹出左括号
        elif val == "(" or val == "{" or prio[val] < prio[op[-1].val]:  # 如果是左括号或者当前操作符优先级小于栈顶操作符优先级
            op.append(t)  # 将当前操作符入栈
        else:
            while prio[val] >= prio[op[-1].val]:  # 当前操作符优先级大于等于栈顶操作符优先级
                temp3 = op.pop()  # 弹出栈顶操作符
                pfix.append(temp3)  # 将弹出的操作符放入后缀表达式中
            op.append(t)  # 将当前操作符入栈
    else:
        pfix.append(t)  # 如果是操作数，直接放入后缀表达式中

def main():
    ini()  # 初始化操作符优先级

    with open("output.txt", 'r') as fin:  # 打开文件
        if not fin:  # 检查文件是否打开成功
            print("文件打不开")
            exit(0)
        for line in fin:  # 逐行读取文件内容
            val, type = line[1:line.index(',')], line[line.index(',') + 2: -2]  # 获取值和类型
            add(val, type)  # 将值和类型加入后缀表达式中
    # add("$$", "op")  # 添加结束标记
    
    root = None  # 表达式树根节点初始化为空
    i = 0
    while i < len(pfix):  # 遍历后缀表达式的每个节点
        if pfix[i].type == "op":  # 如果是操作符
            if root is None:  # 如果根节点为空
                t1 = Node(pfix[i].val, pfix[i].type)  # 创建新节点
                temp1, temp2 = 2, 3  # 临时变量用于记录后续操作
                if t1.val == "!":  # 如果是取反操作
                    t2 = Node(pfix[i - 1].val, pfix[i - 1].type)  # 创建右子节点
                    t1.r = t2
                    temp1 -= 1
                    temp2 -= 1
                else:  # 如果是其他操作
                    t2 = Node(pfix[i - 1].val, pfix[i - 1].type)  # 创建左子节点
                    t3 = Node(pfix[i - 2].val, pfix[i - 2].type)  # 创建右子节点
                    t1.l = t2
                    t1.r = t3
                root = t1  # 根节点指向当前节点
                i -= temp1  # 更新索引位置
                del pfix[i:i + temp2]  # 删除后缀表达式中已经使用的节点
            else:  # 如果根节点不为空
                t1 = Node(pfix[i].val, pfix[i].type)  # 创建新节点
                temp1, temp2 = 1, 2  # 临时变量用于记录后续操作
                if t1.val == "!":  # 如果是取反操作
                    t1.r = root  # 当前节点的右子节点指向根节点
                    temp1 -= 1
                    temp2 -= 1
                else:  # 如果是其他操作
                    t2 = Node(pfix[i - 1].val, pfix[i - 1].type)  # 创建左子节点
                    t1.r = root  # 当前节点的右子节点指向根节点
                    t1.l = t2
                root = t1  # 根节点指向当前节点
                i -= temp1  # 更新索引位置
                del pfix[i:i + temp2]  # 删除后缀表达式中已经使用的节点
        else:
            i += 1  # 如果是操作数，直接遍历下一个节点
    print_tree(root, 3)  # 打印表达式树

if __name__ == "__main__":
    main()
    # print(1)
