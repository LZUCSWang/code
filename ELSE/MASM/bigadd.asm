assume cs:code,ds:data,ss:stack

data segment
           dw 8 dup(1234h)
           dw 8 dup(0ffffh)
data ends

stack segment

stack ends

code segment
      start:
            mov  ax,data
            mov  ds,ax
            mov  di,16
            mov  si,0
            mov  cx,8
            sub  ax,ax
      s:    
            mov  ax,[si]
            adc  ax,[di]
            mov  [si],ax
      ; add  si ,2         ;大忌，不能用add，会将cf清零
      ; add  di ,2
            inc  si
            inc  si
            inc  di
            inc  di
            loop s
            mov  ax,4c00h
            int  21h
code ends

end start