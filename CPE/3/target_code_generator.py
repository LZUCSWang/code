from utils import *


class TargetCodeGenerator:
    def __init__(self, symbol_tables_):
        self.registers_ = [
            # { "$t0","" },{ "$t1","" },{ "$t2","" },{ "$t3","" },{ "$t4","" },
            # { "$t5","" },{ "$t6","" },{ "$t7","" },{ "$t8","" },{ "$t9","" }
            RegisterInfo("$t0", ""),
            RegisterInfo("$t1", ""),
            RegisterInfo("$t2", ""),
            RegisterInfo("$t3", ""),
            RegisterInfo("$t4", ""),
            RegisterInfo("$t5", ""),
            RegisterInfo("$t6", ""),
            RegisterInfo("$t7", ""),
            RegisterInfo("$t8", ""),
            RegisterInfo("$t9", ""),
        ]
        self.GF_INI_OFFSET = 1024
        self.symbol_tables_pt_ = symbol_tables_
        self.target_code_printer_ = open("./gen_data/target_file/target_code.txt", "w")
        if not self.target_code_printer_:
            print("用来保存输出目标代码的文件打开失败！")
        self.InitialSpFpGp()  # 初始化设置，没与Mars内存对齐会出现错误
        self.gf_offset = self.GF_INI_OFFSET

    def TargetCodeGeneratorInit(self, symbol_tables_):
        self.symbol_tables_pt = symbol_tables_

    def __del__(self):
        if self.target_code_printer_:
            self.target_code_printer_.close()

    def InitialSpFpGp(self):
        # lui $sp, 0x1001
        # move $fp, $sp  初始的fp直接给0？ 待修改----------------------------------------------------------------
        self.PrintQuadruples(Instructions("lui", "$sp", "0x1001", ""))
        self.PrintQuadruples(Instructions("lui", "$gp", "0x1000", ""))
        # self.PrintQuadruples(Instructions("move", "$fp", "$sp", ""))
        self.PrintQuadruples(Instructions("j", "main", "", ""))
        return True

    def PrintQuadruples(self, instr):
        self.target_code_printer_.write(
            f"{instr.op} {instr.arg1} {instr.arg2} {instr.arg3}\n"
        )
        return True

    def PrintSyscall(self):
        self.target_code_printer_.write("syscall\n")
        return True

    def print_quadruples(self, *args):
        if len(args) == 1 and isinstance(args[0], Instructions):
            return self._print_quadruples_instructions(args[0])
        elif len(args) == 1 and isinstance(args[0], str):
            return self._print_quadruples_string(args[0])
        else:
            return False  # 或者抛出异常，表示调用不匹配

    def _print_quadruples_instructions(self, instr):
        self.target_code_printer_.write(
            f"{instr.op} {instr.arg1} {instr.arg2} {instr.arg3}\n"
        )
        return True

    def _print_quadruples_string(self, label):
        self.target_code_printer_.write(f"{label}\n")
        return True

    def PushStack_sp(self, num):
        size = num * 4
        self.PrintQuadruples(Instructions("addi", "$sp", "$sp", str(size)))
        # self.print_instructions(Instructions("addi", "$sp", "$sp", str(size)))
        # Similar to: addi $sp $sp 12
        return True

    def CreateStackFrame(self):
        self.target_code_printer_.write("#创建栈帧\n")
        # Save return address sw $ra ($sp)
        self.print_instructions(Instructions("sw", "$ra", "($sp)", ""))
        # Save old fp sw $fp ($sp)
        self.print_instructions(Instructions("sw", "$fp", "4($sp)", ""))
        # Update fp addi $fp $sp 4
        self.print_instructions(Instructions("addi", "$fp", "$sp", "4"))
        # sp + 2*4
        self.PushStack_sp(2)
        self.target_code_printer_.write("\n\n")
        return True

    def SetMissTime(self, reg):
        # Reset the miss time for the specified register to 0, increment for others
        for i in range(len(self.registers_)):
            if reg == i:
                self.registers_[i].miss_time = 0
            else:
                self.registers_[i].miss_time += 1

    def GetTempReg(self):
        # Indicates that not all registers are occupied
        reg = -1
        miss_t = -1  # Number of times not used

        # Indicates all registers are occupied
        reg_p = -1
        miss_t_p = -1

        for i, iter in enumerate(self.registers_):
            # If the register is available
            if not iter.is_possessed:  # Not yet occupied
                if iter.miss_time > miss_t:  # Number of times not used
                    reg = i
                    miss_t = iter.miss_time
            # If all registers are occupied
            if iter.miss_time > miss_t_p:  # Number of times not used
                reg_p = i
                miss_t_p = iter.miss_time

        # If there is an unoccupied register, return it
        if reg != -1:
            return reg
        else:  # All registers are occupied
            return reg_p

    def IsSymbolLoaded(self, pos):
        symbol_tables = self.symbol_tables_pt_
        sb = symbol_tables[pos.table_pos].GetSymbol(pos.symbol_pos)
        return sb.reg != -1

    def LoadTempReg(self, reg, pos):
        symbol_tables = self.symbol_tables_pt_
        # Check if the symbol corresponding to pos is already in a register
        sb = symbol_tables[pos.table_pos].GetSymbol(pos.symbol_pos)

        if self.registers_[reg].is_possessed:  # If occupied, need to write back to memory first
            sw_mem_addr = self.GetMemAddr(self.registers_[reg].content_info)
            self.PrintQuadruples(
                Instructions("sw", self.registers_[reg].name, sw_mem_addr, "")
            )
            # Indicate it's no longer in a register
            reg_pos = self.registers_[reg].content_info
            symbol_tables[reg_pos.table_pos].GetSymbol(reg_pos.symbol_pos).reg = -1

        mem_addr = self.GetMemAddr(pos)
        self.PrintQuadruples(
            Instructions("lw", self.registers_[reg].name, mem_addr, "")
        )

        # Set register information
        self.registers_[reg].content_info = pos
        self.registers_[reg].is_possessed = True
        self.SetMissTime(reg)

        # Set symbol information
        sb.reg = reg

        return True

    def GetMemAddr(self, pos):
        addr = ""
        symbol_tables = self.symbol_tables_pt_
        if pos.table_pos == 1:  # 临时变量
            addr = "($gp)"
            offset_gp = self.GF_INI_OFFSET + pos.symbol_pos
            addr = f"{offset_gp * 4}{addr}"
        elif pos.table_pos == 0:  # 全局变量
            addr = "($gp)"
            offset_gp = -1
            global_table = symbol_tables[0].GetTable()
            for i, symbol in enumerate(global_table):
                if symbol.mode == "FUNCTION":
                    continue
                offset_gp += 1
                if i == pos.symbol_pos:
                    break
            addr = f"{offset_gp * 4}{addr}"
        else:  # 局部变量，形参，返回值
            func_pos_in_global = symbol_tables[0].FindSymbol(
                symbol_tables[pos.table_pos].GetTableName()
            )
            func = symbol_tables[0].GetSymbol(
                func_pos_in_global
            )  # 获取变量所在的符号表

            if pos.symbol_pos == 0:  # 返回值
                return_value = symbol_tables[pos.table_pos].GetSymbol(0)
                if return_value.type == "INT":
                    addr = "$v0"
                else:  # type == "VOID"
                    addr = ""
            else:
                par_num = func.parameter_num  # 获取形参个数
                if pos.symbol_pos <= par_num:  # 形参
                    addr = "($fp)"
                    offset_fp = (
                        -2 - par_num + pos.symbol_pos
                    )  # ($fp)老fp  -4($fp)存返回地址
                    addr = f"{offset_fp * 4}{addr}"
                else:  # 局部变量
                    addr = "($fp)"
                    offset_fp = (
                        pos.symbol_pos - par_num
                    )  # ($fp)老fp  4($fp)存第0个局部变量
                    addr = f"{offset_fp * 4}{addr}"
        return addr

    # def LoadImmToReg(self, imm, pos):
    #     symbol_tables = self.symbol_tables_pt_
    #     reg = self.GetTempReg()  # 获取下一个可用的寄存器

    #     if self.registers_[reg].is_possessed:  # 如果寄存器已被占用，需要先写回到内存
    #         sw_mem_addr = self.GetMemAddr(self.registers_[reg].content_info)
    #         self.PrintQuadruples(
    #             Instructions("sw", self.registers_[reg].name, sw_mem_addr, "")
    #         )
    #         # 标记寄存器内容已不在寄存器上
    #         reg_pos = self.registers_[reg].content_info
    #         symbol_tables[reg_pos.table_pos].GetSymbol(reg_pos.symbol_pos).reg = -1

    #     self.PrintQuadruples(
    #         Instructions("addi", self.registers_[reg].name, "$zero", imm)
    #     )  # 加载立即数到寄存器

    #     sb = symbol_tables[pos.table_pos].GetSymbol(pos.symbol_pos)
    #     # 设置寄存器信息
    #     self.registers_[reg].content_info = pos
    #     self.registers_[reg].is_possessed = True
    #     self.SetMissTime(reg)

    #     # 设置符号信息
    #     sb.reg = reg

    #     return True

    def SetArgBeReady(self, pos):
        name = "$t"
        symbol_tables = self.symbol_tables_pt_
        sb = symbol_tables[pos.table_pos].GetSymbol(pos.symbol_pos)  # 获取该符号

        if sb.reg == -1:  # 如果需要装载
            reg = self.GetTempReg()
            self.LoadTempReg(reg, pos)
        name += str(sb.reg)

        return name

    def ClearRegs(self):
        symbol_tables = self.symbol_tables_pt_
        for i, reg in enumerate(self.registers_):
            if not reg.is_possessed:
                continue
            pos = reg.content_info
            sb = symbol_tables[pos.table_pos].GetSymbol(pos.symbol_pos)  # 获取该符号
            sb.reg = -1
            reg.is_possessed = False
            reg.miss_time = 0
            reg.content_info = {"table_pos": -1, "symbol_pos": -1}
            if sb.mode == "TEMP":
                continue
            # 非临时变量，需要在 MIPS 中写回
            mem_addr = self.GetMemAddr(pos)
            self.PrintQuadruples(Instructions("sw", reg.name, mem_addr, ""))
        return True

    def ResetRegs(self):
        symbol_tables = self.symbol_tables_pt_
        for reg in self.registers_:
            if not reg.is_possessed:
                continue
            pos = reg.content_info
            sb = symbol_tables[pos.table_pos].GetSymbol(pos.symbol_pos)  # 获取该符号
            sb.reg = -1
            reg.is_possessed = False
            reg.miss_time = 0
            reg.content_info = {"table_pos": -1, "symbol_pos": -1}
        return True
