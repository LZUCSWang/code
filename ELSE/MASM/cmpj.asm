assume cs:code,ds:data,ss:stack

data segment

data ends

stack segment

stack ends

code segment
    start:
          mov ah ,100
          mov bh,98
          cmp ah,bh
          je  s
          jmp short ok
    s:    add ah,ah
    ok:   ret
          mov ax,4c00h
          int 21h
code ends

end start