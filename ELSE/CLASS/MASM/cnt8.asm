assume cs:code,ds:data,ss:stack

data segment
           db 8,11,8,1,8,5,63,38
data ends

stack segment

stack ends

code segment
      start:
            mov  ax,data
            mov  ds,ax
            mov  si,0
            mov  cx,8
            mov  bl,8
            mov  ax,0
      s:    
            mov  dl,[si]
            cmp  dl,8
            jnz  no8
            inc  ax
      no8:  
            inc  si
            loop s
            mov  ax,4c00h
            int  21h
code ends

end start