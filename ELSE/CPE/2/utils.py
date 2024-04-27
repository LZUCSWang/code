from enum import Enum
import io


class Production:
    def __init__(self,left,right):
        self.left = left
        self.right = right


class LEXICAL_TYPE(Enum):
    LCINT = 0
    LKEYWORD = 1
    LIDENTIFIER = 2
    LTYPE = 3
    LBORDER = 4
    LUNKNOWN = 5
    LEOF = 6
    LOPERATOR = 7
    LBEGIN = 8
    LCFLOAT = 9
    LCDOUBLE = 10
    LCCHAR = 11
    LCSTRING = 12
    LCERROR = 13
    LOERROR = 14


class WordInfo:
    def __init__(self):
        self.type = None  # 词类型
        self.value = ""  # 常量的值，或者关键字本身
        self.word_string = ""  # 进行语义分析时的符号
        self.functionIndex = 0  # 仅在函数调用的产生式用到，表示函数在全局表中的序号
