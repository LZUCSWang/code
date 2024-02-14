
CODE SEGMENT
          assume cs:code
    start:
          mov    ax,0ffffh    ;//AX=0FFFFH
          mov    ds,ax        ;//DS=AX
          mov    cx,12
          mov    bx,0
          mov    dx,0
    s:    
          mov    al,[bx]
          mov    ah,0
          inc    bx
          add    dx,ax
          loop   s
          mov    ax,4c00h
          int    21h
CODE ENDS
END start