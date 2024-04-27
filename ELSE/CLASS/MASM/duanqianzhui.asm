
CODE SEGMENT
          assume cs:code
    start:
          mov    ax,0ffffh     ;//AX=0FFFFH
          mov    ds,ax         ;//DS=AX
          mov    ax,0020h
          mov    es,ax         ;//ES=AX
          mov    bx,0
          mov    cx,12
    s:    
          mov    al,es:[bx]    ;//al不是ax
          mov    es:[bx],al    ;
          inc    bx
          loop   s
          mov    ax,4c00h
          int    21h6
CODE ENDS
END start