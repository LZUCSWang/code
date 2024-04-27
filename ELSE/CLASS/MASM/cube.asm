 
;立方子程序
;输入：eax为要求立方的数
;输出：eax为该数的立方
cube:
    push ebx
    push ecx
    mov ebx, eax ;将要求立方的数存入ebx
    mul ebx ;eax = eax * ebx
    mul ebx ;eax = eax * ebx
    pop ecx
    pop ebx
    ret

