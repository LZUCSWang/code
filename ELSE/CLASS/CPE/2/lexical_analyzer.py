from io import SEEK_CUR
from utils import *

# Enum for LEXICAL_TYPE
TypeTranslation = [
    "NUM",
    "KEYWARD",
    "IDENTIFIER",
    "TYPE",
    "BOARDER",
    "UNKNOWN",
    "EOF",
    "OPERATOR",
]


class LexicalAnalyzer:

    code_reader_ = io.StringIO()
    lexical_analyser_printer_ = io.StringIO()

    OPERATORS = {
        "+",
        "-",
        "*",
        "/",
        "=",
        ":=",
        ">",
        ">=",
        "<",
        "<=",
        "==",
        "!=",
        "&&",
        "||",
    }
    KEYWORDS = {"if", "then", "else", "while", "do", "read", "write"}
    TYPES = {"int", "bool"}
    PRE_OPERATORS = {"+", "-"}
    BORDERS = {"(", ")", "{", "}", ",", ";"}

    char_idx_ = 0
    input_string_ = ""

    def cal_line_counter(self):
        return self.line_counter_

    def cal_column_counter(self):
        for i in range(self.char_idx_, 0, -1):
            if self.input_string_[i] == "\n":
                return self.char_idx_ - i
        return self.char_idx_

    def IsReadyToAnalyze(self, show_detail, code_filename):
        if show_detail:  # 是否在整个过程中显示词法分析的步骤
            self.print_detail_ = True
            self.lexical_analyser_printer_ = open(
                "./gen_data/lexcial_analyzer/lexical_analyser_result.txt", "w"
            )
            if not self.lexical_analyser_printer_:
                print("词法分析过程中，显示输出结果文件打开失败！")
        else:
            self.print_detail_ = False

        self.code_reader_ = open(code_filename)
        # ios::binary 这里不能用Binary， 因为test.cpp是在win操作系统下创建的，在内存中换行是\r\n。
        # 这个时候如果直接从使用二进制读出来，就是\r\n。
        self.input_string_ = self.code_reader_.read()
        self.input_string_len_ = len(self.input_string_)
        if self.code_reader_.closed:
            print("词法分析过程中，源代码文件打开失败！")
            return False

        return True

    def IsSingleCharOperator(self, ch):
        return ch in ["+", "-", "*", "/"]

    def IsDoubleCharOperatorPre(self, ch):
        return ch in ["=", "<", ">", "!", ":", "&", "|"]

    def IsBlank(self, ch):
        return ch in [" ", "\n", "\t", 255]

    def GetNextChar(self):
        ch = self.input_string_[self.char_idx_]
        if ch == "\n":
            self.line_counter_ += 1
        self.char_idx_ += 1
        return ch

    def IsEOF(self):
        return self.char_idx_ >= self.input_string_len_

    def BackSpace(self):
        self.char_idx_ -= 1

    def GetBasicWord(self):
        str_token = ""
        word = WordInfo()

        while not self.IsEOF():
            ch = self.GetNextChar()
            if ch == "/":  # 处理注释
                next_char = self.GetNextChar()
                if next_char == "/":  # 双斜杠注释
                    while self.GetNextChar() != "\n" and not self.IsEOF():
                        pass
                elif next_char == "*":  # /**/注释
                    while True:
                        while self.GetNextChar() != "*" and not self.IsEOF():
                            pass

                        if self.IsEOF():  # 非正常注释结束
                            word.type = LEXICAL_TYPE.LUNKNOWN
                            word.value = "注释错误！行号：" + str(self.line_counter_)
                            return word

                        elif self.GetNextChar() == "/":  # /**/注释结束
                            break

                else:  # 除号操作符
                    self.BackSpace()
                    word.type = LEXICAL_TYPE.LOPERATOR
                    word.value = ch
                    return word
            elif ch.isdigit():
                str_token += ch
                while not self.IsEOF():
                    next_char = self.GetNextChar()
                    if not next_char.isdigit():
                        self.BackSpace()
                        word.type = LEXICAL_TYPE.LCINT
                        word.value = str_token
                        return word
                    else:
                        str_token += next_char
            elif ch.isalpha() or ch == "_":  # TODO:继续修改词法basicword
                str_token += ch
                while not self.IsEOF():
                    next_char = self.GetNextChar()
                    if not next_char.isdigit() and not (
                        next_char.isalpha() or next_char == "_"
                    ):
                        self.BackSpace()
                        if str_token in self.KEYWORDS:
                            word.type = LEXICAL_TYPE.LKEYWORD
                        elif str_token in self.TYPES:
                            word.type = LEXICAL_TYPE.LTYPE
                        elif str_token in ["true", "false"]:
                            word.type = LEXICAL_TYPE.LCINT
                        else:
                            word.type = LEXICAL_TYPE.LIDENTIFIER
                        word.value = str_token
                        return word
                    else:
                        str_token += next_char
            elif ch in self.BORDERS:
                word.type = LEXICAL_TYPE.LBORDER
                word.value = ch
                return word
            elif self.IsSingleCharOperator(ch):
                word.type = LEXICAL_TYPE.LOPERATOR
                word.value = ch
                return word
            elif self.IsDoubleCharOperatorPre(ch):
                str_token += ch
                next_char = self.GetNextChar()

                if next_char == "=" or ch + next_char in self.OPERATORS:
                    str_token += next_char
                    word.type = LEXICAL_TYPE.LOPERATOR
                    word.value = str_token
                    return word
                else:
                    self.BackSpace()
                    if ch != "!":
                        word.type = LEXICAL_TYPE.LOPERATOR
                        word.value = str_token
                        return word
                    else:
                        word.type = LEXICAL_TYPE.LUNKNOWN
                        word.value = str_token + ", 行号：" + str(self.line_counter_)
                        return word
            elif self.IsBlank(ch):
                pass
            else:
                word.type = LEXICAL_TYPE.LUNKNOWN
                word.value = ch
                word.value += ", 行号：" + str(self.line_counter_)
                return word

        word.type = LEXICAL_TYPE.LEOF
        word.value = "#"
        return word

    def GetWord(self):
        get_word = self.GetBasicWord()
        word_string = ""
        if get_word.type == LEXICAL_TYPE.LEOF:
            word_string = "#"
        elif get_word.type == LEXICAL_TYPE.LCINT:
            word_string = "number"
        elif (
            get_word.type == LEXICAL_TYPE.LKEYWORD
            or get_word.type == LEXICAL_TYPE.LTYPE
            or get_word.type == LEXICAL_TYPE.LBORDER
            or get_word.type == LEXICAL_TYPE.LOPERATOR
        ):
            word_string = get_word.value
        elif get_word.type == LEXICAL_TYPE.LTYPE:
            word_string = get_word.value
        elif get_word.type == LEXICAL_TYPE.LIDENTIFIER:
            word_string = "id"

        get_word.word_string = word_string

        if self.print_detail_:
            self.PrintDetail(get_word)
        return get_word

    def PrintDetail(self, word):
        if word.type == LEXICAL_TYPE.LEOF:
            return
        self.lexical_analyser_printer_.write(
            "step "
            + str(self.step_counter_)
            + " , type: "
            + TypeTranslation[word.type.value]
            + " , value: "
            + word.value
            + "\n"
        )
        if word.type == LEXICAL_TYPE.LUNKNOWN:
            self.lexical_analyser_printer_.write("    ****** warning! ******\n")

        self.lexical_analyser_printer_.write("\n")
        self.step_counter_ += 1
        return

    def __init__(self):
        self.line_counter_ = 1
        self.step_counter_ = 1
        self.print_detail_ = False

    def __del__(self):
        if not self.code_reader_.closed:
            self.code_reader_.close()

        if self.lexical_analyser_printer_.closed == False:
            self.lexical_analyser_printer_.close()
