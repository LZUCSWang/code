CODE segment
         assume cs:CODE
         mov    ax ,0ffffh
         mov    DS,AX
         mov    bx,0
         mov    cx,0ch
         mov    ah,0
         mov    al,0
         mov    dx,0
    s:   mov    al,[bx]
         add    dx,AX
         inc    bx
         loop   s

         mov    ax,4c00h
         int    21h
CODE ENDS
end