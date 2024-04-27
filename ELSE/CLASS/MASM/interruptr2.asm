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

                  mov  cx,offset capitalEND - offset capital

                  rep  movsb

                  mov  ax,0
                  mov  es,ax
                  mov  word ptr es:[74h*4],200h
                  mov  word ptr es:[74h*4+2],0
                  mov  ax,4c00h
                  int  21h
    capital:      
                  push si
                  push ax
    capitalChange:
                  mov  al,ds:[si]
                  mov  ah,0
                  cmp  ax,0
                  je   capitalOK
                  and  al,11011111b
                  mov  ds:[si],al
                  inc  si
                  jmp  short capitalChange
    capitalOK:    
                  pop  ax
                  pop  si
                  iret
    capitalEND:   
                  nop

code ends

end start