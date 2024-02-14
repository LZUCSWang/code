DATA SEGMENT                        ;//定义数据段
    MYWORD DB "hello world!!!!$"    ;//定义字符串数组
DATA ENDS

CODE SEGMENT                        ;//定义代码段
          ASSUME CS:CODE,DS:DATA    ;//说明代码段与数据段
    start:
          MOV    AX,DATA            ;//将DATA(数据首地址)->AX寄存器
          MOV    DS,AX              ;//使得DS等于AX
          LEA    DX,MYWORD          ;//使得DX保存MYWORD的首地址
          MOV    AH,09h             ;//AH输出数组
          INT    21h                ;//执行AH的09h功能，输出
          MOV    AX,4c00h           ;//设置寄存器功能
          INT    21h                ;//调用寄存器功能，结束程序
CODE ENDS

END start;表示在start处执行程序，并结束程序
