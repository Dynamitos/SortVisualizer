section .text
global asmmerge



asmmerge:

	push rbp
	
	mov r10, rcx				; sortedData pointer
	mov rbx, rdx				; readData pointer
	mov esi, r8d				; leftStart (int)
	mov edi, r9d				; rightStart (int)
	mov DWORD r14d, [rsp+30h]	; leftEnd (int)
	mov DWORD r15d, [rsp+38h]	; rightEnd(int)
	
	; r8d = diff
	; r12 = begin^th element of sortedData
	; r13 = begin^th element of readData
	; rdx = maximum sortedData
	
	;FREE
		xor r11, r11
		xor r9, r9
	
	; Initialize r8d and adjust to 4 Bytes
	mov r8d, r15d
	sub r8d, esi
	inc r8d
	mov eax, 4h
	mul r8d
	mov r8d, eax
	
	; Adjust leftStart, rightStart, leftEnd and rightEnd address offsets
	mov eax, 4h
	mul esi
	mov esi, eax
	
	mov eax, 4h
	mul edi
	mov edi, eax
	
	mov eax, 4h
	mul r14d
	mov r14d, eax
	
	mov eax, 4h
	mul r15d
	mov r15d, eax
	
	; Set r12 to r10 and initialize begin^th of sortedData and readData
	mov r12, r10
	add r12, rsi
	mov r13, rbx
	add r13, rsi
	
	; Calculate maximum sortedData address
	mov rdx, r10
	add rdx, r15
	
	; Adjust sortedData pointer
	add r10, rsi
	
	cmp r10, rdx
	ja endAll
	mainLoop:
		startFirstIf:
			cmp esi, r14d
			jna startSecondIf
				cmp edi, r15d
				ja endLoop
				mov DWORD r11d, [rbx+rdi]
				mov DWORD [r10], r11d
				add edi, 4h
				jmp endLoop
		
		startSecondIf:
			cmp edi, r15d
			jna startThirdIf
				cmp esi, r14d
				ja endLoop
				mov DWORD r11d, [rbx+rsi]
				mov DWORD [r10], r11d
				add esi, 4h
				jmp endLoop
			
		startThirdIf:
			fld DWORD [rbx+rsi]
			fld DWORD [rbx+rdi]
			fcomip st0, st1
			fstp
			jnb startFourthIf
				mov DWORD r11d, [rbx+rdi]
				mov DWORD [r10], r11d
				add edi, 4h
				jmp endLoop
		
		startFourthIf:
			mov DWORD r11d, [rbx+rsi]
			mov DWORD [r10], r11d
			add esi, 4h
			
		endLoop:
			add r10, 4h
			cmp r10, rdx
			jna mainLoop
				
	endAll:
		mov ecx, r8d
		mov rdi, r13
		mov rsi, r12
		rep movsb
		
		pop rbp
		ret