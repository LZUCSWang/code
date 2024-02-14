DATAS SEGMENT
          DB '1975', '1976', '1977', '1978', '1979', '1980', '1981', '1982'
          DB '1983', '1984', '1985', '1986', '1987', '1988', '1989', '1990'
          DB '1991', '1992', '1993', '1994', '1995'

          DD 16, 22, 382, 1356, 2390, 8000, 16000, 24486, 50065, 97479, 140417, 197514
          DD 345980, 590827, 803530, 118300, 184300, 2759000, 3753000, 4649000, 5937000

          DW 3, 7, 9, 13, 28, 38, 130, 220, 476, 778, 1001, 1442, 2258, 2793, 4037, 5635, 8226
          DW 11542, 14430, 15257, 17800
DATAS ENDS

TABLE SEGMENT
          DB 21 DUP ('year summ ne ?? ')
TABLE ENDS

STACKS SEGMENT
           DB 16 DUP (0)
STACKS ENDS

ASSUME CS:CODES,DS:DATAS,SS:STACKS

CODES SEGMENT
    START:
    ;相关寄存器初始化
          MOV  AX,DATAS
          MOV  DS,AX
          MOV  AX,TABLE
          MOV  ES,AX
          MOV  AX,STACKS
          MOV  SS,AX
          MOV  SP,16

          MOV  BX, OFFSET DATAS           ; 将年份数组的偏移地址存储在 BX 中
          MOV  BP, OFFSET TABLE           ; 将表格数组的偏移地址存储在 BP 中
          MOV  SI, OFFSET DATAS + 4       ; 将收入数组的偏移地址存储在 SI 中
          MOV  DI, OFFSET TABLE + 4       ; 将表格数组的偏移地址存储在 DI 中

          MOV  CX,21

    cycle:
    ; 使用栈复制年份
          PUSH WORD PTR [BX]
          POP  WORD PTR [BP]

    ; 使用栈复制收入
          PUSH DWORD PTR [SI]
          POP  DWORD PTR [DI]

    ; 使用栈复制雇员数
          ADD  SI, 4
          ADD  DI, 4

    ; 计算人均收入
          MOV  DWORD PTR AX,  [DI - 6]    ; 表格数组中的收入
          MOV  DWORD PTR DX,  [DI - 2]    ; 表格数组中的雇员数
          DIV  DX                         ; AX = AX / DX
          MOV  WORD PTR [DI + 6], AX      ; 将结果存储到表格数组中的人均收入位置

          ADD  BX, 2                      ; 年份数组指针后移2字节
          ADD  BP, 21                     ; 表格数组指针后移21字节

          LOOP cycle

          MOV  AH, 4CH
          INT  21H
CODES ENDS
END START
