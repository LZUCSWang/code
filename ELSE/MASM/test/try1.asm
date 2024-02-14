assume cs:code,ds:data,ss:stack

data segment

data ends

stack segment

stack ends

code segment
    start:
          mov ax, 256
          add ax,1
          mov ax,4c00h
          int 21h
code ends

end start