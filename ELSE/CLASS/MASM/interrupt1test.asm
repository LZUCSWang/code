assume cs:code,ds:data,ss:stack

data segment

data ends

stack segment

stack ends

code segment
    start:  
            mov  ax,cs
            mov  ds,ax
            mov  si,offset pow2

            mov  ax,0
            mov  es,ax
            mov  di,200h

            mov  cx,offset pow2end - offset pow2
            cld
            rep  movsb

            mov  ax,0
            mov  es,ax
            mov  word ptr es:[7ch*4],200h
            mov  word ptr es:[7ch*4+2],0
            mov  ax,4c00h
            int  21h
    pow2:   
            mul  ax
            iret
    pow2end:
            nop

code ends

end start