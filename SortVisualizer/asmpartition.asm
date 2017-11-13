section .text
global asmpartition

asmpartition:
    sub rsp, 20h

    ; Store input data into local fields
    mov QWORD r10, rcx; arr
    mov DWORD r11d, edx  ;left and i
    mov DWORD r12d, r8d   ;right and j
    mov QWORD r13, r9   ;index

    mov eax, 4h
    mov esi, r11d
    mul esi
    mov esi, eax

    mov eax, 4h
    mov edi, r12d
    mul edi
    mov edi, eax

    ; r14d....pivot
    ; r15d....tmp

    finit

    ; Calculate offset for pivot: rax
        mov eax, DWORD r11d
        add eax, r12d
        mov ebx, 2
        xor rdx, rdx
        div ebx

    ; Set pivot
        mov rbx, r10
        mov rcx, 4
        mul rcx

        add rbx, rax
        mov DWORD r14d, [rbx]

    ; Erste Schleife: while(i <= j)
        firstLoop:
            cmp rsi, rdi
            jg endLoops              

        ; Zweite Schleife: while(arr[r11d] < pivot)
            secondLoop:
                mov [rsp+8h], r14d
                fld DWORD [rsp+8h]
                fld DWORD [r10+rsi]
                fcomip st0, st1
                fstp

                jnb thirdLoop
                ;; [DONE] ;;               

                add rsi, 4       
                inc r11d
                
                jmp secondLoop

        ; Dritte Schleife: while(arrr12d > pivot)
            thirdLoop:
                mov [rsp+8h], r14d
                fld DWORD [rsp+8h]
                fld DWORD [r10+rdi]
                fcomip st0, st1
                fstp
                jna ifStatement

                ; Vermindere j
                sub rdi, 4

                jmp thirdLoop

        ; If-Statement: if(i <= j)
            ifStatement:
                cmp rsi, rdi
                ja endLoops                           
                
                ; Store tmp: [rax] = arr[11d]     
                mov DWORD r15d, [r10+rsi]                   
            
                ; Store arr[j] in r9
                mov DWORD r9d, [r10+rdi]            

                ; Store arr[j] in arr[i]
                mov DWORD [r10+rsi], r9d

                ; Store tmp in arrr12d
                mov DWORD [r10+rdi], r15d         

                ; Increment i
                add rsi, 4h
                inc r11d

                ; Decrement j
                sub rdi, 4h
              
                jmp firstLoop

    endLoops:       
        ; Store index
        mov DWORD eax, r11d

        add rsp, 20h
        ret