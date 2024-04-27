assume cs:code
code segment
          dw   1000h,2000h,3000h,4000h,5000h,6000h,7000h,8000h
          dw   16 dup(0)
    start:mov  ax ,cs
          mov  ss,ax
          mov  sp , 30h
          mov  bx,0
          mov  cx,8

    s:    push cs:[bx]
          inc  bx
          inc  bx
          loop s
          mov  bx ,0
          mov  cx ,8
    s1:   pop  cs:[bx]
          inc  bx
          inc  bx
          loop s1
           
          mov  ax,4c00h
          int  21h
        
code ends

end start