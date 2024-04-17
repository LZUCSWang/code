from symbol_table import *
from target_code_generator import *
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
        self.main_line = -1
        self.target_code_generator_ = TargetCodeGenerator(
            self.symbol_tables_
        )  # 将参数表传到目标代码生成器中，实现共享
        self.target_code_generator_.TargetCodeGeneratorInit(self.symbol_tables_)
        self.while_cnt = 0
        self.if_cnt = 0
        self.w_j_label_num = 0

        self.temp_string_=""
        self.quadruples_stack_=[]
        self.quadruples_stack_length = [0]*20
        self.temp = [0]*20
        self.temp_else = [0]*20

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
                    + self.symbol_tables_[sp.table_pos].GetTableName()
                    + "Var"
                )
        else:
            pos = self.symbol_tables_[0].FindSymbol(
                self.symbol_tables_[sp.table_pos].GetTableName()
            )
            symbol = self.symbol_tables_[0].GetSymbol(pos)
            symbol_pos_minus = sp.symbol_pos - 1
            arg_name = (
                arg_name + "-" + symbol.name + "_paramerter " + str(sp.symbol_pos)
            )
        return arg_name

    def PrintQuadruples(self, quadruples=None):
        if quadruples is not None:
            if self.backpatching_level_ == 0:  # 不需要回填
                # self.intermediate_code_temp_printer_.write(
                #     f"{quadruples.num} ({quadruples.op}, "
                #     f"{quadruples.arg1}, {quadruples.arg2}, "
                #     f"{quadruples.result})\n"
                # )
                self.temp_string_+= f"{quadruples.num} ({quadruples.op}, {quadruples.arg1}, {quadruples.arg2}, {quadruples.result})\n"
                with open("./gen_data/target_file/intermediate_code.txt", "w") as file:
                    file.write(self.temp_string_)
            else:  # 需要回填
                self.quadruples_stack_length[self.backpatching_level_] += 1
                self.quadruples_stack_.append(quadruples)
                self.quadruples_stack_.sort(key=lambda x:x.num)

        return True

    def CreateSymbolTable(self, table_type, table_name):
        self.symbol_tables_.append(SymbolTable(table_type, table_name))
        self.current_symbol_table_stack_.append(len(self.symbol_tables_) - 1)
        return True

    # def ExecuteSemanticCheck(self, symbol_info_stack, production):
    #     if "Const_value" == production.left:  # Const_value->num
    #         self.symbol_info = symbol_info_stack[-1]

    #         # 由规约后的产生式左部构造一个文法符号属性
    #         conclude_symbol_info = GrammarSymbolInfo(
    #             symbol_name=production.left, txt_value=self.symbol_info.txt_value
    #         )

    #         # 获取产生式右部的长度
    #         length = 0
    #         if "$" != production.right[0]:
    #             length = len(production.right)

    #         for i in range(length):
    #             symbol_info_stack.pop()

    #         symbol_info_stack.append(conclude_symbol_info)

    #     elif (
    #         "Factor" == production.left and production.right[0] == "Const_value"
    #     ):  # Factor->Const_value
    #         # 需要把 Const_value 加入临时变量表，得到临时变量的名称已经在表中的位置。
    #         # txt_value 表示名称
    #         # pos 表示位置
    #         # 需要 中间代码操作---------------------------------------------------------------------------------------------

    #         # 符号属性
    #         symbol_info = symbol_info_stack[-1]

    #         # 由规约后的产生式左部构造一个文法符号属性
    #         conclude_symbol_info = GrammarSymbolInfo(symbol_name=production.left)

    #         symbol_pos = self.symbol_tables_[1].AddSymbol(symbol_info.txt_value)
    #         symbol_name = self.symbol_tables_[1].GetSymbolName(symbol_pos)

    #         conclude_symbol_info.txt_value = symbol_name
    #         conclude_symbol_info.pos = SymbolPos(1, symbol_pos)  # 1表示临时变量表

    #         self.PrintQuadruples(
    #             Quadruples(
    #                 self.GetNextStateNum(),
    #                 ":=",
    #                 symbol_info.txt_value,
    #                 "-",
    #                 symbol_name,
    #             )
    #         )

    #         # 获取产生式右部的长度
    #         length = len(production.right)
    #         if "$" != production.right[0]:
    #             length = len(production.right)

    #         for i in range(length):
    #             symbol_info_stack.pop()

    #         symbol_info_stack.append(conclude_symbol_info)

    #         # 目标代码生成
    #         self.target_code_generator_.LoadImmToReg(
    #             symbol_info.txt_value, conclude_symbol_info.pos
    #         )
    #     elif (
    #         "Factor" == production.left and production.right[0] == "("
    #     ):  # Factor->(Expression)
    #         # 符号属性
    #         symbol_expression = symbol_info_stack[-2]

    #         # 由规约后的产生式左部构造一个文法符号属性
    #         conclude_symbol_info = GrammarSymbolInfo(
    #             symbol_name=production.left,
    #             txt_value=self.symbol_tables_[
    #                 symbol_expression.pos.table_pos
    #             ].GetSymbolName(symbol_expression.pos.symbol_pos),
    #             pos=symbol_expression.pos,
    #         )

    #         # 获取产生式右部的长度
    #         length = 0
    #         if "$" != production.right[0]:
    #             length = len(production.right)

    #         for i in range(length):
    #             symbol_info_stack.pop()

    #         symbol_info_stack.append(conclude_symbol_info)
    #     elif (
    #         "Factor" == production.left and production.right[0] == "identifier"
    #     ):  # Factor->identifier FTYPE
    #         # 符号属性
    #         symbol_identifier = symbol_info_stack[-2]
    #         symbol_ftype = symbol_info_stack[-1]

    #         # 在符号表栈中一级级逆序寻找 identifier 是否被定义过
    #         identifier_pos = -1
    #         identifier_layer = len(self.current_symbol_table_stack_) - 1
    #         for i in range(identifier_layer, -1, -1):
    #             search_table = self.symbol_tables_[self.current_symbol_table_stack_[i]]
    #             identifier_pos = search_table.FindSymbol(symbol_identifier.txt_value)
    #             if identifier_pos != -1:  # 表示在某一级中找到了
    #                 break

    #         if identifier_pos == -1:  # 没找到，表示不存在，说明没定义就使用，语义错误
    #             print("语义错误！！！", symbol_identifier.txt_value, "没有定义！")
    #             return False

    #         # 给 Identifier 赋值 pos
    #         symbol_identifier.pos.table_pos = self.current_symbol_table_stack_[
    #             identifier_layer
    #         ]
    #         symbol_identifier.pos.symbol_pos = identifier_pos

    #         # 由规约后的产生式左部构造一个文法符号属性
    #         # conclude_symbol_info = {"symbol_name": production.left}
    #         conclude_symbol_info = GrammarSymbolInfo(symbol_name=production.left)
    #         if (
    #             symbol_ftype.txt_value == ""
    #         ):  # 表示 FTYPE 是从 FTYPE -> $ 获取，即这里 Factor 是从标识符获取，而非函数。
    #             # Factor->identifier，而不是函数调用
    #             # 如果不是临时变量的话，需要申请一个临时变量用来存放。
    #             if CATEGORY.TEMP == self.symbol_tables_[
    #                 symbol_identifier.pos.table_pos
    #             ].GetSymbolMode(symbol_identifier.pos.symbol_pos):
    #                 # 原本就是临时变量，无需再申请，可直接传递使用
    #                 conclude_syble_info.pos = SymbolPos(
    #                     symbol_identifier.pos.table_pos,
    #                     symbol_identifier.pos.symbol_pos,
    #                 )
    #                 conclude_syble_info.txt_value = symbol_identifier.txt_value
    #             else:
    #                 # 申请临时变量
    #                 symbol_pos = self.symbol_tables_[1].AddSymbol(
    #                     symbol_identifier.txt_value
    #                 )
    #                 symbol_name = self.symbol_tables_[1].GetSymbolName(symbol_pos)

    #                 # 用临时变量来存储当前变量的值
    #                 self.PrintQuadruples(
    #                     Quadruples(
    #                         self.GetNextStateNum(),
    #                         ":=",
    #                         self.GetArgName(symbol_identifier.pos),
    #                         "-",
    #                         symbol_name,
    #                     )
    #                 )

    #                 conclude_syble_info.pos = {
    #                     "table_pos": 1,
    #                     "symbol_pos": symbol_pos,
    #                 }  # 1 表示临时变量表

    #                 # 目标代码生成
    #                 tar_arg1_name = self.target_code_generator_.SetArgBeReady(
    #                     conclude_syble_info.pos
    #                 )  # 新申请的临时变量
    #                 sb_tmp = {
    #                     "table_pos": symbol_identifier.pos.table_pos,
    #                     "symbol_pos": symbol_identifier.pos.symbol_pos,
    #                 }
    #                 tar_arg2_name = self.target_code_generator_.SetArgBeReady(sb_tmp)

    #                 self.target_code_generator_.PrintQuadruples(
    #                     Instructions("move", tar_arg1_name, tar_arg2_name, "")
    #                 )
    #         else:
    #             # Factor->identifier FTYPE 是从函数调用中获取的
    #             # 向上传递 pos 即可
    #             table_pos, symbol_pos = 0, 0
    #             table_pos = self.symbol_tables_[symbol_ftype.pos.table_pos].GetSymbol(
    #                 symbol_ftype.pos.symbol_pos
    #             )["func_symbol_pos"]
    #             # conclude_syble_info.pos = {"table_pos": table_pos, "symbol_pos": symbol_pos}
    #             conclude_syble_info.txt_value = ""

    #             # 申请临时变量
    #             symbol_pos_t = self.symbol_tables_[1].AddSymbol(
    #                 symbol_identifier.txt_value
    #             )
    #             symbol_name = self.symbol_tables_[1].GetSymbolName(symbol_pos_t)

    #             # 用临时变量来存储当前变量的值
    #             func_table_pos_t = self.symbol_tables_[0].GetSymbol(
    #                 symbol_identifier.pos.symbol_pos
    #             )["func_symbol_pos"]
    #             return_symbol_pos = {"table_pos": func_table_pos_t, "symbol_pos": 0}
    #             self.PrintQuadruples(
    #                 Quadruples(
    #                     self.GetNextStateNum(),
    #                     ":=",
    #                     self.GetArgName(return_symbol_pos),
    #                     "-",
    #                     symbol_name,
    #                 )
    #             )
    #             conclude_syble_info.pos = {
    #                 "table_pos": 1,
    #                 "symbol_pos": symbol_pos_t,
    #             }  # 1 表示临时变量表

    #             # 目标代码生成
    #             self.target_code_generator_.ClearRegs()  # 调用函数前先清空寄存器
    #             target_func_name = self.symbol_tables_[0].GetSymbolName(identifier_pos)
    #             self.target_code_generator_.PrintQuadruples(
    #                 "jal " + target_func_name
    #             )  # 生成函数调用指令
    #             # 清理栈帧
    #             self.target_code_generator_.PrintQuadruples(
    #                 Instructions("move", "$sp", "$fp", "")
    #             )  # sp 指到 fp
    #             self.target_code_generator_.PrintQuadruples(
    #                 Instructions("lw", "$fp", "($fp)", "")
    #             )  # fp 指回老 fp
    #             par_num = self.symbol_tables_[0].GetSymbol(
    #                 symbol_identifier.pos.symbol_pos
    #             )[
    #                 "parameter_num"
    #             ]  # 函数参数个数
    #             sp_back_num = (
    #                 -1 - par_num
    #             )  # sp 指针回退到函数调用前的栈顶。 1 返回地址，以及实际参数的个数
    #             self.target_code_generator_.PushStack_sp(sp_back_num)  # sp 回退

    #             # 返回值修改 v0 -> tmp
    #             tar_arg1_name = self.target_code_generator_.SetArgBeReady(
    #                 conclude_syble_info.pos
    #             )  # 新申请的临时变量
    #             tar_arg2_name = self.target_code_generator_.SetArgBeReady(
    #                 conclude_syble_info.pos
    #             )
    #             self.target_code_generator_.PrintQuadruples(
    #                 Instructions("move", tar_arg1_name, "$v0", "")
    #             )
    #         # 获取产生式右部的长度
    #         length = 0
    #         if production.right[0] != "$":
    #             length = len(production.right)

    #         for i in range(length):
    #             symbol_info_stack.pop()
    #         symbol_info_stack.append(conclude_syble_info)
    #     elif (
    #         "Factor_loop" == production.left and production.right[0] == "$"
    #     ):  # Factor_loop -> $
    #         # 由规约后的产生式左部构造一个文法符号属性
    #         conclude_syble_info = {
    #             "symbol_name": production.left,
    #             "txt_value": "",  # 空，这里必须为空
    #         }
    #         symbol_info_stack.append(conclude_syble_info)
    #     elif "Factor_loop" == production.left and production.right[0] == "Factor_loop":
    #         # Factor_loop->Factor_loop Factor *|Factor_loop Factor /
    #         # 这里需要创建临时变量

    #         # 符号属性
    #         symbol_factor = symbol_info_stack[-2]
    #         symbol_factor_loop = symbol_info_stack[-3]

    #         # 由规约后的产生式左部构造一个文法符号属性
    #         conclude_syble_info = {"symbol_name": production.left}

    #         if symbol_factor_loop.txt_value == "":  # 右部的Factor_loop是从$规约而来
    #             # 申请临时变量，用来存放结果，从左往右传递

    #             conclude_syble_info.txt_value = symbol_info_stack[-1][
    #                 "symbol_name"
    #             ]  # * 或者 /

    #             if CATEGORY.TEMP == self.symbol_tables_[
    #                 symbol_factor.pos.table_pos
    #             ].GetSymbolMode(symbol_factor.pos.symbol_pos):
    #                 # 原本就是临时变量，无需再申请，可直接传递使用
    #                 conclude_syble_info.pos = symbol_factor.pos
    #             else:
    #                 # 申请临时变量
    #                 symbol_pos = self.symbol_tables_[1].AddSymbol(
    #                     symbol_factor.txt_value
    #                 )
    #                 symbol_name = self.symbol_tables_[1].GetSymbolName(symbol_pos)

    #                 # 用临时变量来存储当前变量的值
    #                 self.PrintQuadruples(
    #                     Quadruples(
    #                         self.GetNextStateNum(),
    #                         ":=",
    #                         self.GetArgName(symbol_factor.pos),
    #                         "-",
    #                         symbol_name,
    #                     )
    #                 )
    #                 conclude_syble_info.pos = {
    #                     "table_pos": 1,
    #                     "symbol_pos": symbol_pos,
    #                 }  # 1表示临时变量表

    #                 # 目标代码生成
    #                 tar_arg1_name = self.target_code_generator_.SetArgBeReady(
    #                     conclude_syble_info.pos
    #                 )  # 新申请的临时变量
    #                 tar_arg2_name = self.target_code_generator_.SetArgBeReady(
    #                     symbol_factor.pos
    #                 )

    #                 self.target_code_generator_.PrintQuadruples(
    #                     Instructions("move", tar_arg1_name, tar_arg2_name, "")
    #                 )
    #         else:  # 右部的Factor_loop有东西。需要计算，同时将临时变量向上传递
    #             # 这里需要通过中间代码生成
    #             # 把临时变量 op Factor的值赋给临时变量

    #             # 生成中间代码：临时变量和factor 运算后返回给临时变量
    #             # 获取两个arg的名称。
    #             # 不是临时变量的需要加上表所在的序号
    #             # arg2 类似a_2
    #             arg2_name = self.GetArgName(symbol_factor.pos)
    #             arg1_name = self.GetArgName(symbol_factor_loop.pos)

    #             tar_arg2_name = self.target_code_generator_.SetArgBeReady(
    #                 symbol_factor.pos
    #             )
    #             tar_arg1_name = self.target_code_generator_.SetArgBeReady(
    #                 symbol_factor_loop.pos
    #             )

    #             conclude_syble_info.txt_value = symbol_factor_loop[
    #                 "txt_value"
    #             ]  # * 或者 /
    #             conclude_syble_info.pos = symbol_factor_loop.pos

    #             # 目标代码与中间代码共同生成
    #             if "*" == symbol_factor_loop.txt_value:
    #                 self.PrintQuadruples(
    #                     Quadruples(
    #                         self.GetNextStateNum(), "*", arg1_name, arg2_name, arg1_name
    #                     )
    #                 )
    #                 self.target_code_generator_.PrintQuadruples(
    #                     Instructions("mult", tar_arg1_name, tar_arg2_name, "")
    #                 )
    #                 self.target_code_generator_.PrintQuadruples(
    #                     Instructions("mflo", tar_arg1_name, "", "")
    #                 )  # 取最低的32位。高32舍去

    #             else:  # '/' 除法
    #                 self.PrintQuadruples(
    #                     Quadruples(
    #                         self.GetNextStateNum(), "/", arg1_name, arg2_name, arg1_name
    #                     )
    #                 )
    #                 self.target_code_generator_.PrintQuadruples(
    #                     Instructions("div", tar_arg1_name, tar_arg2_name, "")
    #                 )
    #                 self.target_code_generator_.PrintQuadruples(
    #                     Instructions("mflo", tar_arg1_name, "", "")
    #                 )  # 取最低的32位。高32舍去
    #                 # 获取产生式右部的长度
    #         length = 0
    #         if "$" != production.right[0]:
    #             length = len(production.right)

    #         for i in range(length):
    #             symbol_info_stack.pop()

    #         symbol_info_stack.append(conclude_syble_info)
    #     elif "Item" == production.left:  # Item->Factor_loop Factor
    #         # 符号属性
    #         symbol_factor_loop = symbol_info_stack[-2]
    #         symbol_factor = symbol_info_stack[-1]

    #         # 由规约后的产生式左部构造一个文法符号属性
    #         conclude_syble_info = {"symbol_name": production.left, "txt_value": ""}

    #         # Factor_loop 为空
    #         if symbol_factor_loop.txt_value == "":
    #             conclude_syble_info.txt_value = ""
    #             conclude_syble_info.pos = symbol_factor.pos
    #         else:  # 不为空
    #             # Factor_loop 和 Factor 操作一下，然后返回 Factor_loop
    #             arg2_name = self.GetArgName(symbol_factor.pos)
    #             arg1_name = self.GetArgName(symbol_factor_loop.pos)

    #             tar_arg2_name = self.target_code_generator_.SetArgBeReady(
    #                 symbol_factor.pos
    #             )
    #             tar_arg1_name = self.target_code_generator_.SetArgBeReady(
    #                 symbol_factor_loop.pos
    #             )

    #             if "*" == symbol_factor_loop.txt_value:
    #                 self.PrintQuadruples(
    #                     Quadruples(
    #                         self.GetNextStateNum(), "*", arg1_name, arg2_name, arg1_name
    #                     )
    #                 )
    #                 self.target_code_generator_.PrintQuadruples(
    #                     Instructions("mult", tar_arg1_name, tar_arg2_name, "")
    #                 )
    #                 self.target_code_generator_.PrintQuadruples(
    #                     Instructions("mflo", tar_arg1_name, "", "")
    #                 )  # 取最低的32位。高32舍去
    #             else:  # '/' 除法
    #                 self.PrintQuadruples(
    #                     Quadruples(
    #                         self.GetNextStateNum(), "/", arg1_name, arg2_name, arg1_name
    #                     )
    #                 )
    #                 self.target_code_generator_.PrintQuadruples(
    #                     Instructions("div", tar_arg1_name, tar_arg2_name, "")
    #                 )
    #                 self.target_code_generator_.PrintQuadruples(
    #                     Instructions("mflo", tar_arg1_name, "", "")
    #                 )  # 取最低的32位。高32舍去

    #             # conclude_syble_info.txt_value  == * 或者 /
    #             conclude_syble_info.txt_value = symbol_factor_loop.txt_value
    #             conclude_syble_info.pos = symbol_factor_loop.pos

    #         # 获取产生式右部的长度
    #         length = 0
    #         if "$" != production.right[0]:
    #             length = len(production.right)

    #         for i in range(length):
    #             symbol_info_stack.pop()

    #         symbol_info_stack.append(conclude_syble_info)
    #     elif (
    #         "Item_loop" == production.left and production.right[0] == "$"
    #     ):  # Item_loop->$
    #         # 由规约后的产生式左部构造一个文法符号属性
    #         conclude_syble_info = {"symbol_name": production.left, "txt_value": ""}

    #         # symbol_info_stack.pop_back()
    #         symbol_info_stack.append(conclude_syble_info)

    #     elif (
    #         "Item_loop" == production.left and production.right[0] == "Item_loop"
    #     ):  # Item_loop->Item_loop Item +|Item_loop Item -
    #         # 符号属性
    #         symbol_item = symbol_info_stack[-2]
    #         symbol_item_loop = symbol_info_stack[-3]

    #         # 由规约后的产生式左部构造一个文法符号属性
    #         conclude_syble_info = {"symbol_name": production.left}
    #         if symbol_item_loop.txt_value == "":  # 右部的Item_loop是从$规约而来
    #             # 这里没有必要申请临时变量，直接把值从Item传递到Item_loop
    #             conclude_syble_info.txt_value = symbol_info_stack[-1][
    #                 "symbol_name"
    #             ]  # + 或者 -
    #             conclude_syble_info.pos = symbol_item.pos

    #             # //申请临时变量，用来存放结果，从左往右传递
    #             # //conclude_syble_info.txt_value = symbol_info_stack.back().symbol_name; //  + 或者 -

    #             # //申请临时变量
    #             # //int symbol_pos = self.symbol_tables_[1].AddSymbol(symbol_item.txt_value);
    #             # //string symbol_name = self.symbol_tables_[1].GetSymbolName(symbol_pos);
    #             # //
    #             # ////这里产生中间代码--------
    #             # ////用临时变量来存储当前变量的值
    #             # //PrintQuadruples(Quadruples(GetNextStateNum(), ":=", GetArgName(symbol_item.pos), "-", symbol_name));

    #             # //conclude_syble_info.pos = { 1, symbol_pos };//1表示临时变量表
    #         else:  # 右部的Item_loop有东西。需要计算，同时产生临时变量
    #             # 这里需要通过中间代码生成
    #             # 把临时变量 op Item的值赋给临时变量

    #             # 生成中间代码：临时变量和Item 运算后返回给临时变量
    #             # 获取两个arg的名称。
    #             # 不是临时变量的需要加上表所在的序号
    #             # arg2 类似a_2
    #             arg2_name = self.GetArgName(symbol_item.pos)
    #             arg1_name = self.GetArgName(symbol_item_loop.pos)

    #             tar_arg2_name = self.target_code_generator_.SetArgBeReady(
    #                 symbol_item.pos
    #             )
    #             tar_arg1_name = self.target_code_generator_.SetArgBeReady(
    #                 symbol_item_loop.pos
    #             )

    #             # 目标代码与中间代码共同生成
    #             if "+" == symbol_item_loop.txt_value:
    #                 self.PrintQuadruples(
    #                     Quadruples(
    #                         self.GetNextStateNum(), "+", arg1_name, arg2_name, arg1_name
    #                     )
    #                 )
    #                 self.target_code_generator_.PrintQuadruples(
    #                     Instructions("add", tar_arg1_name, tar_arg1_name, tar_arg2_name)
    #                 )
    #             else:  # '-' 减法
    #                 self.PrintQuadruples(
    #                     Quadruples(
    #                         self.GetNextStateNum(), "-", arg1_name, arg2_name, arg1_name
    #                     )
    #                 )
    #                 self.target_code_generator_.PrintQuadruples(
    #                     Instructions("sub", tar_arg1_name, tar_arg1_name, tar_arg2_name)
    #                 )

    #             conclude_syble_info.txt_value = symbol_info_stack[-1][
    #                 "symbol_name"
    #             ]  # + 或者 -
    #             conclude_syble_info.pos = symbol_item_loop.pos
    #             # 获取产生式右部的长度
    #         length = 0
    #         if production.right[0] != "$":
    #             length = len(production.right)

    #         for i in range(length):
    #             symbol_info_stack.pop()
    #         symbol_info_stack.append(conclude_syble_info)
    #     elif "Add_expression" == production.left:
    #         # 符号属性
    #         symbol_item_loop = symbol_info_stack[-2]
    #         symbol_item = symbol_info_stack[-1]

    #         # 由规约后的产生式左部构造一个文法符号属性
    #         conclude_syble_info = GrammarSymbolInfo()
    #         conclude_syble_info.symbol_name = production.left

    #         # Item_loop 为空
    #         if symbol_item_loop.txt_value == "":
    #             conclude_syble_info.txt_value = ""
    #             conclude_syble_info.pos = symbol_item.pos
    #         else:  # 不为空
    #             # Item_loop 和 Item 操作一下，然后返回 Item_loop
    #             arg2_name = self.GetArgName(symbol_item.pos)
    #             arg1_name = self.GetArgName(symbol_item_loop.pos)

    #             tar_arg2_name = self.target_code_generator_.SetArgBeReady(
    #                 symbol_item.pos
    #             )
    #             tar_arg1_name = self.target_code_generator_.SetArgBeReady(
    #                 symbol_item_loop.pos
    #             )

    #             # 目标代码与中间代码共同生成
    #             if "+" == symbol_item_loop.txt_value:
    #                 self.PrintQuadruples(
    #                     Quadruples(
    #                         self.GetNextStateNum(), "+", arg1_name, arg2_name, arg1_name
    #                     )
    #                 )
    #                 self.target_code_generator_.PrintQuadruples(
    #                     Instructions("add", tar_arg1_name, tar_arg1_name, tar_arg2_name)
    #                 )
    #             else:  # "-" 减法
    #                 self.PrintQuadruples(
    #                     Quadruples(
    #                         self.GetNextStateNum(), "-", arg1_name, arg2_name, arg1_name
    #                     )
    #                 )
    #                 self.target_code_generator_.PrintQuadruples(
    #                     Instructions("sub", tar_arg1_name, tar_arg1_name, tar_arg2_name)
    #                 )

    #             # conclude_syble_info.txt_value == + 或者 -
    #             conclude_syble_info.txt_value = symbol_item_loop.txt_value
    #             conclude_syble_info.pos = symbol_item_loop.pos

    #         # 获取产生式右部的长度
    #         length = 0
    #         if "$" != production.right[0]:
    #             length = len(production.right)

    #         for i in range(length):
    #             symbol_info_stack.pop()
    #         symbol_info_stack.append(conclude_syble_info)
    #     elif "Add_expression_loop" == production.left and production.right[0] == "$":
    #         # 由规约后的产生式左部构造一个文法符号属性
    #         conclude_syble_info = GrammarSymbolInfo()
    #         conclude_syble_info.symbol_name = production.left
    #         conclude_syble_info.txt_value = ""  # 空，这里必须为空
    #         # symbol_info_stack.pop_back();
    #         symbol_info_stack.append(conclude_syble_info)
    #     elif (
    #         "Add_expression_loop" == production.left
    #         and production.right[0] == "Add_expression_loop"
    #     ):
    #         # Add_expression_loop->Add_expression_loop Add_expression Relop
    #         # 这里需要创建临时变量
    #         # 符号属性
    #         symbol_add_expression = symbol_info_stack[-2]
    #         symbol_add_expression_loop = symbol_info_stack[-3]

    #         # 由规约后的产生式左部构造一个文法符号属性
    #         conclude_syble_info = GrammarSymbolInfo()
    #         conclude_syble_info.symbol_name = production.left

    #         if (
    #             symbol_add_expression_loop.txt_value == ""
    #         ):  # 右部的Factor_loop是从$规约而来
    #             # 这里没有必要申请临时变量，直接把值从Add_expression传递到Add_expression_loop
    #             conclude_syble_info.txt_value = symbol_info_stack[
    #                 -1
    #             ].txt_value  # <|<=|>|>=|==|!=
    #             conclude_syble_info.pos = symbol_add_expression.pos
    #         else:  # 右部的Add_expression_loop有东西。需要计算，同时将临时变量向上传递
    #             arg2_name = self.GetArgName(symbol_add_expression.pos)
    #             arg1_name = self.GetArgName(symbol_add_expression_loop.pos)
    #             op_name = "j" + symbol_add_expression_loop.txt_value  # <|<=|>|>=|==|!=;

    #             next_state_num = self.GetNextStateNum()
    #             self.PrintQuadruples(
    #                 Quadruples(
    #                     next_state_num,
    #                     op_name,
    #                     arg1_name,
    #                     arg2_name,
    #                     str(next_state_num + 3),
    #                 )
    #             )
    #             self.PrintQuadruples(
    #                 Quadruples(self.GetNextStateNum(), ":=", "0", "-", arg1_name)
    #             )
    #             self.PrintQuadruples(
    #                 Quadruples(
    #                     self.GetNextStateNum(), "j", "-", "-", str(next_state_num + 4)
    #                 )
    #             )
    #             self.PrintQuadruples(
    #                 Quadruples(self.GetNextStateNum(), ":=", "1", "-", arg1_name)
    #             )

    #             tar_arg2_name = self.target_code_generator_.SetArgBeReady(
    #                 symbol_add_expression.pos
    #             )
    #             tar_arg1_name = self.target_code_generator_.SetArgBeReady(
    #                 symbol_add_expression_loop.pos
    #             )
    #             op = symbol_add_expression_loop.txt_value
    #             if "<" == op:
    #                 self.target_code_generator_.PrintQuadruples(
    #                     Instructions("slt", tar_arg1_name, tar_arg1_name, tar_arg2_name)
    #                 )
    #             elif "<=" == op:
    #                 self.target_code_generator_.PrintQuadruples(
    #                     Instructions("sle", tar_arg1_name, tar_arg1_name, tar_arg2_name)
    #                 )
    #             elif ">" == op:
    #                 self.target_code_generator_.PrintQuadruples(
    #                     Instructions("sgt", tar_arg1_name, tar_arg1_name, tar_arg2_name)
    #                 )
    #             elif ">=" == op:
    #                 self.target_code_generator_.PrintQuadruples(
    #                     Instructions("sge", tar_arg1_name, tar_arg1_name, tar_arg2_name)
    #                 )
    #             elif "==" == op:
    #                 self.target_code_generator_.PrintQuadruples(
    #                     Instructions("seq", tar_arg1_name, tar_arg1_name, tar_arg2_name)
    #                 )
    #             elif "!=" == op:
    #                 self.target_code_generator_.PrintQuadruples(
    #                     Instructions("snq", tar_arg1_name, tar_arg1_name, tar_arg2_name)
    #                 )
    #             else:
    #                 print("语义分析错误！", "Add_expression_loop")
    #                 return False
    #             # 目标代码生成
    #             # <  | <=  |  >  | >= | ==  | !=
    #             # slt | sle | sgt | sge| seq | snq

    #             conclude_syble_info.txt_value = (
    #                 symbol_add_expression_loop.txt_value
    #             )  # <|<=|>|>=|==|!=
    #             conclude_syble_info.pos = symbol_add_expression_loop.pos
    #             # 获取产生式右部的长度
    #         length = 0
    #         if production.right[0] != "$":
    #             length = len(production.right)

    #         # 从符号栈中删除长度为 length 的符号属性
    #         for i in range(length):
    #             symbol_info_stack.pop()

    #         # 将新的符号属性推入符号栈中
    #         symbol_info_stack.append(conclude_syble_info)

    #     elif production.left == "Relop":
    #         # 由规约后的产生式左部构造一个文法符号属性
    #         conclude_syble_info = GrammarSymbolInfo()
    #         conclude_syble_info.symbol_name = production.left
    #         conclude_syble_info.txt_value = symbol_info_stack[
    #             -1
    #         ].txt_value  # <|<=|>|>= |= = |!=

    #         # 获取产生式右部的长度
    #         length = len(production.right) if production.right[0] != "$" else 0

    #         # 从符号栈中删除相应长度的符号属性，并将新的符号属性推入符号栈中
    #         for _ in range(length):
    #             symbol_info_stack.pop()

    #         symbol_info_stack.append(conclude_syble_info)

    #     elif production.left == "Expression":
    #         # 符号属性
    #         symbol_add_expression_loop = symbol_info_stack[-2]
    #         symbol_add_expression = symbol_info_stack[-1]

    #         # 由规约后的产生式左部构造一个文法符号属性
    #         conclude_syble_info = GrammarSymbolInfo()
    #         conclude_syble_info.symbol_name = production.left

    #         # Add_expression_loop 为空
    #         if symbol_add_expression_loop.txt_value == "":
    #             conclude_syble_info.txt_value = symbol_add_expression.txt_value
    #             conclude_syble_info.pos = symbol_add_expression.pos
    #         else:
    #             # Add_expression_loop 和 Add_expression 操作一下，然后返回Add_expression_loop -----------------------中间代码

    #             arg2_name = self.GetArgName(symbol_add_expression.pos)
    #             arg1_name = self.GetArgName(symbol_add_expression_loop.pos)
    #             op_name = "j" + symbol_add_expression_loop.txt_value  # <|<=|>|>=|==|!=;

    #             next_state_num = self.GetNextStateNum()
    #             self.PrintQuadruples(
    #                 Quadruples(
    #                     next_state_num,
    #                     op_name,
    #                     arg1_name,
    #                     arg2_name,
    #                     str(next_state_num + 3),
    #                 )
    #             )
    #             self.PrintQuadruples(
    #                 Quadruples(self.GetNextStateNum(), ":=", "0", "-", arg1_name)
    #             )
    #             self.PrintQuadruples(
    #                 Quadruples(
    #                     self.GetNextStateNum(), "j", "-", "-", str(next_state_num + 4)
    #                 )
    #             )
    #             self.PrintQuadruples(
    #                 Quadruples(self.GetNextStateNum(), ":=", "1", "-", arg1_name)
    #             )

    #             tar_arg2_name = self.target_code_generator_.SetArgBeReady(
    #                 symbol_add_expression.pos
    #             )
    #             tar_arg1_name = self.target_code_generator_.SetArgBeReady(
    #                 symbol_add_expression_loop.pos
    #             )
    #             op = symbol_add_expression_loop.txt_value
    #             if "<" == op:
    #                 self.target_code_generator_.PrintQuadruples(
    #                     Instructions("slt", tar_arg1_name, tar_arg1_name, tar_arg2_name)
    #                 )
    #             elif "<=" == op:
    #                 self.target_code_generator_.PrintQuadruples(
    #                     Instructions("sle", tar_arg1_name, tar_arg1_name, tar_arg2_name)
    #                 )
    #             elif ">" == op:
    #                 self.target_code_generator_.PrintQuadruples(
    #                     Instructions("sgt", tar_arg1_name, tar_arg1_name, tar_arg2_name)
    #                 )
    #             elif ">=" == op:
    #                 self.target_code_generator_.PrintQuadruples(
    #                     Instructions("sge", tar_arg1_name, tar_arg1_name, tar_arg2_name)
    #                 )
    #             elif "==" == op:
    #                 self.target_code_generator_.PrintQuadruples(
    #                     Instructions("seq", tar_arg1_name, tar_arg1_name, tar_arg2_name)
    #                 )
    #             elif "!=" == op:
    #                 self.target_code_generator_.PrintQuadruples(
    #                     Instructions("snq", tar_arg1_name, tar_arg1_name, tar_arg2_name)
    #                 )
    #             else:
    #                 print("语义分析错误！", "Add_expression_loop")
    #                 return False

    #             # conclude_syble_info.txt_value  ==  <|<=|>|>=|==|!=
    #             conclude_syble_info.txt_value = symbol_add_expression_loop.txt_value
    #             conclude_syble_info.pos = symbol_add_expression_loop.pos

    #         # 获取产生式右部的长度
    #         length = len(production.right) if production.right[0] != "$" else 0

    #         # 从符号栈中删除相应长度的符号属性，并将新的符号属性推入符号栈中
    #         for _ in range(length):
    #             symbol_info_stack.pop()

    #         symbol_info_stack.append(conclude_syble_info)
    #     if production.left == "Internal_variable_stmt":
    #         symbol_identifier = symbol_info_stack[-1]
    #         # 这里注意是引用
    #         current_table = self.symbol_tables_[self.current_symbol_table_stack_[-1]]

    #         # 先在当前符号表中寻找 identifier 是否被定义过
    #         if current_table.FindSymbol(symbol_identifier.txt_value) != -1:
    #             # 找到，表示已存在，说明重复定义，语义错误
    #             print("语义错误！！！", symbol_identifier.txt_value, "重复定义！")
    #             return False

    #         # 先在全局符号表中查看这个是与函数定义冲突
    #         search_symbol_pos = self.symbol_tables_[0].FindSymbol(
    #             symbol_identifier.txt_value
    #         )
    #         if (
    #             search_symbol_pos != -1
    #             and self.symbol_tables_[0].GetSymbolMode(search_symbol_pos)
    #             == CATEGORY.FUNCTION
    #         ):
    #             print(
    #                 "语义错误！！！", symbol_identifier.txt_value, "已经被定义为函数！"
    #             )
    #             return False

    #         # 没有被定义过，加入符号表中
    #         variable_symbol = Symbol()
    #         variable_symbol.mode = CATEGORY.VARIABLE  # 类型
    #         variable_symbol.name = symbol_identifier.txt_value  # 名称
    #         variable_symbol.type = VARIABLE_TYPE.INT
    #         variable_symbol.value = ""  # 字面值还没有被赋值，此处为空

    #         symbol_pos = current_table.AddSymbol(variable_symbol)  # 加入符号表中

    #         # 获取产生式右部的长度
    #         length = len(production.right) if production.right[0] != "$" else 0

    #         # 从符号栈中删除相应长度的符号属性
    #         for _ in range(length):
    #             symbol_info_stack.pop()

    #         conclude_syble_info = GrammarSymbolInfo()
    #         conclude_syble_info.symbol_name = production.left

    #         # 下面这两句好像没有什么用处
    #         conclude_syble_info.txt_value = symbol_identifier.txt_value  # 变量的名称
    #         conclude_syble_info.pos = (
    #             self.current_symbol_table_stack_[-1],
    #             symbol_pos,
    #         )  # 把在符号表的顺序，在符号表中的位置存下来

    #         symbol_info_stack.append(conclude_syble_info)

    #         # 目标代码生成：定义一个局部变量就 push 进栈，$sp=$sp+1*4
    #         self.target_code_generator_.PushStack_sp(1)
    #     if production.left == "Assign_sentence":
    #         # 获取identifier与Expression的文法符号属性
    #         symbol_expression = symbol_info_stack[-2]
    #         symbol_identifier = symbol_info_stack[-4]
    #         # SymbolTable current_table = self.symbol_tables_[self.current_symbol_table_stack_.back()]

    #         # 在符号表栈中一级级逆序寻找 identifier 是否被定义过

    #         identifier_pos = -1
    #         identifier_layer = len(self.current_symbol_table_stack_) - 1
    #         while identifier_layer >= 0:
    #             search_table = self.symbol_tables_[
    #                 self.current_symbol_table_stack_[identifier_layer]
    #             ]
    #             identifier_pos = search_table.FindSymbol(symbol_identifier.txt_value)
    #             if identifier_pos != -1:  # 表示在某一级中找到了
    #                 break
    #             identifier_layer -= 1

    #         if identifier_pos == -1:  # 没找到，表示不存在，说明没定义就使用，语义错误
    #             print("语义错误！！！", symbol_identifier.txt_value, "没有定义！")
    #             return False

    #         # 输出赋值的中间代码
    #         sp = SymbolPos()
    #         sp.table_pos = self.current_symbol_table_stack_[identifier_layer]
    #         sp.symbol_pos = identifier_pos
    #         result_name = self.GetArgName(sp)
    #         arg1_name = self.GetArgName(symbol_expression.pos)
    #         self.PrintQuadruples(
    #             Quadruples(self.GetNextStateNum(), ":=", arg1_name, "-", result_name)
    #         )

    #         # 目标代码生成
    #         tar_arg2_name = self.target_code_generator_.SetArgBeReady(
    #             symbol_expression.pos
    #         )
    #         tar_arg1_name = self.target_code_generator_.SetArgBeReady(sp)
    #         self.target_code_generator_.PrintQuadruples(
    #             Instructions("move", tar_arg1_name, tar_arg2_name, "")
    #         )

    #         # 获取产生式右部的长度
    #         length = len(production.right) if production.right[0] != "$" else 0

    #         # 从符号栈中删除相应长度的符号属性
    #         for _ in range(length):
    #             symbol_info_stack.pop_back()

    #         conclude_syble_info = GrammarSymbolInfo()
    #         conclude_syble_info.symbol_name = production.left
    #         conclude_syble_info.txt_value = (
    #             ""  # 这个信息没什么用，就是随便加进去，可能以后会用到
    #         )
    #         symbol_info_stack.append(conclude_syble_info)

    #     elif production.left == "Create_Function_table":
    #         # 由规约后的产生式左部构造一个文法符号属性
    #         conclude_syble_info = GrammarSymbolInfo()
    #         conclude_syble_info.symbol_name = production.left
    #         conclude_syble_info.txt_value = ""

    #         # Stmt->int identifier Stmt_type | void identifier Create_Function_table Function_stmt
    #         # 此时 symbol_info_stack 的最后一个为 identifier，即函数的名称。
    #         symbol_identifier = symbol_info_stack[-1]

    #         # 先在全局符号表中查看这个函数是否被定义过了
    #         if self.symbol_tables_[0].FindSymbol(symbol_identifier.txt_value) != -1:
    #             print(
    #                 "语义错误！！！",
    #                 symbol_identifier.txt_value,
    #                 "重复定义！",
    #                 production.left,
    #             )
    #             return False

    #         # CreateSymbolTable(FUNCTION_TABLE, symbol_identifier.txt_value);//创建新的函数符号表，并进入
    #         new_table = SymbolTable(
    #             TABLE_TYPE.FUNCTION_TABLE, symbol_identifier.txt_value
    #         )
    #         self.symbol_tables_.append(new_table)
    #         # 把函数表看成global_table中的一个符号，并加入
    #         new_function_symbol = Symbol()
    #         new_function_symbol.mode = CATEGORY.FUNCTION
    #         new_function_symbol.name = symbol_identifier.txt_value
    #         new_function_symbol.type = VARIABLE_TYPE.VOID
    #         new_function_symbol.func_symbol_pos = len(self.symbol_tables_) - 1
    #         self.symbol_tables_[0].AddSymbol(new_function_symbol)

    #         # 进入新的符号表中
    #         self.current_symbol_table_stack_.append(len(self.symbol_tables_) - 1)

    #         # 把函数返回值作为第0项添加到函数的符号表中
    #         symbol_return_type = symbol_info_stack[-2]  # int 或者 void

    #         # 定义返回值为变量，加入函数符号表的第0项---
    #         variable_symbol = Symbol()
    #         variable_symbol.mode = CATEGORY.RETURN_VAR  # 类型
    #         variable_symbol.name = (
    #             self.symbol_tables_[self.current_symbol_table_stack_[-1]].GetTableName()
    #             + "-return_value"
    #         )  # 名称
    #         variable_symbol.type = (
    #             VARIABLE_TYPE.INT
    #             if symbol_return_type.txt_value == "int"
    #             else VARIABLE_TYPE.VOID
    #         )
    #         variable_symbol.value = ""  # 字面值还没有被赋值，此处为空

    #         # 查看是否为 Main，是的话做好标记等待跳转
    #         if symbol_identifier.txt_value == "main":
    #             main_line_ = self.PeekNextStateNum()
    #         # 输出函数名称
    #         self.PrintQuadruples(
    #             Quadruples(
    #                 self.GetNextStateNum(), symbol_identifier.txt_value, "-", "-", "-"
    #             )
    #         )

    #         # 将返回值加入符号表 pos =(table_pos, 0)
    #         self.symbol_tables_[self.current_symbol_table_stack_[-1]].AddSymbol(
    #             variable_symbol
    #         )

    #         # 右部为$，所以不用 pop
    #         symbol_info_stack.append(conclude_syble_info)

    #         # 目标代码生成
    #         # 生成函数名的标签
    #         self.target_code_generator_.PrintQuadruples(
    #             symbol_identifier.txt_value + " :"
    #         )
    #         # 函数调用，进入新函数后先进行栈帧建设
    #         self.target_code_generator_.CreateStackFrame()

    #         # 循环标签的存储
    #         self.w_j_label_nums.append(w_j_label_num_)
    #         w_j_label_num_ = 0

    #     elif production.left == "Exit_Function_table":
    #         # 由规约后的产生式左部构造一个文法符号属性
    #         conclude_syble_info = GrammarSymbolInfo()
    #         conclude_syble_info.symbol_name = production.left
    #         conclude_syble_info.txt_value = ""
    #         # Stmt->int identifier Stmt_type | void identifier Create_Function_table Function_stmt
    #         # Function_stmt->(Formal_parameter)Sentence_block Exit_Function_table
    #         symbol_identifier = symbol_info_stack[-6]

    #         # 从当前符号表栈中弹出
    #         self.current_symbol_table_stack_.pop()

    #         # 右部为$，所以不用 pop
    #         symbol_info_stack.append(conclude_syble_info)

    #         # 循环标签的恢复
    #         w_j_label_num_ = self.w_j_label_nums[-1]
    #         self.w_j_label_nums.pop()

    #         self.target_code_generator_.ClearRegs()  # 退出前先清空寄存器

    #         if symbol_identifier.txt_value != "main":
    #             self.target_code_generator_.PrintQuadruples(
    #                 Instructions("jr", "$ra", "", "")
    #             )  # 输出跳回指令
    #         else:  # main函数，需要特殊处理
    #             self.target_code_generator_.PrintSyscall()  # main的特殊结束

    #     elif production.left == "Variavle_stmt":
    #         # 由规约后的产生式左部构造一个文法符号属性
    #         conclude_syble_info = GrammarSymbolInfo()
    #         conclude_syble_info.symbol_name = production.left
    #         conclude_syble_info.txt_value = ";"

    #         # 获取产生式右部的长度
    #         length = 0
    #         if production.right[0] != "$":
    #             length = len(production.right)

    #         for i in range(length):
    #             symbol_info_stack.pop()

    #         symbol_info_stack.append(conclude_syble_info)

    #     elif production.left == "Stmt_type" and production.right[0] == "Variavle_stmt":
    #         # 由规约后的产生式左部构造一个文法符号属性
    #         conclude_syble_info = GrammarSymbolInfo()
    #         conclude_syble_info.symbol_name = production.left
    #         conclude_syble_info.txt_value = ";"

    #         # 获取产生式右部的长度
    #         length = 0
    #         if production.right[0] != "$":
    #             length = len(production.right)

    #         for i in range(length):
    #             symbol_info_stack.pop()

    #         symbol_info_stack.append(conclude_syble_info)

    #     elif production.left == "Stmt" and production.right[0] == "int":
    #         # 符号属性
    #         symbol_identifier = symbol_info_stack[-2]
    #         symbol_Stmt_type = symbol_info_stack[-1]

    #         # 由规约后的产生式左部构造一个文法符号属性
    #         conclude_syble_info = GrammarSymbolInfo()
    #         conclude_syble_info.symbol_name = production.left
    #         if symbol_Stmt_type.txt_value == ";":  # 表示定义变量，而不是函数
    #             # 在符号表栈中一级级逆序寻找 identifier 是否被定义过
    #             identifier_pos = -1
    #             identifier_layer = len(self.current_symbol_table_stack_) - 1
    #             while identifier_layer >= 0:
    #                 search_table = self.symbol_tables_[
    #                     self.current_symbol_table_stack_[identifier_layer]
    #                 ]
    #                 identifier_pos = search_table.FindSymbol(
    #                     symbol_identifier.txt_value
    #                 )
    #                 if identifier_pos != -1:  # 表示在某一级中找到了
    #                     break
    #                 identifier_layer -= 1

    #             if identifier_pos != -1:  # 找到了，表示存在，说明重复定义，语义错误
    #                 print(
    #                     "语义错误！！！",
    #                     symbol_identifier.txt_value,
    #                     "重复定义！",
    #                     production.left,
    #                 )
    #                 return False

    #             # 没有被定义过，加入符号表中
    #             variable_symbol = Symbol()
    #             variable_symbol.mode = CATEGORY.VARIABLE  # 类型
    #             variable_symbol.name = symbol_identifier.txt_value  # 名称
    #             variable_symbol.type = VARIABLE_TYPE.INT
    #             variable_symbol.value = ""  # 字面值还没有被赋值，此处为空

    #             symbol_pos = self.symbol_tables_[
    #                 self.current_symbol_table_stack_[-1]
    #             ].AddSymbol(
    #                 variable_symbol
    #             )  # 加入符号表中
    #             self.target_code_generator_.PushStack_sp(
    #                 1
    #             )  # 定义一个局部变量就 push 进栈，$sp=$sp+1*4

    #             conclude_syble_info.txt_value = symbol_identifier.txt_value

    #         else:
    #             # 定义函数
    #             pass  # 无操作。 创建函数表已经存储返回值的操作在 Create_Function_table 的规约中完成。

    #         # 获取产生式右部的长度
    #         length = len(production.right)
    #         if production.right[0] == "$":
    #             length = 0

    #         for i in range(length):
    #             symbol_info_stack.pop()

    #         symbol_info_stack.append(conclude_syble_info)

    #     elif production.left == "Return_expression" and production.right[0] == "$":
    #         # 由规约后的产生式左部构造一个文法符号属性
    #         conclude_syble_info = GrammarSymbolInfo()
    #         conclude_syble_info.symbol_name = production.left
    #         conclude_syble_info.txt_value = ""  # 空，这里必须为空

    #         # 在这种情况下，返回值为void。 这需要判断当前符号表第0个项目的类型。
    #         # 判断返回类型是否正确
    #         if VARIABLE_TYPE.VOID != self.symbol_tables_[
    #             self.current_symbol_table_stack_[-1]
    #         ].GetSymbolType(0):
    #             # 返回类型存在问题。
    #             print(
    #                 "语义错误！！！",
    #                 self.symbol_tables_[
    #                     self.current_symbol_table_stack_[-1]
    #                 ].GetTableName(),
    #                 "函数定义的返回值为int类型。 但是return语句返回void类型！",
    #             )
    #             return False

    #         symbol_info_stack.append(conclude_syble_info)

    #     elif (
    #         production.left == "Return_expression"
    #         and production.right[0] == "Expression"
    #     ):
    #         # 在这种情况下，返回值为int。 这需要判断当前符号表第0个项目的类型。
    #         # 判断返回类型是否正确
    #         if VARIABLE_TYPE.INT != self.symbol_tables_[
    #             self.current_symbol_table_stack_[-1]
    #         ].GetSymbolType(0):
    #             # 返回类型存在问题。
    #             print(
    #                 "语义错误！！！",
    #                 self.symbol_tables_[
    #                     self.current_symbol_table_stack_[-1]
    #                 ].GetTableName(),
    #                 "函数定义的返回值为void类型。 但是return语句返回int类型！",
    #             )
    #             return False

    #         symbol_expression = symbol_info_stack[-1]
    #         # 由规约后的产生式左部构造一个文法符号属性
    #         conclude_syble_info = GrammarSymbolInfo()
    #         conclude_syble_info.symbol_name = production.left
    #         conclude_syble_info.txt_value = "int"  # 表示有值返回，区别与""
    #         conclude_syble_info.pos = symbol_expression.pos

    #         symbol_info_stack = symbol_info_stack[:-1]  # 移除栈顶元素

    #         symbol_info_stack.append(conclude_syble_info)

    #         # 目标代码生成
    #         # tar_arg2_name = self.target_code_generator_.SetArgBeReady(symbol_expression.pos)
    #         tar_arg_name = self.target_code_generator_.SetArgBeReady(
    #             symbol_expression.pos
    #         )
    #         self.target_code_generator_.PrintQuadruples(
    #             Instructions("move", "$v0", tar_arg_name, "")
    #         )  # 把返回值赋给v0
    #         self.target_code_generator_.PrintQuadruples(
    #             Instructions("lw", "$ra", "-4($fp)", "")
    #         )  # 把返回地址赋给ra

    #     elif "Return_sentence" == production.left:
    #         symbol_return_expression = symbol_info_stack[-2]

    #         # 由规约后的产生式左部构造一个文法符号属性
    #         conclude_syble_info = GrammarSymbolInfo()
    #         conclude_syble_info.symbol_name = production.left

    #         current_function_table = self.symbol_tables_[
    #             self.current_symbol_table_stack_[-1]
    #         ]  # 获取当前函数表
    #         function_pos = self.symbol_tables_[0].FindSymbol(
    #             current_function_table.GetTableName()
    #         )  # 函数在全局符号表的位置
    #         current_function_symbol = self.symbol_tables_[0].GetSymbol(
    #             function_pos
    #         )  # 函数在全局符号表中作为符号

    #         if "" != symbol_return_expression.txt_value:
    #             result_pos = SymbolPos()
    #             result_pos.table_pos = self.current_symbol_table_stack_[-1]
    #             result_pos.symbol_pos = 0  # 返回值的位置在 第0项
    #             result_name = self.GetArgName(result_pos)
    #             arg1_name = self.GetArgName(symbol_return_expression.pos)

    #             # 把返回值写到函数表的第0项
    #             self.PrintQuadruples(
    #                 Quadruples(
    #                     self.GetNextStateNum(), ":=", arg1_name, "-", result_name
    #                 )
    #             )

    #             conclude_syble_info.txt_value = "int"
    #             conclude_syble_info.pos = symbol_return_expression.pos
    #         else:
    #             conclude_syble_info.txt_value = ""

    #         # 输出返回指令
    #         self.PrintQuadruples(
    #             Quadruples(
    #                 self.GetNextStateNum(),
    #                 "return",
    #                 "-",
    #                 "-",
    #                 current_function_table.GetTableName(),
    #             )
    #         )

    #         # 获取产生式右部的长度
    #         length = len(production.right)
    #         if "$" != production.right[0]:
    #             length = len(production.right)

    #         for i in range(length):
    #             symbol_info_stack.pop()

    #         symbol_info_stack.append(conclude_syble_info)
    #     elif "Parameter" == production.left:
    #         symbol_identifier = symbol_info_stack[-1]
    #         current_table = self.symbol_tables_[self.current_symbol_table_stack_[-1]]

    #         table_pos = self.symbol_tables_[0].FindSymbol(current_table.GetTableName())

    #         # 先在当前符号表中寻找 identifier 是否被定义过
    #         if current_table.FindSymbol(symbol_identifier.txt_value) != -1:
    #             # 找到，表示已存在，说明重复定义，语义错误
    #             print(
    #                 "语义错误！！！", symbol_identifier.txt_value, "函数参数 重复定义！"
    #             )
    #             return False

    #         # 先在全局符号表中查看这个是与函数定义冲突
    #         search_symbol_pos = self.symbol_tables_[0].FindSymbol(
    #             symbol_identifier.txt_value
    #         )
    #         if (
    #             search_symbol_pos != -1
    #             and self.symbol_tables_[0].GetSymbolMode(search_symbol_pos)
    #             == CATEGORY.FUNCTION
    #         ):
    #             print(
    #                 "语义错误！！！", symbol_identifier.txt_value, "已经被定义为函数！"
    #             )
    #             return False

    #         # 没有被定义过，加入符号表中
    #         variable_symbol = Symbol()
    #         variable_symbol.mode = CATEGORY.VARIABLE
    #         variable_symbol.name = symbol_identifier.txt_value
    #         variable_symbol.type = VARIABLE_TYPE.INT
    #         variable_symbol.value = ""

    #         symbol_pos = current_table.AddSymbol(variable_symbol)

    #         # 全局符号表中函数的参数个数需要加一
    #         self.symbol_tables_[0].GetSymbol(table_pos).parameter_num += 1

    #         # 获取产生式右部的长度
    #         length = len(production.right)
    #         if "$" != production.right[0]:
    #             length = len(production.right)

    #         for i in range(length):
    #             symbol_info_stack.pop()

    #         conclude_syble_info = GrammarSymbolInfo()
    #         conclude_syble_info.symbol_name = production.left
    #         conclude_syble_info.txt_value = symbol_identifier.txt_value
    #         conclude_syble_info.pos = (self.current_symbol_table_stack_[-1], symbol_pos)

    #         symbol_info_stack.append(conclude_syble_info)
    #     elif "Sentence_block" == production.left:
    #         # 返回下一个 state 的序号。给回填使用
    #         # 由规约后的产生式左部构造一个文法符号属性
    #         conclude_syble_info = GrammarSymbolInfo()
    #         conclude_syble_info.symbol_name = production.left
    #         conclude_syble_info.txt_value = str(self.PeekNextStateNum())

    #         # 获取产生式右部的长度
    #         length = 0
    #         if "$" != production.right[0]:
    #             length = len(production.right)

    #         for i in range(length):
    #             symbol_info_stack.pop()

    #         symbol_info_stack.append(conclude_syble_info)
    #     elif "While_sentence_m2" == production.left:
    #         # While_sentence->while While_sentence_m1 ( Expression ) While_sentence_m2 Sentence_block

    #         symbol_expression = symbol_info_stack[-2]
    #         symbol_name = self.symbol_tables_[
    #             symbol_expression.pos.table_pos
    #         ].GetSymbolName(symbol_expression.pos.symbol_pos)

    #         # 两个等待回填的真假出口
    #         self.PrintQuadruples(
    #             Quadruples(self.GetNextStateNum(), "j=", symbol_name, "0", "---j=")
    #         )
    #         self.backpatching_point_pos_.append(len(self.quadruples_stack_) - 1)

    #         self.PrintQuadruples(
    #             Quadruples(self.GetNextStateNum(), "j", "-", "-", "---j")
    #         )
    #         self.backpatching_point_pos_.append(len(self.quadruples_stack_) - 1)

    #         # 返回下一个 state 的序号。给回填使用
    #         # 由规约后的产生式左部构造一个文法符号属性
    #         conclude_syble_info = GrammarSymbolInfo()
    #         conclude_syble_info.symbol_name = production.left
    #         conclude_syble_info.txt_value = str(self.PeekNextStateNum())

    #         # 获取产生式右部的长度
    #         length = 0
    #         if "$" != production.right[0]:
    #             length = len(production.right)

    #         for i in range(length):
    #             symbol_info_stack.pop()

    #         symbol_info_stack.append(conclude_syble_info)

    #         # 目标代码生成
    #         tar_arg1_name = self.target_code_generator_.SetArgBeReady(
    #             symbol_expression.pos
    #         )
    #         j_label_end = self.j_label_.pop()
    #         # 条件等于0则跳出循环
    #         self.target_code_generator_.PrintQuadruples(
    #             Instructions("beq", tar_arg1_name, "$zero", j_label_end)
    #         )
    #     elif "While_sentence_m1" == production.left:
    #         # 返回下一个 state 的序号。给回填使用
    #         # 由规约后的产生式左部构造一个文法符号属性
    #         conclude_syble_info = GrammarSymbolInfo()
    #         conclude_syble_info.symbol_name = production.left
    #         conclude_syble_info.txt_value = str(self.PeekNextStateNum())

    #         # 同时，回填层级+1
    #         backpatching_level_ += 1

    #         # 获取产生式右部的长度
    #         length = 0
    #         if "$" != production.right[0]:
    #             length = len(production.right)

    #         for i in range(length):
    #             symbol_info_stack.pop()

    #         symbol_info_stack.append(conclude_syble_info)

    #         # 将两个标签生成后压入栈中
    #         table_name = self.symbol_tables_[
    #             self.current_symbol_table_stack_.back()
    #         ].GetTableName()
    #         cnt = w_j_label_num_
    #         w_j_label_num_ += 1
    #         label_1 = "Label_" + table_name + "_while_begin_" + str(cnt)
    #         label_2 = "Label_" + table_name + "_while_end_" + str(cnt)
    #         # 先写 begin
    #         self.w_label_.append(label_2)
    #         self.w_label_.append(label_1)
    #         # 先跳 end
    #         self.j_label_.append(label_1)
    #         self.j_label_.append(label_2)
    #         # 目标代码生成
    #         w_label_begin = self.w_label_.pop()
    #         self.target_code_generator_.PrintQuadruples(
    #             "\n# while循环，先清空寄存器"
    #         )  # 空一行
    #         self.target_code_generator_.ClearRegs()  # 进入循环前先清空寄存器
    #         # 生成 while 的 begin 标签
    #         self.target_code_generator_.PrintQuadruples(w_label_begin + " :")
    #     elif "While_sentence" == production.left:
    #         # While_sentence->while While_sentence_m1 ( Expression ) While_sentence_m2 Sentence_block
    #         # 跳转到 while 的判断条件，这个四元式加入到回填栈中
    #         symbol_while_sentence_m1 = symbol_info_stack[-6]
    #         symbol_while_sentence_m2 = symbol_info_stack[-2]
    #         symbol_sentence_block = symbol_info_stack[-1]
    #         self.PrintQuadruples(
    #             Quadruples(
    #                 self.GetNextStateNum(),
    #                 "j",
    #                 "-",
    #                 "-",
    #                 symbol_while_sentence_m1.txt_value,
    #             )
    #         )

    #         # 开始回填 两个地方
    #         # 真出口
    #         batch_pos = self.backpatching_point_pos_.pop()
    #         self.quadruples_stack_[batch_pos].SetContent(
    #             self.quadruples_stack_[batch_pos].num,
    #             self.quadruples_stack_[batch_pos].op,
    #             self.quadruples_stack_[batch_pos].arg1,
    #             self.quadruples_stack_[batch_pos].arg2,
    #             symbol_while_sentence_m2.txt_value,
    #         )
    #         # 假出口
    #         batch_pos = self.backpatching_point_pos_.pop()
    #         self.quadruples_stack_[batch_pos].SetContent(
    #             self.quadruples_stack_[batch_pos].num,
    #             self.quadruples_stack_[batch_pos].op,
    #             self.quadruples_stack_[batch_pos].arg1,
    #             self.quadruples_stack_[batch_pos].arg2,
    #             str(self.PeekNextStateNum()),
    #         )

    #         backpatching_level_ -= 1  # 回填深度减1
    #         # 判断是否需要输出
    #         if backpatching_level_ == 0:
    #             for quadruple in self.quadruples_stack_:
    #                 self.PrintQuadruples(quadruple)
    #             length = len(self.quadruples_stack_)
    #             for _ in range(length):  # 回填栈全部输出，可以清空了
    #                 self.quadruples_stack_.pop()

    #         # 由规约后的产生式左部构造一个文法符号属性
    #         conclude_syble_info = GrammarSymbolInfo()
    #         conclude_syble_info.symbol_name = production.left
    #         conclude_syble_info.txt_value = ""

    #         # 获取产生式右部的长度
    #         length = len(production.right)
    #         for _ in range(length):
    #             symbol_info_stack.pop()

    #         symbol_info_stack.append(conclude_syble_info)

    #         # 目标代码生成
    #         self.target_code_generator_.ClearRegs()  # 退出循环前先清空寄存器
    #         j_label_begin = self.j_label_.pop()
    #         self.target_code_generator_.PrintQuadruples("j " + j_label_begin)
    #         w_label_end = self.w_label_.pop()

    #         self.target_code_generator_.PrintQuadruples(w_label_end + " :")
    #         # 清空寄存器 --保证出if是干净的
    #         self.target_code_generator_.ClearRegs()
    #         self.target_code_generator_.PrintQuadruples("")  # 空一行
    #     elif "If_sentence_m0" == production.left:
    #         # If_sentence_m0->$
    #         # 主要用来加深回填深度
    #         # 由规约后的产生式左部构造一个文法符号属性
    #         conclude_syble_info = GrammarSymbolInfo()
    #         conclude_syble_info.symbol_name = production.left
    #         conclude_syble_info.txt_value = str(self.PeekNextStateNum())

    #         # 同时，回填层级+1
    #         backpatching_level_ += 1

    #         # 获取产生式右部的长度
    #         length = len(production.right)
    #         for _ in range(length):
    #             symbol_info_stack.pop()

    #         symbol_info_stack.append(conclude_syble_info)

    #         self.target_code_generator_.PrintQuadruples("\n#if判断")  # 空一行
    #         # self.target_code_generator_.PrintQuadruples("\n#if判断，先清空寄存器")  # 空一行
    #         # self.target_code_generator_.ClearRegs()  # 进入循环前先清空寄存器
    #     elif "If_sentence_n" == production.left:
    #         # If_sentence_n->$
    #         # 输出跳转到if-else结束的地方,避免执行else
    #         # 由规约后的产生式左部构造一个文法符号属性
    #         conclude_syble_info = GrammarSymbolInfo()
    #         conclude_syble_info.symbol_name = production.left

    #         # 等待回填的跳出出口
    #         self.PrintQuadruples(
    #             Quadruples(self.GetNextStateNum(), "j", "-", "-", "---j-if-n")
    #         )
    #         self.backpatching_point_pos_.append(len(self.quadruples_stack_) - 1)

    #         conclude_syble_info.txt_value = str(
    #             self.PeekNextStateNum()
    #         )  # 把if-else的假出口地址进行传递

    #         # 获取产生式右部的长度
    #         length = len(production.right)
    #         for _ in range(length):
    #             symbol_info_stack.pop()

    #         symbol_info_stack.append(conclude_syble_info)

    #         # 目标代码生成
    #         # 只输出j else_end  以及 label if_end
    #         w_label_if_end = self.w_label_.pop()
    #         j_label_else_end = self.j_label_.pop()

    #         # 清空寄存器 --保证出if是干净的
    #         self.target_code_generator_.ClearRegs()
    #         # 注意这里的顺序：先跳转，后输出标签
    #         # if结束后要跳转到else_end，从而避免执行else
    #         self.target_code_generator_.PrintQuadruples(
    #             Instructions("j", j_label_else_end, "", "")
    #         )
    #         # 生成if_end标签
    #         self.target_code_generator_.PrintQuadruples(w_label_if_end + " :")
    #     elif "If_sentence_m1" == production.left:
    #         # If_sentence_m1->$
    #         # If_sentence->if If_sentence_m0 ( Expression ) If_sentence_m1 Sentence_block If_expression

    #         symbol_expression = symbol_info_stack[-2]
    #         symbol_name = self.symbol_tables_[
    #             symbol_expression.pos.table_pos
    #         ].GetSymbolName(symbol_expression.pos.symbol_pos)

    #         # 两个等待回填的真假出口
    #         self.PrintQuadruples(
    #             Quadruples(self.GetNextStateNum(), "j=", symbol_name, "0", "---j=")
    #         )
    #         self.backpatching_point_pos_.append(len(self.quadruples_stack_) - 1)

    #         self.PrintQuadruples(
    #             Quadruples(self.GetNextStateNum(), "j", "-", "-", "---j")
    #         )
    #         self.backpatching_point_pos_.append(len(self.quadruples_stack_) - 1)

    #         # 返回下一个state的序号。给回填使用
    #         # 由规约后的产生式左部构造一个文法符号属性
    #         conclude_syble_info = GrammarSymbolInfo()
    #         conclude_syble_info.symbol_name = production.left
    #         conclude_syble_info.txt_value = str(self.PeekNextStateNum())

    #         # 获取产生式右部的长度
    #         length = len(production.right)
    #         for _ in range(length):
    #             symbol_info_stack.pop()

    #         symbol_info_stack.append(conclude_syble_info)

    #         # 将两个标签生成后压入栈中
    #         table_name = self.symbol_tables_[
    #             self.current_symbol_table_stack_[-1]
    #         ].GetTableName()
    #         cnt = w_j_label_num_
    #         w_j_label_num_ += 1
    #         label_1 = "Label_" + table_name + "_if_end_" + str(cnt)
    #         label_2 = "Label_" + table_name + "_else_end_" + str(cnt)
    #         # if_end先写
    #         self.w_label_.append(label_2)
    #         self.w_label_.append(label_1)
    #         # if_end先跳
    #         self.j_label_.append(label_2)
    #         self.j_label_.append(label_1)
    #         # 目标代码生成
    #         j_label_if_end = self.j_label_.pop()

    #         # 目标代码生成
    #         tar_arg1_name = self.target_code_generator_.SetArgBeReady(
    #             symbol_expression.pos
    #         )

    #         self.target_code_generator_.ClearRegs()  # 进入循环前先清空寄存器
    #         # 条件等于0则跳过if
    #         self.target_code_generator_.PrintQuadruples(
    #             Instructions("beq", tar_arg1_name, "$zero", j_label_if_end)
    #         )
    #     elif "If_expression" == production.left and production.right[0] == "$":
    #         # If_expression->$

    #         # 由规约后的产生式左部构造一个文法符号属性
    #         conclude_syble_info = GrammarSymbolInfo()
    #         conclude_syble_info.symbol_name = production.left
    #         conclude_syble_info.txt_value = ""  # 这里为空

    #         # 获取产生式右部的长度
    #         length = len(production.right)
    #         for _ in range(length):
    #             symbol_info_stack.pop()

    #         symbol_info_stack.append(conclude_syble_info)

    #         # 目标代码生成
    #         # 只输出一个if_end的label，把多余的w_label与w_label从栈中弹出。
    #         w_label_if_end = self.w_label_.pop()
    #         self.w_label_.pop()  # 弹出else_end，因为这是if不含else的语句
    #         self.j_label_.pop()  # 弹出else_end，同上

    #         # 清空寄存器 --出if是干净的
    #         self.target_code_generator_.ClearRegs()
    #         # 生成if_end标签
    #         self.target_code_generator_.PrintQuadruples(w_label_if_end + " :")
    #     elif (
    #         "If_expression" == production.left
    #         and production.right[0] == "If_sentence_n"
    #     ):
    #         # If_expression->If_sentence_n else Sentence_block

    #         symbol_if_sentence_n = symbol_info_stack[-3]
    #         # 由规约后的产生式左部构造一个文法符号属性
    #         conclude_syble_info = GrammarSymbolInfo()
    #         conclude_syble_info.symbol_name = production.left
    #         conclude_syble_info.txt_value = (
    #             symbol_if_sentence_n.txt_value
    #         )  # 区别一下 空

    #         # 获取产生式右部的长度
    #         length = len(production.right)
    #         for _ in range(length):
    #             symbol_info_stack.pop()

    #         symbol_info_stack.append(conclude_syble_info)

    #         # 目标代码生成
    #         # 只输出一个else_end的label
    #         w_label_else_end = self.w_label_.pop()

    #         # 清空寄存器 --保证出else是干净的
    #         self.target_code_generator_.ClearRegs()
    #         # 生成if_end标签
    #         self.target_code_generator_.PrintQuadruples(w_label_else_end + " :")
    #     elif "If_sentence" == production.left:
    #         # If_sentence->if If_sentence_m0(Expression) If_sentence_m1 Sentence_block If_expression

    #         symbol_if_sentence_m1 = symbol_info_stack[-3]
    #         symbol_if_expression = symbol_info_stack[-1]

    #         if "" == symbol_if_expression.txt_value:  # 只有if，没有else
    #             # 开始回填两个地方
    #             # 真出口
    #             batch_pos = self.backpatching_point_pos_.pop()
    #             self.quadruples_stack_[batch_pos].SetContent(
    #                 self.quadruples_stack_[batch_pos].num,
    #                 self.quadruples_stack_[batch_pos].op,
    #                 self.quadruples_stack_[batch_pos].arg1,
    #                 self.quadruples_stack_[batch_pos].arg2,
    #                 symbol_if_sentence_m1.txt_value,
    #             )
    #             # 假出口
    #             batch_pos = self.backpatching_point_pos_.pop()
    #             self.quadruples_stack_[batch_pos].SetContent(
    #                 self.quadruples_stack_[batch_pos].num,
    #                 self.quadruples_stack_[batch_pos].op,
    #                 self.quadruples_stack_[batch_pos].arg1,
    #                 self.quadruples_stack_[batch_pos].arg2,
    #                 str(self.PeekNextStateNum()),
    #             )
    #         else:  # if-else语句
    #             # 开始回填三个地方
    #             # 完成if，跳出if-else
    #             batch_pos = self.backpatching_point_pos_.pop()
    #             self.quadruples_stack_[batch_pos].SetContent(
    #                 self.quadruples_stack_[batch_pos].num,
    #                 self.quadruples_stack_[batch_pos].op,
    #                 self.quadruples_stack_[batch_pos].arg1,
    #                 self.quadruples_stack_[batch_pos].arg2,
    #                 str(self.PeekNextStateNum()),
    #             )

    #             # if真出口
    #             batch_pos = self.backpatching_point_pos_.pop()
    #             self.quadruples_stack_[batch_pos].SetContent(
    #                 self.quadruples_stack_[batch_pos].num,
    #                 self.quadruples_stack_[batch_pos].op,
    #                 self.quadruples_stack_[batch_pos].arg1,
    #                 self.quadruples_stack_[batch_pos].arg2,
    #                 symbol_if_sentence_m1.txt_value,
    #             )

    #             # if假出口
    #             batch_pos = self.backpatching_point_pos_.pop()
    #             self.quadruples_stack_[batch_pos].SetContent(
    #                 self.quadruples_stack_[batch_pos].num,
    #                 self.quadruples_stack_[batch_pos].op,
    #                 self.quadruples_stack_[batch_pos].arg1,
    #                 self.quadruples_stack_[batch_pos].arg2,
    #                 symbol_if_expression.txt_value,
    #             )

    #         backpatching_level_ -= 1  # 回填深度减1
    #         # 判断是否需要输出
    #         if backpatching_level_ == 0:
    #             for quad in self.quadruples_stack_:
    #                 self.PrintQuadruples(quad)
    #             self.quadruples_stack_.clear()

    #         # 由规约后的产生式左部构造一个文法符号属性
    #         conclude_syble_info = GrammarSymbolInfo()
    #         conclude_syble_info.symbol_name = production.left
    #         conclude_syble_info.txt_value = ""

    #         # 获取产生式右部的长度
    #         length = len(production.right)
    #         for _ in range(length):
    #             symbol_info_stack.pop()

    #         symbol_info_stack.append(conclude_syble_info)

    #         # 目标代码生成
    #         # self.target_code_generator_.ClearRegs()  # 退出if前先清空寄存器
    #     elif "Call_func_check" == production.left:
    #         # Call_func_check->$

    #         # 做语义检查，是否为合法的函数。
    #         # Factor->identifier ( Call_func_check Actual_parameter_list)
    #         # 符号属性
    #         symbol_identifier = symbol_info_stack[-2]

    #         # 在符号表栈中一级级逆序寻找 identifier 是否被定义过
    #         identifier_pos = -1
    #         identifier_layer = len(self.current_symbol_table_stack_) - 1
    #         while identifier_layer >= 0:
    #             search_table = self.symbol_tables_[
    #                 self.current_symbol_table_stack_[identifier_layer]
    #             ]
    #             identifier_pos = search_table.FindSymbol(symbol_identifier.txt_value)
    #             if identifier_pos != -1:  # 表示在某一级中找到了
    #                 break
    #             identifier_layer -= 1

    #         if identifier_pos == -1:  # 没找到，表示不存在，说明没定义就使用，语义错误
    #             print("语义错误！！！", symbol_identifier.txt_value, "没有定义！")
    #             return False

    #         if CATEGORY.FUNCTION != self.symbol_tables_[
    #             self.current_symbol_table_stack_[identifier_layer]
    #         ].GetSymbolMode(identifier_pos):
    #             # 找到了，但是这个标识符不是函数，语义错误
    #             print(
    #                 "语义错误！！！",
    #                 symbol_identifier.txt_value,
    #                 "不是函数，无法被调用！",
    #             )
    #             return False

    #         # 由规约后的产生式左部构造一个文法符号属性
    #         conclude_syble_info = GrammarSymbolInfo()
    #         conclude_syble_info.symbol_name = production.left
    #         conclude_syble_info.txt_value = ""
    #         conclude_syble_info.pos = (
    #             self.current_symbol_table_stack_[identifier_layer],
    #             identifier_pos,
    #         )  # 存储被调用函数的位置

    #         # 获取产生式右部的长度
    #         length = len(production.right)
    #         for _ in range(length):
    #             symbol_info_stack.pop()

    #         symbol_info_stack.append(conclude_syble_info)
    #     elif "Expression_loop" == production.left and production.right[0] == "$":
    #         # Expression_loop->$

    #         # 由规约后的产生式左部构造一个文法符号属性
    #         conclude_syble_info = GrammarSymbolInfo()
    #         conclude_syble_info.symbol_name = production.left
    #         conclude_syble_info.txt_value = "0"  # 这里为0，表示已经传递了0个参数

    #         # 获取产生式右部的长度
    #         length = len(production.right)
    #         for _ in range(length):
    #             symbol_info_stack.pop()

    #         symbol_info_stack.append(conclude_syble_info)
    #     elif (
    #         "Expression_loop" == production.left
    #         and production.right[0] == "Expression_loop"
    #     ):
    #         # Expression_loop->Expression_loop Expression ,

    #         # Factor->identifier ( Call_func_check Expression_loop Expression ,
    #         # 符号属性
    #         symbol_call_func_check = symbol_info_stack[-4]
    #         symbol_expression_loop = symbol_info_stack[-3]
    #         symbol_expression = symbol_info_stack[-2]
    #         called_function = self.symbol_tables_[
    #             symbol_call_func_check.pos.table_pos
    #         ].GetSymbol(symbol_call_func_check.pos.symbol_pos)
    #         parameters_num = called_function.parameter_num
    #         passed_parameters_num = int(symbol_expression_loop.txt_value)
    #         if passed_parameters_num >= parameters_num:
    #             # 参数传递过多！
    #             print("语义错误！！！", called_function.name, "传递的参数过多！")
    #             return False

    #         table_pos = called_function.func_symbol_pos

    #         result_pos = SymbolPos()
    #         result_pos.table_pos = table_pos
    #         result_pos.symbol_pos = passed_parameters_num + 1  # 第0个是返回值

    #         result_name = self.GetArgName(result_pos, True)

    #         arg1_name = self.GetArgName(symbol_expression.pos)

    #         self.PrintQuadruples(
    #             Quadruples(self.GetNextStateNum(), ":=", arg1_name, "-", result_name)
    #         )

    #         passed_parameters_num += 1
    #         # 由规约后的产生式左部构造一个文法符号属性
    #         conclude_syble_info = GrammarSymbolInfo()
    #         conclude_syble_info.symbol_name = production.left
    #         conclude_syble_info.txt_value = str(passed_parameters_num)

    #         # 获取产生式右部的长度
    #         length = len(production.right)
    #         for _ in range(length):
    #             symbol_info_stack.pop()

    #         symbol_info_stack.append(conclude_syble_info)

    #         # 目标代码生成
    #         # string tar_arg2_name = self.target_code_generator_.SetArgBeReady(symbol_expression.pos);
    #         tar_arg1_name = self.target_code_generator_.SetArgBeReady(
    #             symbol_expression.pos
    #         )  # 获取实参的内存地址名称
    #         self.target_code_generator_.PrintQuadruples(
    #             Instructions("sw", tar_arg1_name, "($sp)", "")
    #         )
    #         self.target_code_generator_.PushStack_sp(
    #             1
    #         )  # 由于在sp上添加了实参,因此sp需要移动1*4
    #     elif (
    #         "Actual_parameter_list" == production.left
    #         and production.right[0] == "Expression_loop"
    #     ):
    #         # Actual_parameter_list->Expression_loop Expression
    #         # Factor->identifier ( Call_func_check Expression_loop Expression
    #         # 符号属性
    #         symbol_call_func_check = symbol_info_stack[-3]
    #         symbol_expression_loop = symbol_info_stack[-2]
    #         symbol_expression = symbol_info_stack[-1]
    #         called_function = self.symbol_tables_[
    #             symbol_call_func_check.pos.table_pos
    #         ].GetSymbol(symbol_call_func_check.pos.symbol_pos)
    #         parameters_num = called_function.parameter_num
    #         passed_parameters_num = int(symbol_expression_loop.txt_value)
    #         if passed_parameters_num >= parameters_num:
    #             # 参数传递过多！
    #             print("语义错误！！！", called_function.name, "传递的参数过多！")
    #             return False

    #         table_pos = called_function.func_symbol_pos

    #         result_pos = SymbolPos()
    #         result_pos.table_pos = table_pos
    #         result_pos.symbol_pos = passed_parameters_num + 1  # 第0个是返回值

    #         result_name = self.GetArgName(result_pos, True)

    #         arg1_name = self.GetArgName(symbol_expression.pos)

    #         self.PrintQuadruples(
    #             Quadruples(self.GetNextStateNum(), ":=", arg1_name, "-", result_name)
    #         )

    #         passed_parameters_num += 1

    #         # 判断是否参数过少！
    #         if passed_parameters_num < parameters_num:
    #             # 参数传递过多！
    #             print("语义错误！！！", called_function.name, "传递的参数过少！")
    #             return False

    #         # 由规约后的产生式左部构造一个文法符号属性
    #         conclude_syble_info = GrammarSymbolInfo()
    #         conclude_syble_info.symbol_name = production.left
    #         conclude_syble_info.txt_value = str(passed_parameters_num)

    #         # 获取产生式右部的长度
    #         length = len(production.right)
    #         for _ in range(length):
    #             symbol_info_stack.pop()

    #         symbol_info_stack.append(conclude_syble_info)

    #         # 目标代码生成
    #         tar_arg1_name = self.target_code_generator_.SetArgBeReady(
    #             symbol_expression.pos
    #         )  # 获取实参的内存地址名称
    #         self.target_code_generator_.PrintQuadruples(
    #             Instructions("sw", tar_arg1_name, "($sp)", "")
    #         )
    #         self.target_code_generator_.PushStack_sp(
    #             1
    #         )  # 由于在sp上添加了实参,因此sp需要移动1*4
    #     elif "Actual_parameter_list" == production.left and production.right[0] == "$":
    #         # Actual_parameter_list->$
    #         # Call_func->( Call_func_check
    #         # 符号属性
    #         symbol_call_func_check = symbol_info_stack[-1]
    #         called_function = self.symbol_tables_[
    #             symbol_call_func_check.pos.table_pos
    #         ].GetSymbol(symbol_call_func_check.pos.symbol_pos)
    #         parameters_num = called_function.parameter_num
    #         if parameters_num != 0:
    #             # 参数传递过多！
    #             print(
    #                 "语义错误！！！",
    #                 called_function.name,
    #                 "函数的调用需要参数，但是没有传入参数！",
    #             )
    #             return False
    #         # 由规约后的产生式左部构造一个文法符号属性
    #         conclude_syble_info = GrammarSymbolInfo()
    #         conclude_syble_info.symbol_name = production.left
    #         conclude_syble_info.txt_value = "0"  # 这里为0，表示已经传递了0个参数

    #         # 获取产生式右部的长度
    #         length = len(production.right)
    #         for _ in range(length):
    #             symbol_info_stack.pop()

    #         symbol_info_stack.append(conclude_syble_info)
    #     elif "Call_func" == production.left:
    #         # Call_func->(Call_func_check Actual_parameter_list)
    #         # 输出call语句
    #         # Factor->identifier ( Call_func_check Actual_parameter_list)
    #         # 符号属性
    #         symbol_identifier = symbol_info_stack[-5]
    #         symbol_call_func_check = symbol_info_stack[-3]
    #         self.PrintQuadruples(
    #             Quadruples(
    #                 self.GetNextStateNum(),
    #                 "call",
    #                 "-",
    #                 "-",
    #                 symbol_identifier.txt_value,
    #             )
    #         )
    #         # 由规约后的产生式左部构造一个文法符号属性
    #         conclude_syble_info = GrammarSymbolInfo()
    #         conclude_syble_info.symbol_name = production.left
    #         conclude_syble_info.txt_value = ""
    #         conclude_syble_info.pos = symbol_call_func_check.pos

    #         # 获取产生式右部的长度
    #         length = len(production.right)
    #         for _ in range(length):
    #             symbol_info_stack.pop()

    #         symbol_info_stack.append(conclude_syble_info)
    #     elif "FTYPE" == production.left and production.right[0] == "Call_func":
    #         symbol_call_func = symbol_info_stack[-1]
    #         # 将调用函数返回pos一级级向上传递
    #         # 由规约后的产生式左部构造一个文法符号属性
    #         conclude_symble_info = GrammarSymbolInfo()
    #         conclude_symble_info.symbol_name = production.left
    #         conclude_symble_info.txt_value = "call_func"  # 这里只要不是""就可以
    #         conclude_symble_info.pos = symbol_call_func.pos
    #         # 获取产生式右部的长度
    #         length = len(production.right)
    #         for _ in range(length):
    #             symbol_info_stack.pop()

    #         symbol_info_stack.append(conclude_syble_info)
    #     elif "Program" == production.left:
    #         # 到这里基本语义分析正确。
    #         # 判断是否存在 Main 函数。
    #         if main_line_ == -1:
    #             print("语义错误！！！main函数没有定义！")
    #             return False
    #         self.PrintQuadruples()
    #         print("中间代码生成完毕！")
    #         # 由规约后的产生式左部构造一个文法符号属性
    #         conclude_symble_info = GrammarSymbolInfo()
    #         conclude_symble_info.symbol_name = production.left
    #         conclude_symble_info.txt_value = ""
    #         # 获取产生式右部的长度
    #         length = len(production.right)
    #         for _ in range(length):
    #             symbol_info_stack.pop()

    #         symbol_info_stack.append(conclude_syble_info)
    #     else:
    #         # Stmt_string->Stmt_loop Stmt
    #         # Stmt_loop->Stmt_loop Stmt | $
    #         # Internal_stmt->$|Internal_variable_stmt ; Internal_stmt
    #         # Sentence_string->Sentence_loop Sentence
    #         # Sentence_loop->Sentence_loop Sentence | $
    #         # Sentence->If_sentence | While_sentence | Return_sentence | Assign_sentence
    #         # Stmt->void identifier Create_Function_table Function_stmt
    #         # Formal_parameter->Formal_parameter_list | void | $
    #         # Formal_parameter_list->Parameter_loop Parameter
    #         # Parameter_loop->Parameter_loop Parameter, | $
    #         # Function_stmt->( Formal_parameter ) Sentence_block Exit_Function_table

    #         # 由规约后的产生式左部构造一个文法符号属性
    #         conclude_syble_info = GrammarSymbolInfo()
    #         conclude_syble_info.symbol_name = production.left
    #         conclude_syble_info.txt_value = ""
    #         # 获取产生式右部的长度
    #         length = len(production.right)
    #         for _ in range(length):
    #             symbol_info_stack.pop()

    #         symbol_info_stack.append(conclude_syble_info)
    #     return True

    def ExecuteSemanticCheck(self, symbol_info_stack, production):
        if "PROG" == production.left:
            # PROG -> { DECLS STMTS }
            # self.PrintQuadruples()
            print("中间代码生成完毕！")
            conclude_symbol_info = GrammarSymbolInfo()
            conclude_symbol_info.symbol_name = production.left
            conclude_symbol_info.txt_value = ""
            length = len(production.right)
            for _ in range(length):
                symbol_info_stack.pop()
            symbol_info_stack.append(conclude_symbol_info)
            pass
        elif "DECLS" == production.left and production.right[0] == "DECLS":
            # DECLS -> DECLS DECL
            # 由规约后的产生式左部构造一个文法符号属性
            conclude_syble_info = GrammarSymbolInfo()
            conclude_syble_info.symbol_name = production.left
            conclude_syble_info.txt_value = ""
            # 获取产生式右部的长度
            length = len(production.right)
            for _ in range(length):
                symbol_info_stack.pop()

            symbol_info_stack.append(conclude_syble_info)
            pass
        elif "DECLS" == production.left and production.right[0] == "$":
            # DECLS -> $
            conclude_symbol_info = GrammarSymbolInfo(
                symbol_name=production.left, txt_value=""
            )
            symbol_info_stack.append(conclude_symbol_info)
            pass
        elif "DECL" == production.left and production.right[0] == "int":
            # DECL -> int NAMES;
            symbol_identifier = symbol_info_stack[-2]
            conclude_syble_info = GrammarSymbolInfo()
            conclude_syble_info.symbol_name = production.left
            # 在符号表栈中一级级逆序寻找 identifier 是否被定义过
            ###
            # identifier_pos = -1
            # identifier_layer = len(self.current_symbol_table_stack_) - 1
            # while identifier_layer >= 0:
            #     search_table = self.symbol_tables_[
            #         self.current_symbol_table_stack_[identifier_layer]
            #     ]
            #     identifier_pos = search_table.FindSymbol(symbol_identifier.txt_value)
            #     if identifier_pos != -1:  # 表示在某一级中找到了
            #         break
            #     identifier_layer -= 1
            # if identifier_pos != -1:  # 找到了，表示存在，说明重复定义，语义错误
            #     print(
            #         "语义错误！！！",
            #         symbol_identifier.txt_value,
            #         "重复定义！",
            #         production.left,
            #     )
            #     return False
            ###
            # 没有被定义过，加入符号表中
            for identifier_txt_value in symbol_identifier.txt_value:
                variable_symbol = Symbol()
                variable_symbol.mode = CATEGORY.VARIABLE  # 类型
                variable_symbol.name = identifier_txt_value  # 名称
                variable_symbol.type = VARIABLE_TYPE.INT
                variable_symbol.value = ""  # 字面值还没有被赋值，此处为空

                symbol_pos = self.symbol_tables_[0].AddSymbol(
                    variable_symbol
                )  # 加入符号表中
                self.target_code_generator_.PushStack_sp(
                    1
                )  # 定义一个局部变量就 push 进栈，$sp=$sp+1*4

            conclude_syble_info.txt_value = symbol_identifier.txt_value
            length = len(production.right)
            for _ in range(length):
                symbol_info_stack.pop()
            symbol_info_stack.append(conclude_syble_info)
            pass
        elif "DECL" == production.left and production.right[0] == "bool":
            # DECL -> bool NAMES;
            symbol_identifier = symbol_info_stack[-2]
            conclude_syble_info = GrammarSymbolInfo()
            conclude_syble_info.symbol_name = production.left
            # 在符号表栈中一级级逆序寻找 identifier 是否被定义过
            ###
            # identifier_pos = -1
            # identifier_layer = len(self.current_symbol_table_stack_) - 1
            # while identifier_layer >= 0:
            #     search_table = self.symbol_tables_[
            #         self.current_symbol_table_stack_[identifier_layer]
            #     ]
            #     identifier_pos = search_table.FindSymbol(symbol_identifier.txt_value)
            #     if identifier_pos != -1:  # 表示在某一级中找到了
            #         break
            #     identifier_layer -= 1
            # if identifier_pos != -1:  # 找到了，表示存在，说明重复定义，语义错误
            #     print(
            #         "语义错误！！！",
            #         symbol_identifier.txt_value,
            #         "重复定义！",
            #         production.left,
            #     )
            #     return False
            ###
            # 没有被定义过，加入符号表中
            for identifier_txt_value in symbol_identifier.txt_value:
                variable_symbol = Symbol()
                variable_symbol.mode = CATEGORY.VARIABLE  # 类型
                variable_symbol.name = identifier_txt_value  # 名称
                variable_symbol.type = VARIABLE_TYPE.BOOL
                variable_symbol.value = ""  # 字面值还没有被赋值，此处为空

                symbol_pos = self.symbol_tables_[0].AddSymbol(
                    variable_symbol
                )  # 加入符号表中
                self.target_code_generator_.PushStack_sp(
                    1
                )  # 定义一个局部变量就 push 进栈，$sp=$sp+1*4

            conclude_syble_info.txt_value = symbol_identifier.txt_value
            length = len(production.right)
            for _ in range(length):
                symbol_info_stack.pop()
            symbol_info_stack.append(conclude_syble_info)
            pass
        elif "NAMES" == production.left and production.right[0] == "NAMES":
            # NAMES -> NAMES , NAME
            # 由规约后的产生式左部构造一个文法符号属性
            conclude_syble_info = GrammarSymbolInfo()
            conclude_syble_info.symbol_name = production.left
            conclude_syble_info.txt_value = symbol_info_stack[-3].txt_value.copy()
            conclude_syble_info.txt_value.append(symbol_info_stack[-1].txt_value)

            # 获取产生式右部的长度
            length = len(production.right)
            for _ in range(length):
                symbol_info_stack.pop()

            symbol_info_stack.append(conclude_syble_info)
            pass
        elif "NAMES" == production.left and production.right[0] == "NAME":
            # NAMES -> NAME
            # 由规约后的产生式左部构造一个文法符号属性
            conclude_syble_info = GrammarSymbolInfo()
            conclude_syble_info.symbol_name = production.left
            conclude_syble_info.txt_value = [symbol_info_stack[-1].txt_value]
            # 获取产生式右部的长度
            length = len(production.right)
            for _ in range(length):
                symbol_info_stack.pop()

            symbol_info_stack.append(conclude_syble_info)
            pass
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
            conclude_syble_info = GrammarSymbolInfo()
            conclude_syble_info.symbol_name = production.left
            conclude_syble_info.txt_value = symbol_identifier.txt_value
            # 获取产生式右部的长度
            length = len(production.right)
            for _ in range(length):
                symbol_info_stack.pop()

            symbol_info_stack.append(conclude_syble_info)
            pass
        elif "STMTS" == production.left and production.right[0] == "STMTS":
            # STMTS -> STMTS STMT
            # 由规约后的产生式左部构造一个文法符号属性
            conclude_syble_info = GrammarSymbolInfo()
            conclude_syble_info.symbol_name = production.left
            conclude_syble_info.txt_value = ""
            # 获取产生式右部的长度
            length = len(production.right)
            for _ in range(length):
                symbol_info_stack.pop()

            symbol_info_stack.append(conclude_syble_info)
            pass
        elif "STMTS" == production.left and production.right[0] == "STMTS":
            # STMTS -> STMT
            # 由规约后的产生式左部构造一个文法符号属性
            conclude_syble_info = GrammarSymbolInfo()
            conclude_syble_info.symbol_name = production.left
            conclude_syble_info.txt_value = ""
            # 获取产生式右部的长度
            length = len(production.right)
            for _ in range(length):
                symbol_info_stack.pop()

            symbol_info_stack.append(conclude_syble_info)
            pass
        elif (
            "STMT" == production.left
            and production.right[0] == "id"
            and production.right[1] == "="
        ):
            # STMT -> id = EXPR;
            # 获取identifier与Expression的文法符号属性
            symbol_expression = symbol_info_stack[-2]
            symbol_identifier = symbol_info_stack[-4]
            # SymbolTable current_table = self.symbol_tables_[self.current_symbol_table_stack_.back()]

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

            # 获取产生式右部的长度
            length = len(production.right) if production.right[0] != "$" else 0

            # 从符号栈中删除相应长度的符号属性
            for _ in range(length):
                symbol_info_stack.pop()

            conclude_syble_info = GrammarSymbolInfo()
            conclude_syble_info.symbol_name = production.left
            conclude_syble_info.txt_value = (
                ""  # 这个信息没什么用，就是随便加进去，可能以后会用到
            )
            symbol_info_stack.append(conclude_syble_info)
            pass
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

            # # 目标代码生成
            # tar_arg2_name = self.target_code_generator_.SetArgBeReady(
            #     symbol_expression.pos
            # )
            # tar_arg1_name = self.target_code_generator_.SetArgBeReady(sp)
            # self.target_code_generator_.PrintQuadruples(
            #     Instructions("move", tar_arg1_name, tar_arg2_name, "")
            # )

            # 获取产生式右部的长度
            length = len(production.right) if production.right[0] != "$" else 0

            # 从符号栈中删除相应长度的符号属性
            for _ in range(length):
                symbol_info_stack.pop()

            conclude_syble_info = GrammarSymbolInfo()
            conclude_syble_info.symbol_name = production.left
            conclude_syble_info.txt_value = (
                ""  # 这个信息没什么用，就是随便加进去，可能以后会用到
            )
            symbol_info_stack.append(conclude_syble_info)
            pass
        elif "else" in production.right:
            # STMT -> if id then STMT else STMT
            symbol_id = symbol_info_stack[-5]
            symbol_pos = self.symbol_tables_[0].FindSymbol(
                symbol_id.txt_value
            )
            symbol_name = self.GetArgName(SymbolPos(0,symbol_pos))
            backpatching_level_temp = self.backpatching_level_
            self.PrintQuadruples(Quadruples(self.temp[backpatching_level_temp],'j',symbol_name,'-',self.temp[backpatching_level_temp]+2))
            self.PrintQuadruples(Quadruples(self.temp[backpatching_level_temp]+1,'j','-','-',self.temp_else[backpatching_level_temp]+1))
            self.PrintQuadruples(Quadruples(self.temp_else[backpatching_level_temp],'j','-','-',self.PeekNextStateNum()))
            
            self.backpatching_level_ -= 1
            if self.backpatching_level_==0:
                for Qua in self.quadruples_stack_:
                    self.PrintQuadruples(Qua)
                self.quadruples_stack_=[]
            length = len(production.right)
            for _ in range(length):
                symbol_info_stack.pop()
            conclude_symbol_info = GrammarSymbolInfo(
                symbol_name=production.left,
                txt_value="",
            )
            symbol_info_stack.append(conclude_symbol_info)
            
            pass
        elif "if" == production.right[0]:
            # STMT -> if id then STMT
            symbol_id = symbol_info_stack[-3]
            symbol_pos = self.symbol_tables_[0].FindSymbol(
                symbol_id.txt_value
            )
            symbol_name = self.GetArgName(SymbolPos(0,symbol_pos))
            backpatching_level_temp = self.backpatching_level_
            self.backpatching_level_ -= 1
            self.PrintQuadruples(
                Quadruples(self.temp[backpatching_level_temp], 'j', symbol_name, '-', self.temp[backpatching_level_temp]+2)
            )
            self.PrintQuadruples(
                Quadruples(self.temp[backpatching_level_temp]+1, 'j', '-', '-', self.temp_else[backpatching_level_temp]+1)
            )
            #then
            if self.backpatching_level_==0:
                for Qua in self.quadruples_stack_:
                    self.PrintQuadruples(Qua)
                self.quadruples_stack_=[]
            length = len(production.right)
            for _ in range(length):
                symbol_info_stack.pop()
            conclude_symbol_info = GrammarSymbolInfo(
                symbol_name=production.left,
                txt_value="",
            )
            symbol_info_stack.append(conclude_symbol_info)
            
            pass
        elif "while" == production.right[0]:
            # STMT -> while id do STMT
            symbol_id = symbol_info_stack[-3]
            backpatching_level_temp = self.backpatching_level_
            self.backpatching_level_ -= 1
            symbol_pos = self.symbol_tables_[0].FindSymbol(
                symbol_id.txt_value
            )
            symbol_name = self.GetArgName(SymbolPos(0,symbol_pos))
            self.PrintQuadruples(
                Quadruples(self.temp[backpatching_level_temp], 'j', symbol_name, '-', self.temp[backpatching_level_temp]+2)
            )
            self.PrintQuadruples(
                Quadruples(self.temp[backpatching_level_temp]+1, 'j', '-', '-', self.PeekNextStateNum()+1)
            )
            #do
            if self.backpatching_level_==0:
                for Qua in self.quadruples_stack_:
                    self.PrintQuadruples(Qua)
                self.quadruples_stack_=[]
            self.PrintQuadruples(
                Quadruples(self.PeekNextStateNum(), 'j', '-', '-',self.temp[backpatching_level_temp])
            )
            self.GetNextStateNum()
            length = len(production.right)
            for _ in range(length):
                symbol_info_stack.pop()
            conclude_symbol_info = GrammarSymbolInfo(
                symbol_name=production.left,
                txt_value="",
            )
            symbol_info_stack.append(conclude_symbol_info)
            pass
        elif "{" == production.right[0]:
            # STMT -> { STMTS STMT }
            # 由规约后的产生式左部构造一个文法符号属性
            conclude_syble_info = GrammarSymbolInfo()
            conclude_syble_info.symbol_name = production.left
            conclude_syble_info.txt_value = ""
            # 获取产生式右部的长度
            length = len(production.right)
            for _ in range(length):
                symbol_info_stack.pop()

            symbol_info_stack.append(conclude_syble_info)
            pass
        elif "read" == production.right[0]:
            # STMT -> read id ;
            symbol_info = symbol_info_stack[-2]
            symbol_pos = self.symbol_tables_[0].FindSymbol(
                symbol_info.txt_value
            )
            symbol_name = self.GetArgName(SymbolPos(0,symbol_pos))
            conclude_symbol_info = GrammarSymbolInfo(
                symbol_name=production.left,
                txt_value="",
            )
            length = len(production.right)
            for _ in range(length):
                symbol_info_stack.pop()
            symbol_info_stack.append(conclude_symbol_info)
            
            self.PrintQuadruples(
                Quadruples(self.GetNextStateNum(), "read", "-", "-", symbol_name)
            )
            pass
        elif "write" == production.right[0]:
            # STMT -> write id ;
            symbol_info = symbol_info_stack[-2]
            symbol_pos = self.symbol_tables_[0].FindSymbol(
                symbol_info.txt_value
            )
            symbol_name = self.GetArgName(SymbolPos(0,symbol_pos))
            conclude_symbol_info = GrammarSymbolInfo(
                symbol_name=production.left,
                txt_value="",
            )
            length = len(production.right)
            for _ in range(length):
                symbol_info_stack.pop()
            symbol_info_stack.append(conclude_symbol_info)
            
            self.PrintQuadruples(
                Quadruples(self.GetNextStateNum(), "write", "-", "-", symbol_name)
            )
            pass
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
                Quadruples(self.GetNextStateNum(), symbol_add.txt_value, arg1_name, arg2_name, symbol_name)
            )
            
            conclude_symbol_info = GrammarSymbolInfo(
                symbol_name=production.left,
                txt_value=symbol_name,
                pos=SymbolPos(1,symbol_pos),
            )
            
            length = len(production.right)
            if "$" != production.right[0]:
                length = len(production.right)

            for i in range(length):
                symbol_info_stack.pop()

            symbol_info_stack.append(conclude_symbol_info)
            pass
        elif "EXPR" == production.left:
            # EXPR -> TERM
            symbol_info = symbol_info_stack[-1]
            conclude_symbol_info = GrammarSymbolInfo(
                symbol_name=production.left,
                txt_value=symbol_info.txt_value,
                pos=symbol_info.pos,
            )
            # 获取产生式右部的长度
            length = len(production.right)
            if "$" != production.right[0]:
                length = len(production.right)

            for i in range(length):
                symbol_info_stack.pop()

            symbol_info_stack.append(conclude_symbol_info)
            pass
        elif "ADD" == production.left and production.right[0] == "+":
            # ADD -> +
            # 由规约后的产生式左部构造一个文法符号属性
            conclude_syble_info = GrammarSymbolInfo()
            conclude_syble_info.symbol_name = production.left
            conclude_syble_info.txt_value = "+"
            # 获取产生式右部的长度
            length = len(production.right)
            for _ in range(length):
                symbol_info_stack.pop()

            symbol_info_stack.append(conclude_syble_info)
            pass
        elif "ADD" == production.left and production.right[0] == "-":
            # ADD -> -
            # 由规约后的产生式左部构造一个文法符号属性
            conclude_syble_info = GrammarSymbolInfo()
            conclude_syble_info.symbol_name = production.left
            conclude_syble_info.txt_value = "-"
            # 获取产生式右部的长度
            length = len(production.right)
            for _ in range(length):
                symbol_info_stack.pop()

            symbol_info_stack.append(conclude_syble_info)
            pass
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
                Quadruples(self.GetNextStateNum(), symbol_add.txt_value, arg1_name, arg2_name, symbol_name)
            )
            
            conclude_symbol_info = GrammarSymbolInfo(
                symbol_name=production.left,
                txt_value=symbol_name,
                pos=SymbolPos(1,symbol_pos),
            )
            
            length = len(production.right)
            if "$" != production.right[0]:
                length = len(production.right)

            for i in range(length):
                symbol_info_stack.pop()

            symbol_info_stack.append(conclude_symbol_info)
            pass
        elif "TERM" == production.left:
            # TERM -> NEGA
            symbol_info = symbol_info_stack[-1]
            conclude_symbol_info = GrammarSymbolInfo(
                symbol_name=production.left,
                txt_value=symbol_info.txt_value,
                pos=symbol_info.pos,
            )
            # 获取产生式右部的长度
            length = len(production.right)
            if "$" != production.right[0]:
                length = len(production.right)

            for i in range(length):
                symbol_info_stack.pop()

            symbol_info_stack.append(conclude_symbol_info)
            pass
        elif "MUL" == production.left and production.right[0] == "*":
            # MUL -> *
            # 由规约后的产生式左部构造一个文法符号属性
            conclude_syble_info = GrammarSymbolInfo()
            conclude_syble_info.symbol_name = production.left
            conclude_syble_info.txt_value = "*"
            # 获取产生式右部的长度
            length = len(production.right)
            for _ in range(length):
                symbol_info_stack.pop()

            symbol_info_stack.append(conclude_syble_info)
            pass
        elif "MUL" == production.left and production.right[0] == "/":
            # MUL -> /
            # 由规约后的产生式左部构造一个文法符号属性
            conclude_syble_info = GrammarSymbolInfo()
            conclude_syble_info.symbol_name = production.left
            conclude_syble_info.txt_value = "/"
            # 获取产生式右部的长度
            length = len(production.right)
            for _ in range(length):
                symbol_info_stack.pop()

            symbol_info_stack.append(conclude_syble_info)
            pass
        elif "NEGA" == production.left and production.right[0] == "FACTOR":
            # NEGA -> FACTOR
            symbol_info = symbol_info_stack[-1]
            conclude_symbol_info = GrammarSymbolInfo(
                symbol_name=production.left,
                txt_value=symbol_info.txt_value,
                pos=symbol_info.pos,
            )

            # symbol_pos = self.symbol_tables_[1].AddSymbol(symbol_info.txt_value)
            # symbol_name = self.symbol_tables_[1].GetSymbolName(symbol_pos)

            # conclude_symbol_info.txt_value = symbol_name
            # conclude_symbol_info.pos = SymbolPos(1, symbol_pos)  # 1表示临时变量表

            # self.PrintQuadruples(
            #     Quadruples(
            #         self.GetNextStateNum(),
            #         ":=",
            #         symbol_info.txt_value,
            #         "-",
            #         symbol_name,
            #     )
            # )

            # 获取产生式右部的长度
            length = len(production.right)
            if "$" != production.right[0]:
                length = len(production.right)

            for i in range(length):
                symbol_info_stack.pop()

            symbol_info_stack.append(conclude_symbol_info)
            # if symbol_info.is_imm:
            #     self.target_code_generator_.LoadImmToReg(
            #         symbol_info.txt_value, conclude_symbol_info.pos
            #     )
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
            # 获取产生式右部的长度
            length = len(production.right)
            if "$" != production.right[0]:
                length = len(production.right)

            for i in range(length):
                symbol_info_stack.pop()

            symbol_info_stack.append(conclude_symbol_info)
            # if symbol_info.is_imm:
            #     self.target_code_generator_.LoadImmToReg(
            #         "-"+symbol_info.txt_value, conclude_symbol_info.pos
            #     )
            identifier_layer = len(self.current_symbol_table_stack_) - 1
            sp = SymbolPos()
            sp.table_pos = self.current_symbol_table_stack_[identifier_layer]
            sp.symbol_pos = self.symbol_tables_[sp.table_pos].FindSymbol(
                symbol_info.txt_value
            )
            # tar_arg1_name = self.target_code_generator_.SetArgBeReady(sp)

            # self.target_code_generator_.PrintQuadruples(
            #     Instructions("nec", tar_arg1_name)
            # )
            pass
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

            # 获取产生式右部的长度
            length = 0
            if "$" != production.right[0]:
                length = len(production.right)

            for i in range(length):
                symbol_info_stack.pop()

            symbol_info_stack.append(conclude_symbol_info)
            pass
        elif "FACTOR" == production.left and production.right[0] == "id":
            # FACTOR -> id
            symbol_info = symbol_info_stack[-1]
            symbol_pos = self.symbol_tables_[0].FindSymbol(symbol_info.txt_value)
            conclude_symbol_info = GrammarSymbolInfo(
                symbol_name=production.left,
                txt_value=symbol_info.txt_value,
                pos=SymbolPos(0, symbol_pos),
            )
            symbol_info_stack.pop()
            symbol_info_stack.append(conclude_symbol_info)
            pass
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
                is_imm=True,
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
            # 获取产生式右部的长度
            length = 0
            if "$" != production.right[0]:
                length = len(production.right)

            for i in range(length):
                symbol_info_stack.pop()

            symbol_info_stack.append(conclude_symbol_info)
            # self.target_code_generator_.LoadImmToReg(
            #         symbol_info.txt_value, conclude_symbol_info.pos
            #     )
            pass
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
                Quadruples(self.GetNextStateNum(), symbol_or.txt_value, arg1_name, arg2_name, symbol_name)
            )
            
            conclude_symbol_info = GrammarSymbolInfo(
                symbol_name=production.left,
                txt_value=symbol_name,
                pos=SymbolPos(1,symbol_pos),
            )
            
            length = len(production.right)
            if "$" != production.right[0]:
                length = len(production.right)

            for i in range(length):
                symbol_info_stack.pop()

            symbol_info_stack.append(conclude_symbol_info)
            pass
        elif "BOOL" == production.left and production.right[0] == "JOIN":
            # BOOL -> JOIN
            symbol_info = symbol_info_stack[-1]
            symbol_pos = self.symbol_tables_[1].FindSymbol(symbol_info.txt_value)
            symbol_name = self.symbol_tables_[1].GetSymbolName(symbol_pos)
            conclude_syble_info = GrammarSymbolInfo()
            conclude_syble_info.symbol_name = production.left
            conclude_syble_info.txt_value = symbol_name
            conclude_syble_info.pos = SymbolPos(1, symbol_pos)
            # 获取产生式右部的长度
            length = len(production.right)
            for _ in range(length):
                symbol_info_stack.pop()

            symbol_info_stack.append(conclude_syble_info)
            pass
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
                Quadruples(self.GetNextStateNum(), symbol_or.txt_value, arg1_name, arg2_name, symbol_name)
            )
            
            conclude_symbol_info = GrammarSymbolInfo(
                symbol_name=production.left,
                txt_value=symbol_name,
                pos=SymbolPos(1,symbol_pos),
            )
            
            length = len(production.right)
            if "$" != production.right[0]:
                length = len(production.right)

            for i in range(length):
                symbol_info_stack.pop()

            symbol_info_stack.append(conclude_symbol_info)
            pass
        elif "JOIN" == production.left and production.right[0] == "NOT":
            # JOIN -> NOT
            symbol_info = symbol_info_stack[-1]
            symbol_pos = self.symbol_tables_[1].FindSymbol(symbol_info.txt_value)
            symbol_name = self.symbol_tables_[1].GetSymbolName(symbol_pos)
            conclude_syble_info = GrammarSymbolInfo()
            conclude_syble_info.symbol_name = production.left
            conclude_syble_info.txt_value = symbol_name
            conclude_syble_info.pos = SymbolPos(1, symbol_pos)
            # 获取产生式右部的长度
            length = len(production.right)
            for _ in range(length):
                symbol_info_stack.pop()

            symbol_info_stack.append(conclude_syble_info)
            pass
        elif "NOT" == production.left and production.right[0] == "REL":
            # NOT -> REL
            symbol_info = symbol_info_stack[-1]
            symbol_pos = self.symbol_tables_[1].FindSymbol(symbol_info.txt_value)
            symbol_name = self.symbol_tables_[1].GetSymbolName(symbol_pos)
            conclude_syble_info = GrammarSymbolInfo()
            conclude_syble_info.symbol_name = production.left
            conclude_syble_info.txt_value = symbol_name
            conclude_syble_info.pos = SymbolPos(1, symbol_pos)
            # 获取产生式右部的长度
            length = len(production.right)
            for _ in range(length):
                symbol_info_stack.pop()

            symbol_info_stack.append(conclude_syble_info)
            pass
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
                pos=SymbolPos(1,symbol_pos),
            )
            # 获取产生式右部的长度
            length = len(production.right)
            for _ in range(length):
                symbol_info_stack.pop()

            symbol_info_stack.append(conclude_syble_info)
            pass
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
                Quadruples(self.GetNextStateNum(), symbol_ROP.txt_value, arg1_name, arg2_name, symbol_name)
            )
            
            conclude_symbol_info = GrammarSymbolInfo(
                symbol_name=production.left,
                txt_value=symbol_name,
                pos=SymbolPos(1,symbol_pos),
            )
            
            length = len(production.right)
            if "$" != production.right[0]:
                length = len(production.right)

            for i in range(length):
                symbol_info_stack.pop()

            symbol_info_stack.append(conclude_symbol_info)
            
            pass
        elif "ROP" == production.left and production.right[0] == ">":
            # ROP -> >
            # 由规约后的产生式左部构造一个文法符号属性
            conclude_syble_info = GrammarSymbolInfo()
            conclude_syble_info.symbol_name = production.left
            conclude_syble_info.txt_value = ">"
            # 获取产生式右部的长度
            length = len(production.right)
            for _ in range(length):
                symbol_info_stack.pop()

            symbol_info_stack.append(conclude_syble_info)
            pass
        elif "ROP" == production.left and production.right[0] == ">=":
            # ROP -> >=
            # 由规约后的产生式左部构造一个文法符号属性
            conclude_syble_info = GrammarSymbolInfo()
            conclude_syble_info.symbol_name = production.left
            conclude_syble_info.txt_value = ">="
            # 获取产生式右部的长度
            length = len(production.right)
            for _ in range(length):
                symbol_info_stack.pop()

            symbol_info_stack.append(conclude_syble_info)
            pass
        elif "ROP" == production.left and production.right[0] == "<":
            # ROP -> <
            # 由规约后的产生式左部构造一个文法符号属性
            conclude_syble_info = GrammarSymbolInfo()
            conclude_syble_info.symbol_name = production.left
            conclude_syble_info.txt_value = "<"
            # 获取产生式右部的长度
            length = len(production.right)
            for _ in range(length):
                symbol_info_stack.pop()

            symbol_info_stack.append(conclude_syble_info)
            pass
        elif "ROP" == production.left and production.right[0] == "<=":
            # ROP -> <=
            # 由规约后的产生式左部构造一个文法符号属性
            conclude_syble_info = GrammarSymbolInfo()
            conclude_syble_info.symbol_name = production.left
            conclude_syble_info.txt_value = "<="
            # 获取产生式右部的长度
            length = len(production.right)
            for _ in range(length):
                symbol_info_stack.pop()

            symbol_info_stack.append(conclude_syble_info)
            pass
        elif "ROP" == production.left and production.right[0] == "==":
            # ROP -> ==
            # 由规约后的产生式左部构造一个文法符号属性
            conclude_syble_info = GrammarSymbolInfo()
            conclude_syble_info.symbol_name = production.left
            conclude_syble_info.txt_value = "=="
            # 获取产生式右部的长度
            length = len(production.right)
            for _ in range(length):
                symbol_info_stack.pop()

            symbol_info_stack.append(conclude_syble_info)
            pass
        elif "ROP" == production.left and production.right[0] == "!=":
            # ROP -> !=
            # 由规约后的产生式左部构造一个文法符号属性
            conclude_syble_info = GrammarSymbolInfo()
            conclude_syble_info.symbol_name = production.left
            conclude_syble_info.txt_value = "!="
            # 获取产生式右部的长度
            length = len(production.right)
            for _ in range(length):
                symbol_info_stack.pop()

            symbol_info_stack.append(conclude_syble_info)
            pass
        else:
            pass
        return True
