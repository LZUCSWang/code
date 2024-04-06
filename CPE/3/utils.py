from enum import Enum
import io


class Production:
    def __init__(self, left, right):
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


class CATEGORY(Enum):
    FUNCTION = 0
    VARIABLE = 1
    CONST = 2
    TEMP = 3
    RETURN_VAR = 4


class VARIABLE_TYPE(Enum):
    INT = 0
    VOID = 1
    BOOL = 2

class RegisterInfo:
    def __init__(self, name="", content="", content_info=None, miss_time=0, is_possessed=False):
        self.name = name
        self.content = content
        self.content_info = content_info
        self.miss_time = miss_time
        self.is_possessed = is_possessed

class Instructions:
    def __init__(self, op="", arg1="", arg2="", arg3=""):
        self.op = op
        self.arg1 = arg1
        self.arg2 = arg2
        self.arg3 = arg3

    def set_content(self, op, arg1, arg2, arg3):
        self.op = op
        self.arg1 = arg1
        self.arg2 = arg2
        self.arg3 = arg3


class GrammarSymbolInfo:
    def __init__(self, symbol_name="", txt_value="", pos=None, op="", is_imm=False):
        self.symbol_name = symbol_name
        self.txt_value = txt_value
        self.pos = pos
        self.op = op
        self.is_imm = is_imm


class SymbolPos:
    def __init__(self, table_pos=0, symbol_pos=0):
        self.table_pos = (
            table_pos  # 变量、常量、临时变量 所在 table 在所有 table 中的序号
        )
        self.symbol_pos = symbol_pos  # 变量、常量、临时变量 所在 table 中的位置


class Quadruples:
    def __init__(self, n=0, o="", a1="", a2="", r=""):
        self.num = n
        self.op = o
        self.arg1 = a1
        self.arg2 = a2
        self.result = r

    def SetContent(self, n, o, a1, a2, r):
        self.num = n
        self.op = o
        self.arg1 = a1
        self.arg2 = a2
        self.result = r
