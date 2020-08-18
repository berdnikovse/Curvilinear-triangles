section .text

global count_prec                               ;unsigned count_prec (double)
count_prec:
    push ebp
    mov ebp, esp
    sub esp, 8
    xor eax, eax

    finit
    fld qword[ebp + 8]
    fld1
    fucomip st1
    jbe .end

    fstp qword[esp]
    call asm_log10
    fchs
    fstp qword[esp]
    call asm_ceil
    fistp dword[esp]
    mov eax, dword[esp]

    .end:
    mov esp, ebp
    pop ebp
    ret

global asm_fabs                                 ;double asm_fabs (double)
asm_fabs:
    push ebp
    mov ebp, esp

    finit
    fld qword[ebp + 8]
    fldz
    fucomip st1
    jbe .end
    fchs
    
    .end:
    mov esp, ebp
    pop ebp
    ret

global asm_log10                                ;double asm_log10 (double)
asm_log10:
    push ebp
    mov ebp, esp

    finit
    fldlg2
    fld qword[ebp + 8]
    fyl2x

    mov esp, ebp
    pop ebp
    ret

global asm_ceil                                 ;double asm_ceil (double)
asm_ceil:
    push ebp
    mov ebp, esp

    finit
    fstcw word[cw]
    mov cx, word[cw]
    or word[cw], 0000_1000_0000_0000b
    and word[cw], 1111_1011_1111_1111b
    fldcw word[cw]

    fld qword[ebp + 8]
    frndint

    mov word[cw], cx
    fldcw word[cw]

    mov esp, ebp
    pop ebp
    ret

global binexp                                   ;double binexp (double)
binexp:
    push ebp
    mov ebp, esp
    
    finit
    fld qword[ebp + 8]
    fld1
    fld st1
    fprem
    f2xm1
    faddp
    fscale

    mov esp, ebp
    pop ebp
    ret

global exp                                      ;double exp (double)
exp:
    push ebp
    mov ebp, esp
    sub esp, 8

    finit
    fldl2e
    fld qword[ebp + 8]
    fmulp
    fstp qword[esp]
    call binexp

    mov esp, ebp
    pop ebp
    ret

global f1
f1:
    push ebp
    mov ebp, esp
    sub esp, 8

    finit
    fld qword[ebp + 8]
    fstp qword[esp]
    call binexp
    fld1
    faddp

    mov esp, ebp
    pop ebp
    ret

global f2
f2:
    push ebp
    mov ebp, esp

    finit
    fld qword[ebp + 8]
    fld st0
    fmul st0, st1
    fmul st0, st0
    fmulp

    mov esp, ebp
    pop ebp
    ret

global f3
f3:
    push ebp
    mov ebp, esp
    sub esp, 8

    finit
    fld1
    fld qword[ebp + 8]
    fsubp
    mov dword[esp], 3
    fild dword[esp]
    fdivp

    mov esp, ebp
    pop ebp
    ret

global f4
f4:
    push ebp
    mov ebp, esp

    finit
    fld dword[C0_5]
    fld1
    fld qword[ebp + 8]
    faddp
    fdivp
    fld1
    faddp

    fld dword[C3]
    fmulp

    mov esp, ebp
    pop ebp
    ret

global f5
f5:
    push ebp
    mov ebp, esp

    finit
    fld qword[ebp + 8]
    fld dword[C2_5]
    fmulp
    fld dword[C9_5]
    fsubp

    mov esp, ebp
    pop ebp
    ret

global f6
f6:
    push ebp
    mov ebp, esp

    finit
    fld dword[C5]
    fld qword[ebp + 8]
    fdivp

    mov esp, ebp
    pop ebp
    ret

global f7
f7:
    push ebp
    mov ebp, esp
    sub esp, 8

    finit
    fld qword[ebp + 8]
    fchs
    fstp qword[esp]
    call exp
    fld dword[C3]
    faddp

    mov esp, ebp
    pop ebp
    ret

global f8
f8:
    push ebp
    mov ebp, esp

    finit
    fld dword[C2]
    fchs
    fld qword[ebp + 8]
    fld st1
    fchs
    fmulp
    faddp

    mov esp, ebp
    pop ebp
    ret

global f9
f9:
    push ebp
    mov ebp, esp

    finit
    fld1
    fld qword[ebp + 8]
    fdivp

    mov esp, ebp
    pop ebp
    ret

global f10
f10:
    push ebp
    mov ebp, esp
    sub esp, 8

    finit
    fld qword[ebp + 8]
    fstp qword[esp]
    call exp
    fld dword[C2]
    faddp

    mov esp, ebp
    pop ebp
    ret

global f11
f11:
    push ebp
    mov ebp, esp

    finit
    fld1
    fchs
    fld qword[esp + 8]
    fdivp

    mov esp, ebp
    pop ebp
    ret

global f12
f12:
    push ebp
    mov ebp, esp

    finit
    fld dword[C2]
    fchs
    fld qword[ebp + 8]
    fld1
    faddp
    fmulp
    fld dword[C3]
    fdivp

    mov esp, ebp
    pop ebp
    ret

global g1
g1:
    push ebp
    mov ebp, esp
    sub esp, 8

    finit
    fld qword[ebp + 8]
    fstp qword[esp]
    call binexp
    fldln2
    fmulp
    
    mov esp, ebp
    pop ebp
    ret

global g2
g2:
    push ebp
    mov ebp, esp

    finit
    fld dword[C5]
    fld qword[ebp + 8]
    fmul st0, st0
    fmul st0, st0
    fmulp
    
    mov esp, ebp
    pop ebp
    ret

global g3
g3:
    push ebp
    mov ebp, esp

    finit
    fld1
    fchs
    fld dword[C3]
    fdivp
    
    mov esp, ebp
    pop ebp
    ret

global g4
g4:
    push ebp
    mov ebp, esp

    finit
    fld dword[C3]
    fchs
    fld dword[C2]
    fdivp
    fld qword[ebp + 8]
    fld1
    faddp
    fmul st0, st0
    fdivp
    
    mov esp, ebp
    pop ebp
    ret

global g5
g5:
    push ebp
    mov ebp, esp

    finit
    fld dword[C2_5]
    
    mov esp, ebp
    pop ebp
    ret

global g6
g6:
    push ebp
    mov ebp, esp

    finit
    fld dword[C5]
    fchs
    fld qword[ebp + 8]
    fmul st0, st0
    fdivp
    
    mov esp, ebp
    pop ebp
    ret

global g7
g7:
    push ebp
    mov ebp, esp
    sub esp, 8

    finit
    fld qword[ebp + 8]
    fchs
    fstp qword[esp]
    call exp
    fchs
    
    mov esp, ebp
    pop ebp
    ret

global g8
g8:
    push ebp
    mov ebp, esp

    finit
    fld dword[C2]
    
    mov esp, ebp
    pop ebp
    ret

global g9
g9:
    push ebp
    mov ebp, esp

    finit
    fld1
    fchs
    fld qword[ebp + 8]
    fmul st0, st0
    fdivp
    
    mov esp, ebp
    pop ebp
    ret

global g10
g10:
    jmp exp

global g11
g11:
    push ebp
    mov ebp, esp

    finit
    fld1
    fld qword[ebp + 8]
    fmul st0, st0
    fdivp
    
    mov esp, ebp
    pop ebp
    ret

global g12
g12:
    push ebp
    mov ebp, esp

    finit
    fld dword[C2]
    fchs
    fld dword[C3]
    fdivp
    
    mov esp, ebp
    pop ebp
    ret

global test1
test1:
    push ebp
    mov ebp, esp

    finit
    fld qword[ebp + 8]
    fmul st0, st0
    
    mov esp, ebp
    pop ebp
    ret

global test2
test2:
    push ebp
    mov ebp, esp

    finit
    fld dword[C3]
    fld dword[C2]
    fld qword[ebp + 8]
    fmulp
    faddp
    
    mov esp, ebp
    pop ebp
    ret

global test3
test3:
    push ebp
    mov ebp, esp

    finit
    fld qword[ebp + 8]
    
    mov esp, ebp
    pop ebp
    ret

global test4
test4:
    push ebp
    mov ebp, esp

    finit
    fld qword[ebp + 8]
    fcos
    
    mov esp, ebp
    pop ebp
    ret

global test5
test5:
    jmp exp

global test6
test6:
    push ebp
    mov ebp, esp

    finit
    fld1
    fld qword[ebp + 8]
    fdivp

    mov esp, ebp
    pop ebp
    ret

global test7
test7:
    push ebp
    mov ebp, esp

    finit
    fld1
    fld qword[ebp + 8]
    fmul st0, st0
    fsubp
    fsqrt
    
    mov esp, ebp
    pop ebp
    ret

global der_test1
der_test1:
    push ebp
    mov ebp, esp

    finit
    fld dword[C2]
    fld qword[ebp + 8]
    fmulp
    
    mov esp, ebp
    pop ebp
    ret

global der_test2
der_test2:
    push ebp
    mov ebp, esp

    finit
    fld dword[C2]
    
    mov esp, ebp
    pop ebp
    ret

global der_test3
der_test3:
    push ebp
    mov ebp, esp

    finit
    fld1
    
    mov esp, ebp
    pop ebp
    ret

global der_test4
der_test4:
    push ebp
    mov ebp, esp

    finit
    fld qword[ebp + 8]
    fsin
    fchs
    
    mov esp, ebp
    pop ebp
    ret

global der_test5
der_test5:
    jmp exp

global der_test6
der_test6:
    push ebp
    mov ebp, esp

    finit
    fld1
    fchs
    fld qword[ebp + 8]
    fmul st0, st0
    fdivp
    
    mov esp, ebp
    pop ebp
    ret

section .data
    C0_5 dd 0.5
    C3 dd 3.0
    C2_5 dd 2.5
    C9_5 dd 9.5
    C5 dd 5.0
    C2 dd 2.0

section .bss
    cw resw 1
