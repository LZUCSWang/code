assume cs:code,ds:data,ss:stack

data segment

data ends

stack segment

stack ends

code segment
    start:  
            mov  ax,cs
            mov  ds,ax
            mov  si,offset d0

            mov  ax,0
            mov  es,ax
            mov  di,200h

            mov  cx,offset d0end - offset d0
            rep  movsb
    ;copy the code to 200h
            mov  ax,0
            mov  es,ax
            mov  word ptr es:[0*4],200h
            mov  word ptr es:[0*4+2],0          ;set interrupt vector
            mov  ax,4c00h
            int  21h
    d0:     jmp  short d0start
            db   'overflow!'
    d0start:
            mov  ax,cs
            mov  ds,ax
            mov  si,202                         ;200+(2) 2 is the length of jmp...
            mov  ax,0b800h
            mov  es,ax
            mov  di,12*160+36*2
            mov  cx,9
    s:      mov  al,[si]
            mov  es:[di],al
            inc  si
            add  di,2                           ;显存中每个字符占两个字节
            loop s
    ;show 'overflow' in the screen
            mov  ax,4c00h
            int  21h
    d0end:  nop
code ends

end start