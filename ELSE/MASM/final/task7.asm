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

ASSUME    CS:CODES,DS:DATAS

CODES SEGMENT
      START:
      ;相关寄存器初始化
            MOV  AX,DATAS
            MOV  DS,AX
            MOV  AX,TABLE
            MOV  ES,AX
    
            MOV  BX,0
            MOV  BP,0
            MOV  DI,0
            MOV  SI,0

            MOV  CX,21
      cycle:                               
      ;使用空闲的BX寄存器复制年份
            MOV  BX,[DI].0
            MOV  ES:[BP].0,BX
            MOV  BX,[DI].2
            MOV  ES:[BP].2,BX
      ;复制收入
            MOV  BX,54H.[DI].0
            MOV  ES:[BP].5,BX
            MOV  BX,54H.[DI].2
            MOV  ES:[BP].7,BX
      ;复制雇员数
            MOV  BX,0A8H.[SI]
            MOV  ES:[BP].0AH,BX
      ;计算人均收入
            MOV  AX,ES:[BP].5
            MOV  DX,ES:[BP].7
            DIV  WORD PTR ES:[BP].0AH
            MOV  ES:[BP].0DH,AX

            ADD  SI,2H
            ADD  DI,4H
            ADD  BP,10H

            loop cycle
                   
            MOV  AH,4CH
            INT  21H
CODES ENDS
END       START