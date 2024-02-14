assume cs:code,ds:data

data segment
         db '1. file         '
         db '2. directory    '
         db '3. exit         '
data ends

code segment
    start:
          mov  ax,data
          mov  ds,ax

          mov  bx,0
          mov  cx,3
    s:    mov  al,[bx+3]
          and  al,11011111b
          mov  [bx+3],al
          add bx,16
          loop s
          mov  ax,4c00h
          int  21h
code ends

end start