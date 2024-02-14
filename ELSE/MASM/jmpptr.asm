assume cs:code,ds:data,ss:stack

data segment

data ends

stack segment

stack ends

code segment
    start:
        mov ax,0123h
        mov ds:[0],ax
        mov ax,0
        mov ds:[2],ax
        ; jmp dword ptr ds:[0]
        jmp word ptr ds:[2]
          mov ax,4c00h
          int 21h
code ends

end start