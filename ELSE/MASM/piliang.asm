assume cs:code,ds:data,ss:stack

data segment
         db 'conversation'
data ends

stack segment

stack ends

code segment
    start:  
            mov  ax,data
            mov  ds,ax
            
            mov  cx,12
    s:      
            call captial
            inc  si
            loop s
            mov  ax,4c00h
            int  21h
    captial:
            mov  al,[si]
            and  al,11011111b
            mov  [si],al
            ret
code ends

end start