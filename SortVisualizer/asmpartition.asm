section .text
global asmpartition

asmpartition:
    sub rsp, 20h

    ; Store input data into local fields
    mov QWORD r10, rcx; arr
    mov DWORD r11d, edx  ;left
    mov DWORD r12d, r8d   ;right
    mov QWORD r13, r9   ;index

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
            cmp r11d, r12d
            jg endLoops              

        ; Zweite Schleife: while(arrr11d < pivot)
            secondLoop:
                mov rcx, r10
                mov ebx, 4
                mov DWORD eax, r11d
                mul ebx
                add rcx, rax
                
                mov [rsp+8h], r14d
                fld DWORD [rsp+8h]
                fld DWORD [rcx]
                fcomip st0, st1
                fstp

                jnb thirdLoop
                ;; [DONE] ;;               

                inc r11d            
                
                jmp secondLoop

        ; Dritte Schleife: while(arrr12d > pivot)
            thirdLoop:
                mov rcx, r10
                mov DWORD eax, r12d
                mov ebx, 4
                mul ebx
                add rcx, rax              

                mov [rsp+8h], r14d
                fld DWORD [rsp+8h]
                fld DWORD [rcx]
                fcomip st0, st1
                fstp
                jna ifStatement

                ; Vermindere j
                dec r12d         

                jmp thirdLoop

        ; If-Statement: if(i <= j)
            ifStatement:
                mov DWORD [rsp+8h], r12d
                mov DWORD [rsp+16h], r11d

                fld DWORD [rsp+8h]
                fld DWORD [rsp+16h]
                fcomip st0, st1
                fstp
                ja endLoops                           
                
                ; Store tmp: [rax] = arr[11d]
                mov DWORD eax, r11d
                mov ebx, 4               
                mul ebx
                add rax, r10               
                mov DWORD r15d, [rax]                   
            
                ; Store arr[j] in r9
                mov DWORD eax, r12d
                mov ebx, 4
                mul ebx
                add rax, r10
                mov DWORD r9d, [rax]              

                ; Store arr[j] in arr[i]
                mov rcx, r10
                mov DWORD eax, r11d
                mov ebx, 4
                mul ebx
                add rcx, rax
                mov DWORD [rcx], r9d              

                ; Store tmp in arrr12d
                mov rcx, r10
                mov DWORD eax, r12d
                mov ebx, 4
                mul ebx
                add rcx, rax
                mov DWORD [rcx], r15d

                ; Increment i
                inc r11d

                ; Decrement j
                dec r12d
              
                jmp firstLoop

    endLoops:       
        ; Store index
        mov DWORD eax, r11d

        add rsp, 20h
        ret