assume cs:code,ds:data,ss:stack

data segment

data ends

stack segment

stack ends

code segment
    start:
          mov  ax,1
          mov  cx,3
          call s
          mov  bx,ax
          mov  ax,4c00h
          int  21h

    s:    
          add  ax,ax
          loop s
          ret
          mov  ax,4c00h
          int  21h
code ends

end start