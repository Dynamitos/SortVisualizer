global floatTest
section .text


floatTest:
    push rbp
    mov rbp, rsp

    sub rsp, 20h

    ;Store input arguments
    mov rbx, rcx
    mov rax, rdx
    mov rcx, r8

    call copyData

    add rsp, 20h

    mov rsp, rbp
    pop rbp
    ret



copyData:
    cld
    mov rsi, rax
    mov rdi, rbx
    rep movsd
    ret