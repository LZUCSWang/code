assume cs:code,ds:data

data segment
         db 'BaSic'
         db 'iNfOrMaTiOn'
data ends
code segment
    start:mov  ax,data
          mov  ds,ax
          mov  bx,0
          mov  cx,5

    s:    
          mov  al,[bx]
          and  al,11011111b
          mov  [bx],al
          inc  bx
          loop s

          mov  bx,5
          mov  cx,11
    s1:   
          mov  al,[bx]
          or   al,00100000b
          mov  [bx],al
          inc  bx
          loop s1
    
          mov  ax,4c00h
          int  21h
code ends
end start