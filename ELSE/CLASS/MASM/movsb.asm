assume cs:code,ds:data,ss:stack

data segment
         db 'Welcome to masm!'
         db 16 dup (0)
data ends

stack segment

stack ends

code segment
    start:
          mov ax,data
          mov ds,ax
          mov es,ax
          mov si,0
          mov di,16
          cld
          mov cx,8
          rep movsw
          mov ax,4c00h
          int 21h
code ends

end start