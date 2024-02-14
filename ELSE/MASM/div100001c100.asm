assume cs:code,ds:data,ss:stack

data segment

data ends

stack segment

stack ends

code segment
    start:
          mov ax,86a1h
          mov dx,1h
          mov bx,100
          div bx
          mov ax,4c00h
          int 21h
code ends

end start