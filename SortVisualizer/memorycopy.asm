
section .text

global memoryCopy

memoryCopy:

    push rbp
    mov rbp, rsp

    sub rsp, 20h

    ; Copy inputs to rax, rbx and rcx
    mov rax, rcx
    mov rbx, rdx
    mov rcx, r8

    lea rdx, [rsp+8]
    mov DWORD [rdx], 1

    fst DWORD [rdx]
    
    copy:
        fst DWORD [rax]

        fadd

        fstp DWORD [rax]

        dec rcx
        cmp rcx, 0
        jne copy




    add rsp, 20h

    pop rbp
    ret