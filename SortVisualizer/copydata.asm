global copyData
section .text

copyData:
    push rbp
    mov rbp, rsp

    sub rsp, 20h

    ;mov from input registers into working regs
    mov rax, rcx
    mov rbx, rdx

    ;set the loop counter
    mov rcx, r8

    ;copyLoop:
    ;    mov rdx, QWORD [rbx]
    ;    mov QWORD [rax], rdx

    ;    inc rax
    ;    inc rbx
        
    ;    loop copyLoop

    ;[FASTER]:

    ; clear direction
    cld
    mov rsi, rbx
    mov rdi, rax      
    rep movsd

    add rsp, 20h

    mov rsp, rbp
    pop rbp
    ret