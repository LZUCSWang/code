assume cs:CODE

CODE SEGMENT 
    mov ax,0123H
    mov bx,0456H
    add ax,bx
    add ax,AX

    mov ax,4c00H
    int 21H
CODE ENDS

end