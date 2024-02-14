assume cs:code,ds:data,ss:stack

data segment
         dw 1,2,3,4,0
data ends

stack segment

stack ends

code segment
    start:
          mov  ax,data
          mov  ds,ax
          mov  bx,0
    s:    mov  cx,[bx]
          jcxz ok
          inc  bx
          inc  bx
          jmp  short s
    ok:   mov  dx,bx
          mov  ax,4c00h
          int  21h
code ends

end start