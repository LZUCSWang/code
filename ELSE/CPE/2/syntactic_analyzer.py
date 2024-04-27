from enum import Enum
from lexical_analyzer import *
from utils import *
import os

class SLR_OPERATIONS(Enum):
    CONCLUDE = 0  # 规约
    MOVE = 1  # 移进
    ACCEPT = 2  # 接受
    NONTERMINAL = 3  # 压入非终结符
    ERROR = 4  # 出错

class TreeNode:
    def __init__(self, value):
        self.value = value
        self.child = []

class LrItem:
    def __init__(self, production_number, point_pos):
        self.production_number = production_number
        self.point_pos = point_pos

    def __eq__(self, other):
        return (
            self.production_number == other.production_number
            and self.point_pos == other.point_pos
        )

    def __lt__(self, other):
        return (self.production_number, self.point_pos) < (
            other.production_number,
            other.point_pos,
        )

    def __hash__(self) -> int:
        return hash((self.production_number, self.point_pos))

# ACTION或者GOTO操作
class SlrOperation:
    def __init__(self, op, state):
        self.op = op  # 规约、移进、接受
        self.state = state  # item中的序号，从0开始

    def __eq__(self, other):
        return self.op == other.op and self.state == other.state

class SyntacticAnalyzer:
    first_map_, follow_map_ = {}, {}
    productions_, grammars_ = [], []
    grammar_symbol_, lr_items_ = set(), set()
    print_detail_ = False
    action_goto_tables_ = {}
    normal_family_ = []
    state_sequence_stack_, move_conclude_string_stack_ = [], []
    tree_node_stack_ = []

    def IsNonTerminalSymbol(self, symbol: str) -> bool:
        if symbol == "":
            return False
        if "A" <= symbol[0] <= "Z":
            return True
        return False

    # Insert code to generate the first set of a given symbol string based on the provided context
    def GetProductionFirstSet(self, symbol_string: list[str]) -> set[str]:
        first = set()
        for iter1 in symbol_string:
            if not self.IsNonTerminalSymbol(iter1):
                first.add(iter1)
                break

            for iter2 in self.first_map_[iter1]:
                if iter2 != "$" and iter2 not in first:
                    first.add(iter2)

            if "$" not in self.first_map_[iter1]:
                break

            if iter1 == symbol_string[-1] and "$" not in first:
                first.add("$")

        return first

    def GenProduction(self) -> bool:
        grammar_filename = "./raw_data/grammar.txt"
        try:
            with open(grammar_filename, "r", encoding="utf-8") as grammar_reader:
                while True:
                    grammar_str = grammar_reader.readline()
                    if not grammar_str:
                        break  # EOF
                    grammar_str = grammar_str.strip()
                    if len(grammar_str) == 0:  # 空串
                        continue

                    left = ""
                    right = []

                    left_pos = grammar_str.find("->")
                    if left_pos < 0:
                        print('grammar出现错误，某个产生式没有" -> "符号，请规范！')
                        return False
                    left = grammar_str[:left_pos].strip()

                    # 跳过"->"
                    grammar_str = grammar_str[left_pos + 2 :]

                    while True:  # 处理产生式右部
                        right_pos = grammar_str.find("|")
                        if right_pos == -1:  # 最后一个候选式
                            right.append(grammar_str)

                            # 将产生式分割
                            split_production = grammar_str.split()
                            self.productions_.append(Production(left, split_production))
                            # 添加终结符的grammar_symbol_集合
                            for iter in split_production:
                                if not self.IsNonTerminalSymbol(iter) and iter != "$":
                                    self.grammar_symbol_.add(iter)

                            break
                        # 不是最后一个候选式
                        # 如果是||
                        if grammar_str[right_pos + 1] == "|":
                            right_pos = grammar_str.find("|", right_pos + 2)
                            if right_pos == -1:  # 最后一个候选式
                                right.append(grammar_str)

                                # 将产生式分割
                                split_production = grammar_str.split()
                                self.productions_.append(
                                    Production(left, split_production)
                                )
                                # 添加终结符的grammar_symbol_集合
                                for iter in split_production:
                                    if (
                                        not self.IsNonTerminalSymbol(iter)
                                        and iter != "$"
                                    ):
                                        self.grammar_symbol_.add(iter)

                                break
                        right.append(grammar_str[:right_pos])

                        # )  # 将产生式分割
                        split_production = grammar_str[:right_pos].split()
                        self.productions_.append(Production(left, split_production))
                        # 添加终结符的grammar_symbol_集合
                        for iter in split_production:
                            if not self.IsNonTerminalSymbol(iter) and iter != "$":
                                self.grammar_symbol_.add(iter)

                        grammar_str = grammar_str[right_pos + 1 :]

                    self.grammars_.append((left, right))
        except IOError:
            print("语法分析过程中，grammar文件打开失败！")
            return False

        return True

    def GenAugmentedGrammar(self) -> None:
        left = "Start"
        right = [self.productions_[0].left]
        self.productions_.insert(0, Production(left, right))
        return

    def GenFirstSet(self) -> None:
        for iter in self.productions_:
            self.first_map_[iter.left] = set()
            self.follow_map_[iter.left] = set()
            if iter.right[0] == "$":
                if "$" not in self.first_map_[iter.left]:
                    self.first_map_[iter.left].add("$")

        while True:
            is_change = False
            for iter1 in self.productions_:
                for iter2 in iter1.right:
                    if iter2 == "$":
                        break

                    if not self.IsNonTerminalSymbol(iter2):  # 如果是终结符
                        if iter2 not in self.first_map_[iter1.left]:
                            self.first_map_[iter1.left].add(iter2)
                            is_change = True
                        break

                    for iter3 in self.first_map_[iter2]:  # 如果是非终结符
                        if iter3 != "$" and iter3 not in self.first_map_[iter1.left]:
                            self.first_map_[iter1.left].add(iter3)
                            is_change = True

                    if "$" not in self.first_map_[iter2]:
                        break

                    if (
                        iter2 == iter1.right[-1]
                        and "$" not in self.first_map_[iter1.left]
                    ):
                        self.first_map_[iter1.left].add("$")
                        is_change = True

            if not is_change:
                break
        return

    def GenFollowSet(self):
        self.follow_map_[self.productions_[0].left].add("#")  # 文法开始符号，添加#

        while True:
            is_change = False
            for iter1 in self.productions_:
                for iter2_idx_, iter2 in enumerate(iter1.right):
                    if not self.IsNonTerminalSymbol(iter2):  # 当前符号为终结符，跳过
                        continue

                    first = self.GetProductionFirstSet(iter1.right[iter2_idx_ + 1 :])
                    for symbol in first:
                        if symbol != "$" and symbol not in self.follow_map_[iter2]:
                            self.follow_map_[iter2].add(symbol)
                            is_change = True

                    if not first or "$" in first:
                        for symbol in self.follow_map_[iter1.left]:
                            if symbol not in self.follow_map_[iter2]:
                                self.follow_map_[iter2].add(symbol)
                                is_change = True

            if not is_change:  # 未发生改变，生成Follow完成
                break

        return

    def GenGrammarSymbolSet(self):
        for key in self.first_map_:
            self.grammar_symbol_.add(key)

        self.grammar_symbol_.add("#")  # 终结符#一起添加进文法符号集合中
        return

    def GenLrItems(self):
        for iter in self.productions_:
            if (
                iter.right[0] == "$"
            ):  # 产生式右部是空串，LR0项目 只有一个 pos用-1来特殊表示
                self.lr_items_.add(
                    LrItem(self.productions_.index(iter), -1)
                )  # 插入产生式编号与-1（表示空）A->epsilon 只生成A->·
                continue
            production_length = len(iter.right)
            for count in range(production_length + 1):
                self.lr_items_.add(
                    LrItem(self.productions_.index(iter), count)
                )  # 插入产生式编号与小圆点位置
        return

    def GenItemClosureSet(self, input_item):
        item_stack = [input_item]
        item_set = set()

        while item_stack:
            item = item_stack.pop()
            item_set.add(item)

            if item.point_pos == -1:
                continue

            if item.point_pos == len(self.productions_[item.production_number].right):
                continue

            if not self.IsNonTerminalSymbol(
                self.productions_[item.production_number].right[item.point_pos]
            ):
                continue

            current_symbol = self.productions_[item.production_number].right[
                item.point_pos
            ]

            for iter in self.lr_items_:
                if self.productions_[
                    iter.production_number
                ].left == current_symbol and (
                    iter.point_pos == 0 or iter.point_pos == -1
                ):
                    if iter not in item_set:
                        item_stack.append(iter)

        return item_set

    def GenItemsClosureSet(self, items):
        item_stack = list(items)
        item_set = set()

        while item_stack:
            item = item_stack.pop()
            item_set.add(item)

            if item.point_pos == -1:
                continue

            if item.point_pos == len(self.productions_[item.production_number].right):
                continue

            if not self.IsNonTerminalSymbol(
                self.productions_[item.production_number].right[item.point_pos]
            ):
                continue

            current_symbol = self.productions_[item.production_number].right[
                item.point_pos
            ]

            for iter in self.lr_items_:
                if self.productions_[
                    iter.production_number
                ].left == current_symbol and (
                    iter.point_pos == 0 or iter.point_pos == -1
                ):
                    if iter not in item_set:
                        item_stack.append(iter)

        return item_set

    def GenNormalFamilySet(self):
        # item_stack = [
        #     self.GenItemClosureSet(next(iter(self.lr_items_)))
        # ]
        item_stack = [self.GenItemClosureSet(LrItem(0, 0))]
        self.normal_family_.append(item_stack[0])

        while item_stack:
            item = item_stack.pop()
            current_state = self.normal_family_.index(item)
            if len(item_stack) == 3:
                a = 1
            for iter1 in item:
                # 小圆点在第-1位置或者最后面，表示是需要规约的项目
                if iter1.point_pos == -1 or iter1.point_pos == len(
                    self.productions_[iter1.production_number].right
                ):
                    symbol = self.productions_[iter1.production_number].left
                    for iter2 in self.follow_map_[symbol]:
                        if (current_state, iter2) not in self.action_goto_tables_:
                            self.action_goto_tables_[(current_state, iter2)] = (
                                SlrOperation(
                                    SLR_OPERATIONS.CONCLUDE, iter1.production_number
                                )
                            )
                        # else:
                        #     if self.action_goto_tables_[
                        #         (current_state, iter2)
                        #     ] != SlrOperation(
                        #         SLR_OPERATIONS.CONCLUDE, iter1.production_number
                        #     ):
                        #         self.PrintSlrError(item)
                        #         return False
                else:
                    current_right_symbol = self.productions_[
                        iter1.production_number
                    ].right[iter1.point_pos]
                    items = set()
                    for iter2 in item:
                        if iter2.point_pos == -1 or iter2.point_pos == len(
                            self.productions_[iter2.production_number].right
                        ):
                            continue
                        if (
                            self.productions_[iter1.production_number].right[
                                iter1.point_pos
                            ]
                            == self.productions_[iter2.production_number].right[
                                iter2.point_pos
                            ]
                        ):
                            items.add(
                                LrItem(iter2.production_number, iter2.point_pos + 1)
                            )

                    next_normal_family = self.GenItemsClosureSet(items)

                    if next_normal_family not in self.normal_family_:
                        self.normal_family_.append(next_normal_family)
                        item_stack.append(next_normal_family)

                    next_state = self.normal_family_.index(next_normal_family)

                    if (
                        current_state,
                        current_right_symbol,
                    ) not in self.action_goto_tables_:
                        self.action_goto_tables_[
                            (current_state, current_right_symbol)
                        ] = SlrOperation(SLR_OPERATIONS.MOVE, next_state)
                    else:  # TODO：作业文法不是SLR文法，会有不可避免的移进规约冲突（if else）, 强行规定移进优先
                        if self.action_goto_tables_[
                            (current_state, current_right_symbol)
                        ] != SlrOperation(SLR_OPERATIONS.MOVE, next_state):
                            self.action_goto_tables_[
                                (current_state, current_right_symbol)
                            ] = SlrOperation(SLR_OPERATIONS.MOVE, next_state)
                            # self.PrintSlrError(item)
                            # return False

        current_state2 = -1
        for iter1 in self.normal_family_:
            for iter2 in iter1:
                if LrItem(0, 1) == iter2:
                    current_state2 = self.normal_family_.index(iter1)
                    break
            if current_state2 >= 0:
                break

        item = {LrItem(0, 1)}
        self.action_goto_tables_[(current_state2, "#")] = SlrOperation(
            SLR_OPERATIONS.ACCEPT, current_state2
        )

        return True

    def build_grammar(self):
        self.GenProduction()
        self.GenAugmentedGrammar()
        self.GenFirstSet()
        self.GenFollowSet()
        self.GenGrammarSymbolSet()
        self.GenLrItems()
        return self.GenNormalFamilySet()

    def PrintGrammars(self):
        for iter1 in self.grammars_:
            print(iter1.left, end="->")
            for iter2 in iter1.right:
                print(iter2, end="|")
            print()

    def PrintProdcutions(
        self, filename="./gen_data/syntactic_analyzer/productions.txt"
    ):  # TODO: 路径修改成相对路径
        with open(filename, "w") as printer:
            if not printer:
                print("语法分析过程中，", filename, "文件打开失败！")
                return

            for iter1 in self.productions_:
                printer.write(iter1.left + "->")
                for iter2 in iter1.right:
                    printer.write(iter2 + " ")
                printer.write("\n")

    def PrintFirst(self, filename="./gen_data/syntactic_analyzer/first.txt"):
        with open(filename, "w") as printer:
            if not printer:
                print("语法分析过程中，", filename, "文件打开失败！")
                return

            printer.write("First集合：\n")
            for iter1, iter1Value in self.first_map_.items():
                printer.write(iter1 + ": ")
                count = 0
                size_ = len(iter1Value)
                for iter2 in iter1Value:
                    printer.write(iter2)
                    if size_ > count + 1:
                        printer.write(" ")
                    count += 1
                printer.write("\n")

    def PrintFollow(self, filename="./gen_data/syntactic_analyzer/follow.txt"):
        with open(filename, "w") as printer:
            if not printer:
                print("语法分析过程中，", filename, "文件打开失败！")
                return

            printer.write("Follow集合：\n")
            for iter1, iter1Value in self.follow_map_.items():
                printer.write(iter1 + ": ")
                count = 0
                size_ = len(iter1Value)
                for iter2 in iter1Value:
                    printer.write(iter2)
                    if size_ > count + 1:
                        printer.write(" ")
                    count += 1
                printer.write("\n")

    def PrintGrammarSymbolSet(
        self, filename="./gen_data/syntactic_analyzer/symbol.txt"
    ):
        with open(filename, "w") as printer:
            if not printer:
                print("语法分析过程中，", filename, "文件打开失败！")
                return

            printer.write("文法符号（终结符与非终结符）：\n")
            for symbol in self.grammar_symbol_:
                printer.write(symbol + "\n")

    def PrintLrItems(self, filename="./gen_data/syntactic_analyzer/items.txt"):
        with open(filename, "w") as printer:
            if not printer:
                print("语法分析过程中，", filename, "文件打开失败！")
                return

            printer.write("LR0项目：\n")
            for iter1 in self.lr_items_:
                printer.write(self.productions_[iter1.production_number].left + "->")

                if iter1.point_pos == -1:
                    printer.write("·\n")
                    continue

                production_length = len(
                    self.productions_[iter1.production_number].right
                )

                for iter2 in self.productions_[iter1.production_number].right:
                    if iter1.point_pos == (
                        self.productions_[iter1.production_number].right.index(iter2)
                    ):
                        printer.write("· ")
                    printer.write(iter2 + " ")

                    if iter1.point_pos == production_length and (
                        len(self.productions_[iter1.production_number].right)
                        - self.productions_[iter1.production_number].right.index(iter2)
                        == 1
                    ):
                        printer.write("·")
                printer.write("\n")

    def PrintClosure(self):
        print("Closure项目：")
        for iter in self.lr_items_:
            lr = self.GenItemClosureSet(iter)

            for iter1 in lr:
                print(self.productions_[iter1.production_number].left + "->")

                if iter1.point_pos == -1:
                    print("·")
                    continue

                production_length = len(
                    self.productions_[iter1.production_number].right
                )

                for iter2 in self.productions_[iter1.production_number].right:
                    if iter1.point_pos == (
                        iter2
                        - self.productions_[iter1.production_number].right.index(iter2)
                    ):
                        print("· ", end="")
                    print(iter2 + " ", end="")

                    if iter1.point_pos == production_length and (
                        len(self.productions_[iter1.production_number].right)
                        - self.productions_[iter1.production_number].right.index(iter2)
                        == 1
                    ):
                        print("·", end="")
                print()
            print()

    def PrintSlrError(self, normal_family):
        print("不是SLR文法！！！ 冲突项目的规范族：")
        lr = normal_family

        for iter1 in lr:
            print(self.productions_[iter1.production_number].left + "->")

            if iter1.point_pos == -1:
                print("·")
                continue

            production_length = len(self.productions_[iter1.production_number].right)

            for iter2 in self.productions_[iter1.production_number].right:
                if iter1.point_pos == (
                    self.productions_[iter1.production_number].right.index(iter2)
                ):
                    print("· ", end="")
                print(iter2 + " ", end="")

                if iter1.point_pos == production_length and (
                    len(self.productions_[iter1.production_number].right)
                    - self.productions_[iter1.production_number].right.index(iter2)
                    == 1
                ):
                    print("·", end="")
            print()
        print()

    def PrintNormalFamiliySet(
        self, filename="./gen_data/syntactic_analyzer/normal_families.txt"
    ):
        with open(filename, "w") as printer:
            if not printer:
                print("语法分析过程中，", filename, "文件打开失败！")
                return

            printer.write("项目集规范族：\n")
            for iter1 in self.normal_family_:
                printer.write(
                    "规范族 " + str(self.normal_family_.index(iter1)) + " : \n"
                )
                for iter2 in iter1:
                    printer.write(
                        self.productions_[iter2.production_number].left + "->"
                    )

                    if iter2.point_pos == -1:
                        printer.write("·\n")
                        continue

                    production_length = len(
                        self.productions_[iter2.production_number].right
                    )

                    for iter3 in self.productions_[iter2.production_number].right:
                        if iter2.point_pos == (
                            self.productions_[iter2.production_number].right.index(
                                iter3
                            )
                        ):
                            printer.write("· ")
                        printer.write(iter3 + " ")

                        if iter2.point_pos == production_length and (
                            len(self.productions_[iter2.production_number].right)
                            - self.productions_[iter2.production_number].right.index(
                                iter3
                            )
                            == 1
                        ):
                            printer.write("·")
                    printer.write("\n")
                printer.write("\n")

    def PrintActionGotoTable(
        self, filename="./gen_data/syntactic_analyzer/action_goto_tables.csv"
    ):
        with open(filename, "w") as printer:
            if not printer:
                print("语法分析过程中，", filename, "文件打开失败！")
                return

            printer.write("  ")
            for symbol in self.grammar_symbol_:
                if self.IsNonTerminalSymbol(symbol):
                    continue
                if "," == symbol:  # 处理由于在CSV中输出 ","导致的位移问题。
                    printer.write(",，")
                else:
                    printer.write("," + symbol)

            for symbol in self.grammar_symbol_:
                if self.IsNonTerminalSymbol(symbol):
                    printer.write("," + symbol)

            printer.write("\n")

            for state in range(len(self.normal_family_)):
                printer.write("state " + str(state))
                for symbol in self.grammar_symbol_:
                    if self.IsNonTerminalSymbol(symbol):
                        continue

                    if (state, symbol) not in self.action_goto_tables_:
                        printer.write(",error")
                    else:
                        next_state = self.action_goto_tables_[(state, symbol)].state
                        op = self.action_goto_tables_[(state, symbol)].op

                        if op == SLR_OPERATIONS.MOVE:
                            printer.write(",s" + str(next_state))
                        elif op == SLR_OPERATIONS.CONCLUDE:
                            printer.write(",r" + str(next_state))
                        elif op == SLR_OPERATIONS.ACCEPT:
                            printer.write(",acc")
                        else:
                            printer.write(",???")

                for symbol in self.grammar_symbol_:
                    if not self.IsNonTerminalSymbol(symbol):
                        continue

                    if (state, symbol) not in self.action_goto_tables_:
                        printer.write(",error")
                    else:
                        next_state = self.action_goto_tables_[(state, symbol)].state
                        op = self.action_goto_tables_[(state, symbol)].op

                        if op == SLR_OPERATIONS.MOVE:
                            printer.write(",s" + str(next_state))
                        elif op == SLR_OPERATIONS.CONCLUDE:
                            printer.write(",r" + str(next_state))
                        elif op == SLR_OPERATIONS.ACCEPT:
                            printer.write(",acc")
                        else:
                            printer.write(",???")

                printer.write("\n")

    def PrintBuildGrammarDetails(self):
        if self.print_detail_:
            self.PrintProdcutions()
            self.PrintFirst()
            self.PrintFollow()
            self.PrintGrammarSymbolSet()
            self.PrintLrItems()
            self.PrintNormalFamiliySet()
            self.PrintActionGotoTable()

    def PrintAnalysisProcess(self, step, sl_op ,get_word):
        if not self.print_detail_:
            return

        self.syntactic_analyzer_printer_.write(str(step) + ",")

        # 输出状态栈
        for state in self.state_sequence_stack_:  # TODO:修改，怎么只显示第一个步骤？
            self.syntactic_analyzer_printer_.write(str(state) + " ")
        self.syntactic_analyzer_printer_.write(",")

        # 输出字符串栈
        for string in self.move_conclude_string_stack_:
            if string == ",":
                self.syntactic_analyzer_printer_.write("，")
            else:
                self.syntactic_analyzer_printer_.write(string + " ")
        self.syntactic_analyzer_printer_.write(",")

        # 输出操作
        if sl_op.op == SLR_OPERATIONS.MOVE:
            self.syntactic_analyzer_printer_.write("移进")
            if self.move_conclude_string_stack_[-1]=="id" or self.move_conclude_string_stack_[-1]=="number":
                self.tree_node_stack_.append(TreeNode(get_word.value))
            else:
                self.tree_node_stack_.append(TreeNode(self.move_conclude_string_stack_[-1]))
        elif sl_op.op == SLR_OPERATIONS.ACCEPT:
            self.syntactic_analyzer_printer_.write("接受")
        elif sl_op.op == SLR_OPERATIONS.CONCLUDE:
            if self.productions_[sl_op.state].right[0] == "$":
                self.tree_node_stack_.append(TreeNode("$"))
            conclude_tree_node_ = TreeNode(self.productions_[sl_op.state].left)
            conclude_tree_node_.child = self.tree_node_stack_[
                -len(self.productions_[sl_op.state].right) :
            ]
            self.tree_node_stack_ = self.tree_node_stack_[
                : -len(self.productions_[sl_op.state].right)
            ]
            self.tree_node_stack_.append(conclude_tree_node_)
            self.syntactic_analyzer_printer_.write(
                "规约： " + self.productions_[sl_op.state].left + "->"
            )
            for symbol in self.productions_[sl_op.state].right:
                if symbol == ",":
                    self.syntactic_analyzer_printer_.write("，")
                else:
                    self.syntactic_analyzer_printer_.write(symbol + " ")
        self.syntactic_analyzer_printer_.write("\n")

    # Constructor for SyntacticAnalyzer class

    def __init__(self, show_detail=True):
        self.print_detail_ = show_detail  # 选择是否在分析过程中打印语法分析的详细信息
        if show_detail:
            self.syntactic_analyzer_printer_ = open(
                "./gen_data/syntactic_analyzer/syntactic_analyser_process.csv", "w"
            )
            if not self.syntactic_analyzer_printer_:
                print("语法分析过程中，显示语法分析过程文件打开失败！")
            else:
                self.syntactic_analyzer_printer_.write(
                    "步骤, 状态栈, 符号栈, 动作说明\n"
                )

        self.build_grammar()  # 根据grammar.txt建立SLR分析表 ACTION 和  GOTO
        self.PrintBuildGrammarDetails()  # 打印构建SLR分析表的详细过程以及结果。（会自动根据print_detail_来判断是否打印）

    # Destructor for SyntacticAnalyzer class
    def __del__(self):
        if (
            self.syntactic_analyzer_printer_
            and not self.syntactic_analyzer_printer_.closed
        ):
            self.syntactic_analyzer_printer_.close()

    def StartAnalize(self, code_filename):
        self.state_sequence_stack_ = [0]  # 初始状态0压入栈中
        self.move_conclude_string_stack_ = ["#"]  # 初始的#字符串压入栈中

        self.grammar_symbol_info_stack_ = [{"PROG"}]  # 初始的文法符号属性

        # 初始化词法分析器
        lexcial_analyzer = LexicalAnalyzer()
        if not lexcial_analyzer.IsReadyToAnalyze(True, code_filename):
            return False

        sytactic_step = 0
        while True:
            get_word = lexcial_analyzer.GetWord()
            word_string = get_word.word_string
            if get_word.type == LEXICAL_TYPE.LUNKNOWN:  # 错误处理
                print("词法分析器过程中，发生unknown错误！")
                print(get_word.value)
            while True:
                current_state = self.state_sequence_stack_[-1]  # 选择状态序列栈栈顶

                if (
                    current_state,
                    word_string,
                ) not in self.action_goto_tables_:  # action_goto表中不存在对应的操作，语法分析过程中出现错误，报告错误并返回
                    print("语法分析器过程中，发生错误！")
                    print(get_word.value, end=" ")
                    print("\t行号：", lexcial_analyzer.cal_line_counter())
                    
                    print(
                        "state：",
                        current_state,
                        " 与 ",
                        word_string,
                        " 在action_goto_table 中不含对应操作!",
                    )
                    return False

                if (
                    self.action_goto_tables_[(current_state, word_string)].op
                    == SLR_OPERATIONS.MOVE
                ):  # 移进操作
                    self.state_sequence_stack_.append(
                        self.action_goto_tables_[(current_state, word_string)].state
                    )
                    self.move_conclude_string_stack_.append(word_string)
                    self.PrintAnalysisProcess(
                        sytactic_step,
                        self.action_goto_tables_[(current_state, word_string)],
                        get_word
                    )
                    sytactic_step += 1
                    self.grammar_symbol_info_stack_.append(
                        {get_word.word_string, get_word.value}
                    )  # 文法符号信息压入
                    break

                elif (
                    self.action_goto_tables_[(current_state, word_string)].op
                    == SLR_OPERATIONS.CONCLUDE
                ):  # 规约操作
                    conclude_production_number = self.action_goto_tables_[
                        (current_state, word_string)
                    ].state
                    if self.productions_[conclude_production_number].right[0] == "$":
                        production_length = 0
                    else:
                        production_length = len(
                            self.productions_[conclude_production_number].right
                        )

                    for i in range(
                        production_length
                    ):  # 将两个栈都弹出production_length个元素
                        self.state_sequence_stack_.pop()
                        self.move_conclude_string_stack_.pop()

                    self.move_conclude_string_stack_.append(
                        self.productions_[conclude_production_number].left
                    )  # 用于规约的产生式的左部 压入栈中
                    if (
                        self.state_sequence_stack_[-1],
                        self.productions_[conclude_production_number].left,
                    ) not in self.action_goto_tables_:  # 不存在goto
                        print("语法分析器算法发生致命错误CONCLUDE中")
                        print(get_word.value)
                        return False

                    self.state_sequence_stack_.append(
                        self.action_goto_tables_[
                            (
                                self.state_sequence_stack_[-1],
                                self.productions_[conclude_production_number].left,
                            )
                        ].state
                    )  # goto对应的状态压入

                elif (
                    self.action_goto_tables_[(current_state, word_string)].op
                    == SLR_OPERATIONS.ACCEPT
                ):  # 宣布接受
                    self.PrintAnalysisProcess(
                        sytactic_step,
                        self.action_goto_tables_[(current_state, word_string)],
                        get_word
                    )
                    sytactic_step += 1

                    print("语法分析正确完成！")
                    return True

                else:  # 语法分析器算法错误
                    print("致命错误！")
                    print("语法分析器算法存在错误，请检查！")
                    return False

                self.PrintAnalysisProcess(
                    sytactic_step,
                    self.action_goto_tables_[(current_state, word_string)],
                    get_word
                )
                sytactic_step += 1

        return True

    def PrintTree(self, node, depth=0, file=None, is_last_child=True):
        if node is not None:
            # 打印当前节点
            file.write("  " * depth)
            if depth > 0:
                file.write(" |--" if not is_last_child else " \\--")
            file.write(str(node.value))
            file.write("\n")
            
            # 如果当前节点有子节点，继续在下一层打印子节点
            if node.child:
                # 判断当前节点是否为其父节点的最后一个子节点
                for i, child in enumerate(node.child):
                    self.PrintTree(child, depth + 1, file, i == len(node.child) - 1)

    def VisualizeTree(self, root, filename="tree_output.txt"):
        with open(filename, "w") as file:
            self.PrintTree(root, file=file)

if __name__ == "__main__": # TODO: true 和 false 布尔型数据的常量在文法的哪个位置

    file_name ="./sourceProgram/sourceProgram9.txt"
    sa = SyntacticAnalyzer()
    if sa.StartAnalize(file_name):
        sa.VisualizeTree(
            sa.tree_node_stack_[0],
            "./treeOutput/treeOutput9.txt"
        )
