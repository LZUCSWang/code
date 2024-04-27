assume cs:code,ds:data,ss:stack

data segment

data ends

stack segment

stack ends

code segment
    start:
          mov ax, offset start
    s:    
          mov ax,offset s
          mov ax,4c00h
          int 21h
code ends

end start