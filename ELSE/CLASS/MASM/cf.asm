assume cs:code,ds:data,ss:stack

data segment

data ends

stack segment

stack ends

code segment
    start:
          sub al,al 
          mov al,10h 
          add al,90h 
          mov al,80h
          add al,al 
          mov al,0fch
          add al,05h
          mov al,7dh
          add al,0bh
        ;   pushf
          mov   ax,4c00h
          int   21h
code ends

end start