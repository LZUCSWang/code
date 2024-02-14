assume cs:code,ds:data,ss:stack

data segment
         db 16 dup(0)
data ends

stack segment

stack ends

code segment
    start:
            
          mov ax,0f000h
          mov ds,ax
          mov ax,data
          mov es,ax
          mov cx,8
    ;   f0000
    ;   fffff
    ;   ffffe
          mov si,0fffeh
          mov [si],0ffffh
          mov di,0eh
          std
          rep movsw
          mov ax,4c00h
          int 21h
code ends

end start