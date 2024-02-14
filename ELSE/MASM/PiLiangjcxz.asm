assume cs:code,ds:data,ss:stack

data segment

         db 'hello',0
         db 'world',0
data ends
stack segment

stack ends

code segment
    start:  
            mov  ax,data
            mov  ds,ax
            mov  si ,0
            mov  cx,2
            mov  bx,0
    s:      mov  si,bx
            call captial
            add  bx,6
            loop s
            mov  ax,4c00h
            int  21h

    captial:push cx
            push si
    change: mov  cl,[si]
            mov  ch,0
            jcxz ok
            and  cl,11011111b
            mov  [si],cl
            inc  si
            jmp  short change

    ok:     
            pop  si
            pop  cx
            ret
code ends

end start