section .text
global asmbubblesort


asmbubblesort:
    sub rsp, 20h


    mov QWORD rsi, rcx     ; data pointer ; start address
    mov DWORD r10d, edx   ; length

    ;ecx.....i
    ;r13......data pointer ; gets bigger
    ;r11d....flag
    ;r12....end address of r13

    ; Initialize floating point operations
    finit

    ; Adjust length of loop
    xor rcx, rcx
    mov DWORD ecx, r10d

    ; Check if length is smaller than two
    mov eax, ecx
    dec eax
    test eax, eax
    jz endLoops

    ; Calculate end address with 4 bytes too much
    mov eax, r10d
    mov ebx, 4h
    mul ebx
    add rax, rsi
    mov r12, rax


    firstLoop:
        ; Clear flag
        xor r11d, r11d

        mov r13, rsi

        sub r12, 4h

        ; Check if end of second loop is already achieved
        cmp r13, r12
        jnb endLoops

        secondLoop:
            ; Check if next is smaller
            fld DWORD [r13]
            fld DWORD [r13+4h]
            fcomip st0, st1
            fstp
            jnb endSecondLoop

            ; Swap values
            mov DWORD eax, [r13]
            mov DWORD ebx, [r13+4h]
            mov DWORD [r13], ebx
            mov DWORD [r13+4h], eax

            ; Set flag
            or r11d, 1h

            endSecondLoop:
                ; Increment r13
                add r13, 4h

                cmp r13, r12
                jb secondLoop
        
    endFirstLoop:
        test r11d, r11d
        jz endLoops

        loop firstLoop

    endLoops:
        add rsp, 20h
        ret
        
    

    