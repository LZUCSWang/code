assume cs:code,ds:data,ss:stack

data segment

data ends

stack segment

stack ends

code segment
    start:       
                 mov  ax,cs
                 mov  ds,ax
                 mov  si,offset capital

                 mov  ax,0
                 mov  es,ax
                 mov  di,200h

                 mov  cx,offset capitalend- offset capital
                 cld
                 rep  movsb

                 mov  ax,0
                 mov  es,ax
                 mov  word ptr es:[7ch*4],200h
                 mov  word ptr es:[7ch*4+2],0

                 mov  ax,4c00h
                 int  21h

    capital:     
                 push cx
                 push si
    capitalstart:
                 mov  cl,ds:[si]
                 mov  ch,0
        
                 jcxz capitalok

                 and  byte ptr ds:[si],11011111b
                 inc  si
                 jmp  short capitalstart
    capitalok:   
                 pop  si
                 pop  cx
                 iret
    capitalend:  
                 nop
code ends

end start