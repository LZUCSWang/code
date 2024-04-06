from enum import Enum


class TABLE_TYPE(Enum):
    CONST_TABLE = 0
    TEMP_TABLE = 1
    GLOBAL_TABLE = 2
    FUNCTION_TABLE = 3
    WHILE_TABLE = 4
    IF_TABLE = 5


class Symbol:
    def __init__(
        self,
        mode="",
        name="",
        type="",
        value="",
        parameter_num=0,
        entry_address=None,
        func_symbol_pos=None,
        function_table_num=None,
        offset=-1,
        reg=-1,
    ):
        self.mode = mode  # MODE: FUNCTION, VARIABLE, CONST, TEMP
        self.name = name
        self.type = type  # Variable type or function return type
        self.value = value  # Constant value

        self.parameter_num = parameter_num  # Number of parameters if it's a function
        self.entry_address = entry_address  # Function entry address
        self.func_symbol_pos = (
            func_symbol_pos  # Position of the function table in the symbol table
        )
        self.function_table_num = function_table_num  # Index of function formal parameters in the function symbol table

        self.offset = offset  # TEMP: Offset from $gp, 1 represents 4 bytes; -1 means invalid. VARIABLE: Position in the stack frame
        self.reg = reg  # MIPS registers t0-t9; valid 0-9, -1 means not used
        # offset and reg are used together:
        # o-1, r-1    means not loaded to reg and not saved in memory
        # o-1, r>-1   means the value in the register is valid
        # o>-1, r-1   means the value in the register is invalid, but it's saved in memory


class SymbolTable:
    def __init__(self, t_type, iname):
        self.table_ = []
        self.table_type_ = t_type
        self.name_ = iname

    def __del__(self):
        pass

    def GetTable(self):
        return self.table_

    def GetTableType(self):
        return self.table_type_

    def GetSymbol(self, pos):
        return self.table_[pos]

    def AddSymbol(self, *args):
        if len(args) == 1 and isinstance(args[0], Symbol):
            return self.AddSymbolSymbol(args[0])
        elif len(args) == 1 and isinstance(args[0], str):
            return self.AddSymbolString(args[0])
        else:
            return self.AddSymbolDefault()

    def AddSymbolSymbol(self, sb):
        if self.FindSymbol(sb.name) != -1:
            return -1
        self.table_.append(sb)
        return len(self.table_) - 1

    def AddSymbolString(self, str_val):
        tmp_name = "T" + str(len(self.table_))
        sb = Symbol()
        sb.name = tmp_name
        sb.mode = "TEMP"
        sb.value = str_val
        self.table_.append(sb)
        return len(self.table_) - 1

    def AddSymbolDefault(self):
        tmp_name = "T" + str(len(self.table_))
        sb = Symbol()
        sb.name = tmp_name
        sb.mode = "TEMP"
        self.table_.append(sb)
        return len(self.table_) - 1

    def GetTableName(self):
        return self.name_

    def GetSymbolName(self, pos):
        return self.table_[pos].name

    def FindSymbol(self, name):
        for i in range(len(self.table_)):
            if self.table_[i].name == name:
                return i
        return -1

    def FindConst(self, const_value):
        for i in range(len(self.table_)):
            if self.table_[i].name == TABLE_TYPE.CONST:
                continue
            if self.table_[i].name == const_value:
                return i
        return -1

    def SetValue(self, pos, value):
        self.table_[pos].value = value
        return True

    def GetSymbolMode(self, pos):
        return self.table_[pos].mode

    def GetSymbolType(self, pos):
        return self.table_[pos].type
