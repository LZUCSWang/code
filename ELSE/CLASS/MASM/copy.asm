CODE SEGMENT
         ASSUME CS:CODE
         mov    ax,0ffffh
         mov    ds,ax
         mov    ax,0020h
         mov    es,ax

         mov    cx,6
         mov    bx,0

    s:   mov    ax,ds:[bx]
         mov    es:[bx],ax
         inc    bx
         inc    bx
         loop   s

         mov    ax , 4c00h
         int    21h
CODE ENDS
END