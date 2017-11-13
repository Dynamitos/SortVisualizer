section .text
global asmpartition

asmpartition:
    push rbp
    mov rbp, rsp
    sub rsp, 40h

    ; Store input data into local fields
    mov QWORD [rsp], rcx; arr
    mov DWORD [rsp+30h], edx  ;left
    mov DWORD [rsp+8h], r8d   ;right
    mov QWORD [rsp+16h], r9   ;index

    finit

    ; Calculate offset for pivot: rax
        mov eax, DWORD [rsp+30h]
        mov ebx, DWORD [rsp+8h]
        add eax, ebx
        mov ebx, 2
        xor rdx, rdx
        div ebx 

    ; Set pivot
        mov rbx, [rsp]
        mov rcx, 4
        mul rcx

        add rbx, rax
        mov ecx, DWORD [rbx]
        mov DWORD [rsp+12h], ecx

        ;; [DONE] ;;

    ; Erste Schleife: while(i <= j)
        firstLoop:
            mov DWORD eax, [rsp+30h]
            mov DWORD ebx, [rsp+8h]
            cmp eax, ebx
            jg endLoops              

        ; Zweite Schleife: while(arr[rsp+30h] < pivot)
            secondLoop:
                mov rcx, [rsp]
                mov DWORD eax, [rsp+30h]
                mov ebx, 4
                mul ebx
                add rcx, rax
                
                fld DWORD [rsp+12h]
                fld DWORD [rcx]
                fcomip st0, st1
                fstp

                jnb thirdLoop
                ;; [DONE] ;;               

                mov DWORD eax, [rsp+30h]
                inc eax
                mov DWORD [rsp+30h], eax               
                
                jmp secondLoop

        ; Dritte Schleife: while(arr[rsp+8h] > pivot)
            thirdLoop:
                mov rcx, [rsp]
                mov DWORD eax, [rsp+8h]
                mov ebx, 4
                mul ebx
                add rcx, rax              

                fld DWORD [rsp+12h]
                fld DWORD [rcx]
                fcomip st0, st1
                fstp
                jna ifStatement

                ; Vermindere j
                mov DWORD eax, [rsp+8h]
                dec eax
                mov DWORD [rsp+8h], eax              

                jmp thirdLoop

        ; If-Statement: if(i <= j)
            ifStatement:
                fld DWORD [rsp+8h]
                fld DWORD [rsp+30h]
                fcomip st0, st1
                fstp
                ja endLoops                           
                
                ; Store tmp: [rax] = arr[rsp+30h]
                mov rcx, [rsp]
                mov DWORD eax, [rsp+30h]
                mov ebx, 4               
                mul ebx
                add rcx, rax               
                mov DWORD ebx, [rcx]
                mov DWORD [rsp+1eh], ebx                   
            
                ; Store arr[j] in r9
                mov rcx, [rsp]
                mov DWORD eax, [rsp+8h]
                mov ebx, 4
                mul ebx
                add rcx, rax
                xor r9, r9
                mov DWORD r9d, [rcx]              

                ; Store arr[j] in arr[i]
                mov rcx, [rsp]
                mov DWORD eax, [rsp+30h]
                mov ebx, 4
                mul ebx
                add rcx, rax
                mov DWORD [rcx], r9d              

                ; Store tmp in arr[rsp+8h]
                mov rcx, [rsp]
                mov DWORD eax, [rsp+8h]
                mov ebx, 4
                mul ebx
                add rcx, rax
                mov DWORD r9d, [rsp+1eh]
                mov DWORD [rcx], r9d           

                ; Increment i
                mov DWORD eax, [rsp+30h]
                inc eax
                mov [rsp+30h], eax

                ; Decrement j
                mov DWORD eax, [rsp+8h]
                dec eax
                mov DWORD [rsp+8h], eax
              
                jmp firstLoop

    endLoops:       
        ; Store index
        mov DWORD eax, [rsp+30h]
        mov QWORD rbx, [rsp+16h]
        mov DWORD [rbx], eax

        add rsp, 40h
        mov rsp, rbp
        pop rbp
        ret