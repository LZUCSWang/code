assume cs:code,ss:stack
stack segment
          dw 8 dup(2333h)
stack ends
code segment
    ;   dw   1234h,5678h,9abch
    start:
          mov  ax,stack
          mov  ss,ax
          mov  sp,6
          mov  bx,0ffffh
          push bx
          mov  ax,4c00h
          int  21h
code ends

end start