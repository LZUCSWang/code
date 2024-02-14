assume cs:code,ds:data,ss:stack

data segment

data ends

stack segment
    db 10 dup(0)
stack ends

code segment
    start:
          mov  ax,stack
          mov  ss,ax
    ;   sub ax,ax
    ;   and ax,1
    ;   or  ax,0
          mov  ah,0
          mov  al,127
          inc  al
          push 123h
          mov  ax,4c00h
          int  21h
code ends

end start