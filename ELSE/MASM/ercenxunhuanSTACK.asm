assume cs:code,ds:data,ss:stack

data segment
         db 'hello'
         db 'world'
         db 'abcde'
data ends

stack segment
          db 10 dup(?)
stack ends

code segment
    start:
          mov  ax,data
          mov  ds,ax
          mov  bx,0
          mov  cx,3
    s:    push cx
          mov  si,0
          mov  cx,5
    s0:   mov  al,[bx+si]
          and  al,11011111b
          mov  [bx+si],al
          inc  si
          loop s0
          pop  cx
          add  bx,5
          loop s

          mov  ax,4c00h
          int  21h
code ends

end start