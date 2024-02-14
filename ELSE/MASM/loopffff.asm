
CODE SEGMENT
          assume cs:code
    start:
          mov    ax,0ffffh    ;//AX=0FFFFH
          mov    ds,ax        ;//DS=AX
          mov    bx,8         ;//BX=6
          mov    al,[bx]      ;//AL=DS[6]
          mov    ah,0         ;//AH=0

          mov    cx,3
    s:    add    dx,ax
          loop   s
          mov    ax,4c00h
          int    21h
CODE ENDS
END start