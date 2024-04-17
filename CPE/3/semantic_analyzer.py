from symbol_table import *
from utils import *

import os


class SemanticAnalyzer:

    def __init__(self):
        # 创建全局符号表，并添加到当前符号表栈中
        self.symbol_tables_ = [SymbolTable(TABLE_TYPE.GLOBAL_TABLE, "global_table")]
        self.current_symbol_table_stack_ = [0]

        # 创建临时变量符号表
        self.symbol_tables_.append(SymbolTable(TABLE_TYPE.TEMP_TABLE, "temp_table"))

        self.next_state_num_ = 1  # 从1开始，0留给跳转到main的指令
        self.backpatching_level_ = 0  # 从0开始

        self.temp_string_ = ""
        self.quadruples_stack_ = []
        self.temp = [0] * 20
        self.temp_else = [0] * 20

    def PopAndAppend(self, symbol_info_stack, conclude_symbol_info, production):
        length = len(production.right)
        for _ in range(length):
            symbol_info_stack.pop()
        symbol_info_stack.append(conclude_symbol_info)

    def GetNextStateNum(self):
        num = self.next_state_num_
        self.next_state_num_ += 1
        return num

    def PeekNextStateNum(self):
        return self.next_state_num_

    def GetArgName(self, sp, is_return=False):
        arg_name = self.symbol_tables_[sp.table_pos].GetSymbolName(sp.symbol_pos)
        if not is_return:
            if CATEGORY.VARIABLE == self.symbol_tables_[sp.table_pos].GetSymbolMode(
                sp.symbol_pos
            ):  # 变量
                arg_name = (
                    arg_name
                    + "-"
                    + "Var"
                )
        else:
            pos = self.symbol_tables_[0].FindSymbol(
                self.symbol_tables_[sp.table_pos].GetTableName()
            )
            symbol = self.symbol_tables_[0].GetSymbol(pos)
            arg_name = (
                arg_name + "-" + symbol.name + "_paramerter " + str(sp.symbol_pos)
            )
        return arg_name

    def PrintQuadruples(self, quadruples=None):
        if quadruples is not None:
            if self.backpatching_level_ == 0:  # 不需要回填
                self.temp_string_ += f"{quadruples.num} ({quadruples.op}, {quadruples.arg1}, {quadruples.arg2}, {quadruples.result})\n"
                with open("./gen_data/target_file/intermediate_code.txt", "w") as file:
                    file.write(self.temp_string_)
            else:  # 需要回填
                self.quadruples_stack_.append(quadruples)
                self.quadruples_stack_.sort(key=lambda x: x.num)
        return True

    def CreateSymbolTable(self, table_type, table_name):
        self.symbol_tables_.append(SymbolTable(table_type, table_name))
        self.current_symbol_table_stack_.append(len(self.symbol_tables_) - 1)
        return True

    def ExecuteSemanticCheck(self, symbol_info_stack, production):
        if "PROG" == production.left:
            # PROG -> { DECLS STMTS }
            print("中间代码生成完毕！")
            conclude_symbol_info = GrammarSymbolInfo(symbol_name=production.left)
            self.PopAndAppend(symbol_info_stack, conclude_symbol_info, production)

        elif "DECLS" == production.left and production.right[0] == "DECLS":
            # DECLS -> DECLS DECL
            # 由规约后的产生式左部构造一个文法符号属性
            conclude_symbol_info = GrammarSymbolInfo(symbol_name=production.left)
            self.PopAndAppend(symbol_info_stack, conclude_symbol_info, production)

        elif "DECLS" == production.left and production.right[0] == "$":
            # DECLS -> $
            conclude_symbol_info = GrammarSymbolInfo(symbol_name=production.left)
            symbol_info_stack.append(conclude_symbol_info)

        elif "DECL" == production.left and production.right[0] == "int":
            # DECL -> int NAMES;
            symbol_identifier = symbol_info_stack[-2]
            for identifier_txt_value in symbol_identifier.txt_value:
                variable_symbol = Symbol()
                variable_symbol.mode = CATEGORY.VARIABLE  # 类型
                variable_symbol.name = identifier_txt_value  # 名称
                variable_symbol.type = VARIABLE_TYPE.INT
                variable_symbol.value = ""  # 字面值还没有被赋值，此处为空
                symbol_pos = self.symbol_tables_[0].AddSymbol(
                    variable_symbol
                )  # 加入符号表中
            conclude_symbol_info = GrammarSymbolInfo(
                symbol_name=production.left, txt_value=symbol_identifier.txt_value
            )
            self.PopAndAppend(symbol_info_stack, conclude_symbol_info, production)

        elif "DECL" == production.left and production.right[0] == "bool":
            # DECL -> bool NAMES;
            symbol_identifier = symbol_info_stack[-2]
            for identifier_txt_value in symbol_identifier.txt_value:
                variable_symbol = Symbol()
                variable_symbol.mode = CATEGORY.VARIABLE  # 类型
                variable_symbol.name = identifier_txt_value  # 名称
                variable_symbol.type = VARIABLE_TYPE.BOOL
                variable_symbol.value = ""  # 字面值还没有被赋值，此处为空

                symbol_pos = self.symbol_tables_[0].AddSymbol(
                    variable_symbol
                )  # 加入符号表中

            conclude_symbol_info = GrammarSymbolInfo(
                symbol_name=production.left, txt_value=symbol_identifier.txt_value
            )
            self.PopAndAppend(symbol_info_stack, conclude_symbol_info, production)

        elif "NAMES" == production.left and production.right[0] == "NAMES":
            # NAMES -> NAMES , NAME
            # 由规约后的产生式左部构造一个文法符号属性
            conclude_symbol_info = GrammarSymbolInfo(
                symbol_name=production.left,
                txt_value=symbol_info_stack[-3].txt_value.copy(),
            )
            conclude_symbol_info.txt_value.append(symbol_info_stack[-1].txt_value)

            self.PopAndAppend(symbol_info_stack, conclude_symbol_info, production)

        elif "NAMES" == production.left and production.right[0] == "NAME":
            # NAMES -> NAME
            # 由规约后的产生式左部构造一个文法符号属性
            conclude_symbol_info = GrammarSymbolInfo(
                symbol_name=production.left, txt_value=[symbol_info_stack[-1].txt_value]
            )
            self.PopAndAppend(symbol_info_stack, conclude_symbol_info, production)

        elif "NAME" == production.left and production.right[0] == "id":
            # NAME -> id
            symbol_identifier = symbol_info_stack[-1]
            # 在符号表栈中一级级逆序寻找 identifier 是否被定义过
            identifier_pos = -1
            identifier_layer = len(self.current_symbol_table_stack_) - 1
            for i in range(identifier_layer, -1, -1):
                search_table = self.symbol_tables_[self.current_symbol_table_stack_[i]]
                identifier_pos = search_table.FindSymbol(symbol_identifier.txt_value)
                if identifier_pos != -1:  # 表示在某一级中找到了
                    break
            if identifier_pos != -1:  # 找到，表示存在，说明重复定义，语义错误
                print("语义错误！！！", symbol_identifier.txt_value, "重复定义！")
                return False
            # 由规约后的产生式左部构造一个文法符号属性
            conclude_symbol_info = GrammarSymbolInfo(
                symbol_name=production.left, txt_value=symbol_identifier.txt_value
            )
            self.PopAndAppend(symbol_info_stack, conclude_symbol_info, production)

        elif "STMTS" == production.left and production.right[0] == "STMTS":
            # STMTS -> STMTS STMT
            # 由规约后的产生式左部构造一个文法符号属性
            conclude_symbol_info = GrammarSymbolInfo(symbol_name=production.left)
            self.PopAndAppend(symbol_info_stack, conclude_symbol_info, production)

        elif "STMTS" == production.left and production.right[0] == "STMTS":
            # STMTS -> STMT
            # 由规约后的产生式左部构造一个文法符号属性
            conclude_symbol_info = GrammarSymbolInfo(symbol_name=production.left)
            self.PopAndAppend(symbol_info_stack, conclude_symbol_info, production)

        elif (
            "STMT" == production.left
            and production.right[0] == "id"
            and production.right[1] == "="
        ):
            # STMT -> id = EXPR;
            # 获取identifier与Expression的文法符号属性
            symbol_expression = symbol_info_stack[-2]
            symbol_identifier = symbol_info_stack[-4]
            # 在符号表栈中一级级逆序寻找 identifier 是否被定义过
            identifier_pos = -1
            identifier_layer = len(self.current_symbol_table_stack_) - 1
            while identifier_layer >= 0:
                search_table = self.symbol_tables_[0]
                identifier_pos = search_table.FindSymbol(symbol_identifier.txt_value)
                if identifier_pos != -1:  # 表示在某一级中找到了
                    break
                identifier_layer -= 1

            if identifier_pos == -1:  # 没找到，表示不存在，说明没定义就使用，语义错误
                print("语义错误！！！", symbol_identifier.txt_value, "没有定义！")
                return False

            # 输出赋值的中间代码
            sp = SymbolPos()
            sp.table_pos = self.current_symbol_table_stack_[identifier_layer]
            sp.symbol_pos = identifier_pos
            result_name = self.GetArgName(sp)
            arg1_name = self.GetArgName(symbol_expression.pos)
            self.PrintQuadruples(
                Quadruples(self.GetNextStateNum(), ":=", arg1_name, "-", result_name)
            )
            conclude_symbol_info = GrammarSymbolInfo(symbol_name=production.left)
            self.PopAndAppend(symbol_info_stack, conclude_symbol_info, production)

        elif (
            "STMT" == production.left
            and production.right[0] == "id"
            and production.right[1] == ":="
        ):
            # STMT -> id := BOOL;
            # 获取identifier与Expression的文法符号属性
            symbol_expression = symbol_info_stack[-2]
            symbol_identifier = symbol_info_stack[-4]
            # SymbolTable current_table = self.symbol_tables_[self.current_symbol_table_stack_.back()]

            # 在符号表栈中一级级逆序寻找 identifier 是否被定义过

            identifier_pos = -1
            identifier_layer = len(self.current_symbol_table_stack_) - 1
            while identifier_layer >= 0:
                search_table = self.symbol_tables_[
                    self.current_symbol_table_stack_[identifier_layer]
                ]
                identifier_pos = search_table.FindSymbol(symbol_identifier.txt_value)
                if identifier_pos != -1:  # 表示在某一级中找到了
                    break
                identifier_layer -= 1

            if identifier_pos == -1:  # 没找到，表示不存在，说明没定义就使用，语义错误
                print("语义错误！！！", symbol_identifier.txt_value, "没有定义！")
                return False

            # 输出赋值的中间代码
            sp = SymbolPos()
            sp.table_pos = self.current_symbol_table_stack_[identifier_layer]
            sp.symbol_pos = identifier_pos
            result_name = self.GetArgName(sp)
            arg1_name = self.GetArgName(symbol_expression.pos)
            self.PrintQuadruples(
                Quadruples(self.GetNextStateNum(), ":=", arg1_name, "-", result_name)
            )
            conclude_symbol_info = GrammarSymbolInfo(symbol_name=production.left)
            self.PopAndAppend(symbol_info_stack, conclude_symbol_info, production)

        elif "else" in production.right:
            # STMT -> if id then STMT else STMT
            symbol_id = symbol_info_stack[-5]
            symbol_pos = self.symbol_tables_[0].FindSymbol(symbol_id.txt_value)
            symbol_name = self.GetArgName(SymbolPos(0, symbol_pos))
            backpatching_level_temp = self.backpatching_level_
            backpatching_level_temp = self.backpatching_level_
            self.PrintQuadruples(
                Quadruples(
                    self.temp[backpatching_level_temp],
                    "j",
                    symbol_name,
                    "-",
                    self.temp[backpatching_level_temp] + 2,
                )
            )
            self.PrintQuadruples(
                Quadruples(
                    self.temp[backpatching_level_temp] + 1,
                    "j",
                    "-",
                    "-",
                    self.temp_else[backpatching_level_temp] + 1,
                )
            )
            self.PrintQuadruples(
                Quadruples(
                    self.temp_else[backpatching_level_temp],
                    "j",
                    "-",
                    "-",
                    self.PeekNextStateNum(),
                )
            )

            self.backpatching_level_ -= 1
            if self.backpatching_level_ == 0:
                for Qua in self.quadruples_stack_:
                    self.PrintQuadruples(Qua)
                self.quadruples_stack_ = []
            conclude_symbol_info = GrammarSymbolInfo(symbol_name=production.left)
            self.PopAndAppend(symbol_info_stack, conclude_symbol_info, production)

        elif "if" == production.right[0]:
            # STMT -> if id then STMT
            symbol_id = symbol_info_stack[-3]
            symbol_pos = self.symbol_tables_[0].FindSymbol(symbol_id.txt_value)
            symbol_name = self.GetArgName(SymbolPos(0, symbol_pos))
            backpatching_level_temp = self.backpatching_level_
            self.backpatching_level_ -= 1
            self.PrintQuadruples(
                Quadruples(
                    self.temp[backpatching_level_temp],
                    "j",
                    symbol_name,
                    "-",
                    self.temp[backpatching_level_temp] + 2,
                )
            )
            self.PrintQuadruples(
                Quadruples(
                    self.temp[backpatching_level_temp] + 1,
                    "j",
                    "-",
                    "-",
                    self.temp_else[backpatching_level_temp] + 1,
                )
            )
            # then
            if self.backpatching_level_ == 0:
                for Qua in self.quadruples_stack_:
                    self.PrintQuadruples(Qua)
                self.quadruples_stack_ = []
            conclude_symbol_info = GrammarSymbolInfo(
                symbol_name=production.left,
            )
            self.PopAndAppend(symbol_info_stack, conclude_symbol_info, production)

        elif "while" == production.right[0]:
            # STMT -> while id do STMT
            symbol_id = symbol_info_stack[-3]
            backpatching_level_temp = self.backpatching_level_
            self.backpatching_level_ -= 1
            symbol_pos = self.symbol_tables_[0].FindSymbol(symbol_id.txt_value)
            symbol_name = self.GetArgName(SymbolPos(0, symbol_pos))
            self.PrintQuadruples(
                Quadruples(
                    self.temp[backpatching_level_temp],
                    "j",
                    symbol_name,
                    "-",
                    self.temp[backpatching_level_temp] + 2,
                )
            )
            self.PrintQuadruples(
                Quadruples(
                    self.temp[backpatching_level_temp] + 1,
                    "j",
                    "-",
                    "-",
                    self.PeekNextStateNum() + 1,
                )
            )
            # do
            if self.backpatching_level_ == 0:
                for Qua in self.quadruples_stack_:
                    self.PrintQuadruples(Qua)
                self.quadruples_stack_ = []
            self.PrintQuadruples(
                Quadruples(
                    self.PeekNextStateNum(),
                    "j",
                    "-",
                    "-",
                    self.temp[backpatching_level_temp],
                )
            )
            self.GetNextStateNum()
            conclude_symbol_info = GrammarSymbolInfo(symbol_name=production.left)
            self.PopAndAppend(symbol_info_stack, conclude_symbol_info, production)

        elif "{" == production.right[0]:
            # STMT -> { STMTS STMT }
            # 由规约后的产生式左部构造一个文法符号属性
            conclude_symbol_info = GrammarSymbolInfo(symbol_name=production.left)
            self.PopAndAppend(symbol_info_stack, conclude_symbol_info, production)

        elif "read" == production.right[0]:
            # STMT -> read id ;
            symbol_info = symbol_info_stack[-2]
            symbol_pos = self.symbol_tables_[0].FindSymbol(symbol_info.txt_value)
            symbol_name = self.GetArgName(SymbolPos(0, symbol_pos))
            self.PrintQuadruples(
                Quadruples(self.GetNextStateNum(), "read", "-", "-", symbol_name)
            )
            conclude_symbol_info = GrammarSymbolInfo(symbol_name=production.left)
            self.PopAndAppend(symbol_info_stack, conclude_symbol_info, production)

        elif "write" == production.right[0]:
            # STMT -> write id ;
            symbol_info = symbol_info_stack[-2]
            symbol_pos = self.symbol_tables_[0].FindSymbol(symbol_info.txt_value)
            symbol_name = self.GetArgName(SymbolPos(0, symbol_pos))
            self.PrintQuadruples(
                Quadruples(self.GetNextStateNum(), "write", "-", "-", symbol_name)
            )
            conclude_symbol_info = GrammarSymbolInfo(
                symbol_name=production.left,
            )
            self.PopAndAppend(symbol_info_stack, conclude_symbol_info, production)

        elif "EXPR" == production.left and production.right[0] == "EXPR":
            # EXPR -> EXPR ADD TERM
            symbol_expression2 = symbol_info_stack[-1]
            symbol_add = symbol_info_stack[-2]
            symbol_expression1 = symbol_info_stack[-3]
            symbol_pos = self.symbol_tables_[1].AddSymbol()
            symbol_name = self.symbol_tables_[1].GetSymbolName(symbol_pos)

            arg1_name = self.GetArgName(symbol_expression1.pos)
            arg2_name = self.GetArgName(symbol_expression2.pos)
            self.PrintQuadruples(
                Quadruples(
                    self.GetNextStateNum(),
                    symbol_add.txt_value,
                    arg1_name,
                    arg2_name,
                    symbol_name,
                )
            )

            conclude_symbol_info = GrammarSymbolInfo(
                symbol_name=production.left,
                txt_value=symbol_name,
                pos=SymbolPos(1, symbol_pos),
            )
            self.PopAndAppend(symbol_info_stack, conclude_symbol_info, production)

        elif "EXPR" == production.left:
            # EXPR -> TERM
            symbol_info = symbol_info_stack[-1]
            conclude_symbol_info = GrammarSymbolInfo(
                symbol_name=production.left,
                txt_value=symbol_info.txt_value,
                pos=symbol_info.pos,
            )
            self.PopAndAppend(symbol_info_stack, conclude_symbol_info, production)

        elif "ADD" == production.left:
            # ADD -> +
            # 由规约后的产生式左部构造一个文法符号属性
            conclude_symbol_info = GrammarSymbolInfo(
                symbol_name=production.left, txt_value=production.right[0]
            )
            self.PopAndAppend(symbol_info_stack, conclude_symbol_info, production)

        elif "TERM" == production.left and production.right[0] == "TERM":
            # TERM -> TERM MUL NEGA
            symbol_expression2 = symbol_info_stack[-1]
            symbol_add = symbol_info_stack[-2]
            symbol_expression1 = symbol_info_stack[-3]
            symbol_pos = self.symbol_tables_[1].AddSymbol()
            symbol_name = self.symbol_tables_[1].GetSymbolName(symbol_pos)

            arg1_name = self.GetArgName(symbol_expression1.pos)
            arg2_name = self.GetArgName(symbol_expression2.pos)
            self.PrintQuadruples(
                Quadruples(
                    self.GetNextStateNum(),
                    symbol_add.txt_value,
                    arg1_name,
                    arg2_name,
                    symbol_name,
                )
            )

            conclude_symbol_info = GrammarSymbolInfo(
                symbol_name=production.left,
                txt_value=symbol_name,
                pos=SymbolPos(1, symbol_pos),
            )

            self.PopAndAppend(symbol_info_stack, conclude_symbol_info, production)

        elif "TERM" == production.left:
            # TERM -> NEGA
            symbol_info = symbol_info_stack[-1]
            conclude_symbol_info = GrammarSymbolInfo(
                symbol_name=production.left,
                txt_value=symbol_info.txt_value,
                pos=symbol_info.pos,
            )
            self.PopAndAppend(symbol_info_stack, conclude_symbol_info, production)

        elif "MUL" == production.left:
            # MUL -> *
            # 由规约后的产生式左部构造一个文法符号属性
            conclude_symbol_info = GrammarSymbolInfo(
                symbol_name=production.left, txt_value=production.right[0]
            )
            self.PopAndAppend(symbol_info_stack, conclude_symbol_info, production)

        elif "NEGA" == production.left and production.right[0] == "FACTOR":
            # NEGA -> FACTOR
            symbol_info = symbol_info_stack[-1]
            conclude_symbol_info = GrammarSymbolInfo(
                symbol_name=production.left,
                txt_value=symbol_info.txt_value,
                pos=symbol_info.pos,
            )
            self.PopAndAppend(symbol_info_stack, conclude_symbol_info, production)

        elif "NEGA" == production.left and production.right[0] == "-":
            # NEGA -> - FACTOR
            symbol_info = symbol_info_stack[-1]
            symbol_pos = self.symbol_tables_[1].AddSymbol(symbol_info.txt_value)
            symbol_name = self.symbol_tables_[1].GetSymbolName(symbol_pos)
            conclude_symbol_info = GrammarSymbolInfo(
                symbol_name=production.left,
                txt_value=symbol_name,
                pos=SymbolPos(1, symbol_pos),
            )

            self.PrintQuadruples(
                Quadruples(
                    self.GetNextStateNum(),
                    "nec",
                    symbol_info.txt_value,
                    "-",
                    symbol_name,
                )
            )
            self.PopAndAppend(symbol_info_stack, conclude_symbol_info, production)

        elif "FACTOR" == production.left and production.right[0] == "(":
            # FACTOR -> ( EXPR )
            symbol_expression = symbol_info_stack[-2]
            # 由规约后的产生式左部构造一个文法符号属性
            conclude_symbol_info = GrammarSymbolInfo(
                symbol_name=production.left,
                txt_value=self.symbol_tables_[
                    symbol_expression.pos.table_pos
                ].GetSymbolName(symbol_expression.pos.symbol_pos),
                pos=symbol_expression.pos,
            )
            self.PopAndAppend(symbol_info_stack, conclude_symbol_info, production)

        elif "FACTOR" == production.left and production.right[0] == "id":
            # FACTOR -> id
            symbol_info = symbol_info_stack[-1]
            symbol_pos = self.symbol_tables_[0].FindSymbol(symbol_info.txt_value)
            conclude_symbol_info = GrammarSymbolInfo(
                symbol_name=production.left,
                txt_value=symbol_info.txt_value,
                pos=SymbolPos(0, symbol_pos),
            )
            self.PopAndAppend(symbol_info_stack, conclude_symbol_info, production)

        elif "FACTOR" == production.left and production.right[0] == "number":
            # FACTOR -> number
            symbol_info = symbol_info_stack[-1]
            symbol_pos = self.symbol_tables_[1].AddSymbol(symbol_info.txt_value)
            symbol_name = self.symbol_tables_[1].GetSymbolName(symbol_pos)
            # 由规约后的产生式左部构造一个文法符号属性
            conclude_symbol_info = GrammarSymbolInfo(
                symbol_name=production.left,
                txt_value=symbol_name,
                pos=SymbolPos(1, symbol_pos),
            )

            self.PrintQuadruples(
                Quadruples(
                    self.GetNextStateNum(),
                    ":=",
                    symbol_info.txt_value,
                    "-",
                    symbol_name,
                )
            )
            self.PopAndAppend(symbol_info_stack, conclude_symbol_info, production)

        elif "BOOL" == production.left and production.right[0] == "BOOL":
            # BOOL -> BOOL || JOIN
            symbol_expression2 = symbol_info_stack[-1]
            symbol_or = symbol_info_stack[-2]
            symbol_expression1 = symbol_info_stack[-3]
            symbol_pos = self.symbol_tables_[1].AddSymbol()
            symbol_name = self.symbol_tables_[1].GetSymbolName(symbol_pos)

            arg1_name = self.GetArgName(symbol_expression1.pos)
            arg2_name = self.GetArgName(symbol_expression2.pos)
            self.PrintQuadruples(
                Quadruples(
                    self.GetNextStateNum(),
                    symbol_or.txt_value,
                    arg1_name,
                    arg2_name,
                    symbol_name,
                )
            )

            conclude_symbol_info = GrammarSymbolInfo(
                symbol_name=production.left,
                txt_value=symbol_name,
                pos=SymbolPos(1, symbol_pos),
            )
            self.PopAndAppend(symbol_info_stack, conclude_symbol_info, production)

        elif "BOOL" == production.left and production.right[0] == "JOIN":
            # BOOL -> JOIN
            symbol_info = symbol_info_stack[-1]
            symbol_pos = self.symbol_tables_[1].FindSymbol(symbol_info.txt_value)
            symbol_name = self.symbol_tables_[1].GetSymbolName(symbol_pos)
            conclude_symbol_info = GrammarSymbolInfo(
                symbol_name=production.left,
                txt_value=symbol_name,
                pos=SymbolPos(1, symbol_pos),
            )
            self.PopAndAppend(symbol_info_stack, conclude_symbol_info, production)

        elif "JOIN" == production.left and production.right[0] == "JOIN":
            # JOIN -> JOIN && NOT
            symbol_expression2 = symbol_info_stack[-1]
            symbol_or = symbol_info_stack[-2]
            symbol_expression1 = symbol_info_stack[-3]
            symbol_pos = self.symbol_tables_[1].AddSymbol()
            symbol_name = self.symbol_tables_[1].GetSymbolName(symbol_pos)

            arg1_name = self.GetArgName(symbol_expression1.pos)
            arg2_name = self.GetArgName(symbol_expression2.pos)
            self.PrintQuadruples(
                Quadruples(
                    self.GetNextStateNum(),
                    symbol_or.txt_value,
                    arg1_name,
                    arg2_name,
                    symbol_name,
                )
            )

            conclude_symbol_info = GrammarSymbolInfo(
                symbol_name=production.left,
                txt_value=symbol_name,
                pos=SymbolPos(1, symbol_pos),
            )
            self.PopAndAppend(symbol_info_stack, conclude_symbol_info, production)

        elif "JOIN" == production.left and production.right[0] == "NOT":
            # JOIN -> NOT
            symbol_info = symbol_info_stack[-1]
            symbol_pos = self.symbol_tables_[1].FindSymbol(symbol_info.txt_value)
            symbol_name = self.symbol_tables_[1].GetSymbolName(symbol_pos)
            conclude_symbol_info = GrammarSymbolInfo(
                symbol_name=production.left,
                txt_value=symbol_name,
                pos=SymbolPos(1, symbol_pos),
            )
            self.PopAndAppend(symbol_info_stack, conclude_symbol_info, production)

        elif "NOT" == production.left and production.right[0] == "REL":
            # NOT -> REL
            symbol_info = symbol_info_stack[-1]
            symbol_pos = self.symbol_tables_[1].FindSymbol(symbol_info.txt_value)
            symbol_name = self.symbol_tables_[1].GetSymbolName(symbol_pos)
            conclude_symbol_info = GrammarSymbolInfo(
                symbol_name=production.left,
                txt_value=symbol_name,
                pos=SymbolPos(1, symbol_pos),
            )
            self.PopAndAppend(symbol_info_stack, conclude_symbol_info, production)

        elif "NOT" == production.left and production.right[0] == "!":
            # NOT -> ! REL
            symbol_info = symbol_info_stack[-1]
            symbol_pos = self.symbol_tables_[1].AddSymbol()
            symbol_name = self.symbol_tables_[1].GetSymbolName(symbol_pos)
            arg1_name = self.GetArgName(symbol_expression1.pos)
            self.PrintQuadruples(
                Quadruples(self.GetNextStateNum(), "nec", arg1_name, "-", symbol_name)
            )
            conclude_symbol_info = GrammarSymbolInfo(
                symbol_name=production.left,
                txt_value=symbol_name,
                pos=SymbolPos(1, symbol_pos),
            )
            self.PopAndAppend(symbol_info_stack, conclude_symbol_info, production)

        elif "REL" == production.left and production.right[0] == "EXPR":
            # REL -> EXPR ROP EXPR
            symbol_expression2 = symbol_info_stack[-1]
            symbol_ROP = symbol_info_stack[-2]
            symbol_expression1 = symbol_info_stack[-3]
            symbol_pos = self.symbol_tables_[1].AddSymbol()
            symbol_name = self.symbol_tables_[1].GetSymbolName(symbol_pos)

            arg1_name = self.GetArgName(symbol_expression1.pos)
            arg2_name = self.GetArgName(symbol_expression2.pos)
            self.PrintQuadruples(
                Quadruples(
                    self.GetNextStateNum(),
                    symbol_ROP.txt_value,
                    arg1_name,
                    arg2_name,
                    symbol_name,
                )
            )

            conclude_symbol_info = GrammarSymbolInfo(
                symbol_name=production.left,
                txt_value=symbol_name,
                pos=SymbolPos(1, symbol_pos),
            )
            self.PopAndAppend(symbol_info_stack, conclude_symbol_info, production)

        elif "ROP" == production.left:
            # ROP -> > || < || >= || <= || == || !=
            # 由规约后的产生式左部构造一个文法符号属性
            conclude_symbol_info = GrammarSymbolInfo(
                symbol_name=production.left, txt_value=production.right[0]
            )
            self.PopAndAppend(symbol_info_stack, conclude_symbol_info, production)
        return True
